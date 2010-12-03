/*
 * $Id$
 */
#ifndef INPUTTRACER_HPP
#  define INPUTTRACER_HPP

#include <vector>
using std::vector ; 

class BlitzNet ; 
class BlitzEulerLiveNetEvaluator ; 

/**
 *  Class converts sensory input to neural activity output.
 */
class InputTracer {

  public:
		InputTracer() ; 
		virtual int generateTrace(string inputTrace,string inputNetwork,string outputTrace, bool doPlot) ; 

	protected:
		virtual void dumpOutput(vector<vector<double>*>*  data,string outputTrace) ; 
		virtual void plot(vector<vector<double>*>*  data) ; 
    BlitzNet* mOrigNet ; 
    BlitzEulerLiveNetEvaluator* mOrigEval ; 
		string mTitleName ; 
		double mRelaxTime ; 

} ;

#endif /* ifndef INPUTTRACE_H */
// -*- C++ -*-

// (C) 2006 by Nathan Dunn, <ndunn@mac.com>


