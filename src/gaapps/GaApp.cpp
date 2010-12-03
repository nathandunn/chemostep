#include <iostream>
using std::cout ; 
using std::endl ; 

#include <vector>
using std::vector ; 

#include <fstream>
using std::ofstream ; 

// simulation files
// Init Random Number Generator
#include <RNG.hpp> 
//#include <blitzdefs.hpp> 
#include <BlitzEulerLiveNetEvaluator.hpp>   
#include <BlitzNet.hpp>
#include <GAAlgorithm.hpp>
#include <BlitzGAAlgorithm.hpp>

// input file stuff
#include <TinyBzNetParser.hpp> 
#include <FileFeeder.hpp> 

// output file stuff
#include <TextEvalTrace.hpp> 


// plotting stuff
#include <gnuplot_i.hpp>

#include "AutoOptionList.hpp"
#include "GaApp.hpp"

GaApp::GaApp(int argc,char *argv[]) :
	AutoOptionList(argc,argv)
	,mDeltaT(1.0)
	,mOutputSigmoid(30.0)
	,mNumInputs(2)
	,mOrigNet(NULL)
	,mOrigEval(NULL)
	,mTrackPlotter(NULL)
{
	initOptions() ; 
	parseOption() ; // for every input map to variables
	standardOptions() ; 

	
	RNG::initSeed() ; 
  struct timeval t;
  gettimeofday(&t,0);
	srand(t.tv_sec) ; 
}

int GaApp::run() 
{
	cout << "running GaApp " << endl  ; 
}


BlitzNet* GaApp::createNetwork() 
{
	 
    if(mOrigNet==NULL){
        mOrigNet = (BlitzNet*) (new TinyBzNetParser())->parseFile(mNetworkFile) ;   
    }
    else{
        *mOrigNet = *((BlitzNet*) (new TinyBzNetParser())->parseFile(mNetworkFile)) ;   
    }
//    mOrigNet->setPerturber( new BlitzEulerWrapPerturber(30) ) ; 
//    (mOrigNet->getNote())->setNote("description",mDescription) ;

    return mOrigNet; 
}


BlitzEulerLiveNetEvaluator* GaApp::createEvaluator(BlitzNet* prototypeNet,int numWorms/*-1*/) 
{

	  mOrigEval = new BlitzEulerLiveNetEvaluator() ; 

    return mOrigEval ;
}


void GaApp::initOptions() 
{ 
	setBinary("distributionapp") ; 
	addDouble(&mSimTime,"time","Evaluation time.",1200.0) ; 
	addOption(&mNetworkFile,"network","Network to evaluate.") ; 
	addFlag(&mDoPlot,"plot","Plot output.",false) ; 

}




int main(int argc,char** argv){
//  RNG::initSeed();
//  for(int i = 0 ; i < 20 ; i++) drand48() ; // pull off a few
	GaApp app(argc,argv) ; 
  return app.run() ; 
//  cout << test.getOptionXML() << endl ; 
}



// -*- C++ -*-

// (C) 2006 by Nathan Dunn, <ndunn@mac.com>


