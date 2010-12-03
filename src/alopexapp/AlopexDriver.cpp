
#define CHAR_LENGTH 256

#include <iostream>
using std::cout ; 
using std::endl ; 
using std::ostream ; 

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

#include "BlitzLiveNet.hpp"
#include "RNG.hpp" 
#include "StepFeeder.hpp"   
#include "SetFeeder.hpp"   
#include "FileFeeder.hpp"   
#include "UniformNetBehaviorModel.hpp"   
#include "BlitzEulerLiveNetEvaluator.hpp"   
#include "BlitzNetAlopexer.hpp"  
#include "BlitzNetAlopexPerturber.hpp"
#include "MomentumPowerTempSchedule.hpp" 
#include "UniformFwdMovement.hpp" 
#include "SharpTurnMovementModel.hpp" 
#include "TextEvalTrace.hpp" 
#include "TinyBzNetParser.hpp" 
#include "BlitzXmlNetRenderer.hpp" 
#include "LinRadialMap.hpp" 
#include "QtFlatRenderer.h" 
#include "WormMapStats.hpp" 
#include "WormSimEval.hpp" 
#include "WormSimMeanDistEval.hpp" 
//#include "WormSimSqrtMeanDistEval.hpp" 
#include "WormSimSqrtRadDistEval.hpp" 

#include <qmessagebox.h>
#include <TiAppParser.hpp>
#include <AlopexThread.hpp>
#include <TiListParser.hpp>
#include <AppInterfaceXmlEngine.hpp>
#include <TinyAppInterfaceXmlEngine.hpp>
#include <Command.hpp>
#include <AppInterface.hpp>
#include <Option.hpp>
#include <Worm.hpp>
#include <TtestAcceptModel.hpp>


#ifdef DOMPI
    #include "mpi.h"
    int ad_myid ; 
    int ad_nprocs ; 
    char realCommand[128] = "wait"  ; 
#endif 


#include "AlopexDriver.hpp"




/*  ***********************************************************************************
    Constructor */
   
//! Description here.
/*  *********************************************************************************** */
AlopexDriver::AlopexDriver(string newInterfaceName,string newTypeName,AppInterface* newParent)  :
TiFlatBaseApp(newInterfaceName,newTypeName,newParent) 
,alopexThread(NULL)
{
   description = "Alopex-B optimizer.  Produces 1 to N." ; 
   RNG::initSeed();
}

ofstream* AlopexDriver::createOutputFileStream(const char* outputFile) 
{
    ofstream *returnstream = new ofstream( outputFile , ios::out) ; 
    return returnstream ; 
}


/// Creates evaluator using the assumption that the network has already been created.  The evaluator is WormSimMeanDistEval() 
WormSimEval* AlopexDriver::createEvaluator(BlitzLiveNet* prototypeNet) {
//    WormSimEval* mEvaluator = new WormSimMeanDistEval(mNumWorms,mNumWormSteps,prototypeNet,new LinRadialMap(mDiameter,mHighMapValue,mLowMapValue),mForwardVelocity,mTurnVelocity,mDeltaT) ;    
    //WormSimEval* mEvaluator = new WormSimSqrtMeanDistEval(mNumWorms,mNumWormSteps,prototypeNet,new LinRadialMap(mDiameter,mHighMapValue,mLowMapValue),mForwardVelocity,mTurnVelocity,mDeltaT) ;    
	WormSimEval* mEvaluator = new WormSimSqrtRadDistEval(mNumWorms,mNumWormSteps,prototypeNet,new LinRadialMap(mDiameter,mHighMapValue,mLowMapValue),mForwardVelocity,mTurnVelocity,mDeltaT,mOutputSigmoid,NULL,mOptimumRadius) ;
	vector<double>* relaxVector = new vector<double>(1) ; 
    (*relaxVector)[0] = 0.5 ; 
    mEvaluator->setRelaxValue(relaxVector) ; 
    mEvaluator->setRelaxTime(mRelaxTime) ; 
    mEvaluator->setRelaxDeltaT(1.0) ; 
    mEvaluator->setRelaxTau(3.0) ; 
//    mEvaluator->setRelaxLimit(0.01) ; 
//    mEvaluator->setGlobalSigLimit(8.0) ; 
//    mEvaluator->resetTrace(mNumItersPerTemp,mNumItersPerTemp) ; 

    return mEvaluator ;
}



