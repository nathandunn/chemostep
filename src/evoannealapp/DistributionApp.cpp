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

// input file stuff
#include <TinyBzNetParser.hpp> 
#include <FileFeeder.hpp> 

// wormsim stuff
#include <TennisCourtMap.hpp> 
#include <OneWormMapSpace.hpp> 
#include <OneWormSimEval.hpp> 
#include <SimpleWorm.hpp> 
#include <TennisCourtAwayShuffler.hpp> 
#include <TennisCourtSetPositionShuffler.hpp> 
#include <UniformNetBehaviorTemplate.hpp> 
#include <StraightFwdMovementTemplate.hpp> 
#include <SharpTurnMovementTemplate.hpp> 
#include <ReflectMovementTemplate.hpp> 
#include <RicochetMovementTemplate.hpp> 
#include <RandomReflectMovementTemplate.hpp> 
#include <WormTrack.hpp> 


// output file stuff
#include <TextEvalTrace.hpp> 


// plotting stuff
#include <gnuplot_i.hpp>

#include "AutoOptionList.hpp"
#include "DistributionApp.hpp"

DistributionApp::DistributionApp(int argc,char *argv[]) :
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


//  if(true){
//    cout << getOptionValueText() << endl ; 
//  }
	
	RNG::initSeed() ; 
  struct timeval t;
  gettimeofday(&t,0);
	srand(t.tv_sec) ; 
}

BlitzLiveNet* DistributionApp::createNetwork() 
{
	 
    if(mOrigNet==NULL){
        mOrigNet = (BlitzLiveNet*) (new TinyBzNetParser())->parseFile(mNetworkFile) ;   
    }
    else{
        *mOrigNet = *((BlitzLiveNet*) (new TinyBzNetParser())->parseFile(mNetworkFile)) ;   
    }
//    mOrigNet->setPerturber( new BlitzEulerWrapPerturber(30) ) ; 
//    (mOrigNet->getNote())->setNote("description",mDescription) ;

    return mOrigNet; 
}


