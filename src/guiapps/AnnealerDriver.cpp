
#include <iostream>
using std::cout ; 
using std::endl ; 

#include <fstream>
using std::ofstream ; 

#include <string>
using std::string ; 

#include <vector>
using std::vector ; 

#include <float.h>

#include <qmessagebox.h>

#include "BlitzNet.hpp" 
#include "RNG.hpp" 
#include "StepFeeder.hpp"   
#include "SetFeeder.hpp"   
#include "FileFeeder.hpp"   
#include "AutoWKineticBlitzEulerEval.hpp"   
#include "BlitzNetAnnealer.hpp"   
#include "TempSchedule.hpp" 
#include "PowerTempSchedule.hpp" 
#include "MomentumTempSchedule.hpp" 
#include "NetPerturber.hpp" 
#include "RNG.hpp" 
#include "TextEvalTrace.hpp" 
#include "TinyBzNetParser.hpp" 
#include "BlitzXmlNetRenderer.hpp" 
#include "QtFlatRenderer.h" 
#include "StringTokenizer.hpp"
using gnuworld::StringTokenizer ; 

#include <TiAppParser.hpp>
#include <TiListParser.hpp>
#include <AppInterfaceXmlEngine.hpp>
#include <TinyAppInterfaceXmlEngine.hpp>
#include <Command.hpp>
#include <AppInterface.hpp>
#include <Option.hpp>

#include "AnnealerDriver.hpp"

#define CHAR_LENGTH 256

#ifdef DOMPI
    #include "mpi.h"
    int ad_myid ; 
    int ad_nprocs ; 
#endif 

AnnealerDriver::AnnealerDriver(string newInterfaceName,string newTypeName,AppInterface* newParent)  :
TiFlatBaseApp(newInterfaceName,newTypeName,newParent)
    ,doWait(true) 
{
   description = "Kinetic annealer.  Produces 1 to N." ; 
}



