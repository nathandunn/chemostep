
#define CHAR_LENGTH 256

#include <iostream>
using std::cout ; 
using std::endl ; 
using std::ostream ; 
using std::ostringstream ; 

#include <fstream>
using std::ofstream ; 


#include <utility>
using std::pair ; 

#include <string>
using std::string ; 

#include <vector>
using std::vector ; 

#include <memory>
#include <algorithm>
#include <functional>
using namespace std ;

#include <time.h>

// Network
#include <BlitzLiveNet.hpp>
#include <Note.hpp>

// Init Random Number Generator
#include <RNG.hpp> 
#include <blitzdefs.hpp> 
#include <TextEvalTrace.hpp> 

// Annealer 
#include <BlitzEulerWrapPerturber.hpp>   
//#include <SeqResetBlitzNetAnnealer.hpp>   
#include <SeqOneWormBlitzNetAnnealer.hpp>   
#include <SzuTempSchedule.hpp> 
#include <SzuAcceptModel.hpp>
#include <GeometricTempSchedule.hpp> 
#include <MetropolisAcceptModel.hpp>
#include <PowerTempSchedule.hpp> 
#include <AcceptModel.hpp>

// Worm Movement
#include <WormTrack.hpp> 
#include <BaseWorm.hpp> 
#include <TennisCourtAwayShuffler.hpp>   
#include <EvenRadWormShuffler.hpp>   
//#include <UniformNetBehaviorTemplate.hpp>   
#include <TwoInputNetBehaviorTemplate.hpp>   


// Template Movement Models
#include <MovementModelTemplate.hpp>
//#include <UniformFwdMovementTemplate.hpp>
#include <StraightFwdMovementTemplate.hpp>
#include <SharpTurnMovementTemplate.hpp> 
//#include <RicochetMovementTemplate.hpp> 
//#include <ReflectMovementTemplate.hpp> 
#include <RandomReflectMovementTemplate.hpp> 



// Parser stuff
#include <TinyBzNetParser.hpp> 
#include <XmlFileTokenizer.hpp>  
#include <BlitzXmlNetRenderer.hpp> 

// Eval Model
#include <OneWormSimEval.hpp> 
#include <WorstPairOneWormSimEval.hpp> 
#include <BlitzEulerLiveNetEvaluator.hpp>   
#include <BlitzMidPointLiveNetEvaluator.hpp>   
#include <BlitzEulerNoiseLiveNetEvaluator.hpp>   
//#include <BlitzEulerSigLiveNetEvaluator.hpp>   

// oneworm/tennis stuff
#include <TennisCourtMap.hpp>
#include <DogbowlLinRadialMap.hpp>
#include <SimpleWorm.hpp>
#include <OneWormMapSpace.hpp>

// window functions
#include <InflectionWindowFunction.hpp> 
#include <ProbDistribution.hpp>

// gui stuff
#include <TiListParser.hpp>
#include <QtFlatRenderer.h> 
#include <Command.hpp>
#include <AppInterface.hpp>

// plotting
#include <gnuplot_i.hpp>


#ifdef DOMPI
    #include "mpi.h"
    int ad_myid ; 
    int ad_nprocs ; 
    char realCommand[128] = "wait"  ; 
#endif 


#include "TennisDriver.hpp"


/*  ***********************************************************************************
    Constructor */
   
//! Description here.
/*  *********************************************************************************** */
TennisDriver::TennisDriver(string newInterfaceName,string newTypeName,AppInterface* newParent)  :
TiFlatBaseApp(newInterfaceName,newTypeName,newParent) 
,mTrackPlotter(NULL)
,mPlotter(NULL)
,mOrigNet(NULL)
,mOrigEval(NULL)
,mOrigAnneal(NULL)
{
   description = "Kinetic annealer.  Produces 1 to N." ; 
   RNG::initSeed();
  struct timeval t;
  gettimeofday(&t,0);
	srand(t.tv_sec) ; 
}

ofstream* TennisDriver::createOutputFileStream(const char* outputFile) 
{
    ofstream *returnstream = new ofstream( outputFile , ios::out) ; 
    return returnstream ; 
}

void TennisDriver::setDriver( BaseFlatDriver* newDriver  ) 
{
    mDriver = newDriver ; 
}



