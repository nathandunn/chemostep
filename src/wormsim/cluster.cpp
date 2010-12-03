
#include <iostream>

#include <strstream>
using std::ostrstream;

#include "MapSpace.hpp"
#include "Worm.hpp"
#include "ClusterWorm.hpp"
#include "MapData.hpp"
#include "LinRadialMap.hpp"
#include "PowerRadialMap.h"
#include "GaussRadialMap.h"
#include "ForwardBehaviorModel.h"
#include "ShortMemoryBehaviorModel.h"
#include "NetworkBehaviorModel.h"
#include "Mode3NetworkBehaviorModel.h"
#include "Logger.h"
#include "LiveNet.h"
#include "blitzdefs.h"
#include "OptionList.h"
#include "NetReader.h" 
#include "DualLimitErrorModel.hpp"

enum { VERB_LOTS, VERB_SOME,VERB_NONE} ;

// option variables
//
char   mapType;		    // -map c 
int    numWorms ;		// -num v 
double centerRadius;	// -center v 
float  minTurn ;		// -turn v 
double numSteps;		// -steps v 
double timeStep;		// -dt v 
double loFilter;		// -lofilter v
double hiFilter;		// -hifilter v
int    outputPrecision; // -prec v
int    outputWidth;     // -wid v
string dumpFileName;    // -dump fileName
string networkFile ;    // -net fileName 
int verbosity ;          // -v v
double gradientPower;   // -power v
double pirForward;     	// -pfor v
double forForward;     	// -ffor v
double pirProb;     	// -pprob v
double forProb;     	// -fprob v
double midProb;     	// -mprob v
double maxConc ;        // -maxc v
double minConc ;        // -minc v
double wormX ;          // -wormx v
double wormY ;          // -wormy v
double wormTheta ;      // -wormtheta v
double diameter;        // -diam v
double noise;			// -noise v 
double leftBias;		// -lfwd v
double rightBias;		// -rfwd v


MapData* getMap(){
   
    MapData* map = 0 ; 
    // get the write map type
    switch(mapType){
		
        
        case 'p': map = new PowerRadialMap(gradientPower,diameter,maxConc,minConc) ; 	
                  break ; 
        case 'g': map = new GaussRadialMap(diameter,maxConc,minConc) ; 	
                  break ; 
        default:
        case 'l': map = new PowerRadialMap(1,diameter,maxConc,minConc) ; 	
                  break ; 

    }
    return map ; 
    
} 