OneWormSimEval* DistributionApp::createEvaluator(BlitzLiveNet* prototypeNet,int numWorms/*-1*/) 
{
		prototypeNet->setTrace(true) ; 

    if(mOrigEval==NULL){
				mOrigEval = new OneWormSimEval() ; 
    }

    mOrigEval->setTarget(mTargetX) ; 
    mOrigEval->setMinDeltaT(mDeltaT) ; 

//    mOrigEval->setRelaxTime(5) ; 
//    mOrigEval->setRelaxLimit(0.01) ; 
//    mOrigEval->setRelaxTime(mRelaxTime) ; 
//    mOrigEval->setRelaxLimit(mRelaxLimit) ; 

    mOrigEval->setNetwork(prototypeNet) ; 

    // SET MAP
//    TennisCourtMap* newMap = NULL ; 
    Map* newMap = NULL ; 
		newMap = new TennisCourtMap(mWidth,mHeight,mTargetX,mLowValue,mTargetValue,mHighValue) ; 


    // SET MAPSPACE
    OneWormMapSpace* newMapSpace = new OneWormMapSpace( ) ; 
    newMapSpace->setMaxWormCount(numWorms) ; 
    mNumWormSteps =  (int)(  mSimTime / mDeltaT ) ; 
//    cout << "mNumWormSteps[" << mNumWormSteps  << "] " << endl ; 
    newMapSpace->setWormStepCount(mNumWormSteps ) ; 
    newMapSpace->setMap(newMap) ; 

    // SET SHUFFLER
//    newMapSpace->setWormShuffler(new TennisCourtAwayShuffler( (TennisCourtMap*) newMap,mSpaceFromTarget)) ; 
		newMapSpace->setWormShuffler(new TennisCourtSetPositionShuffler( (TennisCourtMap*) newMap,mStartX)) ; 

    mOrigEval->setMapSpace( newMapSpace) ;  

    // SET WORM
    SimpleWorm* newWorm = new SimpleWorm(newMapSpace) ; 
    BlitzLiveNet* wormNet = new BlitzLiveNet( prototypeNet) ; 

    // is this really necessary?, maybe to set other things
    BlitzNetEvaluator* wormEval = NULL ; 
		wormEval = new BlitzEulerLiveNetEvaluator( mDeltaT,mOutputSigmoid,wormNet) ; 
    wormEval->resetTrace( mNumWormSteps*numWorms  , mNumWormSteps*numWorms  ) ; 
    wormNet->setEvaluator( wormEval  ) ; 
    BlitzNetEvaluator* wormBehaviorEval = NULL ; 
		wormBehaviorEval = new BlitzEulerLiveNetEvaluator( mDeltaT,mOutputSigmoid,wormNet) ; 
    wormBehaviorEval->resetTrace( mNumWormSteps*numWorms , mNumWormSteps*numWorms ) ; 


   // SET WORM EVAL NETWORK
    newWorm->setBehaviorModel( new UniformNetBehaviorTemplate<SimpleWorm>( wormNet, newWorm, wormBehaviorEval , mNumInputs ) ) ; 
    newWorm->setForwardMovementModel(new StraightFwdMovementTemplate<SimpleWorm>(mForwardVelocity*mDeltaT)) ;  // left and right turning bias
    newWorm->setTurningMovementModel(new SharpTurnMovementTemplate<SimpleWorm>(mDeltaT*50.0,mTurnVelocity*mDeltaT)) ; // sharp-turn value
		if(mBounceStyle=="rr"){
			newWorm->setBounceModel(new RandomReflectMovementTemplate<SimpleWorm>(2.0*mTurnVelocity*mDeltaT) ) ; // sharp-turn value
		}
		else
		if(mBounceStyle=="reflect"){
			newWorm->setBounceModel(new ReflectMovementTemplate<SimpleWorm>(2.0*mTurnVelocity*mDeltaT) ) ; // sharp-turn value
		}
		else
		if(mBounceStyle=="ric"){
			newWorm->setBounceModel(new RicochetMovementTemplate<SimpleWorm>(2.0*mTurnVelocity*mDeltaT) ) ; // sharp-turn value
 	  }
    newMapSpace->setWorm( newWorm) ; 
    

    return mOrigEval ;
}


void DistributionApp::initOptions() 
{ 
	setBinary("distributionapp") ; 
	addInt(&mNumRuns,"runs","Number of runs.",1) ; 
	addDouble(&mSimTime,"time","Evaluation time.",1200.0) ; 
	addOption(&mNetworkFile,"network","Network to evaluate.") ; 
	addOption(&mBounceStyle,"bounce","Bounce style: random reflect (rr), reflect (reflect), and ricochet (ric).","rr") ; 
	addOption(&mOutputTrace,"output","File to dump output trace.","temptrace.txt") ; 
	addDouble(&mTargetX,"target","Target X.",15.0) ; 
	addDouble(&mWidth,"width","Map width.",30.0) ; 
	addDouble(&mHeight,"height","Map height.",30.0) ; 
	addDouble(&mLowValue,"low","Low map value.",-2.5) ; 
	addDouble(&mTargetValue,"middle","Target map value.",0.5) ; 
	addDouble(&mHighValue,"high","high map value.",3.5) ; 
	addDouble(&mForwardVelocity,"forwardv","Forward velocity.",0.015) ; 
	addDouble(&mTurnVelocity,"turnv","Turn velocity.",0.011) ; 
	addFlag(&mDoPlot,"plot","Plot output.",false) ; 
//  addDouble(&mSpaceFromTarget,"space","Space from target.",0.0) ;
	addDouble(&mStartX,"startx","Start X-Position.",15.0) ;

}



int DistributionApp::generateTrace() 
{
	char input = '0' ; 
	cout << "any key to continue, ctrl-c to quit" << endl ; 
  do
	{
    // we do it this way, because we need the SAME for the file
    // and the plot
    pair<vector<double>*,vector<double>*>* trackPair = dumpWorm() ;
    vector<double>* xVec = trackPair->first ; 
    vector<double>* yVec = trackPair->second ; 
    
		
		// plot?
		if(mDoPlot){
		 plotWorm(xVec,yVec) ; 
		}
		else{
		 cout << "NOT plotting data" << endl ; 
		}
	}
	while(cin >> input) ;

	return 1 ; 
}

