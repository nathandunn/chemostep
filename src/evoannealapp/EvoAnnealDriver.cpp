
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

#include <float.h>
#include <time.h>

// model stuff
#include <BlitzLiveNet.hpp>
#include <RNG.hpp> 
#include <StepFeeder.hpp>   
#include <SetFeeder.hpp>   
#include <FileFeeder.hpp>   
#include <MapSpace.hpp>   
#include <UniformNetBehaviorModel.hpp>   
#include <EvenRadWormShuffler.hpp>   
//#include <SetRadWormShuffler.hpp>   
#include <BlitzEulerLiveNetEvaluator.hpp>   
#include <BlitzEulerWrapPerturber.hpp>   
//#include <SeqBlitzNetAnnealer.hpp>   
#include <SeqResetBlitzNetAnnealer.hpp>   
#include <SzuTempSchedule.hpp> 
//#include <MomentumPowerTempSchedule.hpp> 
//#include <Momentum2PowerTempSchedule.hpp> 
#include <UniformFwdMovement.hpp> 
#include <SharpTurnMovementModel.hpp> 
#include <TextEvalTrace.hpp> 
#include <TinyBzNetParser.hpp> 
#include <BlitzXmlNetRenderer.hpp> 
#include <LinRadialMap.hpp> 
#include <DogbowlLinRadialMap.hpp> 
#include <WormMapStats.hpp> 
#include <WormSimEval.hpp> 
//#include <WormSimSqrtRadDistEval.hpp> 
#include <WormSimProbTracks.hpp> 
#include <InflectionWindowFunction.hpp> 
#include <AnnealerThread.hpp> 
#include <Worm.hpp>
//#include <TtestAcceptModel.hpp>
#include <SzuAcceptModel.hpp>
#include <MetropolisAcceptModel.hpp>
#include <ProbDistribution.hpp>
#include <Note.hpp>
#include <PerturbFrame.h>
#include <evoannealapp.hpp>

// LOGGING DEBUG
#include <Logger.hpp>

// gui stuff
#include <qmessagebox.h>
#include "QtFlatRenderer.h" 
#include <TiAppParser.hpp>
#include <TiListParser.hpp>
#include <AppInterfaceXmlEngine.hpp>
#include <TinyAppInterfaceXmlEngine.hpp>
#include <Command.hpp>
#include <AppInterface.hpp>
#include <Option.hpp>

// for plotting
#include <gnuplot_i.hpp>


#ifdef DOMPI
    #include "mpi.h"
    int ad_myid ; 
    int ad_nprocs ; 
    char realCommand[128] = "wait"  ; 
#endif 


#include "EvoAnnealDriver.hpp"


/*  ***********************************************************************************
    Constructor */
   
//! Description here.
/*  *********************************************************************************** */
EvoAnnealDriver::EvoAnnealDriver(string newInterfaceName,string newTypeName,AppInterface* newParent)  :
TiFlatBaseApp(newInterfaceName,newTypeName,newParent) 
,mTrackPlotter(NULL)
,mProbPlotter(NULL)
,mOrigNet(NULL)
,mOrigEval(NULL)
,mOrigAnneal(NULL)
{
   description = "Kinetic annealer.  Produces 1 to N." ; 
   RNG::initSeed();
}

ofstream* EvoAnnealDriver::createOutputFileStream(const char* outputFile) 
{
    ofstream *returnstream = new ofstream( outputFile , ios::out) ; 
    return returnstream ; 
}

void EvoAnnealDriver::setDriver( BaseFlatDriver* newDriver  ) 
{
    mDriver = newDriver ; 
}