bool AnnealerDriver::runapp(){


    // init 
    BlitzNet *blitzNet = new BlitzNet() ; 
    BlitzNetAnnealer* annealer = new BlitzNetAnnealer() ; 
    BlitzEulerPerturber* perturber = new BlitzEulerPerturber() ; 
    KineticBlitzEulerEval* evaluator = new KineticBlitzEulerEval() ;    

    // set feeders
    SetFeeder *stimLeft = new SetFeeder() ; 
    SetFeeder *stimRight = new SetFeeder() ; 
    SetFeeder *targetSet = new SetFeeder() ; 
    // stim feeders


    #ifdef DOMPI
        MPI_Barrier(MPI_COMM_WORLD) ;     
        cout << "in runapp: done waiting: " << ad_myid << endl; 
        syncData() ; 
    #endif

//    #ifdef DOMPI
//    if(ad_myid==0)
//    #endif

    stimLeft->setDeltaT(mLeftStimDeltaT) ; 
    stimRight->setDeltaT(mRightStimDeltaT) ; 
    targetSet->setDeltaT(mTargetDeltaT) ; 




    if( mLeftStim == NULL || mRightStim == NULL || mTarget == NULL || mLeftStim->size() != mRightStim->size()){
        cout << "mLeftStim: " << mLeftStim << endl ; 
        cout << "mRightStim: " << mRightStim << endl ; 
        cout << "mTarget: " << mTarget << endl ; 
        cout << "mLeftStim->size(): " << mLeftStim->size() << endl ; 
        cout << "mRightStim->size(): " << mRightStim->size() << endl ; 
        throw "error in stimulus" ;
    }

    // loop through the files loaded as file loaders
    // for each string from each mLeftStim, mRightStim, and mTarget, and SetFeeder (or FeedeSet, I forget)

    // do the left stimulus first
    for(int i = 0 ; i < mLeftStim->size() ; i++){
        stimLeft->addFeeder(new FileFeeder(  (*mLeftStim)[i])  )  ; 
    }


    for(int i = 0 ; i < mRightStim->size() ; i++){
        stimRight->addFeeder(new FileFeeder(  (*mRightStim)[i])  )  ; 
    }

    for(int i = 0 ; i < mTarget->size() ; i++){
        targetSet->addFeeder(new FileFeeder(  (*mTarget)[i])  )  ; 
    }

    
    vector<double>* relaxVector = new vector<double>(2) ; 
    (*relaxVector)[0] = 0.5 ; 
    (*relaxVector)[1] = 0.5 ; 
    evaluator->setRelaxValue(relaxVector) ; 
    evaluator->setStimulus(stimLeft,0) ; 
    evaluator->setStimulus(stimRight,1) ; 
    evaluator->setTarget(targetSet) ; 
    evaluator->setRelaxTime(mRelaxTime) ; 
    evaluator->setRelaxDeltaT(1) ; 
    evaluator->setRelaxTau(3) ; 
    evaluator->setRelaxLimit(mRelaxDeltaLimit) ; 
    evaluator->setGlobalSigLimit(mSigLimit) ; 

    TextEvalTrace *tracer = new TextEvalTrace() ; 
    tracer->setTimeDelimiter(",") ; 
    TinyBzNetParser* netParser = new TinyBzNetParser() ; 

    blitzNet = netParser->parseFile(mNetworkFile) ; 
    blitzNet->setEvaluator(evaluator) ; 
    blitzNet->setPerturber(perturber) ; 
    tracer->setEvaluator(evaluator) ; 

    // define tempoSchedule
//    MomentumTempSchedule* tempSchedule = new MomentumTempSchedule() ;  
    PowerTempSchedule* tempSchedule= new PowerTempSchedule() ;
    tempSchedule->setPower(3.0) ; 

    tempSchedule->setNumPoints(mNumTemps) ; 
    tempSchedule->setHighTemp(mHighTemp) ; 
    tempSchedule->setLowTemp(mLowTemp) ; 
    tempSchedule->initTemps() ; 


    annealer->setSetBack(mSetBack) ; 
    annealer->setBackStep(mBackStep) ; 
    annealer->setTempSchedule(tempSchedule) ; 
    annealer->setIterPerTemp(mNumIters) ; 
    annealer->setAnnealingTarget(blitzNet) ; 
    cout << "original net: " << blitzNet->eval() << endl ; 


    BlitzNet* greatNet = NULL ; 
    double greatError  ; 
    char netName[256] ;
    char buffer[256] ; 
    cout << "mOutputNet: " << mOutputNet << endl ; 
    cout << "mNumNetworks: " << mNumNetworks << endl ; 
    BlitzXmlNetRenderer* renderer = new BlitzXmlNetRenderer() ; 
    vector<string>* outputNetNames = new vector<string>() ;
    StringTokenizer *tokenizerOut = new StringTokenizer(mOutputNet,'%') ; 
    vector<string>::iterator  iter ; 

    // create the input and output names
    // should just be in one loop, though
    for(int i = 0 ; i < mNumNetworks ; i++){
        sprintf(netName,"%s%i%s", ((*tokenizerOut)[0]).c_str(),i, ((*tokenizerOut)[1]).c_str() ) ; 
        outputNetNames->push_back(netName) ; 
        cout << "pushed back: " << netName << endl ; 
    }

    cout << "number of networks: " << mNumNetworks << endl ; 
    cout << "outputNetNames->size(): " << outputNetNames->size() << endl ; 

    for( iter = outputNetNames->begin()  ; iter!=outputNetNames->end() ; iter++){
        blitzNet = netParser->parseFile(mNetworkFile) ; 
        blitzNet->setEvaluator(evaluator) ; 
        blitzNet->setPerturber(perturber) ; 
        cout << "pre-anneal" << endl ; 
        greatNet = NULL ; 
        greatNet = new BlitzNet((BlitzNet*) annealer->anneal()) ; 
        cout << "post-anneal" << endl ; 
        greatError = greatNet->eval() ; 
        ofstream outputStream(  (*iter).c_str()  ) ; 
        outputStream << renderer->render(greatNet) << endl ;  
        outputStream.close() ; 
        sprintf(buffer,"Error: %f \nWritten to \"%s\".",greatError, (*iter).c_str() ) ; 
        cout << "buffer: " << buffer << endl ; 
        cout << "final network error: " << greatNet->eval() << endl ;
    }

//
//    message("Annealing finished!",buffer) ; 

//    QMessageBox::information(NULL,"Annealing finished!",buffer,QMessageBox::Ok) ; 

}

int AnnealerDriver::message(string caption,string text) 
{
    return QMessageBox::information((QtFlatRenderer*) mRenderer,caption.c_str(),text.c_str(),QMessageBox::Ok) ; 
}

void AnnealerDriver::setRenderer(Renderer* newRenderer) 
{
    mRenderer = newRenderer ; 
}





