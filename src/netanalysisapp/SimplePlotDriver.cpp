
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
//#include "BlitzEulerLiveNetEvaluator.hpp"   
#include "BlitzEulerSigNetEvaluator.hpp"   
#include "BlitzMidPointNetEvaluator.hpp"   
#include "BlitzNetEvaluator.hpp"   
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




#include "SimplePlotDriver.hpp"




/*  ***********************************************************************************
    Constructor */
   
//! Description here.
/*  *********************************************************************************** */
SimplePlotDriver::SimplePlotDriver(string newInterfaceName,string newTypeName,AppInterface* newParent)  :
TiFlatBaseApp(newInterfaceName,newTypeName,newParent) 
    ,mPlotter(NULL)
    ,mCommandStream(new ostringstream())
{
   description = "Kinetic annealer.  Produces 1 to N." ; 
   RNG::initSeed();
}

ofstream* SimplePlotDriver::createOutputFileStream(const char* outputFile) 
{
    ofstream *returnstream = new ofstream( outputFile , ios::out) ; 
    return returnstream ; 
}


/// Creates a network evaluator for BlitzLiveNet*
BlitzNetEvaluator* SimplePlotDriver::createEvaluator(BlitzLiveNet* prototypeNet) {
    BlitzNetEvaluator* tempEvaluator = NULL ; 

    if(mDoMidPoint==true){
        tempEvaluator = new BlitzMidPointNetEvaluator() ; 
        ((BlitzMidPointNetEvaluator*) tempEvaluator)->setOutputSigmoid(mOutputSigmoid) ; 
    }
    else{
        tempEvaluator = new BlitzEulerSigNetEvaluator(mDeltaT) ; 
        ((BlitzEulerSigNetEvaluator*) tempEvaluator)->setOutputSigmoid(mOutputSigmoid) ; 
    }

    vector<double>* relaxVector = new vector<double>(mNumInputs) ; 

    fill(relaxVector->begin(),relaxVector->end(),mBaseline) ; 
    tempEvaluator->setRelaxValue(relaxVector) ; 
    tempEvaluator->setRelaxTime(mRelaxTime) ; 
    tempEvaluator->setRelaxDeltaT(1.0) ; 
    tempEvaluator->setRelaxTau(3.0) ; 


    // 1.0 second duration poulse
    // stim
    for(int i = 0 ; i < mNumInputs ; i++){
        PulseFeeder* stimFeeder = new PulseFeeder() ;
        stimFeeder->setBaseline(mBaseline) ; 
        stimFeeder->setPulse(mPulse) ; 
        stimFeeder->setPulseAt(mPulseAt) ; 
        stimFeeder->setPulseDuration(mPulseDuration) ; 
        stimFeeder->setTotalTime(mTotalTime) ; 
        stimFeeder->setDeltaT(mDeltaT) ; 
        tempEvaluator->setStimulus(stimFeeder,i) ; 
    }

    // target
    PulseFeeder* targetFeeder = new PulseFeeder() ;
    targetFeeder->setTotalTime(mTotalTime) ; 
    targetFeeder->setDeltaT(mDeltaT) ; 

    // set to the evaluator
    tempEvaluator->setTarget(targetFeeder) ; 

    return tempEvaluator ;
}





BlitzLiveNet* SimplePlotDriver::createNetwork() 
{
    BlitzLiveNet* newNet = (BlitzLiveNet*) (new TinyBzNetParser())->parseFile(mNetworkFile) ;
    newNet->setPerturber( new BlitzEulerPerturber() ) ; 
    return newNet ; 
}



/*  ***********************************************************************************
    message() */
   
//! Description here.
/*  *********************************************************************************** */
int SimplePlotDriver::message(string caption,string text) 
{
    return QMessageBox::information((QtFlatRenderer*) mRenderer,caption.c_str(),text.c_str(),QMessageBox::Ok) ; 
}


/*  ***********************************************************************************
    setRenderer() */
   
//! Description here.
/*  *********************************************************************************** */
void SimplePlotDriver::setRenderer(Renderer* newRenderer) 
{
    mRenderer = newRenderer ; 
}