/// Creates evaluator using the assumption that the network has already been created.  The evaluator is WormSimMeanDistEval() 
WormSimEval* EvoAnnealDriver::createEvaluator(BlitzLiveNet* prototypeNet,int numWorms,int numRefWorms) {

    if(numWorms==-1){
        numWorms = mNumWorms ; 
    }
    if(numRefWorms==-1){
        numRefWorms = mRefWorms ;
    }

    if(mOrigEval==NULL){
        mOrigEval  = new WormSimProbTracks(numWorms,mNumWormSteps,prototypeNet,new DogbowlLinRadialMap(mDiameter,mHighMapValue,mLowMapValue,mMidMapValue,mMidMapRadius),mForwardVelocity,mTurnVelocity,mDeltaT,mOutputSigmoid,new EvenRadWormShuffler( mDiameter,numWorms,mEdgeBuffer),mOptimumRadius,mLastSteps,mBinSize,new InflectionWindowFunction(0,mWindow,mWindowPower,1,0,mInflectionRatio),numRefWorms,mSpacing,mDieOnEdge, createRefEval(prototypeNet,numRefWorms) ) ;    
        vector<double>* relaxVector = new vector<double>(1) ; 
        (*relaxVector)[0] = 0.5 ; 
        mOrigEval->setRelaxValue(relaxVector) ; 
        mOrigEval->setRelaxTime(mRelaxTime) ; 
//        mOrigEval->setRelaxLimit(mRelaxLimit) ; 
        mOrigEval->setRelaxDeltaT(1.0) ; 
        mOrigEval->setRelaxTau(3.0) ; 
    //    mOrigEval->setRelaxLimit(0.01) ; 
    //    mOrigEval->setGlobalSigLimit(8.0) ; 
        mOrigEval->resetTrace(mNumItersPerTemp,mNumItersPerTemp) ; 
    }
    else{

        
        mOrigEval->setNetwork(prototypeNet) ; 
    //    mOrigEval->setRefEval(createRefEval(prototypeNet)) ; 
    }
    

    return mOrigEval ;
}



/************************************************************************************
    runapp() */
   
//! Create a network and an evaluator. Make the call to evaluate the network.
/************************************************************************************ */

void *EvoAnnealDriver::runapp(){

    int wormState = MapSpace::SOME_RUNNING ; 

    createNetwork() ; // creates mOrigNet stuff
    mOrigNet->setEvaluator( createEvaluator(mOrigNet)) ; 

    BlitzXmlNetRenderer* renderer = new BlitzXmlNetRenderer() ; 
    // LOGGING DEBUG
    Logger* logger = Logger::getLogger("wormoutput.txt") ; 


    clock_t initTime = time(NULL) ; 
    double netValue ; 
#ifdef DOMPI
    if(ad_myid==0)
#endif
    cout << "********** start *********" <<  endl ; 

    netValue = mOrigNet->eval() ; 
#ifdef DOMPI
    if(ad_myid==0)
#endif
    cout << "network eval 1: " << netValue  << endl ; 

    #ifdef DOMPI
    if(ad_myid==0)
    #endif
    plotDistribution( mOrigNet)  ; 
    
#ifdef DOMPI
    if(ad_myid==0)
#endif
    cout << "********** finish *********" <<  endl ; 


#ifdef DOMPI
    if(ad_myid!=0){
        strcpy(realCommand,"wait") ;
        waitForCommand() ;
    }
#endif
}



