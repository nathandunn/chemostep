
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
#include <UniformNetBehaviorModel.hpp>   
#include <EvenRadWormShuffler.hpp>   
//#include <SetRadWormShuffler.hpp>   
#include <BlitzEulerLiveNetEvaluator.hpp>   
#include <MomentumPowerTempSchedule.hpp> 
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
#include <Worm.hpp>
#include <TtestAcceptModel.hpp>
#include <ProbDistribution.hpp>
//#include <BlitzNetAlopexPerturber.hpp>
#include <BlitzNetAlopexWrapPerturber.hpp>
#include <BlitzNetAlopexer.hpp>
#include <Note.hpp>
#include <alopex2app.hpp>

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

// for output
#include <XmlFileTokenizer.hpp>   


#ifdef DOMPI
    #include "mpi.h"
    int ad_myid ; 
    int ad_nprocs ; 
    char realCommand[128] = "wait"  ; 
#endif 


#include "Alopex2Driver.hpp"


/*  ***********************************************************************************
    Constructor */
   
//! Description here.
/*  *********************************************************************************** */
Alopex2Driver::Alopex2Driver(string newInterfaceName,string newTypeName,AppInterface* newParent)  :
TiFlatBaseApp(newInterfaceName,newTypeName,newParent) 
,mTrackPlotter(NULL)
,mProbPlotter(NULL)
,mOrigNet(NULL)
,mOrigEval(NULL)
,mOrigAlopex(NULL)
,mOrigPerturber(NULL)
{
   description = "Kinetic annealer.  Produces 1 to N." ; 
   RNG::initSeed();
}

ofstream* Alopex2Driver::createOutputFileStream(const char* outputFile) 
{
    ofstream *returnstream = new ofstream( outputFile , ios::out) ; 
    return returnstream ; 
}

void Alopex2Driver::setDriver( BaseFlatDriver* newDriver  ) 
{
    mDriver = newDriver ; 
}



