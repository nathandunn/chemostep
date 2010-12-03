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

/**
 *  Class converts sensory input to neural activity output.
 */
class InputTracerAuto : public AutoOptionList {

  public:
		InputTracerAuto(int argc,char *argv[]) ; 
		virtual int generateTrace(string inputTrace,string inputNetwork,string outputTrace, bool doPlot) ; 
		virtual int run() ; 

	protected:
			// AutoOptionList method
		virtual void initOptions() ; 

		// app methods
		virtual void dumpOutput(vector<vector<double>*>*  data,string outputTrace) ; 
		virtual void plot(vector<vector<double>*>*  data) ; 
    BlitzNet* mOrigNet ; 
    BlitzEulerLiveNetEvaluator* mOrigEval ; 
		string mTitleName ; 

		// app variables 
		string mInputTrace, mOutputTrace, mNetwork ; 
		double mRelaxTime ; 
		bool mDoPlot ; 

} ;

#endif /* ifndef INPUTTRACE_H */
// -*- C++ -*-

// (C) 2006 by Nathan Dunn, <ndunn@mac.com>


