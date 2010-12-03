
#define CHAR_LENGTH 256

#include <iostream>
using std::cout ; 
using std::endl ; 
using std::ostream ; 
using std::ostringstream ; 

#include <fstream>
using std::ofstream ; 

#include <string>
using std::string ; 


#include <vector>
using std::vector ; 

#include <memory>
using namespace std ;

#include <float.h>
#include <time.h>

// plot stuff
#include <gnuplot_i.hpp>

// net stuff
#include "BlitzLiveNet.hpp"
#include "ScaledFileFeeder.hpp"   
#include "BlitzEulerSigNetEvaluator.hpp"   
#include "BlitzMidPointNetEvaluator.hpp"   
#include "TextEvalTrace.hpp" 
#include "TinyBzNetParser.hpp" 
#include "BlitzXmlNetRenderer.hpp" 


// gui stuff
#include <QtFlatRenderer.h>
#include <qmessagebox.h>
#include <TiAppParser.hpp>
#include <TiListParser.hpp>
#include <AppInterfaceXmlEngine.hpp>
#include <TinyAppInterfaceXmlEngine.hpp>
#include <Command.hpp>
#include <AppInterface.hpp>
#include <Option.hpp>



#include "PlotDriver.hpp"




PlotDriver::PlotDriver(string newInterfaceName,string newTypeName,AppInterface* newParent)  :
TiFlatBaseApp(newInterfaceName,newTypeName,newParent) 
    ,mPlotVector(NULL)
    ,mPlotMultiple(false)
    ,mPlotVersusInput(false)
{

   mInputList = new vector<string>() ; 
   mNetworkList = new vector<string>() ; 
   description = "Kinetic annealer.  Produces 1 to N." ; 
   RNG::initSeed();
}

ofstream* PlotDriver::createOutputFileStream(const char* outputFile) 
{
    ofstream *returnstream = new ofstream( outputFile , ios::out) ; 
    return returnstream ; 
}


/// Creates a network evaluator for BlitzLiveNet*
BlitzNetEvaluator* PlotDriver::createEvaluator(BlitzLiveNet* prototypeNet) {

    BlitzNetEvaluator* tempEvaluator = NULL ; 
    mTracer = new TextEvalTrace() ; 
    
    
    if(mDoMidPoint==true){
        tempEvaluator = new BlitzMidPointNetEvaluator() ; 
        ((BlitzMidPointNetEvaluator*) tempEvaluator)->setOutputSigmoid(mOutputSigmoid) ; 
    }
		else
    if(mDoSimpleOutput==true){
        tempEvaluator = new BlitzEulerNetEvaluator() ; 
		}
    else{
        tempEvaluator = new BlitzEulerSigNetEvaluator(mDeltaT,mOutputSigmoid,prototypeNet) ; 
    }

    vector<double>* relaxVector = new vector<double>(mNumInputs) ; 
    ScaledFileFeeder *tempFileFeeder = new ScaledFileFeeder(mInputFile,mScale) ; 
    mBaseline = tempFileFeeder->getNextPoint() ;  // makes baseline the first point
    delete tempFileFeeder ; 
    fill(relaxVector->begin() , relaxVector->end() , mBaseline) ; 
    tempEvaluator->setRelaxValue(relaxVector) ; 
    tempEvaluator->setRelaxTime(mRelaxTime) ; 
    tempEvaluator->setRelaxDeltaT(1.0) ; 
    tempEvaluator->setRelaxTau(3.0) ; 

    mTracer->setTimeDelimiter(",") ; 
    mTracer->setEvaluator(tempEvaluator) ; 


    // set to the evaluator
    if(mNumInputs>1){
        tempEvaluator->setStimulus(new ScaledFileFeeder(mInputFile,mScale,mDeltaT),0) ; 
        tempEvaluator->setStimulus(new ScaledFileFeeder(mInputFile,mScale,mDeltaT),1) ; 
    }
    else{
        tempEvaluator->setStimulus(new ScaledFileFeeder(mInputFile,mScale,mDeltaT),0) ; 
    }

    tempEvaluator->setTarget(new ScaledFileFeeder(mInputFile,mScale,mDeltaT)) ; 
    prototypeNet->setEvaluator( tempEvaluator ) ; 

    return tempEvaluator ;
}





