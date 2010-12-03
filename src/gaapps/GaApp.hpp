/*
 * $Id$
 */
#ifndef DISTRIBUTIONAPP_HPP 
#  define DISTRIBUTIONAPP_HPP 

#include <vector>
using std::vector ; 

#include "AutoOptionList.hpp"

class BlitzNet ; 
class BlitzEulerLiveNetEvaluator ; 
class Gnuplot ; 

/**
 *  Class runs a TennisMapp N times, and plots the distribution at every second.
 */
class GaApp : public AutoOptionList {

  public:
		GaApp(int argc,char *argv[]) ; 
//    virtual int generateTrace(string inputTrace,string inputNetwork,string outputTrace, bool doPlot) ; 
		virtual int run() ; 

	protected:
			// AutoOptionList method
		virtual void initOptions() ; 

		// app methods
    virtual BlitzEulerLiveNetEvaluator* createEvaluator(BlitzNet* prototypeNet,int numWorms=-1) ; 
    virtual BlitzNet* createNetwork() ; 
    BlitzNet* mOrigNet ; 
    BlitzEulerLiveNetEvaluator* mOrigEval ; 
		Gnuplot* mTrackPlotter; 
		TextEvalTrace* mTracer ; 
		
	
		// default variables
		double mDeltaT ; 
		double mOutputSigmoid ; 
		int mNumInputs ; 

		// app variables 
		string mNetworkFile ; 
		double mSimTime ;
		bool mDoPlot ; 

} ;

#endif /* ifndef INPUTTRACE_H */
// -*- C++ -*-

// (C) 2006 by Nathan Dunn, <ndunn@mac.com>