///  This method plots the probability densitities of an evaluated worm and a reference worm (turning probability=0.5).  It SHOULD also plot the distribution of ration between the two.
// TODO:  clean up this method, too
double EvoAnnealDriver::plotDistribution(BlitzLiveNet* mOrigNet) 
{
    double returnValue = mOrigNet->eval() ; 

    pair<ProbDistribution*,ProbDistribution*> distributionPair = ((WormSimProbTracks*) mOrigNet->getEvaluator())->getDistributions() ;

    ProbDistribution* refDist = distributionPair.first ; 
    ProbDistribution* currentDist = distributionPair.second ; 

    mProbPlotter = new Gnuplot("lines") ;
    WormSimProbTracks* wormEvaluator = (WormSimProbTracks*) mOrigNet->getEvaluator() ; 
    vector<double>* xPlotData  =  wormEvaluator->getBinsForPlotting() ; 
    vector<double>* refPlotData  = refDist->getDoublePlot() ; 
    vector<double>* currentPlotData = currentDist->getDoublePlot() ; 
    vector<double>* windowData =  wormEvaluator->getWindowPlot() ; 
    vector<double>* ratioData =  wormEvaluator->getCompareProbs() ; 

    ostringstream* titleString = new ostringstream() ; 
    string titleName = mNetworkFile.substr(mNetworkFile.find_last_of("/")+1) ; 
    (*titleString) << "set title \"error: " << returnValue << " (" << (1/returnValue) << ") window: " << mWindow <<  " power: " << mWindowPower << " inflec ratio: " << mInflectionRatio << " \\n" << titleName << "\" ;" ; 

    mProbPlotter->cmd( "set terminal x11" ) ; 
    plotProbs(xPlotData,refPlotData,currentPlotData,windowData,ratioData,returnValue,titleString->str()) ; 
    mProbPlotter->cmd( "set terminal png" ) ; 
    titleString = new ostringstream() ; 
    (*titleString) << "set output \"" << titleName << ".png\"" ; 
    mProbPlotter->cmd(   (titleString->str()).c_str()  ) ; 

    plotProbs(xPlotData,refPlotData,currentPlotData,windowData,ratioData,returnValue,titleString->str()) ; 

    return returnValue ; 
}




BlitzLiveNet* EvoAnnealDriver::createNetwork() 
{
    if(mOrigNet==NULL){
        mOrigNet = (BlitzLiveNet*) (new TinyBzNetParser())->parseFile(mNetworkFile) ;   
//        mOrigNet->setPerturber( new BlitzEulerPerturber() ) ; 
        mOrigNet->setPerturber( new BlitzEulerWrapPerturber(mWrapValue) ) ; 
        (mOrigNet->getNote())->setNote("description",mDescription) ; 
    }
    else{
        *mOrigNet = *((BlitzLiveNet*) (new TinyBzNetParser())->parseFile(mNetworkFile)) ;   
    }
    return mOrigNet; 
}

BlitzNetAnnealer* EvoAnnealDriver::createAnnealer() 
{
    if(mOrigAnneal==NULL){
//        mTempSchedule = new MomentumPowerTempSchedule(mNumTempSteps,mPower,mTempConstant,mHighTemp,mLowTemp) ;
//        mTempSchedule = new MomentumPowerTempSchedule() ;
        mTempSchedule = new SzuTempSchedule() ;
//        mOrigAnneal = new SeqBlitzNetAnnealer() ;
        mOrigAnneal = new SeqResetBlitzNetAnnealer() ;
        mAcceptModel = new SzuAcceptModel() ; 
//        mAcceptModel = new MetropolisAcceptModel() ; 
    }

    // set temp data
    ((TempSchedule*) mTempSchedule)->setNumPoints(mNumTempSteps) ; 
//    ((MomentumPowerTempSchedule*) mTempSchedule)->setPower(mPower) ; 
//    ((MomentumPowerTempSchedule*) mTempSchedule)->setConstant(mTempConstant) ; 
    ((TempSchedule*) mTempSchedule)->setHighTemp(mHighTemp) ; 
    ((TempSchedule*) mTempSchedule)->setLowTemp(mLowTemp) ; 


    // set accept model
    ((MetropolisAcceptModel*) mAcceptModel)->setConstant(mAcceptConstant) ; 
   
    // set annealer data
    mOrigAnneal->setSetBack(mSetBack) ; 
    mOrigAnneal->setBackStep(mBackStep) ; 
    mOrigAnneal->setTempSchedule(mTempSchedule) ; 
    mOrigAnneal->setIterPerTemp(mNumItersPerTemp) ; 
    mOrigAnneal->setAcceptModel(mAcceptModel) ; 
    ((SeqBlitzNetAnnealer *) mOrigAnneal)->setMinInitialImprovement(mMinInitialImprovement) ;
    return mOrigAnneal ;
}


/*  ***********************************************************************************
    message() */
   
//! Description here.
/*  *********************************************************************************** */
int EvoAnnealDriver::message(string caption,string text) 
{
    return QMessageBox::information((QtFlatRenderer*) mRenderer,caption.c_str(),text.c_str(),QMessageBox::Ok) ; 
}