/// Creates evaluator using the assumption that the network has already been created.  The evaluator is WormSimMeanDistEval() 
OneWormSimEval* TennisDriver::createEvaluator(BlitzLiveNet* prototypeNet,int numWorms,int numRefWorms) {

    // for annealing, bulk worm evaluation, etc.
    if(numWorms==-1){
        numWorms = mNumWorms ; 
        prototypeNet->setTrace(false) ; 
    }
    // for plotting worms
    else{
        prototypeNet->setTrace(true) ; 
    }

    if(mOrigEval==NULL){
        if(mDoWorstPair==true){
            mOrigEval = new WorstPairOneWormSimEval() ; 
        }
        else{
            mOrigEval = new OneWormSimEval() ; 
        }
    }

    mOrigEval->setTarget(mTargetX) ; 
    mOrigEval->setMinDeltaT(mDeltaT) ; 

//    mOrigEval->setRelaxTime(5) ; 
//    mOrigEval->setRelaxLimit(0.01) ; 
//    mOrigEval->setRelaxTime(mRelaxTime) ; 
//    mOrigEval->setRelaxLimit(mRelaxLimit) ; 

    mOrigEval->setNetwork(prototypeNet) ; 

    // SET MAP
//    TennisCourtMap* newMap = NULL ; 
    Map* newMap = NULL ; 
    if(mDoTennisCourtMap==true){
        newMap = new TennisCourtMap(mWidth,mHeight,mTargetX,mLowValue,mTargetValue,mHighValue) ; 
//        newMapSpace->setWormShuffler(new TennisCourtAwayShuffler(newMap,mSpaceFromTarget)) ; 
    }
    else{
        newMap = new DogbowlLinRadialMap(mWidth,mHighValue,mLowValue,mTargetValue,mTargetX) ; 
    }


    // SET MAPSPACE
    OneWormMapSpace* newMapSpace = new OneWormMapSpace( ) ; 
    newMapSpace->setMaxWormCount(numWorms) ; 
    mNumWormSteps =  (int)(  mSimTime / mDeltaT ) ; 
//    cout << "mNumWormSteps[" << mNumWormSteps  << "] " << endl ; 
    newMapSpace->setWormStepCount(mNumWormSteps ) ; 
    newMapSpace->setMap(newMap) ; 

    // SET SHUFFLER
    if(mDoTennisCourtMap==true){
        newMapSpace->setWormShuffler(new TennisCourtAwayShuffler( (TennisCourtMap*) newMap,mSpaceFromTarget)) ; 
    }
    else{
        newMapSpace->setWormShuffler(new EvenRadWormShuffler( mWidth,mNumWorms,  mSpaceFromTarget)) ; 
        //new EvenRadWormShuffler( mDiameter,numWorms,mEdgeBuffer)
    }

    mOrigEval->setMapSpace( newMapSpace) ;  

    // SET WORM
    SimpleWorm* newWorm = new SimpleWorm(newMapSpace) ; 
    BlitzLiveNet* wormNet = new BlitzLiveNet( prototypeNet) ; 

    // is this really necessary?, maybe to set other things
    BlitzNetEvaluator* wormEval = NULL ; 
    if(mOutputNoise > 0.0 || mInputNoise > 0.0){
        wormEval = new BlitzEulerNoiseLiveNetEvaluator( mDeltaT,mOutputSigmoid,wormNet,mInputNoise,mOutputNoise) ; 
    }
    else{
        if(mDoMidMethod==true){
            wormEval = new BlitzMidPointLiveNetEvaluator( mDeltaT,mOutputSigmoid,wormNet) ; 
        }else{
            wormEval = new BlitzEulerLiveNetEvaluator( mDeltaT,mOutputSigmoid,wormNet) ; 
        }
    }
    wormEval->resetTrace( mNumWormSteps*numWorms  , mNumWormSteps*numWorms  ) ; 
    wormNet->setEvaluator( wormEval  ) ; 
    BlitzNetEvaluator* wormBehaviorEval = NULL ; 
    if(mOutputNoise > 0.0 || mInputNoise > 0.0){
        wormBehaviorEval = new BlitzEulerNoiseLiveNetEvaluator( mDeltaT,mOutputSigmoid,wormNet,mInputNoise,mOutputNoise) ; 
    }
    else{
        if(mDoMidMethod==true){
            wormBehaviorEval = new BlitzMidPointLiveNetEvaluator( mDeltaT,mOutputSigmoid,wormNet) ; 
        }
        else{
            wormBehaviorEval = new BlitzEulerLiveNetEvaluator( mDeltaT,mOutputSigmoid,wormNet) ; 
        }
    }
    wormBehaviorEval->resetTrace( mNumWormSteps*numWorms , mNumWormSteps*numWorms ) ; 
   // SET WORM EVAL NETWORK
    newWorm->setBehaviorModel( new UniformNetBehaviorTemplate<SimpleWorm>( wormNet, newWorm, wormBehaviorEval , mNumInputs ) ) ; 
    newWorm->setForwardMovementModel(new StraightFwdMovementTemplate<SimpleWorm>(mForwardVelocity*mDeltaT)) ;  // left and right turning bias
    newWorm->setTurningMovementModel(new SharpTurnMovementTemplate<SimpleWorm>(mDeltaT*50.0,mTurnVelocity*mDeltaT)) ; // sharp-turn value
//    newWorm->setBounceModel(new ReflectMovementTemplate<SimpleWorm>(mTurnVelocity*mDeltaT) ) ; // sharp-turn value
		newWorm->setBounceModel(new RandomReflectMovementTemplate<SimpleWorm>(2.0*mTurnVelocity*mDeltaT) ) ; // sharp-turn value
    newMapSpace->setWorm( newWorm) ; 
    

    return mOrigEval ;
}


BlitzLiveNet* TennisDriver::createNetwork() 
{
    if(mOrigNet==NULL){
        mOrigNet = (BlitzLiveNet*) (new TinyBzNetParser())->parseFile(mNetworkFile) ;   
    }
    else{
        *mOrigNet = *((BlitzLiveNet*) (new TinyBzNetParser())->parseFile(mNetworkFile)) ;   
    }
    mOrigNet->setPerturber( new BlitzEulerWrapPerturber(mWrapValue) ) ; 
    (mOrigNet->getNote())->setNote("description",mDescription) ;

    return mOrigNet; 
}