pair<vector<double>*,vector<double>*>* DistributionApp::evalWorm() 
{
		createNetwork() ; 
//    mOrigNet->setEvaluator( createEvaluator(mOrigNet,1,1)) ; // create evaluator with 1 worm
		mOrigNet->setEvaluator( createEvaluator(mOrigNet,mNumRuns)) ; // create evaluator with 1 worm
    mOrigNet->setEvaluator( mOrigEval) ; // create evaluator with 1 worm
    mTracer = new TextEvalTrace() ; 
    mTracer->setTimeDelimiter(",") ; 
    mTracer->setEvaluator( mOrigNet->getEvaluator() ) ; 
    cout << "eval: " << mOrigNet->eval() << endl ; 

    vector<double>* xVec = new vector<double>() ; 
    vector<double>* yVec = new vector<double>() ; 

    vector<WormTrack*>* wormTracks = ( (OneWormSimEval*) mOrigNet->getEvaluator())->getWormTracks() ; 
    for(int wormNumber = 0 ; wormNumber < wormTracks->size() ; wormNumber++){
        for(int stepNumber = 0 ; stepNumber < ((*wormTracks)[wormNumber])->rows() ; stepNumber++){
            xVec->push_back(  (*(*wormTracks)[wormNumber])(stepNumber,0)  ) ; 
            yVec->push_back(  (*(*wormTracks)[wormNumber])(stepNumber,1)  ) ; 
        }
    }

    return new pair<vector<double>*,vector<double>*>(xVec,yVec) ; 
}


/// This method dumps out worm tracks, neural activity and input data to a file kind of named for the input network.
pair<vector<double>*,vector<double>*>* DistributionApp::dumpWorm() 
{
    pair<vector<double>*,vector<double>*>* trackPair = evalWorm() ; 
    vector<double>* xVec = trackPair->first ; 
    vector<double>* yVec = trackPair->second ; 
   
    
    
    vector<vector<double>*>* neuronTrace = ( ( (OneWormSimEval*) mOrigNet->getEvaluator())->getWormEval())->getLastFullTraceAsSeries() ; 
    int numNeurons = neuronTrace->size() ; 

//    string outputFile = mNetworkFile.substr(mNetworkFile.find_last_of("/")+1) ; 
//    string outputFile = mOutputTrace.substr(mOutputTrace.find_last_of("/")+1) ; 
//    outputFile = outputFile.substr(0,outputFile.find_last_of("."))+"_trace.txt" ; 
//    ofstream *of = new ofstream(outputFile.c_str(), ios::out) ; 
    ofstream *of = new ofstream(mOutputTrace.c_str(), ios::out) ; 


		// for each run, create a header? or better, just for X
		for(int run = 0 ; run < mNumRuns ; run++){
			*of << "X"  << run ; 
			*of << "\t" ; 
		}
		*of << endl ; 
		
		int calculatedTimeStep ; 
		int numTimeSteps = (int) (mSimTime / mDeltaT) ; 
		for(int timeStep = 0 ; timeStep < numTimeSteps ; timeStep++){
			for(int run = 0 ; run < mNumRuns ; run++){
				 calculatedTimeStep = timeStep + (run*numTimeSteps) ; 
					*of << (*xVec)[ timeStep + (run*numTimeSteps)] << " "  ; 
					*of << "\t" ; 
			}
			*of << endl ; 
	}

    of->close() ; 
    delete of ; 

    return trackPair ; 
}

