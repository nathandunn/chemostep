#ifndef TENNISDRIVER_HPP_
#  define TENNISDRIVER_HPP_


#include <TiFlatBaseApp.hpp>

#include <vector>
using std::vector ; 

#include <fstream>
using std::ofstream ; 



class Map; 
class Worm ; 
class TinyBzNetParser ; 
class TinyAppInterfaceXmlEngine ; 
class BlitzLiveNet ; 
class WormSimAllTrackEval; 
class OneWormSimEval; 
class SeqBlitzNetAnnealer ; 
class AnnealerThread ; 
class Gnuplot ; 
class BaseFlatDriver ; 
class TennisCourtMap ; 
class TextEvalTrace ; 
class DogbowlLinRadialMap ; 

/** This class runs an Annealer over the tenniscourt app.
 *
 */

class TennisDriver : public TiFlatBaseApp {

public:
    TennisDriver(string newInterfaceName, string newTypeName, AppInterface* newParent) ; 
    virtual void setDriver( BaseFlatDriver* newDriver  ) ; 
    virtual bool startAnnealer() ; 
    virtual bool perturbTest() ; 
    virtual bool evalTest() ; 
    virtual void setRenderer(Renderer* newRenderer) ; 

    // AppInterface classes
    virtual bool createLocalMaps() ; 
    virtual string doLocalCommand(Command *theCommand) ; 
#ifdef DOMPI
    virtual void waitForCommand() ; 
    virtual void syncData() ; 
    virtual BlitzLiveNet* syncNet(BlitzLiveNet* origNet) ; 
#endif

    virtual BlitzLiveNet* createNetwork() ; 
    virtual OneWormSimEval* createEvaluator(BlitzLiveNet* prototypeNet,int numWorms=-1,int numRefWorms=-1) ; 
    virtual ofstream* createOutputFileStream(const char* outputFile) ; 
    virtual BlitzNetAnnealer* createAnnealer() ; 
    AnnealerThread* annealerThread ; 

    // commands
    const static string PLOT_WORM ; 
    const static string PERTURB_TEST ; 
    const static string EVAL_TEST ; 
    const static string START_ANNEALER ; 
    const static string QUIT_ANNEALER ; 

protected:
    // network values
    virtual void plotWorm() ; 
    virtual pair<vector<double>*,vector<double>*>* dumpWorm() ; 
    virtual pair<vector<double>*,vector<double>*>* evalWorm() ; 
    virtual void quitAnnealer() ; 
    virtual vector<double>* calculateInputFromTracks(pair<vector<double>*,vector<double>*>* tracks) ; 
    virtual void plotTennisTracks(vector<double>* xTracks,vector<double>* yTracks,TennisCourtMap* newMap,string titleName="") ; 
    virtual void plotPetriTracks(vector<double>* xTracks,vector<double>* yTracks,DogbowlLinRadialMap* newMap,string titleName="") ; 
    virtual void plotNeurons() ; 
    virtual void setOutput(Gnuplot* aPlot,string outputName) ; 
	friend class AnnealerThread ; 
    string mNetworkFile; 
    string mDescription ; 
    string mBestNetworkFile ; 
    string mOutputFile; 
    double mRelaxTime ,mRelaxLimit; 
    double mOutputSigmoid , mInputSigmoid; 
    double mInputNoise,mOutputNoise ;

    // plot stuff
    string mOutputType, mTitleName ; 
    vector<string>* mOutputList ; 

    /// sigmoid lookup stuff
    double mSigLimit ; 
    int mTableSize ; 


    // error function 
//    double mWindow ; 
//    double mWindowPower ; 
//    double mOptimumRadius ; 
    int mIgnoreLastSteps ; 
//    double mInflectionRatio ; 


    // wormsim values
    int mNumWorms ; 
//    int mRefWorms ; 
    int mNumWormSteps ; 
    double mSimTime ; 
    double mForwardVelocity ; 
    double mTurnVelocity; 
    double mDeltaT ; 
    double mSpaceFromTarget; 
    bool mDoWorstPair ; 

    // map values
    double mHighValue ; 
    double mTargetValue ; 
    double mTargetX ; 
    double mLowValue ; 
    double mWidth ; 
    double mHeight ; 
    bool mDoTennisCourtMap ;  

    // annealer data
    bool mQuitAfterAnneal ;  
    int mNumTempSteps ; 
    int mNumItersPerTemp ; 
    int mSetBack ; 
    int mNumNetworks; 
    double mWrapValue ; 
    int mVerifyMultiply ; 
    int mNumInputs ; 

    //  temp specific
    double mHighTemp ; 
    double mLowTemp ; 
    double mAcceptConstant ; 

    // plotting stuff
    Gnuplot* mTrackPlotter ; 
    Gnuplot* mPlotter ; 
    TextEvalTrace* mTracer ; 

    // local data
    BlitzLiveNet* mOrigNet ; 
    OneWormSimEval* mOrigEval ; 
    SeqBlitzNetAnnealer* mOrigAnneal; 
    TempSchedule* mTempSchedule ; 
    AcceptModel* mAcceptModel ; 
    BlitzLiveNet* mFinalNet ; 
    string mTempScheduleString ; 
    vector<string>* mTempType ; 
    bool mDoMidMethod ; 

    // output streams
    ofstream *mOutputStream  ; 
    ofstream *mNetworkStream ; 

    // gui thing
    BaseFlatDriver* mDriver ; 

} ;

#endif /* ifndef EVOANNEALERDRIVER_HPP_ */
// -*- C++ -*-
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: TennisDriver.hpp,v 1.3 2004/01/27 20:27:19 ndunn Exp $

