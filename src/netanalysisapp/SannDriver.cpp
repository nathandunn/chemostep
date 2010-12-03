
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
#include "PulseFeeder.hpp"   
#include "BlitzEulerSigNetEvaluator.hpp"   
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

// zero order impulse stuff
#include "ZeroOrderLabel.hpp"
#include "ZeroOrderLabelIdentifier.hpp"
#include "ZeroOrderImpulseFilter.hpp"
#include "ZeroOrderImpulseLabelIdentifier.hpp"

// first order impulse stuff
#include "FirstOrderLabel.hpp"
#include "FirstOrderLabelIdentifier.hpp"
#include "FirstOrderImpulseFilter.hpp"
#include "FirstOrderImpulseLabelIdentifier.hpp"

// second order impulse stuff
#include "SecondOrderLabel.hpp"
#include "SecondOrderLabelIdentifier.hpp"
#include "SecondOrderImpulseFilter.hpp"
#include "SecondOrderImpulseLabelIdentifier.hpp"


// netanalysis stuff
#include "GenericLabelIdentifierSet.hpp"
#include "ImpulseSignal.hpp"
#include "LabelSet.hpp"



#include "SannDriver.hpp"




/*  ***********************************************************************************
    Constructor */
   
//! Description here.
/*  *********************************************************************************** */
SannDriver::SannDriver(string newInterfaceName,string newTypeName,AppInterface* newParent)  :
TiFlatBaseApp(newInterfaceName,newTypeName,newParent) 
    ,mPlotVector(NULL)
    ,mPlotMultiple(false)
{
   description = "Kinetic annealer.  Produces 1 to N." ; 
   RNG::initSeed();
}

ofstream* SannDriver::createOutputFileStream(const char* outputFile) 
{
    ofstream *returnstream = new ofstream( outputFile , ios::out) ; 
    return returnstream ; 
}


/// Creates a network evaluator for BlitzLiveNet*
BlitzEulerNetEvaluator* SannDriver::createEvaluator(BlitzLiveNet* prototypeNet) {
    BlitzEulerNetEvaluator* tempEvaluator = NULL ;
    tempEvaluator = new BlitzEulerSigNetEvaluator(1.0,mOutputSigmoid,prototypeNet) ; 


    vector<double>* relaxVector = new vector<double>(mNumInputs) ; 

    fill(relaxVector->begin(),relaxVector->end(),mBaseline) ; 
    tempEvaluator->setRelaxValue(relaxVector) ; 
    tempEvaluator->setRelaxTime(mRelaxTime) ; 
    tempEvaluator->setRelaxDeltaT(1.0) ; 
    tempEvaluator->setRelaxTau(3.0) ; 
//    tempEvaluator->setRelaxLimit(mRelaxLimit) ; 

    mTracer = new TextEvalTrace() ; 
    mTracer->setTimeDelimiter(",") ; 
    mTracer->setEvaluator(tempEvaluator) ; 

    // 1.0 second duration poulse
    // stim
    for(int i = 0 ; i < mNumInputs ; i++){
        PulseFeeder* stimFeeder = new PulseFeeder() ;
        stimFeeder->setBaseline(mBaseline) ; 
        stimFeeder->setPulse(mPulse) ; 
        stimFeeder->setPulseAt(mPulseAt) ; 
        stimFeeder->setTotalTime(mTotalTime) ; 
        // set to the evaluator
        tempEvaluator->setStimulus(stimFeeder,i) ; 
    }


    // target
    PulseFeeder* targetFeeder = new PulseFeeder() ;
    targetFeeder->setTotalTime(mTotalTime) ; 
    tempEvaluator->setTarget(targetFeeder) ; 

    return tempEvaluator ;
}






LabelSet* SannDriver::analysisAlphaOrder(){

    BlitzLiveNet* thisNet = createNetwork() ; 
    thisNet->setEvaluator( createEvaluator(thisNet)) ; 
    thisNet->eval() ; 

    // each outer vector point is a time-slice from 0 to finalTime, each inner-vector point is a neuron value from input to output neuron
    vector<vector<double>*>* sliceTrace = (thisNet->getEvaluator())->getLastFullTraceAsSeries() ; 


    // REPLACE THIS SHIT with GSL or R code
    ImpulseSignal* impulseSignal = new ImpulseSignal(sliceTrace,mPulse,mBaseline,mPulseAt,1.0) ; 
    LabelFactory* labelFactory = new LabelFactory(new FirstOrderImpulseFilter(),new FirstOrderImpulseLabelIdentifier() ) ; 
    LabelSet* firstOrderLabelSet= (LabelSet*) labelFactory->extractLabelSet( impulseSignal ) ; 


    for(int i = 0 ; i < firstOrderLabelSet->size() ; i++){
        // Print transfer function of model
        cout << "neuron[" << i << "] " << (*firstOrderLabelSet)[i]->print() << endl ; 
        // Compare output produced with transfer function to real data
    }

    return firstOrderLabelSet ; 
    
}





