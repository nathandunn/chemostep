#ifndef ANALYSISDRIVER_HPP_


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

class PlotDriver : public TiFlatBaseApp {

public:
//    PlotDriver() ; 
    PlotDriver(string newInterfaceName, string newTypeName, AppInterface* newParent) ; 
    void setRenderer(Renderer* newRenderer) ; 

    // AppInterface classes
    bool createLocalMaps() ; 
    string doLocalCommand(Command *theCommand) ; 

    virtual BlitzLiveNet* createNetwork() ; 
    virtual BlitzNetEvaluator* createEvaluator(BlitzLiveNet* prototypeNet) ; 
    ofstream* createOutputFileStream(const char* outputFile) ; 
    virtual void* dumpTraceFromNet(BlitzLiveNet* plotNet,string dumpFile) ; 

    // commands
    const static string START_PLOTTER ; 

protected:
    // plotter value/methods
    virtual void initPlotter(int size ) ; 
    virtual void* plotPulseFromNet(BlitzLiveNet* plotNet) ; 
    virtual BlitzLiveNet* loadNet() ; 
    virtual void setOutput(Gnuplot* aPlot,int counter = 0) ; 
    vector<Gnuplot*>*  mPlotVector ; 
    bool mPlotMultiple ,mPlotVersusInput ; 
    // network values
    string mNetworkFile,  mInputFile , mNeuronOutput ; 
    vector<string>* mInputList ; 
    vector<string>* mNetworkList; 
    double mStimDeltaT , mRelaxTime ,mRelaxLimit, mOutputSigmoid , mDeltaT ; 

    // pulse values
    double  mBaseline ;  // set from the first point
    int mNumInputs , mScale ; 
    bool mDoMidPoint, mDoPlot,mDoSimpleOutput  ; 

    // plotting options
    vector<string>* mTempType ; 
    string mLineType ; 
    vector<string>* mOutputList; 
    string mOutputType ; 

    // tracer
    TextEvalTrace* mTracer ; 

    // text
    string mTitleString ; 

} ;

#endif /* ifndef ANALYSISERDRIVER_HPP_ */
// -*- C++ -*-
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: PlotDriver.hpp,v 1.3 2004/01/27 20:27:19 ndunn Exp $