bool AnnealerDriver::createLocalMaps() 
{
    string APP_NAME = "APP/ANNEALER" ; 
    addCommandToMap(START_ANNEALER) ; 
    addOptionToMap(HIGH_TEMP,OPT_DOUBLE,&mHighTemp,APP_NAME,"Initial annealer\ntemperature") ; 
    addOptionToMap(LOW_TEMP,OPT_DOUBLE,&mLowTemp,APP_NAME,"Final annealer\ntemperature") ; 
    addOptionToMap(NUM_ITERS,OPT_INT,&mNumIters,APP_NAME,"Base iterations\nper temperature") ; 
    addOptionToMap(NUM_TEMPS,OPT_INT,&mNumTemps,APP_NAME) ; 
    addOptionToMap(BACK_STEP,OPT_DOUBLE,&mBackStep,APP_NAME) ; 
    addOptionToMap(SETBACK,OPT_INT,&mSetBack,APP_NAME) ; 
    addOptionToMap(VERBOSE,OPT_BOOL,&mVerbose,APP_NAME) ; 
    addOptionToMap(NETWORK,OPT_FILE_LOAD,&mNetworkFile,APP_NAME) ; 
    addOptionToMap(OUTPUT_NET,OPT_FILE_SAVE,&mOutputNet,APP_NAME) ; 
    addOptionToMap(LEFT_STIM_DELTAT,OPT_DOUBLE,&mLeftStimDeltaT,APP_NAME) ; 
    addOptionToMap(RIGHT_STIM_DELTAT,OPT_DOUBLE,&mRightStimDeltaT,APP_NAME) ; 
    addOptionToMap(TARGET_DELTAT,OPT_DOUBLE,&mTargetDeltaT,APP_NAME) ; 
    addOptionToMap(LEFT_STIM_FILES,LIST_FILE_LOAD,&mLeftStim,APP_NAME) ; 
    addOptionToMap(RIGHT_STIM_FILES,LIST_FILE_LOAD,&mRightStim,APP_NAME) ; 
    addOptionToMap(TARGET_FILES,LIST_FILE_LOAD,&mTarget,APP_NAME) ; 
    addOptionToMap(RELAX_TIME,OPT_DOUBLE,&mRelaxTime,APP_NAME) ; 
    addOptionToMap(NUM_NETWORKS,OPT_INT,&mNumNetworks,APP_NAME) ; 
    addOptionToMap(SIG_LIMIT,OPT_DOUBLE,&mSigLimit,APP_NAME) ; 
    addOptionToMap(RELAX_DELTA_LIMIT,OPT_DOUBLE,&mRelaxDeltaLimit,APP_NAME) ; 
    return true ; 
}




string AnnealerDriver::doLocalCommand(Command *theCommand) 
{
    cout << "doing command: " << theCommand->getName() << endl ; 
    cout << "mRenderer: " << mRenderer << endl ; 
    mRenderer->savePreferences() ; 
    cout << "finished saving preferences" << endl ; 
    // eventually this should be start and stop annealer
    string theName  = theCommand->getName() ; 
    string returnString = "" ; 
    if(theName==START_ANNEALER){
        try{
                cout << "proc A: " << procId << endl ; 
                #ifdef DOMPI
                MPI_Comm_rank(MPI_COMM_WORLD,&ad_myid) ; 
                if(ad_myid==0){
                    waitForCommand("runapp") ; 
                }
                #else
                    runapp() ; 
                #endif
                cout << "proc B: " << procId << endl ; 
        }
        catch(...){
            returnString += InterfaceXmlString::COMMANDSTATUS_FAILURE ; 
        }
    }
        cout << "proc D: " << procId << endl ; 
    return returnString ; 
}


#ifdef DOMPI


/**
 *  Syncs the parallel data between processors.
 */