BlitzLiveNet* SannDriver::createNetwork() 
{
    BlitzLiveNet* newNet = (BlitzLiveNet*) (new TinyBzNetParser())->parseFile(mNetworkFile) ;
    return newNet ; 
}



/*  ***********************************************************************************
    message() */
   
//! Description here.
/*  *********************************************************************************** */
int SannDriver::message(string caption,string text) 
{
    return QMessageBox::information((QtFlatRenderer*) mRenderer,caption.c_str(),text.c_str(),QMessageBox::Ok) ; 
}


/*  ***********************************************************************************
    setRenderer() */
   
//! Description here.
/*  *********************************************************************************** */
void SannDriver::setRenderer(Renderer* newRenderer) 
{
    mRenderer = newRenderer ; 
}


/*  ***********************************************************************************
    creaetLocalMaps() */
   
//! Add items to GUI
/*  *********************************************************************************** */
bool SannDriver::createLocalMaps() 
{
    string APP_NAME = "APP/PRUNER" ; 
    addCommandToMap(START_PLOTTER) ; 
    addCommandToMap(ANALYSISALPHAORDER) ; 
    addOptionToMap("01a_network",OPT_FILE_LOAD,&mNetworkFile,APP_NAME,"Network File") ; 
    addOptionToMap("01b_sigmoid",OPT_DOUBLE,&mOutputSigmoid,APP_NAME,"Output Sigmoid (1.0)") ; 
    addOptionToMap("01c_numinputs",OPT_INT,&mNumInputs,APP_NAME,"Num Inputs") ; 
    addOptionToMap("02_relaxtime",OPT_DOUBLE,&mRelaxTime,APP_NAME,"Relax Time (0.0)") ; 
//    addOptionToMap("02a_relaxlimit",OPT_DOUBLE,&mRelaxLimit,APP_NAME,"Relax Limit (0.0)") ; 
    addOptionToMap("03_baseline",OPT_DOUBLE,&mBaseline,APP_NAME,"Baseline") ; 
//    addOptionToMap("04_pulse",OPT_DOUBLE,&mPulse,APP_NAME,"Pulse Value") ; 
    mPulse = 100 ; 
    addOptionToMap("05_pulseat",OPT_DOUBLE,&mPulseAt,APP_NAME,"Pulse At") ; 
//    addOptionToMap("06_pulseduration",OPT_DOUBLE,&mPulseDuration,APP_NAME,"Pulse Duration") ; 
    mPulseDuration = 1 ; 
    addOptionToMap("07_totaltime",OPT_DOUBLE,&mTotalTime,APP_NAME,"Analysis Time") ; 
    addOptionToMap("08_outputname",OPT_STRING,&mNeuronOutput,APP_NAME,"Neuron Output Name") ; 
    addOptionToMap("09_plotmultiple",OPT_BOOL,&mPlotMultiple,APP_NAME,"Plot Multiple") ; 
    mTempType = new vector<string>() ; 
    mTempType->push_back("lines") ; 
    mTempType->push_back("dots") ; 
    mTempType->push_back("points") ; 
    mTempType->push_back("linespoints") ; 
    addOptionToMap("10_linetype",LIST_TYPE,&mLineType,APP_NAME,"Line Type",(new TiListParser())->createList(mTempType)) ; 
    return true ; 
}


/*  ***********************************************************************************
    doLocalCommand() */
   
//! Description here.
/*  *********************************************************************************** */
string SannDriver::doLocalCommand(Command *theCommand) 
{
    mRenderer->savePreferences() ; 

    string theName = theCommand->getName()  ;

    if(theName==START_PLOTTER){
        BlitzLiveNet* net = loadNet() ; 
        initPlotter(net->getNumNeurons()) ; 
        plotPulseFromNet(  net ) ; 
        dumpPulseFromNet(  net ,"dumpfile.txt" ) ; 
    } 
    if(theName==ANALYSISALPHAORDER){
        BlitzLiveNet* net = loadNet() ; 
        initPlotter(net->getNumNeurons()) ; 
        plotPulseFromNet( net ) ; 
        LabelSet* labelSet = analysisAlphaOrder() ; 
        plotPulseFromModel(labelSet) ; 
        plotPulseModelError(labelSet) ; 
    }
    
    return "it runned  "; 
}



