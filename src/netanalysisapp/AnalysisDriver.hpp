#ifndef ANALYSISDRIVER_HPP_
#  define ANALYSISDRIVER_HPP_


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
class BlitzEulerNetEvaluator ; 
class Gnuplot ; 
class TextEvalTrace ; 
class LabelSet ; 
/**
 *  This class runs that actual Analysisr. 
 *
 */

class AnalysisDriver : public TiFlatBaseApp {

public:
//    AnalysisDriver() ; 
    AnalysisDriver(string newInterfaceName, string newTypeName, AppInterface* newParent) ; 
    LabelSet* analysis0thOrder() ; 
    LabelSet* analysis1stOrder() ; 
    LabelSet* analysis2ndOrder() ; 
    LabelSet* analysisGeneral() ; 
    void* startPlotter() ; 
    void* analysisAndPlot() ; 
    int message(string caption,string text) ; 
    void setRenderer(Renderer* newRenderer) ; 

    // AppInterface classes
    bool createLocalMaps() ; 
    string doLocalCommand(Command *theCommand) ; 

    virtual BlitzLiveNet* createNetwork() ; 
    virtual BlitzEulerNetEvaluator* createEvaluator(BlitzLiveNet* prototypeNet) ; 
    ofstream* createOutputFileStream(const char* outputFile) ; 

    // commands
    const static string START_ANALYSIS ; 
    const static string START_PLOTTER ; 
    const static string ANALYSIS0THORDER ; 
    const static string ANALYSIS1STORDER ; 
    const static string ANALYSIS2NDORDER ; 
    const static string ANALYSISGENERAL; 

protected:

    // plotter value/methods
    virtual void initPlotter(int size ) ; 
    virtual void* plotPulseFromNet(BlitzLiveNet* plotNet) ; 
    virtual void* plotPulseFromModel(LabelSet* newLabelSet) ; 
    virtual void* plotPulseModelError(LabelSet* newLabelSet) ; 
    virtual BlitzLiveNet* loadNet() ; 
    vector<Gnuplot*>*  mPlotVector ; 
    // network values
    string mNetworkFile, mOutputFile; 
    double mStimDeltaT , mRelaxTime ,mRelaxLimit, mOutputSigmoid , mDeltaT  ; 
    int mNumInputs ; 

    // pulse values
    double mBaseline, mPulse, mPulseAt, mPulseDuration, mTotalTime ; 

    // prune values
    string mBestNetworkFile ; 
    double mActivityThreshold ; 

    // tracer
    TextEvalTrace* mTracer ; 


} ;

#endif /* ifndef ANALYSISERDRIVER_HPP_ */
// -*- C++ -*-
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: AnalysisDriver.hpp,v 1.3 2004/01/27 20:27:19 ndunn Exp $

