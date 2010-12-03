
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
#include "BlitzEulerLiveNetEvaluator.hpp"   
#include "BlitzEulerSigNetEvaluator.hpp"   
#include "TextEvalTrace.hpp" 
#include "TinyBzNetParser.hpp" 
#include "BlitzXmlNetRenderer.hpp" 
#include "BlitzNetPruner.hpp" 
#include "PulseAnalyzer.hpp" 
#include <Note.hpp> 


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




#include "PruneDriver.hpp"




/*  ***********************************************************************************
    Constructor */
   
//! Description here.
/*  *********************************************************************************** */
PruneDriver::PruneDriver(string newInterfaceName,string newTypeName,AppInterface* newParent)  :
TiFlatBaseApp(newInterfaceName,newTypeName,newParent) 
    ,mPlotter(NULL)
{
   description = "Kinetic annealer.  Produces 1 to N." ; 
   RNG::initSeed();
}

ofstream* PruneDriver::createOutputFileStream(const char* outputFile) 
{
    ofstream *returnstream = new ofstream( outputFile , ios::out) ; 
    return returnstream ; 
}


/// Creates a network evaluator for BlitzLiveNet*
BlitzEulerNetEvaluator* PruneDriver::createEvaluator(BlitzLiveNet* prototypeNet) {
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
        tempEvaluator->setStimulus(stimFeeder,i) ; 
    }

    // target
    PulseFeeder* targetFeeder = new PulseFeeder() ;
    targetFeeder->setTotalTime(mTotalTime) ; 

    // set to the evaluator
    tempEvaluator->setTarget(targetFeeder) ; 

    return tempEvaluator ;
}



/************************************************************************************
    runapp() */
   
//! Create a network and an evaluator. Make the call to evaluate the network.
/************************************************************************************ */

void *PruneDriver::startPruner(){

    BlitzLiveNet* thisNet = createNetwork() ; 
    thisNet->setEvaluator( createEvaluator(thisNet)) ; 
    BlitzXmlNetRenderer* renderer = new BlitzXmlNetRenderer() ; 

    thisNet->eval() ; 
    ofstream outFile("netout.txt",ios::out) ; 
    outFile << mTracer->allNeuronTrace() << endl ; 
//    cout << "neuronTrace: " << endl << mTracer->allNeuronTrace() << endl ; 
    vector<vector<double>*>* sliceTrace = (thisNet->getEvaluator())->getLastFullTraceAsSeries() ; 
    PulseAnalyzer* pulseAnalyzer = new PulseAnalyzer() ; 
    vector<double>* activity = pulseAnalyzer->getAmplitude( sliceTrace , (int) mPulseAt) ; 
//    for(int i = 0 ; i < activity->size() ; i++){
//        cout << i << ": ampl " << (*activity)[i] << endl ; 
//    }
    BlitzNetPruner* blitzNetPruner = new BlitzNetPruner() ; 
//    BlitzNet* prunedNet  = new BlitzNet(blitzNetPruner->prune(thisNet,activity,mActivityThreshold)) ; 
    BlitzNet* prunedNet  = (blitzNetPruner->prune(thisNet,activity,mActivityThreshold)) ; 
    ofstream* prunedNetStream = new ofstream(mBestNetworkFile.c_str(),ios::out) ; 
    (*prunedNetStream) <<  renderer->render(prunedNet)  << endl ; 
}


BlitzLiveNet* PruneDriver::createNetwork() 
{
    BlitzLiveNet* newNet = (BlitzLiveNet*) (new TinyBzNetParser())->parseFile(mNetworkFile) ;
    newNet->setPerturber( new BlitzEulerPerturber() ) ; 
    return newNet ; 
}



/*  ***********************************************************************************
    message() */
   
//! Description here.
/*  *********************************************************************************** */
int PruneDriver::message(string caption,string text) 
{
    return QMessageBox::information((QtFlatRenderer*) mRenderer,caption.c_str(),text.c_str(),QMessageBox::Ok) ; 
}


/*  ***********************************************************************************
    setRenderer() */
   
//! Description here.
/*  *********************************************************************************** */
void PruneDriver::setRenderer(Renderer* newRenderer) 
{
    mRenderer = newRenderer ; 
}


/*  ***********************************************************************************
    creaetLocalMaps() */
   