void* SannDriver::plotPulseModelError(LabelSet* newLabelSet) 
{
    vector<vector<double>*>* sliceTrace = newLabelSet->getErrorTraceAsSeries() ; 
    for(int i = 0 ; i < sliceTrace->size() ; i++){
        (*mPlotVector)[i]->set_style("impulses") ; 
        ostringstream* nameString = new ostringstream() ; 
        *nameString  << "error neuron " << i ; 
        (*mPlotVector)[i]->plot_x( *((*sliceTrace)[i]) ,nameString->str() ) ; 
        nameString->clear() ; 
    }
}


/// Plots all of the models from a label set.
void* SannDriver::plotPulseFromModel(LabelSet* newLabelSet) 
{
    vector<vector<double>*>* sliceTrace = newLabelSet->getModelTraceAsSeries() ; 
    for(int i = 0 ; i < sliceTrace->size() ; i++){
        (*mPlotVector)[i]->set_style("lines") ; 
        ostringstream* nameString = new ostringstream() ; 
        *nameString  << "model neuron " << i ; 
        (*mPlotVector)[i]->plot_x( *((*sliceTrace)[i]) ,nameString->str() ) ; 
        nameString->clear() ; 
    }
}

void SannDriver::initPlotter(int size) 
{

    if(mPlotVector==NULL){
        mPlotVector = new vector<Gnuplot*>(size) ; 
        for(int i = 0 ; i < mPlotVector->size() ; i++){
            (*mPlotVector)[i] = new Gnuplot("line") ; 
        }
    }
    else{
        for( vector<Gnuplot*>::iterator plotIter = mPlotVector->begin(); plotIter!= mPlotVector->end(); ++plotIter  ) {
            (*plotIter)->reset_plot() ; 
        } ; 
    }

    for( vector<Gnuplot*>::iterator plotIter = mPlotVector->begin(); plotIter!= mPlotVector->end(); ++plotIter  ) {
        (*plotIter)->cmd("set ytics(0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9)") ; 
        (*plotIter)->cmd("set grid") ; 
        (*plotIter)->cmd("set title 'Neuron Pulse Response'") ; 
        (*plotIter)->cmd("set xlabel 'Time(s)'") ; 
        (*plotIter)->cmd("set ylabel 'Neural Activity'") ; 
    } ; 

}

void* SannDriver::dumpPulseFromNet(BlitzLiveNet* plotNet,string dumpFile) 
{
    plotNet->eval() ; 
    vector<vector<double>*>* sliceTrace = (plotNet->getEvaluator())->getLastFullTraceAsSeries() ; 
    for(int i = 0 ; i < sliceTrace->size() ; i++){
        ostringstream* nameString = new ostringstream() ; 
        *nameString  << mNeuronOutput << i << ".txt" ; 
        ofstream* outputTextStream = new ofstream( (nameString->str()).c_str(),ios::out) ; 
        for(int j = 0 ; j <  ((*sliceTrace)[i])->size() ; j++){
            (*outputTextStream) << (*((*sliceTrace)[i]))[j] << endl ; 
        }
        outputTextStream->close() ; 
    }
}


void* SannDriver::plotPulseFromNet(BlitzLiveNet* plotNet) 
{
    plotNet->eval() ; 
    vector<vector<double>*>* sliceTrace = (plotNet->getEvaluator())->getLastFullTraceAsSeries() ; 
    if(mPlotMultiple==true){
        for(int i = 0 ; i < sliceTrace->size() ; i++){
            (*mPlotVector)[i]->set_style(mLineType) ; 
            ostringstream* nameString = new ostringstream() ; 
            *nameString  << "neuron " << i ; 
            (*mPlotVector)[i]->plot_x( *((*sliceTrace)[i]) ,nameString->str() ) ; 
            nameString->clear() ; 
        }
    }
    else{
        for(int i = 0 ; i < sliceTrace->size() ; i++){
            (*mPlotVector)[0]->set_style(mLineType) ; 
            ostringstream* nameString = new ostringstream() ; 
            *nameString  << "neuron " << i ; 
            (*mPlotVector)[0]->plot_x( *((*sliceTrace)[i]) ,nameString->str() ) ; 
            nameString->clear() ; 
        }
    }
}


BlitzLiveNet* SannDriver::loadNet() 
{
    BlitzLiveNet* thisNet = createNetwork() ; 
    thisNet->setEvaluator( createEvaluator(thisNet)) ; 
    return thisNet ; 
}


const string SannDriver::START_PLOTTER = "START_PLOTTER"  ; 
const string SannDriver::ANALYSISALPHAORDER = "ANALYSISALPHAORDER"  ; 




/* Modeline for ViM {{{
 * vim:set ts=4:
 * vim600:fdm=marker fdl=0 fdc=3:
 * }}} */