BlitzLiveNet* PlotDriver::createNetwork() 
{
    BlitzLiveNet* newNet = (BlitzLiveNet*) (new TinyBzNetParser())->parseFile(mNetworkFile) ;
    return newNet ; 
}



   


void PlotDriver::setRenderer(Renderer* newRenderer) 
{
    mRenderer = newRenderer ; 
}



void* PlotDriver::dumpTraceFromNet(BlitzLiveNet* plotNet,string dumpFile) 
{
    plotNet->eval() ; 
    vector<vector<double>*>* sliceTrace = (plotNet->getEvaluator())->getLastFullTraceAsSeries() ; 
    int start,end  ; 
    string networkName ; 
    for(int i = 0 ; i < sliceTrace->size() ; i++){
        ostringstream* nameString = new ostringstream() ; 
        // parse the output so its of the form:
        // dumpFile.networkFile.inputFile.<neuronNum>.txt
        start = mNetworkFile.find_last_of("/") ; 
        end = mNetworkFile.find_last_of(".") ; 
        networkName = mNetworkFile.substr(start+1,end-start-1) ; 
        *nameString  <<  dumpFile <<  "_" << networkName << "." << mInputFile.substr(mInputFile.find_last_of("/")+1,mInputFile.find_last_of(".")-mInputFile.find_last_of("/")-1)  << "." << i << ".txt" ; 
//        cout << "output to: " << nameString->str() << endl ; 
        ofstream* outputTextStream = new ofstream( (nameString->str()).c_str(),ios::out) ; 
        for(int j = 0 ; j <  ((*sliceTrace)[i])->size() ; j++){
            (*outputTextStream) << (*((*sliceTrace)[i]))[j] << endl ; 
        }
        outputTextStream->close() ; 
    }
}



bool PlotDriver::createLocalMaps() 
{
    string APP_NAME = "APP/PRUNER" ; 
    addCommandToMap(START_PLOTTER) ; 
//    addOptionToMap("01a_network",OPT_FILE_LOAD,&mNetworkFile,APP_NAME,"Network File") ; 
    addOptionToMap("01a_network",LIST_FILE_LOAD,&mNetworkList,APP_NAME,"Network List") ; 
    addOptionToMap("01aa_fileinput",LIST_FILE_LOAD,&mInputList,APP_NAME,"Input Files") ; 
    addOptionToMap("01ab_scale",OPT_INT,&mScale,APP_NAME,"Input Scale") ; 
    addOptionToMap("01b_sigmoid",OPT_DOUBLE,&mOutputSigmoid,APP_NAME,"Output Sigmoid (1.0)") ; 
    addOptionToMap("02_relaxtime",OPT_DOUBLE,&mRelaxTime,APP_NAME,"Relax Time (0.0)") ; 
    addOptionToMap("03_deltat",OPT_DOUBLE,&mDeltaT,APP_NAME,"Delta Time") ; 
    addOptionToMap("07b_numinputs",OPT_INT,&mNumInputs,APP_NAME,"Num Inputs") ; 
    mOutputList = new vector<string>() ; 
    mOutputList->push_back("x11") ; 
    mOutputList->push_back("pdf") ; 
    mOutputList->push_back("png") ; 
    addOptionToMap("07c_outputtype",LIST_TYPE,&mOutputType,APP_NAME,"Output Type",(new TiListParser())->createList(mOutputList) ) ; 
    addOptionToMap("07d_doplot",OPT_BOOL,&mDoPlot,APP_NAME,"Do Plot") ; 
    addOptionToMap("08_plotmultiple",OPT_BOOL,&mPlotMultiple,APP_NAME,"Plot Multiple") ; 
    addOptionToMap("08a_plotvsinput",OPT_BOOL,&mPlotVersusInput,APP_NAME,"Plot vs Input") ; 
    mTempType = new vector<string>() ; 
    mTempType->push_back("lines") ; 
    mTempType->push_back("dots") ; 
    mTempType->push_back("points") ; 
    mTempType->push_back("linespoints") ; 
    addOptionToMap("09_linetype",LIST_TYPE,&mLineType,APP_NAME,"Line Type",(new TiListParser())->createList(mTempType)) ; 
    addOptionToMap("10_outputname",OPT_FILE_SAVE,&mNeuronOutput,APP_NAME,"Neuron Output") ; 
    addOptionToMap("11_domidpoint",OPT_BOOL,&mDoMidPoint,APP_NAME,"Midpoint Eval") ; 
    addOptionToMap("12_dosimple",OPT_BOOL,&mDoSimpleOutput,APP_NAME,"Simple Eval") ; 
    return true ; 
}


