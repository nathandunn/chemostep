#ifndef ALOPEXDRIVER_HPP_ 
#  define ALOPEXDRIVER_HPP_


#include <TiFlatBaseApp.hpp>

#include <vector>
using std::vector ; 

#include <fstream>
using std::ofstream ; 

#include <AlopexThread.hpp>


class Worm ; 
class MapData ; 
class MapSpace ; 
class TinyBzNetParser ; 
class TinyAppInterfaceXmlEngine ; 
class BlitzLiveNet ; 
class WormSimEval; 
class SeqBlitzNetAnnealer ; 
class AlopexThread ; 

/**
 *  This class runs that actual Annealer. 
 *
 *  \todo Add MapSpace
 *  \todo Add Make sure worms are being added.
*   \todo Are worms running?
*   \todo Train dem worms!
 *
 */

class AlopexDriver : public TiFlatBaseApp {

public:
//    AlopexDriver() ; 
    AlopexDriver(string newInterfaceName, string newTypeName, AppInterface* newParent) ; 
    void *runapp() ; 
    bool startAnnealer() ; 
    bool stopAnnealer() ; 
    int message(string caption,string text) ; 
    void setRenderer(Renderer* newRenderer) ; 

    // AppInterface classes
    bool createLocalMaps() ; 
    string doLocalCommand(Command *theCommand) ; 
#ifdef DOMPI
    void waitForCommand() ; 
    void syncData() ; 
    BlitzLiveNet* syncNet(BlitzLiveNet* origNet) ; 
#endif

    // Moved from private to protected to here - JB
    virtual BlitzLiveNet* createNetwork() ; 
    virtual WormSimEval* createEvaluator(BlitzLiveNet* prototypeNet) ; 
    AlopexThread* alopexThread ; 
//    ofstream* createOutputFileStream() ; 
    ofstream* createOutputFileStream(const char* outputFile) ; 
    BlitzNetAlopexer* createAlopex() ; 

    // commands
    const static string START_SIMWORM ; 
    const static string START_ALOPEXER ; 
    const static string STOP_ALOPEXER ; 

protected:
    // network values
	friend class AlopexThread ; 
    string mNetworkFile; 
    string mBestNetworkFile ; 
    string mOutputFile; 
    double mStimDeltaT ; 
    double mRelaxTime ;
		double mOutputSigmoid ;

    // wormsim values
    int mNumWorms ; 
    int mNumWormSteps ; 
    double mHighMapValue ; 
    double mLowMapValue ; 
    double mDiameter ; 
		double mOptimumRadius ;
    double mForwardVelocity ; 
    double mTurnVelocity; 
    double mDeltaT ; 

    // optimization data
    int mNumNetworks; 
		double mCriticalAcceptance ; 
			

    // alopex variables
    double mMinError ; 
    int mTotalIterations ; 
    double mAlopexLambda ; 
    double mAlopexDelta ;
		double mAlopexBeta ;
		
		// output variables
		int mOutputPeriod ;


} ;

#endif /* ifndef EVOALOPEXERDRIVER_HPP_ */
// -*- C++ -*-
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: AlopexDriver.hpp,v 1.3 2004/01/27 20:27:19 ndunn Exp $

