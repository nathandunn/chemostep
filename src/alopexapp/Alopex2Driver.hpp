#ifndef ALOPEX2DRIVER_HPP_
#  define ALOPEX2DRIVER_HPP_


#include <TiFlatBaseApp.hpp>

#include <vector>
using std::vector ; 

#include <fstream>
using std::ofstream ; 



class Worm ; 
class MapData ; 
class MapSpace ; 
class TinyBzNetParser ; 
class TinyAppInterfaceXmlEngine ; 
class BlitzLiveNet ; 
class WormSimAllTrackEval; 
class WormSimEval; 
class BlitzNetAlopexer ; 
class BlitzNetAlopexPerturber ; 
class AlopexerThread ; 
class Gnuplot ; 
class BaseFlatDriver ; 
/**
 *  This class runs that actual Alopexer. 
 *
 *  \todo Add MapSpace
 *  \todo Add Make sure worms are being added.
*   \todo Are worms running?
*   \todo Train dem worms!
 *
 */

class Alopex2Driver : public TiFlatBaseApp {

public:
//    Alopex2Driver() ; 
    Alopex2Driver(string newInterfaceName, string newTypeName, AppInterface* newParent) ; 
    virtual void* runapp() ; 
    virtual void setDriver( BaseFlatDriver* newDriver  ) ; 
    virtual bool startAlopexer() ; 
    virtual bool perturbTest() ; 
    virtual int message(string caption,string text) ; 
    virtual void setRenderer(Renderer* newRenderer) ; 
    virtual double plotDistribution(BlitzLiveNet* thisNet) ; 

    // AppInterface classes
    virtual bool createLocalMaps() ; 
    virtual string doLocalCommand(Command *theCommand) ; 
#ifdef DOMPI
    virtual void waitForCommand() ; 
    virtual void syncData() ; 
    virtual BlitzLiveNet* syncNet(BlitzLiveNet* origNet) ; 
#endif

    virtual BlitzLiveNet* createNetwork() ; 
    virtual WormSimEval* createEvaluator(BlitzLiveNet* prototypeNet,int numWorms=-1,int numRefWorms=-1) ; 
    virtual WormSimAllTrackEval* createRefEval(BlitzLiveNet* prototypeNet,int numRefWorms=-1) ; 
    virtual ofstream* createOutputFileStream(const char* outputFile) ; 
    virtual BlitzNetAlopexer* createAlopexer() ; 

    // commands
    const static string PLOT_WORM ; 
    const static string START_SIMWORM ; 
    const static string PERTURB_TEST ; 
    const static string START_ALOPEXER ; 
    const static string QUIT_ALOPEXER ; 

protected:
    // network values
    virtual void plotWorm() ; 
    virtual void quitAlopexer() ; 
    virtual void plotTracks(vector<double>* xTracks,vector<double>* yTracks,double targetRadius,double dishRadius,string titleName="") ; 
    virtual void plotProbs(vector<double>* xDistData,vector<double>* refProb,vector<double>* currentProb,vector<double>* windowPlot,vector<double>* ratioPlot,double netValue,string theTitle) ; 
    string mNetworkFile; 
    string mDescription ; 
    string mBestNetworkFile ; 
    string mOutputFile; 
    double mStimDeltaT ; 
    double mRelaxTime ,mRelaxLimit; 
    double mOutputSigmoid ; 


    // error function 
    double mWindow ; 
    double mWindowPower ; 
    double mOptimumRadius ; 
    int mLastSteps ; 
    double mInflectionRatio ; 


    // wormsim values
    int mNumWorms ; 
    int mRefWorms ; 
    int mNumWormSteps ; 
    double mBinSize ; 
    double mForwardVelocity ; 
    double mTurnVelocity; 
    double mDeltaT ; 
    double mSpacing ; 
    double mEdgeBuffer; 
    bool mDieOnEdge ; 

    // map values
    double mHighMapValue ; 
    double mMidMapValue ; 
    double mMidMapRadius ; 
    double mLowMapValue ; 
    double mDiameter ; 

    // annealer data
    bool mQuitAfterAlopex ;  
    int mNumTempSteps ; 
    int mNumItersPerTemp ; 
    int mSetBack ; 
    int mBackStep ; 
    int mNumNetworks; 
    double mMinInitialImprovement ;

    //  temp specific
    double mHighTemp ; 
    double mLowTemp ; 
    double mPower ; 
    double mTempConstant ; 
    double mCriticalAcceptance ; 

    // plotting stuff
    Gnuplot* mTrackPlotter ; 
    Gnuplot* mProbPlotter ; 

    // local data
    BlitzLiveNet* mOrigNet ; 
    WormSimEval* mOrigEval ; 
    BlitzNetAlopexer* mOrigAlopex; 
    BlitzNetAlopexPerturber* mOrigPerturber ; 


    // gui thing
    BaseFlatDriver* mDriver ; 

    // output stuff
    ofstream *mOutputStream  ; 
    ofstream *mNetworkStream ; 
    BlitzLiveNet* mFinalNet ;
    int mOutputPeriod ;

    // alopex variables
    double mMinError ; 
    int mTotalIterations ; 
    double mAlopexLambda ; 
    double mAlopexDelta ;
    double mAlopexBeta ;
    double mWrapValue ;


} ;

#endif /* ifndef ALOPEX2DRIVER_HPP_ */
// -*- C++ -*-
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>