/*  ***********************************************************************************
    setRenderer() */
   
//! Description here.
/*  *********************************************************************************** */
void EvoAnnealDriver::setRenderer(Renderer* newRenderer) 
{
    mRenderer = newRenderer ; 
}


/*  ***********************************************************************************
    creaetLocalMaps() */
   
//! Add items to GUI
/*  *********************************************************************************** */
bool EvoAnnealDriver::createLocalMaps() 
{
    string APP_NAME = "APP/SIMWORM" ; 
    #ifdef DOMPI
    MPI_Comm_size(MPI_COMM_WORLD,&ad_nprocs) ; 
    if(ad_nprocs==1)
    #endif
    addCommandToMap(PLOT_WORM) ; 
    addCommandToMap(START_SIMWORM) ; 
    addCommandToMap(PERTURB_TEST) ; 
    addCommandToMap(START_ANNEALER) ; 
    addCommandToMap(QUIT_ANNEALER) ; 


    // ANNEALING DESCRIPTION
    addOptionToMap("01_description",OPT_STRING,&mDescription,APP_NAME,"Description") ; 

    // NETWORK VALUES
    addOptionToMap("01a_network",OPT_FILE_LOAD,&mNetworkFile,APP_NAME,"Network File") ; 
    mRelaxTime = 200; 
//    mRelaxLimit= 0.01 ; 
    addOptionToMap("01b_sigmoid",OPT_DOUBLE,&mOutputSigmoid,APP_NAME,"Output Sigmoid (1.0)") ; 

    // WORMSIM VALUES VALUES
    addOptionToMap("01c_numworms",OPT_INT,&mNumWorms,APP_NAME,"Number of Worms") ; 
    addOptionToMap("01d_refsize",OPT_INT,&mRefWorms,APP_NAME,"Number Ref Worms") ; 
    addOptionToMap("02_dieonedge",OPT_BOOL,&mDieOnEdge,APP_NAME,"Die on Edge") ; 
    mNumWormSteps = 1200 ; 
    mForwardVelocity = 0.015 ; 
    mTurnVelocity = 0.011 ; 
    mDeltaT = 1.0 ; 


    // MAP VALUES
    addOptionToMap("03_highvalue",OPT_DOUBLE,&mHighMapValue,APP_NAME,"High Temp on Map") ; 
//    addOptionToMap("03b_midvalue",OPT_DOUBLE,&mMidMapValue,APP_NAME,"Mid Temp on Map") ; 
    mMidMapValue = 0.5 ; 
//    addOptionToMap("03c_lowvalue",OPT_DOUBLE,&mLowMapValue,APP_NAME,"Low Temp on Map") ; 
    mLowMapValue = -0.125 ; 
//    addOptionToMap("04_midrad",OPT_DOUBLE,&mMidMapRadius,APP_NAME,"Mid Rad on Map") ; 
    mMidMapRadius = 2.0 ; 
    addOptionToMap("04b_setradius",OPT_DOUBLE,&mOptimumRadius,APP_NAME,"Target Radius") ; 
//    addOptionToMap("04c_mbuffer",OPT_DOUBLE,&mEdgeBuffer,APP_NAME,"Edge Buffer") ; 
    mEdgeBuffer = 0.5 ; 
    mDiameter = 9.0 ; 
    mSpacing = 0 ; 

    // ERROR WINDOW VALUES
//    mLastSteps = 0 ; 
    addOptionToMap("04c0_laststeps",OPT_INT,&mLastSteps,APP_NAME,"Last Steps to Ignore") ; 
//    addOptionToMap("04d_binsize",OPT_DOUBLE,&mBinSize,APP_NAME,"Bin Size") ; 
    mBinSize = 0.2 ; 
    addOptionToMap("04e_windowerror",OPT_DOUBLE,&mWindow,APP_NAME,"Error Window Size") ; 
    addOptionToMap("04f_windowpower",OPT_DOUBLE,&mWindowPower,APP_NAME,"Power of Window (1.0)") ; 
    addOptionToMap("04g_inflectionratio",OPT_DOUBLE,&mInflectionRatio,APP_NAME,"Inflection Ratio (1.0)") ; 

    // ANNEALER VALUES
    addOptionToMap("08a_numnetwork",OPT_INT,&mNumNetworks,APP_NAME,"Number of Networks") ; 
    mMinInitialImprovement = 1 ; 
    addOptionToMap("08c_hightemp",OPT_DOUBLE,&mHighTemp,APP_NAME,"Annealer high temp") ; 
    addOptionToMap("09a_lowtemp",OPT_DOUBLE,&mLowTemp,APP_NAME,"Annealer low temp cutoff") ; 
    addOptionToMap("09aa_tempConst",OPT_DOUBLE,&mAcceptConstant,APP_NAME,"Accept Constant") ; 
    addOptionToMap("09b_iterspertemp",OPT_INT,&mNumItersPerTemp,APP_NAME,"Annealer iters per temp") ; 
    addOptionToMap("09c_setback",OPT_INT,&mSetBack,APP_NAME,"Annealer setback") ; 
    addOptionToMap("09d_wrapvalue",OPT_DOUBLE,&mWrapValue,APP_NAME,"Wrap Value (max)") ; 
    addOptionToMap("100_tempsteps",OPT_INT,&mNumTempSteps,APP_NAME,"Min anneal steps") ; 
//    addOptionToMap("101_power",OPT_DOUBLE,&mPower,APP_NAME,"Temp curve power") ; 
//    addOptionToMap("12_tempconstant",OPT_DOUBLE,&mTempConstant,APP_NAME,"Temp constant >> 1") ; 



    // output options
    addOptionToMap("13_outputfile",OPT_STRING,&mOutputFile,APP_NAME,"Annealer output") ; 
    addOptionToMap("14_bestnetwork",OPT_STRING,&mBestNetworkFile,APP_NAME,"Best net output") ; 
	mQuitAfterAnneal = true ; 

    
    return true ; 
}