BlitzNetAnnealer* TennisDriver::createAnnealer() 
{
    if(mOrigAnneal==NULL){
        mOrigAnneal = new SeqOneWormBlitzNetAnnealer( mNumWorms * mVerifyMultiply ) ;
        if(mTempScheduleString=="szu"){
            mTempSchedule = new SzuTempSchedule() ;
            mAcceptModel = new SzuAcceptModel() ; 
        }
        else
        if(mTempScheduleString=="metropolis"){
            mTempSchedule = new GeometricTempSchedule() ;
            mAcceptModel = new MetropolisAcceptModel() ; 
            // set accept model
        }
        else
        if(mTempScheduleString=="power2"){
            mTempSchedule = new PowerTempSchedule(mNumTempSteps,2.0,mHighTemp,mLowTemp) ;
            mAcceptModel = new AcceptModel() ; 
        }

        if(mTempScheduleString=="metropolis" || mTempScheduleString=="szu"){
            // set temp data
            ((TempSchedule*) mTempSchedule)->setNumPoints(mNumTempSteps) ; 
            ((TempSchedule*) mTempSchedule)->setHighTemp(mHighTemp) ; 
            ((TempSchedule*) mTempSchedule)->setLowTemp(mLowTemp) ; 

            ((MetropolisAcceptModel*) mAcceptModel)->setConstant(mAcceptConstant) ; 
        }
    }



   
    // set annealer data
    mOrigAnneal->setSetBack(mSetBack) ; 
    mOrigAnneal->setTempSchedule(mTempSchedule) ; 
    mOrigAnneal->setIterPerTemp(mNumItersPerTemp) ; 
    mOrigAnneal->setAcceptModel(mAcceptModel) ; 
    return mOrigAnneal ;
}



void TennisDriver::setRenderer(Renderer* newRenderer) 
{
    mRenderer = newRenderer ; 
}


bool TennisDriver::createLocalMaps() 
{
    string APP_NAME = "APP/SIMWORM" ; 
    #ifdef DOMPI
    MPI_Comm_size(MPI_COMM_WORLD,&ad_nprocs) ; 
    if(ad_nprocs==1)
    #endif
    addCommandToMap(PLOT_WORM) ; 
    addCommandToMap(PERTURB_TEST) ; 
    addCommandToMap(EVAL_TEST) ; 
    addCommandToMap(START_ANNEALER) ; 
    addCommandToMap(QUIT_ANNEALER) ; 


    // ANNEALING DESCRIPTION
    addOptionToMap("01_description",OPT_STRING,&mDescription,APP_NAME,"Description") ; 

    // NETWORK VALUES
    addOptionToMap("01a_network",OPT_FILE_LOAD,&mNetworkFile,APP_NAME,"Network File") ; 
    mRelaxTime = 200; 
    mRelaxLimit= 0.01 ; 
    addOptionToMap("01b_sigmoid",OPT_DOUBLE,&mOutputSigmoid,APP_NAME,"Output Sigmoid (1.0)") ; 
//    addOptionToMap("01bb_inputnoise",OPT_DOUBLE,&mInputNoise,APP_NAME,"Input Noise") ; 
    mInputNoise = 0.0 ; 
    addOptionToMap("01bc_outputnoise",OPT_DOUBLE,&mOutputNoise,APP_NAME,"Output Noise") ; 

    // SIGMOID LOOKUP VALUES
//    addOptionToMap("02bbb_sigmoidlimit",OPT_DOUBLE,&mSigLimit,APP_NAME,"Sig Limit (8.0)") ; 
//    addOptionToMap("02bbbb_tablesize",OPT_INT,&mTableSize,APP_NAME,"Table Size (1024)") ; 
    mSigLimit = 20.0 ;   
    mTableSize = 8192 ; 
    
    // WORMSIM VALUES VALUES
    addOptionToMap("01c_numworms",OPT_INT,&mNumWorms,APP_NAME,"Number of Worms") ; 
    addOptionToMap("02_numinputs",OPT_INT,&mNumInputs,APP_NAME,"Number of Inputs") ; 
    addOptionToMap("02a_doworst",OPT_BOOL,&mDoWorstPair,APP_NAME,"Worst pair eval") ;
    addOptionToMap("02aaa_simtime",OPT_DOUBLE,&mSimTime,APP_NAME,"Run time") ;
//    mNumWormSteps = 1200 ; 
//    addOptionToMap("02aa_fwd",OPT_DOUBLE,&mForwardVelocity,APP_NAME,"Fwd Vel") ;
//    addOptionToMap("02ab_turn",OPT_DOUBLE,&mTurnVelocity,APP_NAME,"Turn Vel") ;
    mForwardVelocity = 0.015 ; 
    mTurnVelocity = 0.011 ; 
//    mDeltaT = 1.0 ; 
    addOptionToMap("02aab_deltaT",OPT_DOUBLE,&mDeltaT,APP_NAME,"Delta T") ; 


    // MAP VALUES
    addOptionToMap("02b_tenniscourt",OPT_BOOL,&mDoTennisCourtMap,APP_NAME,"Tennis Court Map?") ; 
    addOptionToMap("03_highvalue",OPT_DOUBLE,&mHighValue,APP_NAME,"High Map Value") ; 
//    addOptionToMap("03b_midvalue",OPT_DOUBLE,&mTargetValue,APP_NAME,"Target Map Value") ; 
    mTargetValue = 0.5 ; 
    addOptionToMap("03c_lowvalue",OPT_DOUBLE,&mLowValue,APP_NAME,"Low Map Value") ; 
//    mLowValue = -2.5 ; 
    addOptionToMap("04_midrad",OPT_DOUBLE,&mTargetX,APP_NAME,"Target X") ; 
//    mTargetX = 15.0 ; 
    addOptionToMap("04b_width",OPT_DOUBLE,&mWidth,APP_NAME,"Map Width") ; 
//    mWidth = 30.0 ; 
//    addOptionToMap("04b_height",OPT_DOUBLE,&mHeight,APP_NAME,"Map Height") ; 
	mHeight = 30.0 ; 
    addOptionToMap("04c_spacefromtarget",OPT_DOUBLE,&mSpaceFromTarget,APP_NAME,"Space from Target") ; 
//    mSpaceFromTarget = 2.5  ; 


    // ERROR WINDOW VALUES
//    addOptionToMap("04c0_laststeps",OPT_INT,&mIgnoreLastSteps,APP_NAME,"Last Steps to Ignore") ; 
    mIgnoreLastSteps = 0 ; 


    // ANNEALER VALUES
    addOptionToMap("08a_numnetwork",OPT_INT,&mNumNetworks,APP_NAME,"Number of Networks") ; 
    mTempType = new vector<string>() ; 
    mTempType->push_back("szu") ; 
    mTempType->push_back("metropolis") ; 
    mTempType->push_back("power2") ; 
    addOptionToMap("08b_type",LIST_TYPE,&mTempScheduleString,APP_NAME,"Temp Schedulte Type", (new TiListParser())->createList(mTempType) ) ; 
    addOptionToMap("08c_hightemp",OPT_DOUBLE,&mHighTemp,APP_NAME,"Annealer high temp") ; 
    addOptionToMap("09a_lowtemp",OPT_DOUBLE,&mLowTemp,APP_NAME,"Annealer low temp cutoff") ; 
    addOptionToMap("09aa_tempConst",OPT_DOUBLE,&mAcceptConstant,APP_NAME,"Accept Constant") ; 
    addOptionToMap("09b_iterspertemp",OPT_INT,&mNumItersPerTemp,APP_NAME,"Annealer iters per temp") ; 
    addOptionToMap("09c_setback",OPT_INT,&mSetBack,APP_NAME,"Annealer setback") ; 
//    mSetBack = 0 ; 
    addOptionToMap("09d_wrapvalue",OPT_DOUBLE,&mWrapValue,APP_NAME,"Wrap Value (max)") ; 
//    mWrapValue = 20 ; 
    addOptionToMap("100_tempsteps",OPT_INT,&mNumTempSteps,APP_NAME,"Min anneal steps") ; 
    addOptionToMap("101_mVerifyMultiply",OPT_INT,&mVerifyMultiply,APP_NAME,"Verify=worms*N") ; 


    // plot stuff
    mOutputList = new vector<string>() ; 
    mOutputList->push_back("x11") ; 
    mOutputList->push_back("pdf") ; 
    mOutputList->push_back("png") ; 
    addOptionToMap("11_outputtype",LIST_TYPE,&mOutputType,APP_NAME,"Output Type",(new TiListParser())->createList(mOutputList) ) ; 

    // output options
    addOptionToMap("13_outputfile",OPT_FILE_SAVE,&mOutputFile,APP_NAME,"Annealer output") ; 
    addOptionToMap("14_bestnetwork",OPT_FILE_SAVE,&mBestNetworkFile,APP_NAME,"Best net output") ; 
    addOptionToMap("15_midmethod",OPT_BOOL,&mDoMidMethod,APP_NAME,"Mid method") ; 
	mQuitAfterAnneal = true ; 

    
    return true ; 
}