void DistributionApp::plotWorm(vector<double>* xVec,vector<double>* yVec) 
{

	if(mTrackPlotter==NULL){
        mTrackPlotter = new Gnuplot("lines") ; 
    }
    else{
        mTrackPlotter->reset_plot() ; 
    }


    // create title
    mTitleName = mNetworkFile.substr(mNetworkFile.find_last_of("/")+1) ; 
//    setOutput( mTrackPlotter,mTitleName+"worm") ; 
    ostringstream* thisStream = new ostringstream() ; 

    thisStream->str("") ; 
//    *thisStream << "set terminal " << mOutputType << " ; " << endl ; 
    string outputType = "x11" ; 
    *thisStream << "set terminal " << outputType << " ; " << endl ; 
    *thisStream << "set output \"" << mTitleName << "." << outputType << "\" ; " << endl ; 
    mTrackPlotter->cmd(  (thisStream->str()).c_str() ) ; 

    // plot to screen
    plotTennisTracks(xVec,yVec, (TennisCourtMap*) (((OneWormSimEval*) mOrigNet->getEvaluator())->getMapSpace())->getMap(),mTitleName) ; 


    // FOR NEW PLOT
//    mTrackPlotter = NULL ; 
//    delete mTrackPlotter ; 
	 
}




int DistributionApp::run() 
{
	 generateTrace() ;
}


int main(int argc,char** argv){
//  RNG::initSeed();
//  for(int i = 0 ; i < 20 ; i++) drand48() ; // pull off a few
	DistributionApp app(argc,argv) ; 
  return app.run() ; 
//  cout << test.getOptionXML() << endl ; 
}

void DistributionApp::plotTennisTracks(vector<double>* xTracks,vector<double>* yTracks,TennisCourtMap* newMap,string titleName/*""*/) 
{
    double width = newMap->getWidth() ; 
    double height = newMap->getHeight() ; 
    double targetX = newMap->getTargetX() ; 
    ostringstream* commands = NULL ; 

      mTrackPlotter->cmd( "set size square 1,1" ) ; 
      mTrackPlotter->cmd("set xlabel 'X'") ; 
      mTrackPlotter->cmd("set ylabel 'Y'") ; 
      mTrackPlotter->cmd("set grid") ; 
      mTrackPlotter->cmd("unset key") ; 
      commands = new ostringstream() ; 
      // remainder of title
      // can also get it from others, as well
      *commands << "set title \"" << titleName <<  "\\n" ; 
      *commands << "targetX=" << targetX << "\" ; " ; 
      *commands << "set xrange [0:" << width << "] ;" ; 
      *commands << "set yrange [0:" << height << "] ;" ; 
      mTrackPlotter->cmd( (commands->str()).c_str() ) ; 
      mTrackPlotter->cmd( "set multiplot ; " ) ; 
      mTrackPlotter->plot_xy( *(new vector<double>(*xTracks)),  *(new vector<double>(*yTracks)),"Worm Track" ) ; 

     
      // set multiplot to draw in the other garbage
      // PLOT TARGETX 
      vector<double>* xData = new vector<double>() ; 
      vector<double>* yData = new vector<double>() ; 
			xData->push_back(mTargetX) ; 
			xData->push_back(mTargetX) ; 
      yData->push_back(0) ; 
			yData->push_back(mHeight) ; 
      mTrackPlotter->plot_xy( *xData, *yData, "Target X" ) ; 

      // PLOT SPACE-STARTING X
//      (*xData)[0] = (mTargetX-mSpaceFromTarget) ; 
//      (*xData)[1] = (mTargetX-mSpaceFromTarget) ; 
			(*xData)[0] = (mStartX) ; 
			(*xData)[1] = (mStartX) ; 
      mTrackPlotter->plot_xy( *xData, *yData, "W start-X" ) ; 

      // PLOT SPACE-STARTING X
//      (*xData)[0] = (mTargetX+mSpaceFromTarget) ; 
//      (*xData)[1] = (mTargetX+mSpaceFromTarget) ; 
//      mTrackPlotter->plot_xy( *xData, *yData, "E start-X" ) ; 


      // unset 
      mTrackPlotter->cmd("set nomultiplot ; ") ; 
      
	  
}


// -*- C++ -*-

// (C) 2006 by Nathan Dunn, <ndunn@mac.com>


