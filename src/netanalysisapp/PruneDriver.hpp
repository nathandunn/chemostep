#ifndef PRUNEDRIVER_HPP_
#  define PRUNEDRIVER_HPP_


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
class BlitzEulerLiveNetEvaluator ; 
class Gnuplot ; 
class TextEvalTrace ; 
/**
 *  This class runs that actual Pruner. 
 *
 */

class PruneDriver : public TiFlatBaseApp {

public:
//    PruneDriver() ; 
    PruneDriver(string newInterfaceName, string newTypeName, AppInterface* newParent) ; 
    void* startPruner() ; 
    void* startPlotter() ; 
    int message(string caption,string text) ; 
    void setRenderer(Renderer* newRenderer) ; 

    // AppInterface classes
    bool createLocalMaps() ; 
    string doLocalCommand(Command *theCommand) ; 

    // Moved from private to protected to here - JB
    virtual BlitzLiveNet* createNetwork() ; 
    virtual BlitzEulerNetEvaluator* createEvaluator(BlitzLiveNet* prototypeNet) ; 
    ofstream* createOutputFileStream(const char* outputFile) ; 

    // commands
    const static string START_PRUNER ; 
    const static string START_PLOTTER ; 
    const static string STOP_PRUNER ; 

protected:

    // plotter value/methods
    void* plotPulse(BlitzLiveNet* plotNet) ; 
    Gnuplot* mPlotter ; 
    // network values
    string mNetworkFile, mOutputFile; 
//    double mStimDeltaT , mRelaxTime ,mRelaxLimit, mOutputSigmoid , mDeltaT  ;
    double mStimDeltaT , mRelaxTime, mOutputSigmoid , mDeltaT  ;
    int mNumInputs ; 

    // pulse values
    double mBaseline, mPulse, mPulseAt, mPulseDuration, mTotalTime ; 

    // prune values
    string mBestNetworkFile ; 
    double mActivityThreshold ; 

    // tracer
    TextEvalTrace* mTracer ; 




} ;

#endif /* ifndef PRUNEERDRIVER_HPP_ */
// -*- C++ -*-
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: PruneDriver.hpp,v 1.3 2004/01/27 20:27:19 ndunn Exp $