/*  ***********************************************************************************
    doLocalCommand() */
   
//! Description here.
/*  *********************************************************************************** */
string TennisDriver::doLocalCommand(Command *theCommand) 
{
    mRenderer->savePreferences() ; 

    string theName = theCommand->getName()  ;


    if(theName==START_ANNEALER){
        #ifdef DOMPI
           strcpy(realCommand,"startannealer") ; 
           waitForCommand() ; 
        #else
           startAnnealer() ; 
        #endif 
    } else 
    if(theName==PERTURB_TEST){
        #ifdef DOMPI
           strcpy(realCommand,"perturbtest") ; 
           waitForCommand() ; 
        #else
           perturbTest() ; 
       #endif
    } else 
    if(theName==EVAL_TEST){
        #ifdef DOMPI
           strcpy(realCommand,"evaltest") ; 
           waitForCommand() ; 
        #else
           evalTest() ; 
       #endif
    } else 
    if(theName==PLOT_WORM){
           plotWorm() ; 
    } else 
    if(theName==QUIT_ANNEALER){
        #ifdef DOMPI
           strcpy(realCommand,"quitannealer") ; 
           waitForCommand() ; 
        #else
           quitAnnealer() ; 
        #endif 
    }
    
    return "it runned  "; 
}


/// This method evaluates a network N times.  
bool TennisDriver::evalTest() 
{
#ifdef DOMPI
    if(ad_myid==0)
#endif
    cout << "start init" << endl ; 
    BlitzLiveNet* thisNet = createNetwork() ; 
    thisNet->setEvaluator( createEvaluator(thisNet)) ; 
    thisNet->eval() ; 
    thisNet->setValid(false) ; 
#ifdef DOMPI
    if(ad_myid==0)
#endif
    cout << "finish init" << endl ; 

    int numIters = 200 ; 

    clock_t initTime = time(NULL) ; 
    Vector errorValues(numIters) ; 
    for(int i = 0 ; i < numIters ; i++){
        errorValues(i) = thisNet->eval() ;
        thisNet->setValid(false) ; 
    }


    double diffTime = difftime(time(NULL),initTime) ; 
#ifdef DOMPI
        if(ad_myid==0){
#endif
    cout << "avg error: " << mean(errorValues) << endl ; 
    cout << "min error: " << min(errorValues) << endl ; 
    cout << "max error: " << max(errorValues) << endl ; 
    cout << "total time: " << diffTime << endl ; 
    cout << "avg time/eval: " << (diffTime/((float) numIters)) << endl ; 
#ifdef DOMPI
        }
#endif


#ifdef DOMPI
    if(ad_myid!=0){
        strcpy(realCommand,"wait") ;
        waitForCommand() ;
    }
#endif


}