//! Add items to GUI
/*  *********************************************************************************** */
bool PruneDriver::createLocalMaps() 
{
    string APP_NAME = "APP/PRUNER" ; 
    addCommandToMap(START_PRUNER) ; 
    addCommandToMap(START_PLOTTER) ; 
    addOptionToMap("01a_network",OPT_FILE_LOAD,&mNetworkFile,APP_NAME,"Network File") ; 
    addOptionToMap("01b_sigmoid",OPT_DOUBLE,&mOutputSigmoid,APP_NAME,"Output Sigmoid") ; 
//    addOptionToMap("01bb_inputsig",OPT_DOUBLE,&mInputSigmoid,APP_NAME,"Input Sigmoid") ; 
    addOptionToMap("01c_numinputs",OPT_INT,&mNumInputs,APP_NAME,"Num Inputs") ; 
    addOptionToMap("02_relaxtime",OPT_DOUBLE,&mRelaxTime,APP_NAME,"Relax Time (0.0)") ; 
//    addOptionToMap("02a_relaxlimit",OPT_DOUBLE,&mRelaxLimit,APP_NAME,"Relax Limit (0.0)") ; 
    addOptionToMap("03_baseline",OPT_DOUBLE,&mBaseline,APP_NAME,"Baseline") ; 
    addOptionToMap("04_pulse",OPT_DOUBLE,&mPulse,APP_NAME,"Pulse Value") ; 
    addOptionToMap("05_pulseat",OPT_DOUBLE,&mPulseAt,APP_NAME,"Pulse At") ; 
    addOptionToMap("06_pulseduration",OPT_DOUBLE,&mPulseDuration,APP_NAME,"Pulse Duration") ; 
    addOptionToMap("07_totaltime",OPT_DOUBLE,&mTotalTime,APP_NAME,"Analysis Time") ; 
    addOptionToMap("08_activitythresh",OPT_DOUBLE,&mActivityThreshold,APP_NAME,"Activity Threshold") ; 
    addOptionToMap("13_outputfile",OPT_STRING,&mOutputFile,APP_NAME,"Pruner output") ; 
    addOptionToMap("14_bestnetwork",OPT_STRING,&mBestNetworkFile,APP_NAME,"Best net output") ; 
    return true ; 
}


/*  ***********************************************************************************
    doLocalCommand() */
   
//! Description here.
/*  *********************************************************************************** */
string PruneDriver::doLocalCommand(Command *theCommand) 
{
    mRenderer->savePreferences() ; 

    string theName = theCommand->getName()  ;

    if(theName==START_PRUNER){
           startPruner() ; 
    } 
    else
    if(theName==START_PLOTTER){
           startPlotter() ; 
    } 
    
    return "it runned  "; 
}

void* PruneDriver::plotPulse(BlitzLiveNet* plotNet) 
{
    plotNet->eval() ; 
    if(mPlotter==NULL){
//        mPlotter = new Gnuplot("Neuron Pulse Response","Line","time","Neural Activity") ; 
        mPlotter = new Gnuplot("line") ; 
    }
    else{
        mPlotter->reset_plot() ; 
    }

    mPlotter->cmd("set ytics(0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9)") ; 
    mPlotter->cmd("set grid") ; 
    mPlotter->cmd("set title 'Neuron Pulse Response'") ; 
    mPlotter->cmd("set xlabel 'Time(s)'") ; 
    mPlotter->cmd("set ylabel 'Neural Activity'") ; 
    vector<vector<double>*>* sliceTrace = (plotNet->getEvaluator())->getLastFullTraceAsSeries() ; 
    for(int i = 0 ; i < sliceTrace->size() ; i++){
        ostringstream* nameString = new ostringstream() ; 
        *nameString  << "neuron " << i ; 
        mPlotter->plot_x( *((*sliceTrace)[i]) ,nameString->str() ) ; 
        nameString->clear() ; 
    }
}


void* PruneDriver::startPlotter() 
{
    BlitzLiveNet* thisNet = createNetwork() ; 
    thisNet->setEvaluator( createEvaluator(thisNet)) ; 
    BlitzXmlNetRenderer* renderer = new BlitzXmlNetRenderer() ; 
    plotPulse(thisNet) ; 
}


const string PruneDriver::START_PRUNER = "START_PRUNER"  ; 
const string PruneDriver::START_PLOTTER = "START_PLOTTER"  ; 




/* Modeline for ViM {{{
 * vim:set ts=4:
 * vim600:fdm=marker fdl=0 fdc=3:
 * }}} */