void runNSimulations(){
    cout <<"running simulation with " << numWorms << " worms." << endl ; 
    MapData *map = getMap() ; 
	// load map


    // create behavior model
    NetReader util ; 
   
    // create space
    MapSpace *space = new MapSpace() ; 
	
    // the space will keep track of where the "goal" is
    space->setCenterRadius(centerRadius,diameter/2.0,diameter/2.0) ;
    LiveNet* aNet = new LiveNet(util.loadNetwork(networkFile)) ; 
    ErrorModel* tempErrorModel = aNet->getErrorModel() ;
    if(tempErrorModel->getType().find(DUAL_LIMIT)>=0){
        if(loFilter==0){
            loFilter = (dynamic_cast<DualLimitErrorModel *>  (tempErrorModel))->getLowThresh() ; 
            cout << "setting low threshold from worm to: " << loFilter << endl ; 
        }
        if(hiFilter==1){
            hiFilter = (dynamic_cast<DualLimitErrorModel *>  (tempErrorModel))->getHighThresh() ; 
            cout << "setting high threshold from worm to: " << hiFilter << endl ; 
        }
    }
    delete tempErrorModel ; 
  
	// create and add worm
    for(int i = 0 ; i < numWorms ; i++){
        aNet->resetNeurons() ; 
        aNet->invalidate() ; 
        Worm* worm = new Worm(space,wormX,wormY,wormTheta,0,leftBias,rightBias) ; 
        worm->setBehaviorModel(new Mode3NetworkBehaviorModel(worm,aNet,noise,loFilter,hiFilter,forProb,pirProb,midProb)) ; 
//        worm->setBehaviorModel(new NetworkBehaviorModel(worm,aNet,noise,loFilter,hiFilter,forProb,pirProb)) ; 

        // set time and dt
        aNet->resetNeurons() ; 
        aNet->setTimeStep(timeStep) ; 

        worm->setForwardVelocity(forForward) ; 
        worm->setPirouetteVelocity(pirForward) ; 
        worm->setName("charlie") ; 
        worm->setTurningThreshold(minTurn) ; 
        space->addWorm(worm) ; 
    }



    // set output 
    string headerFile = "" ;
    ostrstream stringStream ; 
    Logger *log = Logger::getLogger(dumpFileName) ; 
    if(verbosity==VERB_SOME){
        cout << "some verbosity:" << verbosity << endl ; 
        for(int i = 0 ; i < numWorms ; i++){
            stringStream << "x" << i << " " ; 
            stringStream << "y" << i << " " ; 
            stringStream << "value" << i << " " ; 
        }
        stringStream << endl ; 
        headerFile = stringStream.str() ; 
//cout << "the header file" << headerFile << endl ; 
        space->setVerbosity(MapSpace::VERB_SOME) ; 
    	log->log(headerFile) ; 
    }else
    if(verbosity==VERB_LOTS){
        cout << "very verbose:" << verbosity << endl ; 
        for(int i = 0 ; i < numWorms ; i++){
            stringStream << "x" << i << " " ; 
            stringStream << "y" << i << " " ; 
            stringStream << "gradVal" << i << " " ; 
            stringStream << "netProb" << i << " " ; 
            stringStream << "netDec" << i << " " ; 
            stringStream << "netMov" << i << " " ; 
        }
        stringStream << endl ; 
        headerFile = stringStream.str() ; 
//cout << "the header file" << headerFile << endl ; 
        space->setVerbosity(MapSpace::VERB_LOTS) ; 
        log->log(headerFile) ; 
    }else{  // assume no verbosity
        cout << "no verbosity:" << verbosity << endl ; 
        headerFile = "" ; 
        space->setVerbosity(MapSpace::VERB_NONE) ; 
    }

    
    // run through loop
	space->setMap(map) ; 
    int wormState = MapSpace::SOME_RUNNING; 
	
    for(int i = 0 ; i < numSteps && wormState!=MapSpace::NO_RUNNING; i++){
    	wormState = space->moveWorms() ; 
        space->printWorms() ; 
        if(wormState==MapSpace::NO_RUNNING){
			cout <<" simulation finished after move: "<< i << endl ; 
        }
    }
    if(wormState!=MapSpace::NO_RUNNING){
		cout <<" simulation finished after all: " << numSteps << " moves "<< endl ; 
	}
	
   
    // run report on starting, stopping, compile stats
    cout << "average time at center: " << space->getAverageTimeAtCenter()  ; 
    cout << "  time at center: " << (100.0*space->getAverageTimeAtCenter()/numSteps) << " \%" << endl  ; 
    cout << "average time to center: " << space->getAverageTimeToCenter() ; 
    cout << "  time to center: " << (100.0*space->getAverageTimeToCenter()/numSteps) << " \%" << endl  ; 
    cout << " \% of time reached center: " << (100.0*space->getAverageReachedCenter())<< " \%" <<  endl  ; 
    cout << " \% of time worm died: " << (100.0*space->getAverageWormDies())<< " \%" <<  endl  ; 
    cout << " average output: " << space->getProbabilityAverage()<< " " <<  endl  ; 
    cout << "decision ratios, pirouette/middle/run : " ;
	cout << 100*space->getPirouetteDecisionRatio()<< "%/"  ;  
	cout << 100*space->getMiddleDecisionRatio()<< "%/"  ;  
	cout << 100*space->getRunDecisionRatio()<< "%"  ;  
	cout << endl ; 
    cout << "behavior ratios, sharp-turn/run : " ;
	cout << 100*space->getSharpTurnBehaviorRatio()<< "%/"  ;  
	cout << 100*space->getRunBehaviorRatio()<< "%"  ;  
	cout << endl ; 
    cout << "average concentration difference: " ;
	cout << space->getAverageConcentrationDiff()<< " mM/s"  ;  
	cout << endl ; 




}

