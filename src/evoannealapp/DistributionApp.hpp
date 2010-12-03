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
class TennisCourtMap; 
class OneWormMapSpace ; 
class SimpleWorm ; 
class Gnuplot ; 

/**
 *  Class runs a TennisMapp N times, and plots the distribution at every second.
 */
class DistributionApp : public AutoOptionList {

  public:
		DistributionApp(int argc,char *argv[]) ; 
//    virtual int generateTrace(string inputTrace,string inputNetwork,string outputTrace, bool doPlot) ; 
		virtual int generateTrace() ; 
		virtual int run() ; 

	protected:
			// AutoOptionList method
		virtual void initOptions() ; 

		// app methods
    virtual OneWormSimEval* createEvaluator(BlitzLiveNet* prototypeNet,int numWorms=-1) ; 
    virtual BlitzLiveNet* createNetwork() ; 
		virtual void plotWorm(vector<double>* xVec,vector<double>* yVec) ; 
    virtual pair<vector<double>*,vector<double>*>* dumpWorm() ; 
    virtual pair<vector<double>*,vector<double>*>* evalWorm() ; 
    virtual void plotTennisTracks(vector<double>* xTracks,vector<double>* yTracks,TennisCourtMap* newMap,string titleName="") ; 
    BlitzLiveNet* mOrigNet ; 
    OneWormSimEval* mOrigEval ; 
		string mTitleName ; 
		TennisCourtMap* mMap ; 
		OneWormMapSpace* mMapSpace ; 
		SimpleWorm* mWorm ; 
		BlitzLiveNet* mWormNet ; 
		Gnuplot* mTrackPlotter; 
		TextEvalTrace* mTracer ; 
		
	
		// default variables
		double mDeltaT ; 
//    double mSpaceFromTarget ; 
		double mStartX; 
		double mOutputSigmoid ; 
		int mNumInputs ; 


		// app variables 
		string mOutputTrace; 
		string mNetworkFile ; 
		string mBounceStyle ; 
		int mNumRuns; 
		int mNumWormSteps ; 
		double mSimTime ;
		bool mDoPlot ; 
		double mTargetX,  mWidth, mHeight; 
		double mLowValue,  mTargetValue, mHighValue; 
		double mForwardVelocity, mTurnVelocity ; 

} ;

#endif /* ifndef INPUTTRACE_H */
// -*- C++ -*-

// (C) 2006 by Nathan Dunn, <ndunn@mac.com>