/*  ***********************************************************************************
    doLocalCommand() */
   
//! Description here.
/*  *********************************************************************************** */
string EvoAnnealDriver::doLocalCommand(Command *theCommand) 
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

    } else if(theName==START_ANNEALER){
        #ifdef DOMPI
           strcpy(realCommand,"startannealer") ; 
           waitForCommand() ; 
        #else
           startAnnealer() ; 
        #endif 
    } else if(theName==PERTURB_TEST){
        #ifdef DOMPI
           strcpy(realCommand,"perturbtest") ; 
           waitForCommand() ; 
        #else
           perturbTest() ; 
       #endif
    } else if(theName==PLOT_WORM){
           plotWorm() ; 
    } else if(theName==QUIT_ANNEALER){
        #ifdef DOMPI
           strcpy(realCommand,"quitannealer") ; 
           waitForCommand() ; 
        #else
           quitAnnealer() ; 
        #endif 
    }
    
    return "it runned  "; 
}

///  In this method, the network is evaluated a series of times after being perturbed at a particular temperature.  Produce dialog querying # of iterations of pre-perturb, post-perturb as well as the size/temp of the perturbation 
bool EvoAnnealDriver::perturbTest() 
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

#ifdef DOMPI
        if(ad_myid==0)
#endif
    cout << "Perturb at: " << perturbValue << endl ; 
    if(postPerturb>0){
        thisNet->perturb(perturbValue) ; 
    }
    
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


void EvoAnnealDriver::quitAnnealer() 
{
        #ifdef DOMPI
           MPI_Abort(MPI_COMM_WORLD,0) ; 
           MPI_Finalize() ; 
           exit(0) ; 
        #else
           exit(0) ; 
        #endif 

}



bool EvoAnnealDriver::startAnnealer() 
{
    if(annealerThread==NULL || annealerThread->running()==false){
        annealerThread = new AnnealerThread(this) ; 
//        annealerThread->start() ; 
        annealerThread->run() ; 
        if(mQuitAfterAnneal){
            // this is fine here, since all threads will hit this point
            quitAnnealer() ; 
        }
    } else{
        message("Already annealing.","Already annealing, stop thread, first") ; 
    }
    return true ; 
}