/************************************************************************************
    runapp() */
   
//! Create a network and an evaluator. Make the call to evaluate the network.
/************************************************************************************ */

void *AlopexDriver::runapp(){

    BlitzLiveNet* thisNet = createNetwork() ; 
    thisNet->setEvaluator( createEvaluator(thisNet)) ; 

    BlitzXmlNetRenderer* renderer = new BlitzXmlNetRenderer() ; 


    clock_t initTime = time(NULL) ; 
    cout << "********** start *********" <<  endl ; 
    cout << "network eval 1: " << thisNet->eval() << endl ; 
    thisNet->setValid(false) ; 
    cout << "network eval 2: " << thisNet->eval() << endl ; 
    thisNet->setValid(false) ; 
    cout << "network eval 3: " << thisNet->eval() << endl ; 
    double diffTime = difftime(time(NULL),initTime) ; 
    cout << "perturb" << endl ; 
#ifdef DOMPI
    if(ad_myid==0) thisNet->perturb(thisNet->eval())  ; 
    thisNet = syncNet(thisNet) ; 
#else
    thisNet->perturb(thisNet->eval())  ; 
#endif
    cout << "network eval 4: " << thisNet->eval() << endl ; 
    thisNet->setValid(false) ; 
    cout << "network eval 5: " << thisNet->eval() << endl ; 
    thisNet->setValid(false) ; 
    cout << "network eval 6: " << thisNet->eval() << endl ; 
    cout << "********** finish *********" <<  endl ; 

    cout << "diffTime for first 3 (eval/sec): " << ((diffTime/3.0)/ (double) CLOCKS_PER_SEC) << endl ; 

#ifdef DOMPI
    if(ad_myid!=0){
        strcpy(realCommand,"wait") ;
        waitForCommand() ;
    }
#endif
}


BlitzLiveNet* AlopexDriver::createNetwork() 
{
    BlitzLiveNet* newNet = (BlitzLiveNet*) (new TinyBzNetParser())->parseFile(mNetworkFile) ;
    // auto_ptr<BlitzLiveNet> newNet = (BlitzLiveNet*) (new TinyBzNetParser())->parseFile(mNetworkFile) ; 
		BlitzNetAlopexPerturber *pert = new BlitzNetAlopexPerturber(mAlopexDelta, mAlopexLambda);
		pert->initTrace(newNet->getWeights(), newNet->getTau(), newNet->getBias());
		pert->setBeta(mAlopexBeta) ;
		newNet->setPerturber(pert) ; 
		
		return newNet ; 
}

BlitzNetAlopexer* AlopexDriver::createAlopex() 
{
    BlitzNetAlopexer* returnAlopexer = new BlitzNetAlopexer() ;
    returnAlopexer->setMinError( mMinError) ; 
    returnAlopexer->setTotalIterations( mTotalIterations ) ; 
		returnAlopexer->setAcceptModel(new TtestAcceptModel(mCriticalAcceptance)) ;
		returnAlopexer->setOutputPeriod(mOutputPeriod);
    return returnAlopexer ;
}


/*  ***********************************************************************************
    message() */
   
//! Description here.
/*  *********************************************************************************** */
int AlopexDriver::message(string caption,string text) 
{
    return QMessageBox::information((QtFlatRenderer*) mRenderer,caption.c_str(),text.c_str(),QMessageBox::Ok) ; 
}


/*  ***********************************************************************************
    setRenderer() */
   
//! Description here.
/*  *********************************************************************************** */
void AlopexDriver::setRenderer(Renderer* newRenderer) 
{
    mRenderer = newRenderer ; 
}


/*  ***********************************************************************************
    creaetLocalMaps() */
   