/// Creates evaluator using the assumption that the network has already been created.  The evaluator is WormSimMeanDistEval() 
WormSimEval* Alopex2Driver::createEvaluator(BlitzLiveNet* prototypeNet,int numWorms,int numRefWorms) {

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
        mOrigEval->setRelaxLimit(mRelaxLimit) ; 
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

void *Alopex2Driver::runapp(){

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
double Alopex2Driver::plotDistribution(BlitzLiveNet* mOrigNet) 
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




BlitzLiveNet* Alopex2Driver::createNetwork() 
{
    if(mOrigNet==NULL){
        mOrigNet = (BlitzLiveNet*) (new TinyBzNetParser())->parseFile(mNetworkFile) ;   
        mOrigNet->setPerturber( new BlitzEulerPerturber() ) ; 
        (mOrigNet->getNote())->setNote("description",mDescription) ; 
    }
    else{
        *mOrigNet = *((BlitzLiveNet*) (new TinyBzNetParser())->parseFile(mNetworkFile)) ;   
    }

    if(mOrigPerturber==NULL){
        mOrigPerturber = new BlitzNetAlopexWrapPerturber(mWrapValue,mAlopexDelta,mAlopexLambda) ; 
    }
    else{
        mOrigPerturber->setDelta(mAlopexDelta) ; 
        mOrigPerturber->setLambda(mAlopexLambda) ; 
    }
    // for some reason not set in constructor ?!?
    mOrigPerturber->setBeta(mAlopexBeta) ; 
    mOrigPerturber->initTrace(mOrigNet->getWeights(), mOrigNet->getTau(), mOrigNet->getBias());
    mOrigNet->setPerturber( mOrigPerturber ) ; 
    return mOrigNet; 
}

BlitzNetAlopexer* Alopex2Driver::createAlopexer() 
{
    if(mOrigAlopex==NULL){
        mOrigAlopex = new BlitzNetAlopexer() ;
    }
    mOrigAlopex->setMinError( mMinError) ; 
    mOrigAlopex->setTotalIterations( mTotalIterations ) ; 
//    mOrigAlopex->setAcceptModel(new TtestAcceptModel(mCriticalAcceptance)) ;
    mOrigAlopex->setOutputPeriod(mOutputPeriod);
    return mOrigAlopex ;
}


/*  ***********************************************************************************
    message() */
   
//! Description here.
/*  *********************************************************************************** */
int Alopex2Driver::message(string caption,string text) 
{
    return QMessageBox::information((QtFlatRenderer*) mRenderer,caption.c_str(),text.c_str(),QMessageBox::Ok) ; 
}


/*  ***********************************************************************************
    setRenderer() */
   
//! Description here.
/*  *********************************************************************************** */
void Alopex2Driver::setRenderer(Renderer* newRenderer) 
{
    mRenderer = newRenderer ; 
}


/*  ***********************************************************************************
    creaetLocalMaps() */
   
//! Add items to GUI
/*  *********************************************************************************** */
bool Alopex2Driver::createLocalMaps() 
{
    string APP_NAME = "APP/SIMWORM" ; 
    #ifdef DOMPI
    MPI_Comm_size(MPI_COMM_WORLD,&ad_nprocs) ; 
    if(ad_nprocs==1)
    #endif
    addCommandToMap(PLOT_WORM) ; 
    addCommandToMap(START_SIMWORM) ; 
    addCommandToMap(PERTURB_TEST) ; 
    addCommandToMap(START_ALOPEXER) ; 
    addCommandToMap(QUIT_ALOPEXER) ; 


    // ANNEALING DESCRIPTION
    addOptionToMap("01_description",OPT_STRING,&mDescription,APP_NAME,"Description") ; 

    // NETWORK VALUES
    addOptionToMap("01a_network",OPT_FILE_LOAD,&mNetworkFile,APP_NAME,"Network File") ; 
    mRelaxTime = 200; 
    mRelaxLimit= 0.01 ; 
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
    addOptionToMap("04d_laststeps",OPT_DOUBLE,&mLastSteps,APP_NAME,"Initial Steps to Ignore") ; 
//    addOptionToMap("04d_binsize",OPT_DOUBLE,&mBinSize,APP_NAME,"Bin Size") ; 
    mBinSize = 0.2 ; 
    addOptionToMap("04e_windowerror",OPT_DOUBLE,&mWindow,APP_NAME,"Error Window Size") ; 
    addOptionToMap("04f_windowpower",OPT_DOUBLE,&mWindowPower,APP_NAME,"Power of Window (1.0)") ; 
    addOptionToMap("04g_inflectionratio",OPT_DOUBLE,&mInflectionRatio,APP_NAME,"Inflection Ratio (1.0)") ; 

    // ALOPEXER VALUES
    addOptionToMap("08a_numnetwork",OPT_INT,&mNumNetworks,APP_NAME,"Number of Networks") ; 
    addOptionToMap("121_minerror",OPT_DOUBLE,&mMinError,APP_NAME,"Minimum Error") ; 
    addOptionToMap("13_TotalIterations:",OPT_INT,&mTotalIterations,APP_NAME,"Max Iterations") ; 
    addOptionToMap("14_lambda:",OPT_DOUBLE,&mAlopexLambda,APP_NAME,"Alopex Lambda") ; 
    addOptionToMap("15_delta:",OPT_DOUBLE,&mAlopexDelta,APP_NAME,"Alopex Delta") ; 
    addOptionToMap("16_beta:",OPT_DOUBLE,&mAlopexBeta,APP_NAME,"Alopex Beta (sigmoid gain)") ;
    addOptionToMap("16b_wrapvalue:",OPT_DOUBLE,&mWrapValue,APP_NAME,"Wrap Value (max value)") ;

    

    addOptionToMap("17_outputfile",OPT_STRING,&mOutputFile,APP_NAME,"Alopexer output") ; 
    addOptionToMap("18_bestnetwork",OPT_STRING,&mBestNetworkFile,APP_NAME,"Best net output") ; 
    addOptionToMap("19_outputPeriod:",OPT_INT,&mOutputPeriod,APP_NAME,"XML render period (Iter/step)") ;
    addOptionToMap("20_quit:",OPT_BOOL,&mQuitAfterAlopex,APP_NAME,"Quit after Alopex") ;
//    mQuitAfterAlopex = true ; 

    
    return true ; 
}


/*  ***********************************************************************************
    doLocalCommand() */
   
//! Description here.
/*  *********************************************************************************** */
string Alopex2Driver::doLocalCommand(Command *theCommand) 
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
           startAlopexer() ; 
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
    } else if(theName==QUIT_ALOPEXER){
        #ifdef DOMPI
           strcpy(realCommand,"quitannealer") ; 
           waitForCommand() ; 
        #else
           quitAlopexer() ; 
        #endif 
    }
    
    return "it runned  "; 
}

///  In this method, the network is evaluated a series of times after being perturbed at a particular temperature.  Produce dialog querying # of iterations of pre-perturb, post-perturb as well as the size/temp of the perturbation 
bool Alopex2Driver::perturbTest() 
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
    double perturbValue = mAlopexDelta ; 



    

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


void Alopex2Driver::quitAlopexer() 
{
        #ifdef DOMPI
           MPI_Abort(MPI_COMM_WORLD,0) ; 
           MPI_Finalize() ; 
           exit(0) ; 
        #else
           exit(0) ; 
        #endif 

}