/**
 *
 *  (finished) 1. Get lin-radial map to work.
 *  (finished) 1.2 Add Mapdata to MapSpace
 *  (finished) 2. Get the worm to hit edges. (should finish simulation)
 *  (finished) 2.2  Add timer to simulation. (should finish simulation)
 *  (finished) 3. Get data-dump to plot Igor-readable files (jp31 igor file procedure).
 *  (finished) 4. Tie in worm to a direct probability (dC/dt< 0 versus >0) and observe.
 *  (finisheD) 4.2.  Need probabilities of turns for each position.
 *  (finished) 5. Get the network portion to work.
 *  (finished) 5.2 Load the network from a file.
 *  (finished) 6. Get real turning distributions from Shawn/Serge.
 *
 */
void runSimulation(){
	// load map
	MapData *map = new PowerRadialMap(gradientPower,diameter,maxConc,minConc) ; 	
//	MapData *map = new GaussRadialMap(1,0.5,0) ; 	

    // create behavior model
    NetReader util ; 
    LiveNet* aNet = new LiveNet(util.loadNetwork(networkFile)) ; 
   
    // create space
    MapSpace *space = new MapSpace() ; 
	
    // the space will keep track of where the "goal" is
    space->setCenterRadius(centerRadius,diameter/2.0,diameter/2.0) ;
  
	// create and add worm
	Worm* worm = new Worm(space,wormX,wormY,wormTheta,0,leftBias,rightBias) ; 
    worm->setBehaviorModel(new NetworkBehaviorModel(worm,aNet,noise,loFilter,hiFilter,forProb,pirProb)) ; 
    worm->setForwardVelocity(forForward) ; 
    worm->setPirouetteVelocity(pirForward) ; 
    worm->setName("charlie") ; 
    worm->setTurningThreshold(minTurn) ; 

    space->addWorm(worm) ; 

    // set time and dt
	aNet->resetNeurons() ; 
	aNet->setTimeStep(timeStep) ; 


    // set output 
    string headerFile ;
    Logger *log = Logger::getLogger(dumpFileName) ; 
    if(verbosity==VERB_LOTS){
        cout << "very berbose:" << verbosity << endl ; 
        headerFile = "x1 y1 gradVal1 netProb1 netDec1 netMov1" ; 
        space->setVerbosity(MapSpace::VERB_LOTS) ; 
    	log->log(headerFile) ; 
    }else
    if(verbosity==VERB_SOME){
        cout << "some verbosity:" << verbosity << endl ; 
        headerFile = "x1 y1 value1" ; 
        space->setVerbosity(MapSpace::VERB_SOME) ; 
    	log->log(headerFile) ; 
    }else{  // assume no verbosity
        cout << "no verbosity:" << verbosity << endl ; 
        headerFile = "" ; 
        space->setVerbosity(MapSpace::VERB_NONE) ; 
    }

    
    // run through loop
	space->setMap(map) ; 
    int wormState = MapSpace::SOME_RUNNING; 

    for(int i = 0 ; i < numSteps ; i++){
    	wormState = space->moveWorms() ; 
        space->printWorms() ; 

//        space->printWorms(MapSpace::VERB_LOTS) ; 
//        space->printWorms(MapSpace::VERB_SOME) ; 
        if(wormState==MapSpace::NO_RUNNING){
			cout <<" simulation finished after move: "<< i << endl ; 
            //exit(1) ; 
        }
    }
	cout <<" simulation finished after all: " << numSteps << " moves "<< endl ; 
	
   
    // run report on starting, stopping, compile stats
    cout << "time at center: " << worm->getTimeAtCenter() << endl  ; 
    cout << "time to center: " << worm->getTimeToCenter()<< endl  ; 

}