//! Add items to GUI
/*  *********************************************************************************** */
bool AlopexDriver::createLocalMaps() 
{
    string APP_NAME = "APP/SIMWORM" ; 
    addCommandToMap(START_SIMWORM) ; 
    addCommandToMap(START_ALOPEXER) ; 
    addCommandToMap(STOP_ALOPEXER) ; 
    
    // app values
    addOptionToMap("00_numnetwork",OPT_INT,&mNumNetworks,APP_NAME,"Number of Networks") ; 
    addOptionToMap("01_network",OPT_FILE_LOAD,&mNetworkFile,APP_NAME,"Network File") ; 
    addOptionToMap("02_outputfile",OPT_STRING,&mOutputFile,APP_NAME,"Annealer output") ; 

    // network values
    addOptionToMap("03_bestnetwork",OPT_STRING,&mBestNetworkFile,APP_NAME,"Best net output") ;
		addOptionToMap("03a_sigOp",OPT_DOUBLE,&mOutputSigmoid,APP_NAME,"Network Beta") ;
    addOptionToMap("010_outputfile",OPT_STRING,&mOutputFile,APP_NAME,"Alopex Out") ; 
    addOptionToMap("011_outputnet",OPT_STRING,&mBestNetworkFile,APP_NAME,"Best Net Out") ; 

    // wormsim values
    addOptionToMap("04_numworms",OPT_INT,&mNumWorms,APP_NAME,"Number of Worms") ; 
    addOptionToMap("05_numiters",OPT_INT,&mNumWormSteps,APP_NAME,"Worm Steps") ; 
    addOptionToMap("06_forwardspeed",OPT_DOUBLE,&mForwardVelocity,APP_NAME,"Forward Speed") ; 
    addOptionToMap("07_turnspeed",OPT_DOUBLE,&mTurnVelocity,APP_NAME,"Turn Speed") ; 
    addOptionToMap("08_deltat",OPT_DOUBLE,&mDeltaT,APP_NAME,"Delta t") ; 
    addOptionToMap("09_highvalue",OPT_DOUBLE,&mHighMapValue,APP_NAME,"High Temp on Map") ; 
    addOptionToMap("10_lowvalue",OPT_DOUBLE,&mLowMapValue,APP_NAME,"Low Temp on Map") ; 
    addOptionToMap("11_diameter",OPT_DOUBLE,&mDiameter,APP_NAME,"Map Diameter") ; 
		addOptionToMap("11b_setradius",OPT_DOUBLE,&mOptimumRadius,APP_NAME,"Target Radius") ;
//    addOptionToMap("07_relaxtime",OPT_DOUBLE,&mRelaxTime,APP_NAME,"Time to relax network.") ; 
		addOptionToMap("092_crit",OPT_DOUBLE,&mCriticalAcceptance,APP_NAME,"Acceptance 1-0") ; 

    // alopex values
    addOptionToMap("120_numNetworks",OPT_INT,&mNumNetworks,APP_NAME,"Number of Networks") ; 
    addOptionToMap("121_minerror",OPT_DOUBLE,&mMinError,APP_NAME,"Minimum Error") ; 
    addOptionToMap("13_TotalIterations:",OPT_INT,&mTotalIterations,APP_NAME,"Max Iterations") ; 
    addOptionToMap("14_lambda:",OPT_DOUBLE,&mAlopexLambda,APP_NAME,"Alopex Lambda") ; 
    addOptionToMap("15_delta:",OPT_DOUBLE,&mAlopexDelta,APP_NAME,"Alopex Delta") ; 
		addOptionToMap("16_beta:",OPT_DOUBLE,&mAlopexBeta,APP_NAME,"Alopex Beta (sigmoid gain)") ;
		
		// output values

		addOptionToMap("16_outputPeriod:",OPT_INT,&mOutputPeriod,APP_NAME,"XML render period (Iter/step)") ;
     
    return true ; 
}


/*  ***********************************************************************************
    doLocalCommand() */
   
//! Description here.
/*  *********************************************************************************** */
string AlopexDriver::doLocalCommand(Command *theCommand) 
{
    mRenderer->savePreferences() ; 

    string theName = theCommand->getName()  ;

    if(theName==START_SIMWORM){
        #ifdef DOMPI
           strcpy(realCommand,"runapp") ; 
           waitForCommand() ; 
        #else
           runapp() ; 
        #endif 

    } else if(theName==START_ALOPEXER){
        #ifdef DOMPI
           strcpy(realCommand,"startannealer") ; 
           waitForCommand() ; 
        #else
           startAnnealer() ; 
        #endif 

    } else if(theName==STOP_ALOPEXER){
         stopAnnealer() ; 
    }
    
    return "it runned  "; 
}