bool Alopex2Driver::startAlopexer() 
{
    vector<string>* outputAlopexerNames = NULL ; 
    vector<string>* outputNetworkNames =  NULL ; 


    outputAlopexerNames = XmlFileTokenizer::createFileNames( mOutputFile , mNumNetworks) ; 
    outputNetworkNames = XmlFileTokenizer::createFileNames( mBestNetworkFile, mNumNetworks) ; 


//  TODO:  create annealer, network, etc., here and just do a reset within the loop, making sure to change the output name

    int wormState = MapSpace::SOME_RUNNING ; 
    // init stuff
//    mNetwork = new BlitzLiveNet(*mOrigNet) ; 
    createNetwork() ; 
    createAlopexer() ; 
    createEvaluator(mOrigNet) ; 

    
    for(int i = 0 ; i < mNumNetworks ; i++){
        mOrigNet->setEvaluator( mOrigEval ) ; 
        mOrigAlopex->setAlopexTarget(mOrigNet)  ; 
        mOutputStream = createOutputFileStream( ((*outputAlopexerNames)[i]).c_str() ) ; 

        if(mFinalNet==NULL){
            mFinalNet =   new BlitzLiveNet( (BlitzLiveNet*) ( ((BlitzNetAlopexer*) mOrigAlopex)->alopex(mOutputStream, (*outputNetworkNames)[i]  )  )  ) ; 
        }
        else{
            *mFinalNet =   *( (BlitzLiveNet*) ( ((BlitzNetAlopexer*) mOrigAlopex)->alopex(mOutputStream, (*outputNetworkNames)[i]  )  )  ) ; 
        }
        mOutputStream->close() ; 
        mOutputStream = NULL ;

    }
   

    if(mQuitAfterAlopex){
            // this is fine here, since all threads will hit this point
            quitAlopexer() ; 
    }

#ifdef DOMPI
    if(ad_myid!=0){
        strcpy(realCommand,"wait") ;
        waitForCommand() ;
    }
#endif


    return true ; 
}



void Alopex2Driver::plotTracks(vector<double>* xTracks,vector<double>* yTracks,double targetRadius,double dishRadius,string titleName) 
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

WormSimAllTrackEval* Alopex2Driver::createRefEval(BlitzLiveNet* prototypeNet,int numRefWorms/*-1*/) 
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
    thisEval->setRelaxLimit(mRelaxLimit) ; 
    thisEval->setRelaxDeltaT(1.0) ; 
    thisEval->setRelaxTau(3.0) ; 
    thisEval->resetTrace(mNumWormSteps,mNumWormSteps) ; 

    return thisEval ;
}


/// This method plots a single worm track using gnuplot.
void Alopex2Driver::plotWorm() 
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

void Alopex2Driver::plotProbs(vector<double>* xDistData,vector<double>* refProb,vector<double>* currentProb,vector<double>* windowPlot,vector<double>* ratioPlot,double netValue,string theTitle) 
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
void Alopex2Driver::syncData() 
{
    char fileName[CHAR_LENGTH]; 

    // RUN DESCRIPTION
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


    // ALOPEX VALUES
    MPI_Bcast(&mNumNetworks,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mMinError,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mTotalIterations,1,MPI_INT,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mAlopexLambda,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mAlopexDelta,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mAlopexBeta,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mWrapValue,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mOutputPeriod,1,MPI_INT,0,MPI_COMM_WORLD) ; 

    if(ad_myid==0) sprintf(fileName,"%s",mOutputFile.c_str()) ; 
    MPI_Bcast(fileName, CHAR_LENGTH,MPI_CHAR,0,MPI_COMM_WORLD) ; 
    if(ad_myid!=0) mOutputFile=fileName ; 

    if(ad_myid==0) sprintf(fileName,"%s",mBestNetworkFile.c_str()) ; 
    MPI_Bcast(fileName, CHAR_LENGTH,MPI_CHAR,0,MPI_COMM_WORLD) ; 
    if(ad_myid!=0) mBestNetworkFile=fileName ; 

    MPI_Bcast(&mQuitAfterAlopex,1,MPI_INT,0,MPI_COMM_WORLD) ; 

}

/// Synchronizes the networks from the original network.
BlitzLiveNet* Alopex2Driver::syncNet(BlitzLiveNet* origNet) 
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



void Alopex2Driver::waitForCommand() 
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
        startAlopexer() ;
    } else if( strncmp(realCommand,"perturbtest",strlen(realCommand))==0){
//        cout << ad_myid << ": waitForCommand starting annealer" << endl ; 
        perturbTest() ;
    } else if( strncmp(realCommand,"quitannealer",strlen(realCommand))==0){
//        cout << ad_myid << ": waitForCommand quit annealer" << endl ; 
        quitAlopexer() ; 
	
    } else if(ad_myid!=0){
        strcpy(realCommand,"wait") ; 
        waitForCommand() ; 
    }



    // send a command, to all others to do startAlopexer, and see what's missing
}
#endif




const string Alopex2Driver::START_SIMWORM = "START_SIMWORM"  ; 
const string Alopex2Driver::START_ALOPEXER = "START_ALOPEXER"  ; 
const string Alopex2Driver::QUIT_ALOPEXER = "QUIT_ALOPEXER"  ; 
const string Alopex2Driver::PERTURB_TEST = "PERTURB_TEST"  ; 
const string Alopex2Driver::PLOT_WORM = "PLOT_WORM"  ; 




/* Modeline for ViM {{{
 * vim:set ts=4:
 * vim600:fdm=marker fdl=0 fdc=3:
 * }}} */