///  In this method, the network is evaluated a series of times after being perturbed at a particular temperature.  Produce dialog querying # of iterations of pre-perturb, post-perturb as well as the size/temp of the perturbation 
bool TennisDriver::perturbTest() 
{
#ifdef DOMPI
    if(ad_myid==0)
#endif
    cout << "start init" << endl ; 
    BlitzLiveNet* thisNet = createNetwork() ; 
    thisNet->setEvaluator( createEvaluator(thisNet)) ; 
    thisNet->eval() ; 
    thisNet->setValid(false) ; 
#ifdef DOMPI
    if(ad_myid==0)
#endif
    cout << "finish init" << endl ; 

    int prePerturb = 5 ; 
    int postPerturb = 5 ; 
    double perturbValue = mHighTemp ; 



    clock_t initTime = time(NULL) ; 
    double netValue ; 
#ifdef DOMPI
    if(ad_myid==0)
#endif
    cout << "********** PRE-PERTURB start *********" <<  endl ; 
    for(int i = 0 ; i < prePerturb ; i++){
        netValue = thisNet->eval() ;
#ifdef DOMPI
        if(ad_myid==0)
#endif
        cout << i << " network eval: " << netValue << endl ; 
        thisNet->setValid(false) ; 
    }
#ifdef DOMPI
        if(ad_myid==0)
#endif
    cout << "********** PRE-PERTURB finish *********" <<  endl ; 

//    BlitzXmlNetRenderer* renderer = new BlitzXmlNetRenderer() ; 
#ifdef DOMPI
    if(ad_myid==0){
#endif
//    cout << "PRE-perturb: " << thisNet << endl << renderer->render(thisNet) << endl ; 
    cout << "Perturb at: " << perturbValue << endl ; 
#ifdef DOMPI
    }
#endif
    if(postPerturb>0){
         thisNet->perturb(perturbValue) ; 
         (thisNet->getEvaluator())->setNetwork(thisNet) ; 
    }
//    cout << "POST-perturb: " << thisNet << endl << renderer->render(thisNet) << endl ; 
    
#ifdef DOMPI
        if(ad_myid==0)
#endif
    cout << "********** POST-PERTURB start *********" <<  endl ; 
    for(int i = 0 ; i < postPerturb ; i++){
        netValue = thisNet->eval() ;
#ifdef DOMPI
        if(ad_myid==0)
#endif
        cout << i << " network eval: " << netValue << endl ; 
        thisNet->setValid(false) ; 
    }
#ifdef DOMPI
        if(ad_myid==0)
#endif
    cout << "********** POST-PERTURB finish *********" <<  endl ; 

    double diffTime = difftime(time(NULL),initTime) ; 
#ifdef DOMPI
        if(ad_myid==0){
#endif
    cout << "total time: " << diffTime << endl ; 
    cout << "avg time/eval: " << (diffTime/(prePerturb+postPerturb)) << endl ; 
#ifdef DOMPI
        }
#endif

#ifdef DOMPI
    if(ad_myid!=0){
        strcpy(realCommand,"wait") ;
        waitForCommand() ;
    }
#endif


   return true ;  
}


void TennisDriver::quitAnnealer() 
{
        #ifdef DOMPI
           MPI_Barrier(MPI_COMM_WORLD) ; 
           MPI_Abort(MPI_COMM_WORLD,0) ; 
           MPI_Finalize() ; 
           exit(0) ; 
        #else
           exit(0) ; 
        #endif 

}



bool TennisDriver::startAnnealer() 
{
    vector<string>* outputAnnealerNames = NULL ; 
    vector<string>* outputNetworkNames =  NULL ; 
    outputAnnealerNames = XmlFileTokenizer::createFileNames( mOutputFile , mNumNetworks) ; 
    outputNetworkNames = XmlFileTokenizer::createFileNames( mBestNetworkFile, mNumNetworks) ; 
    // init stuff
    createNetwork() ; // loads mOrigNet from file
    mOrigAnneal = (SeqBlitzNetAnnealer*) createAnnealer() ; 
    mOrigEval = createEvaluator(mOrigNet) ; 
    
    for(int i = 0 ; i < mNumNetworks ; i++){
    // reload network here from file
        createNetwork() ; // loads mOrigNet from file
        mOrigNet->setEvaluator( mOrigEval ) ; // don't need to call setNetwork, as its called in evaluateWorms( . . . )
        mOrigAnneal->setAnnealingTarget(mOrigNet)  ; 
        mOutputStream = createOutputFileStream( ((*outputAnnealerNames)[i]).c_str() ) ; 

        if(mFinalNet==NULL){
            mFinalNet =   new BlitzLiveNet( (BlitzLiveNet*) ( ((SeqBlitzNetAnnealer*) mOrigAnneal)->anneal(mOutputStream, (*outputNetworkNames)[i]  )  )  ) ; 
        }
        else{
            *mFinalNet =   *( (BlitzLiveNet*) ( ((SeqBlitzNetAnnealer*) mOrigAnneal)->anneal(mOutputStream, (*outputNetworkNames)[i]  )  )  ) ; 
        }
        mOutputStream->close() ; 
        mOutputStream = NULL ;

    }


    if(mQuitAfterAnneal){
        // this is fine here, since all threads will hit this point
        quitAnnealer() ; 
    }
    return true ; 
}