// tests the map functions
void runMapTest() {
    cout << "running: " << numSteps << " steps at dt: "<< timeStep << endl ; 
    cout << "networkFile: " << networkFile << endl ; 

//	NeuralNet testNet ;
    NetReader util ; 
    LiveNet* aNet = new LiveNet(util.loadNetwork(networkFile)) ; 
	aNet->resetNeurons() ; 
	aNet->setTimeStep(timeStep) ; 
	cout << "testNet: " << aNet->getInitVmem() << endl ; 
    
	//MapData *map = new LinRadialMap(10,1,0) ; 	
//	MapData *map = new LinRadialMap(10,0.8,0) ; 	
	//MapData *map = new PowerRadialMap(6,1,0.8,0) ; 	
//MapData *map = new GaussRadialMap(10,0.8,0) ; 	
    MapData *map = new GaussRadialMap(diameter,maxConc,minConc) ; 	
	double x,y ; 
	x = diameter/2.0 ; 
	y = diameter/2.0 ; 
	cout << "x: " << x << " y: " << y << " value: " <<  map->getValue(x,y) << endl ; 
	x = diameter*0.7 ; 
	y = diameter/2.0 ; 
	cout << "x: " << x << " y: " << y << " value: " <<  map->getValue(x,y) << endl ; 
	x = diameter*0.9 ; 
	y = diameter*0.7 ; 
	cout << "x: " << x << " y: " << y << " value: " <<  map->getValue(x,y) << endl ; 
	x = diameter ; 
	y = diameter*0.5 ; 
	cout << "x: " << x << " y: " << y << " value: " <<  map->getValue(x,y) << endl ; 

    Logger *log = Logger::getLogger(dumpFileName) ; 
    //string headerFile = "x1 y1 value1 x2 y2 value2 x3 y3 value3" ; 
	//string headerFile = "x1 y1 gradVal1 netProb1 netDec1" ; 
    string headerFile = "x1 y1 value1" ; 
    log->log(headerFile) ; 
    MapSpace *space = new MapSpace() ; 
	//Worm* worm = new Worm(space,(float)12,(float)2,180) ; 
	//Worm* worm = new Worm(space,(float)0.8,(float)0.5,180) ; 
	Worm* worm = new Worm(space,4,4,0,0) ; 

	
    worm->setBehaviorModel(new NetworkBehaviorModel(worm,aNet,0,0.499,0.501,0.0,1.0)) ; 
    worm->setName("charlie") ; 
    space->addWorm(worm) ; 


	space->setMap(map) ; 
    int wormState = MapSpace::SOME_RUNNING; 
    for(int i = 0 ; i < numSteps ; i++){
    	wormState = space->moveWorms() ; 
        //space->printWorms(MapSpace::VERB_LOTS) ; 
        space->printWorms(MapSpace::VERB_SOME) ; 
        if(wormState==MapSpace::NO_RUNNING){
			cout <<" simulation finished after move: "<< i << endl ; 
            exit(1) ; 
        }
    }
	cout <<" simulation finished after all: " << numSteps << " moves "<< endl ; 
}

void runTest(){
  Logger *log = Logger::getLogger("thislog.txt") ; 
  cout << "running " << endl ; 

  MapSpace* space = new MapSpace() ; 
  MapData *map = getMap() ;
  space->setMap(map) ; 
  // set homeboy out at an angle pi/4
  Worm* worm1 = new Worm(space,wormX,wormY,wormTheta,0,leftBias,rightBias) ; 
  worm1->setBehaviorModel(new ForwardBehaviorModel()) ; 
  space->addWorm(worm1) ; 

	for(int i = 0 ; i < numSteps ; i++){
		space->moveWorms() ; 
	} 
}