void EvoAnnealDriver::plotTracks(vector<double>* xTracks,vector<double>* yTracks,double targetRadius,double dishRadius,string titleName) 
{
    ostringstream* commands = NULL ; 


      mTrackPlotter->cmd( "set size square 1,1" ) ; 
      mTrackPlotter->cmd("set xlabel 'X'") ; 
      mTrackPlotter->cmd("set ylabel 'Y'") ; 
      mTrackPlotter->cmd("set grid") ; 
      commands = new ostringstream() ; 
      // remainder of title
      // can also get it from others, as well
      *commands << "set title \"" << titleName <<  "\\n" ; 
      *commands << "targetrad=" << targetRadius << "\" ; " ; 
      *commands << "set xrange [0:" << mDiameter << "] ;" ; 
      *commands << "set yrange [0:" << mDiameter << "] ;" ; 
      mTrackPlotter->cmd( (commands->str()).c_str() ) ; 
      mTrackPlotter->cmd( "set multiplot" ) ; 
      mTrackPlotter->plot_xy( *(new vector<double>(*xTracks)),  *(new vector<double>(*yTracks)),"Worm Track" ) ; 
      mTrackPlotter->cmd( "replot" ) ; 


      // set multiplot to draw in the other garbage
//      mTrackPlotter->cmd( "replot" ) ; 
      commands = new ostringstream() ; 
      // top circle
      *commands << "plot [0:" << mDiameter << "] sqrt( -(x-"<< mDiameter/2.0 << ")**2 + (" << mDiameter/2.0 << ")**2)+" << mDiameter/2.0 << " ; " ; 
      // bottom circle
      *commands << "plot [0:" << mDiameter << "] -sqrt( -(x-"<< mDiameter/2.0 << ")**2 + (" << mDiameter/2.0 << ")**2)+" << mDiameter/2.0 << " ; " ; 

      // plot the target radii
      // top circle
      *commands << "plot [0:" << mDiameter << "] sqrt( -(x-"<< mDiameter/2.0 << ")**2 + (" << targetRadius << ")**2)+" << mDiameter/2.0 << " ; " ; 
      // bottom circle
      *commands << "plot [0:" << mDiameter << "] -sqrt( -(x-"<< mDiameter/2.0 << ")**2 + (" << targetRadius << ")**2)+" << mDiameter/2.0 << " ; " ; 
      mTrackPlotter->cmd( (commands->str()).c_str() ) ; 

      // unset 
      mTrackPlotter->cmd("set nomultiplot") ; 
//      mTrackPlotter->cmd("unset multiplot") ; 
      
}

WormSimAllTrackEval* EvoAnnealDriver::createRefEval(BlitzLiveNet* prototypeNet,int numRefWorms/*-1*/) 
{
    BlitzLiveNet* nullNet = new BlitzLiveNet(prototypeNet) ; 
    (*(nullNet->getBias())) = 0 ; 
//    (*(nullNet->getBias()))(nullNet->getNumNeurons()-1) = 10000.0  ;  // we want only running
    (*(nullNet->getWeights())) = 0 ; 

    WormSimAllTrackEval* thisEval = new WormSimAllTrackEval(numRefWorms,mNumWormSteps,nullNet, new DogbowlLinRadialMap(mDiameter,mHighMapValue,mLowMapValue,mMidMapValue,mMidMapRadius) ,mForwardVelocity,mTurnVelocity,mDeltaT,mOutputSigmoid,new EvenRadWormShuffler( mDiameter,numRefWorms,mEdgeBuffer ),mOptimumRadius) ;    
    vector<double>* relaxVector = new vector<double>(1) ;
    (*relaxVector)[0] = 0.5 ; 
    thisEval->setRelaxValue(relaxVector) ; 
    thisEval->setRelaxTime(mRelaxTime) ; 
//    thisEval->setRelaxLimit(mRelaxLimit) ; 
    thisEval->setRelaxDeltaT(1.0) ; 
    thisEval->setRelaxTau(3.0) ; 
    thisEval->resetTrace(mNumWormSteps,mNumWormSteps) ; 

    return thisEval ;
}