/*  ***********************************************************************************
    doLocalCommand() */
   
//! Description here.
/*  *********************************************************************************** */
string PlotDriver::doLocalCommand(Command *theCommand) 
{
    mRenderer->savePreferences() ; 
    string theName = theCommand->getName()  ;

    if(theName==START_PLOTTER){
        BlitzLiveNet* net = NULL ; 
        for(int j = 0 ; j < mNetworkList->size() ; j++){
            for(int i = 0 ; i < mInputList->size() ; i++){
                mInputFile = (*mInputList)[i] ; 
                mNetworkFile = (*mNetworkList)[j] ; 
                cout << "processing network[" << mNetworkFile << "] "; 
                cout << "input[" << mInputFile << "]" <<  endl ; 
                net =  loadNet() ; 
                initPlotter(net->getNumNeurons()) ; 
                if(mDoPlot==true){
                    plotPulseFromNet(  net ) ; 
                }
                dumpTraceFromNet( net , mNeuronOutput ) ; 
            }
        }
        cout << "*DONE*" << endl ; 
    } 
    
    return "it runned  "; 
}




void PlotDriver::initPlotter(int size) 
{

    if(mPlotVector==NULL){
        mPlotVector = new vector<Gnuplot*>(size) ; 
        for(int i = 0 ; i < mPlotVector->size() ; i++){
            (*mPlotVector)[i] = new Gnuplot(mLineType) ; 
        }
    }
    else{
        for( vector<Gnuplot*>::iterator plotIter = mPlotVector->begin(); plotIter!= mPlotVector->end(); ++plotIter  ) {
            (*plotIter)->set_style(mLineType) ; 
            (*plotIter)->reset_plot() ; 
        } ; 
    }


    ostringstream *commandStream  = new ostringstream() ; 


    int count = 0  ;  
    for( vector<Gnuplot*>::iterator plotIter = mPlotVector->begin(); plotIter!= mPlotVector->end(); ++plotIter ,++count  ) {
        mTitleString = mNetworkFile.substr( mNetworkFile.find_last_of("/")+1) ; 
        (*plotIter)->cmd("set ytics(0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9)") ; 
        (*plotIter)->cmd("set grid") ; 
        commandStream->str("") ; 
        *commandStream << "set title '" << mTitleString << "'" << endl ; 
        (*plotIter)->cmd(  (commandStream->str()).c_str() ) ; 
        if(mPlotVersusInput==true){
            (*plotIter)->cmd("set xlabel 'Neural Input'") ; 
        }
        else{
            (*plotIter)->cmd("set xlabel 'Time(s)'") ; 
        }
        (*plotIter)->cmd("set ylabel 'Neural Activity'") ; 
    } ; 

}