#ifdef DOMPI

bool AlopexDriver::startAnnealer() 
{
    cout << ad_myid << ": in startAnnealer method" << endl ; 

    if(alopexThread==NULL || alopexThread->running()==false){
        alopexThread = new AlopexThread(this) ; 
    }
    alopexThread->run() ;

    if(ad_myid!=0){
        strcpy(realCommand,"wait") ;
        waitForCommand() ;
	return true;
    }
}

#else

bool AlopexDriver::startAnnealer() 
{
        alopexThread = new AlopexThread(this) ; 
        alopexThread->run() ; 
}

#endif



bool AlopexDriver::stopAnnealer() 
{
//    alopexThread->terminate() ; 
//    while(alopexThread->running()){
//        sleep(1) ; 
//    }
//    alopexThread = NULL ; 
//    message("Annealing Stopped","Stopped annealing.") ;
    return true ; 
}

#ifdef DOMPI
/// Sync's data from the gui input
void AlopexDriver::syncData() 
{
    char fileName[CHAR_LENGTH]; 


    // ALOPEX DESCRIPTION
    if(ad_myid==0) sprintf(fileName,"%s",mDescription.c_str()) ; 
    MPI_Bcast(fileName, CHAR_LENGTH,MPI_CHAR,0,MPI_COMM_WORLD) ; 
    if(ad_myid!=0) mDescription=fileName ; 

    // NETWORK VALUES
    if(ad_myid==0) sprintf(fileName,"%s",mNetworkFile.c_str()) ; 
    MPI_Bcast(fileName, CHAR_LENGTH,MPI_CHAR,0,MPI_COMM_WORLD) ; 
    if(ad_myid!=0) mNetworkFile=fileName ; 

    MPI_Bcast(&mRelaxTime,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mRelaxLimit,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mOutputSigmoid,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 

    // WORMSIM VALUES VALUES
    MPI_Bcast(&mNumWormSteps,1,MPI_INT,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mRefWorms,1,MPI_INT,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mDieOnEdge,1,MPI_INT,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mNumWormSteps,1,MPI_INT,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mForwardVelocity,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mTurnVelocity,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mDeltaT,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 


    // MAP VALUES
    MPI_Bcast(&mHighMapValue,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mMidMapValue,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mLowMapValue,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mMidMapRadius,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mOptimumRadius,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mEdgeBuffer,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mDiameter,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mSpacing,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 

    // ERROR WINDOW VALUES
    MPI_Bcast(&mLastSteps,1,MPI_INT,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mBinSize,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mWindow,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mWindowPower,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mInflectionRatio,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 


    // ALOPEX VALUES
    MPI_Bcast(&mNumNetworks,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mMinError,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mTotalIterations,1,MPI_INT,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mAlopexLambda,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mAlopexDelta,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mOutputPeriod,1,MPI_INT,0,MPI_COMM_WORLD) ; 

    if(ad_myid==0) sprintf(fileName,"%s",mOutputFile.c_str()) ; 
    MPI_Bcast(fileName, CHAR_LENGTH,MPI_CHAR,0,MPI_COMM_WORLD) ; 
    if(ad_myid!=0) mOutputFile=fileName ; 

    if(ad_myid==0) sprintf(fileName,"%s",mBestNetworkFile.c_str()) ; 
    MPI_Bcast(fileName, CHAR_LENGTH,MPI_CHAR,0,MPI_COMM_WORLD) ; 
    if(ad_myid!=0) mBestNetworkFile=fileName ; 

//    MPI_Bcast(&mQuitAfterAnneal,1,MPI_INT,0,MPI_COMM_WORLD) ; 



//
//    MPI_Bcast(&mNumWorms,1,MPI_INT,0,MPI_COMM_WORLD) ; 
//    MPI_Bcast(&mNumWormSteps,1,MPI_INT,0,MPI_COMM_WORLD) ; 
//    MPI_Bcast(&mForwardVelocity,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
//    MPI_Bcast(&mTurnVelocity,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
//    MPI_Bcast(&mDeltaT,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
//    MPI_Bcast(&mHighMapValue,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
//    MPI_Bcast(&mLowMapValue,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
//    MPI_Bcast(&mDiameter,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
//    MPI_Bcast(&mNumNetworks,1,MPI_INT,0,MPI_COMM_WORLD) ; 
////    MPI_Bcast(&mCriticalAcceptance,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
//    mRelaxTime = 0.0 ; 
//
//    if(ad_myid==0) sprintf(fileName,"%s",mOutputFile.c_str()) ; 
//    MPI_Bcast(fileName, CHAR_LENGTH,MPI_CHAR,0,MPI_COMM_WORLD) ; 
//    if(ad_myid!=0) mOutputFile=fileName ; 
//
//    if(ad_myid==0) sprintf(fileName,"%s",mNetworkFile.c_str()) ; 
//    MPI_Bcast(fileName, CHAR_LENGTH,MPI_CHAR,0,MPI_COMM_WORLD) ; 
//    if(ad_myid!=0) mNetworkFile=fileName ; 

}

/// Synchronizes the networks from the original network.
BlitzLiveNet* AlopexDriver::syncNet(BlitzLiveNet* origNet) 
{
      int numNeurons = origNet->getNumNeurons() ; 
      Matrix* bcastMatrix = new Matrix( (numNeurons+3),numNeurons) ; 
      Matrix* hereWeights = new Matrix( (numNeurons+3),numNeurons) ; 
      Vector* hereTau = new Vector( numNeurons) ; 
      Vector* hereBias = new Vector( numNeurons) ; 
      Vector* hereInitNeurons = new Vector( numNeurons) ; 
      Vector* hereVmem = new Vector( numNeurons) ; 
      (*bcastMatrix)( Range(0, numNeurons - 1), Range(0, numNeurons - 1) ) =*(origNet->getWeights()) ;
      (*bcastMatrix)( numNeurons, Range::all() ) = *(origNet->getTau());
      (*bcastMatrix)( numNeurons + 1,  Range::all() ) = *(origNet->getBias()) ; 
      (*bcastMatrix)( numNeurons + 2,  Range::all() ) = *(origNet->getInitNeuron()) ; 
      MPI_Bcast(bcastMatrix->data(), bcastMatrix->size(), MPI_DOUBLE, 0, MPI_COMM_WORLD);

      if(ad_myid != 0){
          (*hereWeights) = (*bcastMatrix) ( Range(0,numNeurons-1),Range(0,numNeurons-1)  ) ;
          (*hereTau) = (*bcastMatrix) (numNeurons,Range::all() ) ; 
          (*hereBias) = (*bcastMatrix) (numNeurons+1,Range::all() ) ; 
          (*hereInitNeurons) = (*bcastMatrix) (numNeurons+2,Range::all() ) ; 
            
          origNet->setWeights( hereWeights     ) ; 
          origNet->setTau(  hereTau ) ; 
          origNet->setBias( hereBias ) ; 
          origNet->setInitNeuron(  hereInitNeurons ) ; 
          origNet->setNeurons(  hereInitNeurons   ) ; 
      }

      return origNet ;
}



void AlopexDriver::waitForCommand() 
{
    MPI_Comm_rank(MPI_COMM_WORLD,&ad_myid) ; 
    MPI_Barrier(MPI_COMM_WORLD) ;     
    syncData() ; 

    
    MPI_Bcast( &realCommand , 128 ,MPI_CHAR,0,MPI_COMM_WORLD) ;
    
    
    if( strncmp(realCommand,"runapp",strlen(realCommand))==0){
        runapp() ;
	
    } else if( strncmp(realCommand,"startannealer",strlen(realCommand))==0){
        startAnnealer() ;
	
    } else if(ad_myid!=0){
        strcpy(realCommand,"wait") ; 
        waitForCommand() ; 
    }

    // send a command, to all others to do startAnnealer, and see what's missing
}
#endif




const string AlopexDriver::START_SIMWORM = "START_SIMWORM"  ; 
const string AlopexDriver::START_ALOPEXER = "START_ALOPEXER"  ; 
const string AlopexDriver::STOP_ALOPEXER = "STOP_ALOPEXER"  ; 




/* Modeline for ViM {{{
 * vim:set ts=4:
 * vim600:fdm=marker fdl=0 fdc=3:
 * }}} */