bool SimplePlotDriver::createLocalMaps() 
{
    string APP_NAME = "APP/PRUNER" ; 
    addCommandToMap(START_PLOTTER) ; 
    addOptionToMap("01a_network",OPT_FILE_LOAD,&mNetworkFile,APP_NAME,"Network File") ; 
    addOptionToMap("01b_sigmoid",OPT_DOUBLE,&mOutputSigmoid,APP_NAME,"Output Sigmoid") ; 
    addOptionToMap("01c_numinputs",OPT_INT,&mNumInputs,APP_NAME,"Num Inputs") ; 
    addOptionToMap("03_baseline",OPT_DOUBLE,&mBaseline,APP_NAME,"Baseline") ; 
    addOptionToMap("04_pulse",OPT_DOUBLE,&mPulse,APP_NAME,"Pulse Value") ; 
    addOptionToMap("05_pulseat",OPT_DOUBLE,&mPulseAt,APP_NAME,"Pulse At") ; 
    addOptionToMap("07_totaltime",OPT_DOUBLE,&mTotalTime,APP_NAME,"Analysis Time") ; 
    addOptionToMap("08_deltat",OPT_DOUBLE,&mDeltaT,APP_NAME,"Delta T") ; 

    mTempType = new vector<string>() ; 
    mTempType->push_back("lines") ; 
    mTempType->push_back("dots") ; 
    mTempType->push_back("points") ; 
    mTempType->push_back("linespoints") ; 
    addOptionToMap("08_linetype",LIST_TYPE,&mLineType,APP_NAME,"Line Type",(new TiListParser())->createList(mTempType)) ; 
    addOptionToMap("09_high",OPT_DOUBLE,&mYHigh,APP_NAME,"High Y") ; 
    addOptionToMap("10_low",OPT_DOUBLE,&mYLow,APP_NAME,"Low Y") ; 
    addOptionToMap("11_midpoint",OPT_BOOL,&mDoMidPoint,APP_NAME,"MidPoint?") ; 




    // known constants
    mRelaxTime = 200 ; 
//    addOptionToMap("02_relaxtime",OPT_DOUBLE,&mRelaxTime,APP_NAME,"Relax Time (0.0)") ; 
//    mPulseDuration = 1 ; 
    addOptionToMap("06_pulseduration",OPT_DOUBLE,&mPulseDuration,APP_NAME,"Pulse Duration") ; 

    return true ; 
}


/*  ***********************************************************************************
    doLocalCommand() */
   
//! Description here.
/*  *********************************************************************************** */
string SimplePlotDriver::doLocalCommand(Command *theCommand) 
{
    mRenderer->savePreferences() ; 

    string theName = theCommand->getName()  ;

    if(theName==START_PLOTTER){
           startPlotter() ; 
    } 
    
    return "it runned  "; 
}

void* SimplePlotDriver::plotPulse(BlitzLiveNet* plotNet) 
{
    plotNet->eval() ; 
    if(mPlotter==NULL){
        mPlotter = new Gnuplot( mLineType) ; 
    }
    else{
        mPlotter->set_style(mLineType) ; 
        mPlotter->reset_plot() ; 
    }

    mCommandStream->str("") ; 
    *mCommandStream << "set yrange[" << mYLow << " to " << mYHigh << "]" ; 
    mPlotter->cmd( (mCommandStream->str()).c_str() ) ; 

    mPlotter->cmd("set ytics(0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9)") ; 
    mPlotter->cmd("set grid") ; 
//    mPlotter->cmd("set title 'Neuron Pulse Response'") ; 
    string titleString = mNetworkFile.substr( mNetworkFile.find_last_of("/")+1) ; 
    mCommandStream->str("") ; 
    *mCommandStream  << "set title '" << titleString << "'" << endl ; 
    mPlotter->cmd(  (mCommandStream->str()).c_str() ) ; 
    mPlotter->cmd("set xlabel 'Time(s)'") ; 
    mPlotter->cmd("set ylabel 'Neural Activity'") ; 
    vector<vector<double>*>* sliceTrace = (plotNet->getEvaluator())->getLastFullTraceAsSeries() ; 
    vector<double>* xTrace = new vector<double>( ) ; 
    for(int i = 0 ; i < mTotalTime / mDeltaT ; i++){
        xTrace->push_back(i*mDeltaT) ; 
    }

    mCommandStream->str("") ; 
    for(int i = 0 ; i < sliceTrace->size() ; i++){
        *mCommandStream<< "neuron " << i ; 
//        mPlotter->plot_x( *((*sliceTrace)[i]) ,mCommandStream->str() ) ; 
        mPlotter->plot_xy(*xTrace , *((*sliceTrace)[i]),mCommandStream->str() ) ; 
        mCommandStream->str("") ; 
    }


}


void* SimplePlotDriver::startPlotter() 
{
    BlitzLiveNet* thisNet = createNetwork() ; 
    thisNet->setEvaluator( createEvaluator(thisNet)) ; 
    BlitzXmlNetRenderer* renderer = new BlitzXmlNetRenderer() ; 
    plotPulse(thisNet) ; 
    dumpTrace(thisNet,"output") ; 
}

void* SimplePlotDriver::dumpTrace(BlitzLiveNet* plotNet , string dumpFile) 
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


const string SimplePlotDriver::START_PLOTTER = "START_PLOTTER"  ; 




/* Modeline for ViM {{{
 * vim:set ts=4:
 * vim600:fdm=marker fdl=0 fdc=3:
 * }}} */