void TennisDriver::plotPetriTracks(vector<double>* xTracks,vector<double>* yTracks,DogbowlLinRadialMap* newMap,string titleName/*""*/) 
{
    double targetRadius =  mTargetX  ; 
    double diameter = newMap->getDiameter() ; 
    ostringstream* commands = NULL ; 


      mTrackPlotter->cmd( "set size square 1,1" ) ; 
      mTrackPlotter->cmd("set xlabel 'X'") ; 
      mTrackPlotter->cmd("set ylabel 'Y'") ; 
      mTrackPlotter->cmd("set grid") ; 
      mTrackPlotter->cmd("unset key") ; 
      commands = new ostringstream() ; 
      // remainder of title
      // can also get it from others, as well
      *commands << "set title \"" << titleName <<  "\\n" ; 
      *commands << "targetrad=" << targetRadius << "\" ; " ; 
      *commands << "set xrange [0:" << diameter << "] ;" ; 
      *commands << "set yrange [0:" << diameter << "] ;" ; 
      mTrackPlotter->cmd( (commands->str()).c_str() ) ; 
      mTrackPlotter->cmd( "set multiplot ; " ) ; 
      mTrackPlotter->plot_xy( *(new vector<double>(*xTracks)),  *(new vector<double>(*yTracks)),"Worm Track" ) ; 
      mTrackPlotter->cmd( "replot" ) ; 

     
      commands = new ostringstream() ; 

      *commands << "plot [0:" << diameter << "] sqrt( -(x-"<< diameter/2.0 << ")**2 + (" << diameter/2.0 << ")**2)+" << diameter/2.0 << " ; " ; 
      // bottom circle
      *commands << "plot [0:" << diameter << "] -sqrt( -(x-"<< diameter/2.0 << ")**2 + (" << diameter/2.0 << ")**2)+" << diameter/2.0 << " ; " ; 

      // plot the target radii
      // top circle
      *commands << "plot [0:" << diameter << "] sqrt( -(x-"<< diameter/2.0 << ")**2 + (" << targetRadius << ")**2)+" << diameter/2.0 << " ; " ; 
      // bottom circle
      *commands << "plot [0:" << diameter << "] -sqrt( -(x-"<< diameter/2.0 << ")**2 + (" << targetRadius << ")**2)+" << diameter/2.0 << " ; " ; 
      mTrackPlotter->cmd( (commands->str()).c_str() ) ; 

      // unset 
      mTrackPlotter->cmd("set nomultiplot") ; 


      // unset 
      mTrackPlotter->cmd("set nomultiplot ; ") ; 
}



void TennisDriver::plotTennisTracks(vector<double>* xTracks,vector<double>* yTracks,TennisCourtMap* newMap,string titleName) 
{
    double width = newMap->getWidth() ; 
    double height = newMap->getHeight() ; 
    double targetX = newMap->getTargetX() ; 
    ostringstream* commands = NULL ; 


      mTrackPlotter->cmd( "set size square 1,1" ) ; 
      mTrackPlotter->cmd("set xlabel 'X'") ; 
      mTrackPlotter->cmd("set ylabel 'Y'") ; 
      mTrackPlotter->cmd("set grid") ; 
      mTrackPlotter->cmd("unset key") ; 
      commands = new ostringstream() ; 
      // remainder of title
      // can also get it from others, as well
      *commands << "set title \"" << titleName <<  "\\n" ; 
      *commands << "targetX=" << targetX << "\" ; " ; 
      *commands << "set xrange [0:" << width << "] ;" ; 
      *commands << "set yrange [0:" << height << "] ;" ; 
      mTrackPlotter->cmd( (commands->str()).c_str() ) ; 
      mTrackPlotter->cmd( "set multiplot ; " ) ; 
      mTrackPlotter->plot_xy( *(new vector<double>(*xTracks)),  *(new vector<double>(*yTracks)),"Worm Track" ) ; 

     
      // set multiplot to draw in the other garbage
      // PLOT TARGETX 
      vector<double>* xData = new vector<double>() ; 
      vector<double>* yData = new vector<double>() ; 
      xData->push_back(mTargetX) ; 
      xData->push_back(mTargetX) ; 
      yData->push_back(0) ; 
      yData->push_back(mHeight) ; 
      mTrackPlotter->plot_xy( *xData, *yData, "Target X" ) ; 

      // PLOT SPACE-STARTING X
      (*xData)[0] = (mTargetX-mSpaceFromTarget) ; 
      (*xData)[1] = (mTargetX-mSpaceFromTarget) ; 
      mTrackPlotter->plot_xy( *xData, *yData, "W start-X" ) ; 

      // PLOT SPACE-STARTING X
      (*xData)[0] = (mTargetX+mSpaceFromTarget) ; 
      (*xData)[1] = (mTargetX+mSpaceFromTarget) ; 
      mTrackPlotter->plot_xy( *xData, *yData, "E start-X" ) ; 


      // unset 
      mTrackPlotter->cmd("set nomultiplot ; ") ; 
      
}

void TennisDriver::setOutput(Gnuplot* aPlot,string title) 
{
    ostringstream* thisStream = new ostringstream() ; 

    thisStream->str("") ; 
    *thisStream << "set terminal " << mOutputType << " ; " << endl ; 
    *thisStream << "set output \"" << title << "." << mOutputType << "\" ; " << endl ; 

    aPlot->cmd(  (thisStream->str()).c_str() ) ; 
}