void printHelpAndExit() 
{
  cout << "Usage:" << endl;
  cout << "  cluster [commands]" << endl;
  cout << endl;

  // help commands
  cout << "Help options:" << endl  ;
  cout << "  -help           Print this message" << endl;
  cout << endl ; 

  cout << "Output options: " << endl ; 
  cout << "  -N v			 The number of worms in the simulation. " << endl;
  cout << "  -out  filename   File for model output data, separate by line return. " << endl;
  cout << "  -prec           Precision of output" << endl;
  cout << "  -wid            Width of output" << endl;
  cout << endl ; 

  // neural networks 
  cout << "Network parameters:" << endl;
  cout << "  -net            Loads network from xml file" << endl;
  cout << "  -dt             Timestep, defaults to 1." << endl;
  cout << "  -steps N        Run tests for this many time steps" << endl;
  cout << endl ; 
 
	// gradient parameters
  cout << "Gradient parameters:" << endl;
  cout << "  -map 			Map type, guassian 'g', power 'p', linear 'l'.  Default 'l'." << endl;
  cout << "  -maxc 			Maximum concentration.  Default 1." << endl;
  cout << "  -minc 			Minimum concentration.  Default 0." << endl;
  cout << "  -diam			Diameter of gradient.  Default 1." << endl;
  cout << "  -power v       The power of the gradient slope.  Default is 1, linear." << endl;
  cout << "  -wormx  		Worm initial x position.  Default 1/2 diameter." << endl;
  cout << "  -wormy  		Worm initial y position.  Default 1/2 diameter." << endl;
  cout << "  -wormtheta  	Worm initial theta position.  Default 0." << endl;
  cout << "  -center v      The radius from the center which is considered the center.  Default is 0.0" << endl;
  cout << endl ; 
 

  // worm parameters
  cout << "Worm parameters:" << endl;
  cout << "  -lofilter       The low filter, default 0" << endl;
  cout << "  -hifilter       The high filter, default 1" << endl;
  cout << "  -noise          Decision making noise." << endl;
  cout << "  -mprob v         The probability of doing a Pirouette when in the Midrange probability state between the 2 threshold.  Default is 0.5" << endl;
  cout << "  -pprob v         The probability of doing a Pirouette when in the Pirouette probability state.  Default is 1" << endl;
  cout << "  -fprob v         The probability of doing a turn when in the forward probability state.  Default is 0" << endl;
  cout << "  -pfor v         The forward velocity when in the Pirouette state.  Default is 0.01" << endl;
  cout << "  -ffor v         The forward velocity when in the Forward state.  Default is 0.01" << endl;
  cout << "  -lfwd v         Left turning bias (in degrees) during forward movement.   Default is 0 (straight)." << endl;
  cout << "  -rfwd v         Right turning bias (in degrees) during forward movement.   Default is 0 (straight)." << endl;
  cout << "  -turn v         The minimum sharp-turn ratio.  Default is 0.0" << endl;
  cout << endl ; 

  // movement parameters
  
  
  // output parameters 
  cout << "Output options:" << endl;
  cout << "  -v N             Verbosity output: lots (0), some (1), none (2)" << endl;
  cout << endl;

  exit(1);
}



bool init(int argc, char *argv[]) 
{
  // create a command line parser object:
  OptionList opt(argc,argv);
  
  // if no command line arguments, or if -help speficied, print a 
  // message and exit

  if ((argc == 1) || (opt.getFlag("help",false)))
    printHelpAndExit();

  // Get the command line settings

  dumpFileName = opt.getOption("out", "");
  networkFile  = opt.getOption("net", "");
  verbosity      = opt.getInt("v", 0);
  outputPrecision = opt.getInt("prec",12);
  outputWidth  = opt.getInt("wid",12);
  loFilter     = opt.getDouble("lofilter", 0.0);
  hiFilter     = opt.getDouble("hifilter", 1.0);
  timeStep     = opt.getDouble("dt", 1.0);
  numSteps = opt.getDouble("steps", 1.0);
  gradientPower = opt.getDouble("power", 1.0);
  pirForward = opt.getDouble("pfor", 0.01);
  forForward = opt.getDouble("ffor", 0.01);
  pirProb = opt.getDouble("pprob", 1);
  forProb = opt.getDouble("fprob", 0);
  midProb = opt.getDouble("mprob", 0.5);
  maxConc = opt.getDouble("maxc", 1.0);
  minConc = opt.getDouble("minc", 0.0);
  diameter = opt.getDouble("diam", 1.0);
  wormX = opt.getDouble("wormx",diameter/(2.0));
  wormY = opt.getDouble("wormy",diameter/(2.0));
  wormTheta = opt.getDouble("wormtheta",0.0);
  noise = opt.getDouble("noise",0.0);
  minTurn = (float) opt.getDouble("turn",0.0);
  centerRadius =  opt.getDouble("center",0.0);
  leftBias =  opt.getDouble("lfwd",0.0);
  rightBias =  opt.getDouble("rfwd",0.0);
  numWorms =  opt.getInt("N",1);
  mapType =  opt.getChar("map",'l');

  cout << "verbosity: "<< verbosity << endl ; 

  return true;
}





int cluster(int argc, char** argv){

  if (!init(argc, argv)) {
    cerr << "cluster: initialization errors" << endl;
    return 1;
  }
    cout << setprecision(outputPrecision) ; 
    cout << setw(outputWidth) ; 


	runNSimulations() ;
//runSimulation() ;
//runTest() ;
//runMapTest() ;
}