/// This method plots a single worm track using gnuplot.
void EvoAnnealDriver::plotWorm() 
{
    createNetwork() ; 
    mOrigNet->setEvaluator( createEvaluator(mOrigNet,1,1)) ; // create evaluator with 1 worm
    cout << "eval: " << mOrigNet->eval() << endl ; 

    vector<double>* xVec = new vector<double>() ; 
    vector<double>* yVec = new vector<double>() ; 

    vector<vector<pair<double,double> >*>* wormTracks = ( (WormSimEval*) mOrigNet->getEvaluator())->getWormTracks() ; 
    for(int i = 0 ; i < wormTracks->size() ; i++){
        xVec->push_back(  ((*(*wormTracks)[i]))[0].first) ; 
        yVec->push_back(  ((*(*wormTracks)[i]))[0].second) ; 
//        cout << "x,y: " << ((*(*wormTracks)[i]))[0].first << "," << ((*(*wormTracks)[i]))[0].second << endl ; 
    }
    if(mTrackPlotter!= NULL){
        mTrackPlotter = NULL ; 
        delete mTrackPlotter ; 
    }
//    mTrackPlotter = new Gnuplot("lines") ; 
    mTrackPlotter = new Gnuplot("dots") ; 

    // create title
    string titleName ; 
    titleName = mNetworkFile.substr(mNetworkFile.find_last_of("/")+1) ; 

    // plot to screen
    mTrackPlotter->cmd( "set terminal x11" ) ; 
    plotTracks(xVec,yVec, ((WormSimEval*) mOrigNet->getEvaluator())->getTargetRadius(),mDiameter,titleName) ; 

    mTrackPlotter = NULL ; 
    delete mTrackPlotter ; 
    mTrackPlotter = new Gnuplot("lines") ; 

    ostringstream *theseCommands = new ostringstream() ; 
    *theseCommands << "set terminal png ; " ; 
    *theseCommands << "set output \"" <<   titleName << ".png" <<  "\" ;" ; 
    mTrackPlotter->cmd( (theseCommands->str()).c_str() ) ; 
    plotTracks(xVec,yVec, ((WormSimEval*) mOrigNet->getEvaluator())->getTargetRadius(),mDiameter , titleName) ; 


}

void EvoAnnealDriver::plotProbs(vector<double>* xDistData,vector<double>* refProb,vector<double>* currentProb,vector<double>* windowPlot,vector<double>* ratioPlot,double netValue,string theTitle) 
{
    mProbPlotter->cmd(  theTitle.c_str()  ) ; 
    ostringstream* cmdstring = new ostringstream() ; 
    (*cmdstring) << "set xrange [0: " << ((*xDistData)[xDistData->size()-1]+ mBinSize) << "]; "  ; 
    (*cmdstring) << "set yrange [0:0.2] ; "  ; 
    (*cmdstring) << "set ylabel \"Probability Density\" ; "  ; 
    (*cmdstring) << "set y2label \"Ratio & Window\" ; "  ; 
    (*cmdstring) << "set xlabel \"Radius(cm)\" ; "  ; 
    mProbPlotter->cmd( (cmdstring->str()).c_str() ) ; 
    mProbPlotter->plot_xy( *xDistData,*refProb,"Reference Prob Dens (left)") ; 
    mProbPlotter->plot_xy( *xDistData,*currentProb,"Network Prob Dens (left)") ; 

    // y2 axes
    mProbPlotter->plot_xy( *xDistData,*windowPlot,"Window of Evaluation (right)","x1y2") ; 
    mProbPlotter->plot_xy( *xDistData,*ratioPlot,"Ratio (right)","x1y2") ; 
    mProbPlotter->cmd("set y2tics 0,1") ; 
    mProbPlotter->cmd("replot") ; 

}