void PlotDriver::setOutput(Gnuplot* aPlot,int count) 
{
    ostringstream* thisStream = new ostringstream() ; 

    thisStream->str("") ; 
    *thisStream << "set terminal " << mOutputType << " ; " << endl ; 
    if(mPlotMultiple==true){
        *thisStream << "set output \"" << mTitleString << "." << count << "." << mOutputType << "\" ; " << endl ; 
    }
    else{
        *thisStream << "set output \"" << mTitleString << "." << mOutputType << "\" ; " << endl ; 
    }

    aPlot->cmd(  (thisStream->str()).c_str() ) ; 
}



void* PlotDriver::plotPulseFromNet(BlitzLiveNet* plotNet) 
{
    plotNet->eval() ; 
    vector<vector<double>*>* sliceTrace = (plotNet->getEvaluator())->getLastFullTraceAsSeries() ;

    // We add this for the x-axis, though its used in too different ways.
    ScaledFileFeeder *plotFeeder= new ScaledFileFeeder(mInputFile,mScale) ; 
    vector<double> *inputVector = NULL ; 
    int numPoints = plotFeeder->getNumPoints()  ; 
    if(mPlotMultiple==true){
        for(int i = 0 ; i < sliceTrace->size() ; i++){
            setOutput( (*mPlotVector)[i],i) ; 
            (*mPlotVector)[i]->set_style(mLineType) ; 
            ostringstream* nameString = new ostringstream() ; 
            *nameString  << "neuron " << i ; 


            // Here we plot versus the input.  
            if(mPlotVersusInput==true){
                if(inputVector==NULL){
                    inputVector = new vector<double>() ; 
                    while(plotFeeder->hasMorePoints()==true){
                        inputVector->push_back(plotFeeder->getNextPoint()) ; 
                    }
                }

                
                (*mPlotVector)[i]->plot_xy( *inputVector, *((*sliceTrace)[i]) ,nameString->str() ) ; 
            }
            // Here we plot versus time. 
            else{
                if(inputVector==NULL){
                    inputVector = new vector<double>() ; 
                    for(int timePoint = 0 ; timePoint < numPoints ; timePoint++){
                        inputVector->push_back(timePoint*mDeltaT) ; 
                    }
                }
                (*mPlotVector)[i]->plot_xy(*inputVector, *((*sliceTrace)[i]) ,nameString->str() ) ; 
            }
            nameString->clear() ; 
        }
    }
    else{
        for(int i = 0 ; i < sliceTrace->size() ; i++){
            setOutput( (*mPlotVector)[0]) ; 
            (*mPlotVector)[0]->set_style(mLineType) ; 
            ostringstream* nameString = new ostringstream() ; 
            *nameString  << "neuron " << i ; 
            if(mPlotVersusInput==true){
                if(inputVector==NULL){
                    inputVector = new vector<double>() ; 
                    while(plotFeeder->hasMorePoints()==true){
                        inputVector->push_back(plotFeeder->getNextPoint()) ; 
                    }
                }

                (*mPlotVector)[0]->plot_xy( *inputVector, *((*sliceTrace)[i]) ,nameString->str() ) ; 
            }
            else{
                if(inputVector==NULL){
                    inputVector = new vector<double>() ; 
                    for(int timePoint = 0 ; timePoint < numPoints ; timePoint++){
                        inputVector->push_back(timePoint*mDeltaT) ; 
                    }
                }
                (*mPlotVector)[0]->plot_xy(*inputVector, *((*sliceTrace)[i]) ,nameString->str() ) ; 
            }
            nameString->clear() ; 
        }
    }
}


BlitzLiveNet* PlotDriver::loadNet() 
{
    BlitzLiveNet* thisNet = createNetwork() ; 
    NetEvaluator* eval = createEvaluator(thisNet) ; 
    thisNet->setEvaluator( eval ) ; 
    return thisNet ; 
}


const string PlotDriver::START_PLOTTER = "START_PLOTTER"  ; 



/* Modeline for ViM {{{
 * vim:set ts=4:
 * vim600:fdm=marker fdl=0 fdc=3:
 * }}} */