void AnnealerDriver::syncData() 
{
      
        MPI_Bcast(&mLeftStimDeltaT,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
        MPI_Bcast(&mRightStimDeltaT,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
        MPI_Bcast(&mTargetDeltaT,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 

    	int numIters = 0 ; 
    	if(ad_myid==0){
            numIters = mLeftStim->size() ; 
            cout << "numIters: " << numIters << endl ; 
        }
        MPI_Bcast(&numIters, 1,MPI_INT,0,MPI_COMM_WORLD) ; 

        char fileName[CHAR_LENGTH]; 

		if(ad_myid!=0){
            mLeftStim = new vector<string>() ; 
            mRightStim = new vector<string>() ; 
            mTarget = new vector<string>() ; 
        }

        
        for(int j = 0 ; j < numIters ; j++){
            // set left stim file
            if(ad_myid==0) sprintf(fileName,"%s",((*mLeftStim)[j]).c_str()) ; 
            MPI_Bcast(fileName, CHAR_LENGTH,MPI_CHAR,0,MPI_COMM_WORLD) ; 
            if(ad_myid!=0) mLeftStim->push_back(fileName) ; 

            // set right stim file
            if(ad_myid==0) sprintf(fileName,"%s",((*mRightStim)[j]).c_str()) ; 
            MPI_Bcast(fileName, CHAR_LENGTH,MPI_CHAR,0,MPI_COMM_WORLD) ; 
            if(ad_myid!=0) mRightStim->push_back(fileName) ; 

            // set target file
            if(ad_myid==0) sprintf(fileName,"%s",((*mTarget)[j]).c_str()) ; 
            MPI_Bcast(fileName, CHAR_LENGTH,MPI_CHAR,0,MPI_COMM_WORLD) ; 
            if(ad_myid!=0) mTarget->push_back(fileName) ; 
        }

        if(ad_myid==0) sprintf(fileName,"%s",mNetworkFile.c_str()) ; 
        MPI_Bcast(fileName, CHAR_LENGTH,MPI_CHAR,0,MPI_COMM_WORLD) ; 
        if(ad_myid!=0) mNetworkFile = fileName ; 

        if(ad_myid==0) sprintf(fileName,"%s",mOutputNet.c_str()) ; 
        MPI_Bcast(fileName, CHAR_LENGTH,MPI_CHAR,0,MPI_COMM_WORLD) ; 
        if(ad_myid!=0) mOutputNet = fileName ; 


        // do temmperature schedule here
        MPI_Bcast(&mNumTemps,1,MPI_INT,0,MPI_COMM_WORLD) ; 
        MPI_Bcast(&mHighTemp,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
        MPI_Bcast(&mLowTemp,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 

        // do number of networks, next
        MPI_Bcast(&mNumNetworks,1,MPI_INT,0,MPI_COMM_WORLD) ; 
       
        // do backstep and setback next
        MPI_Bcast(&mSetBack,1,MPI_INT,0,MPI_COMM_WORLD) ; 
        MPI_Bcast(&mBackStep,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
        MPI_Bcast(&mNumIters,1,MPI_INT,0,MPI_COMM_WORLD) ; 

        // do relax times, here
        MPI_Bcast(&mRelaxTime,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
}



void AnnealerDriver::waitForCommand(char* command) 
{
    MPI_Comm_rank(MPI_COMM_WORLD,&ad_myid) ; 
    cout << "waitingn in waitForCommand: "  << ad_myid << endl ; 
    MPI_Barrier(MPI_COMM_WORLD) ;     
    runapp() ; 

    if(ad_myid!=0){
        waitForCommand("wait") ; 
    }

    // send a command, to all others to do runapp, and see what's missing
}
#endif



const string AnnealerDriver::HIGH_TEMP = "HIGH_TEMP"  ; 
const string AnnealerDriver::LOW_TEMP = "LOW_TEMP"  ; 
const string AnnealerDriver::START_ANNEALER = "START_ANNEALER"  ; 
const string AnnealerDriver::NUM_ITERS = "NUM_ITERS"  ; 
const string AnnealerDriver::NUM_TEMPS = "NUM_TEMPS"  ; 
const string AnnealerDriver::BACK_STEP = "BACK_STEP"  ; 
const string AnnealerDriver::SIG_LIMIT = "SIG_LIMIT"  ; 
const string AnnealerDriver::RELAX_DELTA_LIMIT = "RELAX_DELTA_LIMIT"  ; 
const string AnnealerDriver::SETBACK = "SETBACK"  ; 
const string AnnealerDriver::VERBOSE= "VERBOSE"  ; 
const string AnnealerDriver::NETWORK= "NETWORK"  ; 
const string AnnealerDriver::OUTPUT_NET= "OUTPUT_NET"  ; 
const string AnnealerDriver::LEFT_STIM_DELTAT= "LEFT_STIM_DELTAT"  ; 
const string AnnealerDriver::RIGHT_STIM_DELTAT= "RIGHT_STIM_DELTAT"  ; 
const string AnnealerDriver::TARGET_DELTAT= "TARGET_DELTAT"  ; 
const string AnnealerDriver::LEFT_STIM_FILES= "LEFT_STIM_FILES"  ; 
const string AnnealerDriver::RIGHT_STIM_FILES= "RIGHT_STIM_FILES"  ; 
const string AnnealerDriver::TARGET_FILES= "TARGET_FILES"  ; 
const string AnnealerDriver::RELAX_TIME= "RELAX_TIME"  ; 
const string AnnealerDriver::NUM_NETWORKS= "NUM_NETWORKS"  ; 




/* Modeline for ViM {{{
 * vim:set ts=4:
 * vim600:fdm=marker fdl=0 fdc=3:
 * }}} */