pair<vector<double>*,vector<double>*>* TennisDriver::evalWorm() 
{
    createNetwork() ; 
    mOrigNet->setEvaluator( createEvaluator(mOrigNet,1,1)) ; // create evaluator with 1 worm
    mTracer = new TextEvalTrace() ; 
    mTracer->setTimeDelimiter(",") ; 
    mTracer->setEvaluator( mOrigNet->getEvaluator() ) ; 
    cout << "eval: " << mOrigNet->eval() << endl ; 

    vector<double>* xVec = new vector<double>() ; 
    vector<double>* yVec = new vector<double>() ; 

    vector<WormTrack*>* wormTracks = ( (OneWormSimEval*) mOrigNet->getEvaluator())->getWormTracks() ; 
    for(int wormNumber = 0 ; wormNumber < wormTracks->size() ; wormNumber++){
        for(int stepNumber = 0 ; stepNumber < ((*wormTracks)[wormNumber])->rows() ; stepNumber++){
            xVec->push_back(  (*(*wormTracks)[wormNumber])(stepNumber,0)  ) ; 
            yVec->push_back(  (*(*wormTracks)[wormNumber])(stepNumber,1)  ) ; 
        }
    }

    return new pair<vector<double>*,vector<double>*>(xVec,yVec) ; 
}

vector<double>* TennisDriver::calculateInputFromTracks(pair<vector<double>*,vector<double>*>* tracks) 
{
    vector<double>* xVec = tracks->first ; 
    vector<double>* yVec = tracks->second ; 
    int numPoints = xVec->size() ; 
    vector<double>* input = new vector<double>(numPoints) ; 
    Map* map = (((OneWormSimEval*) mOrigNet->getEvaluator())->getMapSpace())->getMap() ;  
    for(int i = 0 ; i < numPoints ; i++){
       (*input)[i]  = map->getValue( (*xVec)[i],(*yVec)[i] ) ; 
    }

    return input ; 
}


/// This method dumps out worm tracks, neural activity and input data to a file kind of named for the input network.
pair<vector<double>*,vector<double>*>* TennisDriver::dumpWorm() 
{
    pair<vector<double>*,vector<double>*>* trackPair = evalWorm() ; 
    vector<double>* xVec = trackPair->first ; 
    vector<double>* yVec = trackPair->second ; 
    vector<double>* input = calculateInputFromTracks(trackPair) ; 
   

    
    int numTimeSteps = xVec->size() ; 
    
    vector<vector<double>*>* neuronTrace = ( ( (OneWormSimEval*) mOrigNet->getEvaluator())->getWormEval())->getLastFullTraceAsSeries() ; 
    int numNeurons = neuronTrace->size() ; 

    string outputFile = mNetworkFile.substr(mNetworkFile.find_last_of("/")+1) ; 
    outputFile = outputFile.substr(0,outputFile.find_last_of("."))+"_trace.txt" ; 
    ofstream *of = createOutputFileStream( outputFile.c_str() ) ; 


    // init header
    *of << "XPos YPos Input " ; 
    for(int neuronNum = 0 ; neuronNum < numNeurons ; neuronNum++){
        *of << "neuron"  << neuronNum << " " ; 
    }
    *of << endl ; 

    
    for(int timeStep = 0 ; timeStep < numTimeSteps ; timeStep++){
        *of << (*xVec)[ timeStep] << " "  ; 
        *of << (*yVec)[ timeStep] << " " ; 
        *of << (*input)[ timeStep] << " " ; 
        for(int neuronNum = 0 ; neuronNum < numNeurons ; neuronNum++){
            *of << (*((*neuronTrace)[neuronNum]))[timeStep] << " " ; 
        }
        *of << endl ; 
    }

    of->close() ; 
    delete of ; 

    return trackPair ; 
}


/// This method plots a single worm track using gnuplot.
void TennisDriver::plotWorm() 
{
    // we do it this way, because we need the SAME for the file
    // and the plot
    pair<vector<double>*,vector<double>*>* trackPair = dumpWorm() ;
    vector<double>* xVec = trackPair->first ; 
    vector<double>* yVec = trackPair->second ; 
    

	if(mTrackPlotter==NULL){
        mTrackPlotter = new Gnuplot("lines") ; 
    }
    else{
        mTrackPlotter->reset_plot() ; 
    }


    // create title
    mTitleName = mNetworkFile.substr(mNetworkFile.find_last_of("/")+1) ; 
    setOutput( mTrackPlotter,mTitleName+"worm") ; 

    // plot to screen
    if (mDoTennisCourtMap==true){
        plotTennisTracks(xVec,yVec, (TennisCourtMap*) (((OneWormSimEval*) mOrigNet->getEvaluator())->getMapSpace())->getMap(),mTitleName) ; 
    }
    else{
        plotPetriTracks(xVec,yVec, (DogbowlLinRadialMap*) (((OneWormSimEval*) mOrigNet->getEvaluator())->getMapSpace())->getMap(),mTitleName) ; 
    }


    plotNeurons() ; 

    // FOR NEW PLOT
//    mTrackPlotter = NULL ; 
//    delete mTrackPlotter ; 

}