#ifdef DOMPI
/// Sync's data from the gui input
void EvoAnnealDriver::syncData() 
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
//    MPI_Bcast(&mRelaxLimit,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mOutputSigmoid,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 

    // WORMSIM VALUES VALUES
    MPI_Bcast(&mNumWormSteps,1,MPI_INT,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mRefWorms,1,MPI_INT,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mDieOnEdge,1,MPI_INT,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mNumWorms,1,MPI_INT,0,MPI_COMM_WORLD) ; 
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


    // ANNEALER VALUES
    MPI_Bcast(&mNumNetworks,1,MPI_INT,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mMinInitialImprovement,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mHighTemp,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mLowTemp,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mAcceptConstant,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mNumItersPerTemp,1,MPI_INT,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mSetBack,1,MPI_INT,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mWrapValue,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mNumTempSteps,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
//    MPI_Bcast(&mPower,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
//    MPI_Bcast(&mTempConstant,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 

    if(ad_myid==0) sprintf(fileName,"%s",mOutputFile.c_str()) ; 
    MPI_Bcast(fileName, CHAR_LENGTH,MPI_CHAR,0,MPI_COMM_WORLD) ; 
    if(ad_myid!=0) mOutputFile=fileName ; 

    if(ad_myid==0) sprintf(fileName,"%s",mBestNetworkFile.c_str()) ; 
    MPI_Bcast(fileName, CHAR_LENGTH,MPI_CHAR,0,MPI_COMM_WORLD) ; 
    if(ad_myid!=0) mBestNetworkFile=fileName ; 

    MPI_Bcast(&mQuitAfterAnneal,1,MPI_INT,0,MPI_COMM_WORLD) ; 

}

/// Synchronizes the networks from the original network.
BlitzLiveNet* EvoAnnealDriver::syncNet(BlitzLiveNet* origNet) 
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



void EvoAnnealDriver::waitForCommand() 
{
    MPI_Comm_rank(MPI_COMM_WORLD,&ad_myid) ; 
    MPI_Barrier(MPI_COMM_WORLD) ;     
    syncData() ; 

//    cout << "PRE waiting in waitForCommand: "  << ad_myid << " command: " << realCommand << endl ;
    
    MPI_Bcast( &realCommand , 128 ,MPI_CHAR,0,MPI_COMM_WORLD) ;
    
//    cout << "POST waiting in waitForCommand: "  << ad_myid << " command: " << realCommand << endl ;
    
    if( strncmp(realCommand,"runapp",strlen(realCommand))==0){
//        cout << ad_myid << ": waitForCommand running app" << endl ; 
        runapp() ;
	
    } else if( strncmp(realCommand,"startannealer",strlen(realCommand))==0){
//        cout << ad_myid << ": waitForCommand starting annealer" << endl ; 
        startAnnealer() ;
    } else if( strncmp(realCommand,"perturbtest",strlen(realCommand))==0){
//        cout << ad_myid << ": waitForCommand starting annealer" << endl ; 
        perturbTest() ;
    } else if( strncmp(realCommand,"quitannealer",strlen(realCommand))==0){
//        cout << ad_myid << ": waitForCommand quit annealer" << endl ; 
        quitAnnealer() ; 
	
    } else if(ad_myid!=0){
        strcpy(realCommand,"wait") ; 
        waitForCommand() ; 
    }



    // send a command, to all others to do startAnnealer, and see what's missing
}
#endif




const string EvoAnnealDriver::START_SIMWORM = "START_SIMWORM"  ; 
const string EvoAnnealDriver::START_ANNEALER = "START_ANNEALER"  ; 
const string EvoAnnealDriver::QUIT_ANNEALER = "QUIT_ANNEALER"  ; 
const string EvoAnnealDriver::PERTURB_TEST = "PERTURB_TEST"  ; 
const string EvoAnnealDriver::PLOT_WORM = "PLOT_WORM"  ; 




/* Modeline for ViM {{{
 * vim:set ts=4:
 * vim600:fdm=marker fdl=0 fdc=3:
 * }}} */





