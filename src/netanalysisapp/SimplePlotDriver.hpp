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

class SimplePlotDriver : public TiFlatBaseApp {

public:
    SimplePlotDriver(string newInterfaceName, string newTypeName, AppInterface* newParent) ; 
    void* startPlotter() ; 
    int message(string caption,string text) ; 
    void setRenderer(Renderer* newRenderer) ; 

    // AppInterface classes
    bool createLocalMaps() ; 
    string doLocalCommand(Command *theCommand) ; 

    // Moved from private to protected to here - JB
    virtual BlitzLiveNet* createNetwork() ; 
    virtual BlitzNetEvaluator* createEvaluator(BlitzLiveNet* prototypeNet) ; 
    ofstream* createOutputFileStream(const char* outputFile) ; 

    // commands
    const static string START_PLOTTER ; 

protected:

    // plotter value/methods
    void* plotPulse(BlitzLiveNet* plotNet) ; 
    void* dumpTrace(BlitzLiveNet* plotNet ,string dumpFile) ; 
    Gnuplot* mPlotter ; 
    ostringstream* mCommandStream ; 
    // network values
    string mNetworkFile, mOutputFile; 
    double  mRelaxTime, mOutputSigmoid ,mRelaxLimit ;
    double mDeltaT ; 
    int mNumInputs ; 
    bool mDoMidPoint ; 

    // pulse values
    double mBaseline, mPulse, mPulseAt, mPulseDuration, mTotalTime ; 

    // plotting options
    vector<string>* mTempType ; 
    string mLineType ; 
    double mYLow, mYHigh ; 



} ;

#endif /* ifndef PRUNEERDRIVER_HPP_ */
// -*- C++ -*-
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: SimplePlotDriver.hpp,v 1.3 2004/01/27 20:27:19 ndunn Exp $