void TennisDriver::plotNeurons() 
{
    if(mPlotter==NULL){
//        mPlotter = new Gnuplot("lines") ; 
//        mPlotter = new Gnuplot("dots") ; 
        mPlotter = new Gnuplot("points") ; 
    }
    else{
        mPlotter->reset_plot() ; 
    }
    setOutput( mPlotter ,mTitleName ) ; 

    mPlotter->cmd("set ytics(0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9)") ; 
    mPlotter->cmd("set grid") ; 
//    mPlotter->cmd("set title 'Neuron Pulse Response'") ; 
    mPlotter->cmd("set xlabel 'Time(s)'") ; 
    mPlotter->cmd("set ylabel 'Neural Activity'") ; 

    ostringstream *commands = new ostringstream() ; 
    *commands << "set title '" << mTitleName <<  "' ;" ; 
    mPlotter->cmd( (commands->str()).c_str()) ; 

    vector<vector<double>*>* sliceTrace = ( ( (OneWormSimEval*) mOrigNet->getEvaluator())->getWormEval())->getLastFullTraceAsSeries() ; 
    ostringstream* nameString = new ostringstream() ; 
    for(int i = 0 ; i < sliceTrace->size() ; i++){
        nameString->str("") ; 
        *nameString  << "neuron " << i ; 
        mPlotter->plot_x( *((*sliceTrace)[i]) ,nameString->str() ) ; 
    }



}




#ifdef DOMPI
/// Sync's data from the gui input
void TennisDriver::syncData() 
{
    char fileName[CHAR_LENGTH]; 

    // ANNEAL DESCRIPTION
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
    MPI_Bcast(&mInputNoise,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mOutputNoise,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 

    // SIG LOOKUP VALUES
    MPI_Bcast(&mSigLimit,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mTableSize,1,MPI_INT,0,MPI_COMM_WORLD) ; 

    // WORMSIM VALUES VALUES
    MPI_Bcast(&mNumWormSteps,1,MPI_INT,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mSimTime,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mNumWorms,1,MPI_INT,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mForwardVelocity,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mTurnVelocity,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mDeltaT,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mNumInputs,1,MPI_INT,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mDoWorstPair,1,MPI_INT,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mDoTennisCourtMap,1,MPI_INT,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mDoMidMethod,1,MPI_INT,0,MPI_COMM_WORLD) ; 


    // MAP VALUES
    MPI_Bcast(&mHighValue,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mTargetValue,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mLowValue,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mTargetX,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mWidth,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mHeight,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mSpaceFromTarget,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 

    // ERROR WINDOW VALUES
    MPI_Bcast(&mIgnoreLastSteps,1,MPI_INT,0,MPI_COMM_WORLD) ; 

    // ANNEALER VALUES
    MPI_Bcast(&mNumNetworks,1,MPI_INT,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mHighTemp,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mLowTemp,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mAcceptConstant,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mNumItersPerTemp,1,MPI_INT,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mSetBack,1,MPI_INT,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mWrapValue,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mNumTempSteps,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mVerifyMultiply,1,MPI_INT,0,MPI_COMM_WORLD) ; 

    if(ad_myid==0) sprintf(fileName,"%s",mOutputFile.c_str()) ; 
    MPI_Bcast(fileName, CHAR_LENGTH,MPI_CHAR,0,MPI_COMM_WORLD) ; 
    if(ad_myid!=0) mOutputFile=fileName ; 
    if(ad_myid==0) sprintf(fileName,"%s",mBestNetworkFile.c_str()) ; 
    MPI_Bcast(fileName, CHAR_LENGTH,MPI_CHAR,0,MPI_COMM_WORLD) ; 

    if(ad_myid!=0) mBestNetworkFile=fileName ; 
    if(ad_myid==0) sprintf(fileName,"%s",mTempScheduleString.c_str()) ; 
    MPI_Bcast(fileName, CHAR_LENGTH,MPI_CHAR,0,MPI_COMM_WORLD) ; 

    if(ad_myid!=0) mTempScheduleString=fileName ; 
    MPI_Bcast(&mQuitAfterAnneal,1,MPI_INT,0,MPI_COMM_WORLD) ; 



}

/// Synchronizes the networks from the original network.
BlitzLiveNet* TennisDriver::syncNet(BlitzLiveNet* origNet) 
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



void TennisDriver::waitForCommand() 
{
    MPI_Comm_rank(MPI_COMM_WORLD,&ad_myid) ; 
    MPI_Barrier(MPI_COMM_WORLD) ;     
    syncData() ; 

    
    MPI_Bcast( &realCommand , 128 ,MPI_CHAR,0,MPI_COMM_WORLD) ;
    
	
    if( strncmp(realCommand,"startannealer",strlen(realCommand))==0){
        startAnnealer() ;
    } else 
    if( strncmp(realCommand,"perturbtest",strlen(realCommand))==0){
        perturbTest() ;
    } else 
    if( strncmp(realCommand,"evaltest",strlen(realCommand))==0){
        evalTest() ;
    } else 
    if( strncmp(realCommand,"quitannealer",strlen(realCommand))==0){
        quitAnnealer() ; 
    } else 
    if(ad_myid!=0){
        strcpy(realCommand,"wait") ; 
        waitForCommand() ; 
    }



    // send a command, to all others to do startAnnealer, and see what's missing
}
#endif




const string TennisDriver::START_ANNEALER = "START_ANNEALER"  ; 
const string TennisDriver::QUIT_ANNEALER = "QUIT_ANNEALER"  ; 
const string TennisDriver::PERTURB_TEST = "PERTURB_TEST"  ; 
const string TennisDriver::EVAL_TEST = "EVAL_TEST"  ; 
const string TennisDriver::PLOT_WORM = "PLOT_WORM"  ; 




/* Modeline for ViM {{{
 * vim:set ts=4:
 * vim600:fdm=marker fdl=0 fdc=3:
 * }}} */








