
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

// Blitz stuff
//#include <blitz/array/convolve.h>

#include "WienerDriver.hpp"




WienerDriver::WienerDriver(string newInterfaceName,string newTypeName,AppInterface* newParent)  :
TiFlatBaseApp(newInterfaceName,newTypeName,newParent) 
    ,mPlotVector(NULL)
    ,mPlotMultiple(false)
    ,mPlotVersusInput(false)
{
   description = "Kinetic annealer.  Produces 1 to N." ; 
   RNG::initSeed();
}

ofstream* WienerDriver::createOutputFileStream(const char* outputFile) 
{
    ofstream *returnstream = new ofstream( outputFile , ios::out) ; 
    return returnstream ; 
}


/// Creates a network evaluator for BlitzLiveNet*
BlitzNetEvaluator* WienerDriver::createEvaluator(BlitzLiveNet* prototypeNet) {

    BlitzNetEvaluator* tempEvaluator = NULL ; 
    mTracer = new TextEvalTrace() ; 
    
    
    if(mDoMidPoint==true){
        tempEvaluator = new BlitzMidPointNetEvaluator() ; 
        ((BlitzMidPointNetEvaluator*) tempEvaluator)->setOutputSigmoid(mOutputSigmoid) ; 
    }
    else{
        tempEvaluator = new BlitzEulerSigNetEvaluator(mDeltaT,mOutputSigmoid,prototypeNet) ; 
    }

    vector<double>* relaxVector = new vector<double>(mNumInputs) ; 
//    ScaledFileFeeder *tempFileFeeder = new ScaledFileFeeder(mInputFile,mScale) ; 
//    mBaseline = tempFileFeeder->getNextPoint() ;  // makes baseline the first point
//    delete tempFileFeeder ; 
    fill(relaxVector->begin() , relaxVector->end() , mBaseline) ; 
    tempEvaluator->setRelaxValue(relaxVector) ; 
    tempEvaluator->setRelaxTime(mRelaxTime) ; 
    tempEvaluator->setRelaxDeltaT(1.0) ; 
    tempEvaluator->setRelaxTau(3.0) ; 

    mTracer->setTimeDelimiter(",") ; 
    mTracer->setEvaluator(tempEvaluator) ; 


//    // set to the evaluator
//    if(mNumInputs>1){
//        tempEvaluator->setStimulus(new ScaledFileFeeder(mInputFile,mScale,mDeltaT),0) ; 
//        tempEvaluator->setStimulus(new ScaledFileFeeder(mInputFile,mScale,mDeltaT),1) ; 
//    }
//    else{
//        tempEvaluator->setStimulus(new ScaledFileFeeder(mInputFile,mScale,mDeltaT),0) ; 
//    }

//    tempEvaluator->setTarget(new ScaledFileFeeder(mInputFile,mScale,mDeltaT)) ; 
    prototypeNet->setEvaluator( tempEvaluator ) ; 

    return tempEvaluator ;
}





BlitzLiveNet* WienerDriver::createNetwork() 
{
    BlitzLiveNet* newNet = (BlitzLiveNet*) (new TinyBzNetParser())->parseFile(mNetworkFile) ;
    return newNet ; 
}



   


void WienerDriver::setRenderer(Renderer* newRenderer) 
{
    mRenderer = newRenderer ; 
}



void* WienerDriver::dumpTraceFromNet(BlitzLiveNet* plotNet,string dumpFile) 
{
    plotNet->eval() ; 
    vector<vector<double>*>* sliceTrace = (plotNet->getEvaluator())->getLastFullTraceAsSeries() ; 
    for(int i = 0 ; i < sliceTrace->size() ; i++){
        ostringstream* nameString = new ostringstream() ; 
        *nameString  << dumpFile << "." << i << ".txt" ; 
        ofstream* outputTextStream = new ofstream( (nameString->str()).c_str(),ios::out) ; 
        for(int j = 0 ; j <  ((*sliceTrace)[i])->size() ; j++){
            (*outputTextStream) << (*((*sliceTrace)[i]))[j] << endl ; 
        }
        outputTextStream->close() ; 
    }
}



bool WienerDriver::createLocalMaps() 
{
    string APP_NAME = "APP/PRUNER" ; 
    addCommandToMap(ZERO_ORDER_KERNEL) ; 
    addCommandToMap(FIRST_ORDER_KERNEL) ; 
    addCommandToMap(SECOND_ORDER_KERNEL) ; 
    addOptionToMap("01a_network",OPT_FILE_LOAD,&mNetworkFile,APP_NAME,"Network File") ; 
//    addOptionToMap("01ab_scale",OPT_INT,&mScale,APP_NAME,"Input Scale") ; 
    mScale = 1 ; 
    addOptionToMap("01b_sigmoid",OPT_DOUBLE,&mOutputSigmoid,APP_NAME,"Output Sigmoid (1.0)") ; 
    addOptionToMap("02_relaxtime",OPT_DOUBLE,&mRelaxTime,APP_NAME,"Relax Time (0.0)") ; 
    addOptionToMap("03_deltat",OPT_DOUBLE,&mDeltaT,APP_NAME,"Delta Time") ; 
    addOptionToMap("04_memory",OPT_INT,&mNumLags,APP_NAME,"Number of Lags") ; 
    addOptionToMap("05_validate",OPT_BOOL,&mCrossValidate,APP_NAME,"Cross Validate") ; 
    addOptionToMap("07b_numinputs",OPT_INT,&mNumInputs,APP_NAME,"Num Inputs") ; 
    mOutputList = new vector<string>() ; 
    mOutputList->push_back("x11") ; 
    mOutputList->push_back("pdf") ; 
    mOutputList->push_back("png") ; 
    addOptionToMap("07c_outputtype",LIST_TYPE,&mOutputType,APP_NAME,"Output Type",(new TiListParser())->createList(mOutputList) ) ; 
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
    return true ; 
}


/*  ***********************************************************************************
    doLocalCommand() */
   
//! Description here.
/*  *********************************************************************************** */
string WienerDriver::doLocalCommand(Command *theCommand) 
{
    mRenderer->savePreferences() ; 

    string theName = theCommand->getName()  ;

//    BlitzLiveNet* net = loadNet() ; 
//    initPlotter(net->getNumNeurons()) ; 
    if(theName==ZERO_ORDER_KERNEL){
        cout << "ZERO_ORDER_KERNEL" << endl ; 
        
    } 
    else
    if(theName==FIRST_ORDER_KERNEL){
        cout << "FIRST_ORDER_KERNEL" << endl ; 

    }
    else
    if(theName==SECOND_ORDER_KERNEL){
        cout << "SECOND_ORDER_KERNEL" << endl ; 

    }
    
    return "it runned  "; 
}




void WienerDriver::initPlotter(int size) 
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

void WienerDriver::setOutput(Gnuplot* aPlot,int count) 
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





BlitzLiveNet* WienerDriver::loadNet() 
{
    BlitzLiveNet* thisNet = createNetwork() ; 
    thisNet->setEvaluator( createEvaluator(thisNet)) ; 
    return thisNet ; 
}


const string WienerDriver::ZERO_ORDER_KERNEL = "ZERO_ORDER_KERNEL"  ; 
const string WienerDriver::FIRST_ORDER_KERNEL = "FIRST_ORDER_KERNEL"  ; 
const string WienerDriver::SECOND_ORDER_KERNEL = "SECOND_ORDER_KERNEL"  ; 



/* Modeline for ViM {{{
 * vim:set ts=4:
 * vim600:fdm=marker fdl=0 fdc=3:
 * }}} */






