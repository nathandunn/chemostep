
// Adding as a test for subversion. Got at precog and removing.

#include <iostream>

#include <strstream>
using std::ostrstream;



// external classes
#include <blitzdefs.hpp>
#include <OptionList.hpp>
#include <TinyBzNetParser.hpp> 
#include <BlitzEulerNetEvaluator.hpp>

#include "MapSpace.hpp"
#include "Worm.hpp"
#include "MapData.hpp"
#include "LinRadialMap.hpp"
#include "QuadMap.hpp"
#include "PowerRadialMap.hpp"
#include "GaussRadialMap.hpp"
#include "ForwardBehaviorModel.hpp"
#include "ShortMemoryBehaviorModel.hpp"
#include "NetworkBehaviorModel.hpp"
#include "Mode3NetworkBehaviorModel.hpp"
#include "Logger.hpp"
#include "StatReporter.hpp"


enum { VERB_LOTS, VERB_SOME,VERB_NONE} ;

// option variables
//
char   mapType;		    // -map c 
int    numWorms ;		// -num v 
double centerRadius;	// -center v 
double clusterCorrelation ;	// -cluster v 
float  minTurn ;		// -turn v 
int    numSteps;		// -steps v 
double timeStep;		// -dt v 
double loFilter;		// -lofilter v
double hiFilter;		// -hifilter v
double tempLoFilter;	
double tempHiFilter;		
int    outputPrecision; // -prec v
int    outputWidth;     // -wid v
string dumpFileName;    // -dump fileName
string networkFile ;    // -net fileName 
double randomize;          // -random v (random value)
int verbosity ;          // -v v
double gradientPower;   // -power v
double pirForward;     	// -pfor v
double forForward;     	// -ffor v
double pirProb;     	// -pprob v
double forProb;     	// -fprob v
double midProb;     	// -mprob v
double maxConc ;        // -maxc v
double minConc ;        // -minc v
double startX;          // -wormx v
double startY;          // -wormy v
double wormX;          
double wormY;         
double wormTheta ;      // -wormtheta v
double diameter;        // -diam v
double noise;			// -noise v 
double leftBias;		// -lfwd v
double rightBias;		// -rfwd v
vector<int> netList ;		// -list v,-v
vector<string> netFileList;		// <produced from netList and netwokrFile>
string reportFile;
string reportDelimiter;		// -rdl c


MapData* getMap(){
   
    MapData* map = 0 ; 
    // get the write map type
    switch(mapType){
        case 'q': map = new QuadMap(diameter,maxConc,minConc) ; 	
                  break ; 
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

    // A MapData object describes simple features of the environment
    //  like the diameter or any random location.
    MapData *map = getMap() ; 

    // create behavior model
    TinyBzNetParser *util ; 
   
    // A MapSpace is a description of the environment, including worms,
    //  the activities of the worms, and some properties of the "dish."
    //  MapSpace includes lots of methods for getting attributes of worms
    //  within the space. Contrast with explanation of "MapData" above.
    MapSpace *space = new MapSpace() ; 
	
    // the space will keep track of where the "goal" is
    space->setCenterRadius(centerRadius,diameter/2.0,diameter/2.0) ;
    StatReporter *reporter = new StatReporter(reportFile,reportDelimiter)  ; 
    reporter->doReportHeader() ;  

    // set output 
    string headerFile = "" ;
    ostrstream stringStream ; 
    Logger *log = Logger::getLogger(dumpFileName) ; 

//  stringStream << endl ; 
//  cout << "the header file" << headerFile << endl ; 

    headerFile = stringStream.str() ; 
    space->setVerbosity(MapSpace::VERB_SOME) ; 
    log->log(headerFile) ; 

    BlitzNet* aNet ;
    NetEvaluator* netEvaluator ; // place-holder for real evaluator
    
    for(int i = 0 ; i < netList.size() ; i++){

	// Networks are created from .xml files specified in the command line (?)
//      aNet = new LiveNet(util.loadNetwork(netFileList[i])) ;
	aNet = new BlitzNet(util->parseFile(netFileList[i])) ; 
	netEvaluator = new BlitzEulerNetEvaluator() ; 
	aNet->setEvaluator(netEvaluator) ; 
	
	Dimension d ; 
	double avgStartingDistance = 0.0 ;

	// Worms start in the dead-center of the dish by default.
	// This will only change if the user specifies a "random" option.
	wormX = startX ; 
	wormY = startY ; 
	
	// Create and add worms
	for(int k = 0 ; k < numWorms ; k++){

	    // randomize is set to -1 by default
	    if(randomize >= 0.0){

		d = map->getRandom(randomize,startX,startY) ; 
		wormX = d.getX() ; 
		wormY = d.getY() ; 
//              cout << "distance: " << sqrt(pow(wormX-4.5,2.0)+pow(wormY-4.5,2.0)) << endl ;
	    }
	    
//          cout << "worm " << i << " placed at " << wormX << " " << wormY << endl ; 
//          aNet->resetNeurons() ; 
//          aNet->invalidate() ; 
	    aNet->reset() ;

	    // Create a pointer to a worm.
	    Worm* worm ;

	    // Instantiate the worm with various propertes of the worm and its space.
	    //  Note that wormTheta is zero by default. The '0' below is its initial velocity.
	    worm = new Worm(space,wormX,wormY,wormTheta,0,leftBias,rightBias) ;

	    // Set the worm's behavior model which describes its
	    //  choices and movement tendencies.
	    worm->setBehaviorModel(new Mode3NetworkBehaviorModel(worm,aNet,noise,tempLoFilter,tempHiFilter,forProb,pirProb,midProb)) ; 
	    
	    // set time and dt
	    aNet->reset() ; 
	    
	    worm->setForwardVelocity(forForward) ; 
	    worm->setPirouetteVelocity(pirForward) ; 
//          worm->setName("charlie") ; 
	    worm->setTurningThreshold(minTurn) ;

	    // Add the worm to the dish.
	    space->addWorm(worm) ; 

	    // Sum the distance of each worm from the center of the dish. 
	    avgStartingDistance += sqrt( pow((wormX-diameter/2),2.0)+pow((wormY-diameter/2),2.0)) ; 
	}
	
	avgStartingDistance = avgStartingDistance/numWorms ; 
	
	cout << "average starting distance: "<< avgStartingDistance << endl ; 
		
	if(verbosity==VERB_SOME){
	    cout << "some verbosity:" << verbosity << endl ;
	    
	    for(int l = 0 ; l < numWorms ; l++){
		stringStream << "x" << l << " " ; 
		stringStream << "y" << l << " " ; 
		stringStream << "value" << l << " " ; 
	    }
	    
	} else {
	    if(verbosity==VERB_LOTS){
		cout << "very verbose:" << verbosity << endl ;
		
		for(int l = 0 ; l < numWorms ; l++){
		    stringStream << "x" << l << " " ; 
		    stringStream << "y" << l << " " ; 
		    stringStream << "gradVal" << l << " " ; 
		    stringStream << "netProb" << l << " " ; 
		    stringStream << "netDec" << l << " " ; 
		    stringStream << "netMov" << l << " " ; 
		}
		
//              stringStream << endl ; 
		headerFile = stringStream.str() ; 
//              cout << "the header file" << headerFile << endl ; 
		space->setVerbosity(MapSpace::VERB_LOTS) ; 
		log->log(headerFile) ;
		
	    } else {  // assume no verbosity
		cout << "no verbosity:" << verbosity << endl ; 
		headerFile = "" ; 
		space->setVerbosity(MapSpace::VERB_NONE) ; 
	    }
	}
	
	space->setMap(map) ;

	// Other options here are NO_RUNNING and VERB_LOTS (?)
	int wormState = MapSpace::SOME_RUNNING; 
	
//      cout << "number of worms: " << space->getWormCount() << endl  ;
	
	for(int j = 0 ; j < numSteps && wormState != MapSpace::NO_RUNNING; j++){
	   
	    wormState = space->moveWorms() ; 
	    space->printWorms() ; 

	    if(wormState == MapSpace::NO_RUNNING){
		cout <<" simulation finished after move: "<< j << endl ; 
	    }
	}

	if(wormState != MapSpace::NO_RUNNING){
	    cout <<" simulation finished after all: " << numSteps << " moves "<< endl ; 
	}
	
//      reporter->doReport(space,netList[i],numSteps,aNet->getOriginalError()) ;  
	reporter->doReport(space,netList[i],numSteps,aNet->eval()) ;  
	
	space->clearStats() ; 
	
	aNet=NULL ; 
//      tempErrorModel=NULL ; 
	
    }  // end of for net loop
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
    TinyBzNetParser* util ; 
//    LiveNet* aNet = new LiveNet(util.loadNetwork(networkFile)) ; 
    BlitzNet* aNet = new BlitzNet(util->parseFile(networkFile)) ; 
   
    // create space
    MapSpace *space = new MapSpace() ; 
	
    // the space will keep track of where the "goal" is
    space->setCenterRadius(centerRadius,diameter/2.0,diameter/2.0) ;
  
	// create and add worm
	Worm* worm = new Worm(space,wormX,wormY,wormTheta,0,leftBias,rightBias) ; 
    worm->setBehaviorModel(new NetworkBehaviorModel(worm,aNet,noise,tempLoFilter,tempHiFilter,forProb,pirProb)) ; 
    worm->setForwardVelocity(forForward) ; 
    worm->setPirouetteVelocity(pirForward) ; 
    worm->setName("charlie") ; 
    worm->setTurningThreshold(minTurn) ; 

    space->addWorm(worm) ; 

    // set time and dt
	aNet->reset() ; 
//    aNet->setTimeStep(timeStep) ; 


    // set output 
    string headerFile ;
    Logger *log = Logger::getLogger(dumpFileName) ; 
    if(verbosity==VERB_LOTS){
//        cout << "very berbose:" << verbosity << endl ; 
        headerFile = "x1 y1 gradVal1 netProb1 netDec1 netMov1" ; 
        space->setVerbosity(MapSpace::VERB_LOTS) ; 
    	log->log(headerFile) ; 
    }else
    if(verbosity==VERB_SOME){
//        cout << "some verbosity:" << verbosity << endl ; 
        headerFile = "x1 y1 value1" ; 
        space->setVerbosity(MapSpace::VERB_SOME) ; 
    	log->log(headerFile) ; 
    }else{  // assume no verbosity
//        cout << "no verbosity:" << verbosity << endl ; 
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

    TinyBzNetParser* util ; 
//    LiveNet* aNet = new LiveNet(util.loadNetwork(networkFile)) ; 
    BlitzNet* aNet = new BlitzNet(util->parseFile(networkFile)) ; 
	aNet->reset() ; 
//    aNet->setTimeStep(timeStep) ; 
	cout << "testNet: " << aNet->getInitNeuron() << endl ; 
    
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
  cout << "  main [commands]" << endl;
  cout << endl;

  // help commands
  cout << "Help options:" << endl  ;
  cout << "  -help               Print this message" << endl;
  cout << endl ; 

  cout << "Output options: " << endl ; 
  cout << "  -N v                The number of worms in the simulation. " << endl;
  cout << "  -list v,-v          The list of networks we want to work, using the \% token in -net. " << endl ; 
  cout << "                      e.g., -list 5,8-12,15 -net network\%Stripped.txt" << endl ; 
  cout << "  -out  filename      File for model output data, separate by line return. " << endl;
  cout << "  -report  filename   File for report data, separate by line return, default space delimited. " << endl;
  cout << "  -rdl  string        Delimiter for report, default space delimited. " << endl;
  cout << "  -prec               Precision of output" << endl;
  cout << "  -wid                Width of output" << endl;
  cout << endl ; 

  // neural networks 
  cout << "Network parameters:" << endl;
  cout << "  -net                Loads network from xml file" << endl;
  cout << "  -dt                 Timestep, defaults to 1." << endl;
  cout << "  -steps N            Run tests for this many time steps" << endl;
  cout << endl ; 
 
  // gradient parameters
  cout << "Gradient parameters:" << endl;
  cout << "  -map                Map type, guassian 'g', power 'p', linear 'l'.  Default 'l'." << endl;
  cout << "  -maxc               Maximum concentration. Default 1." << endl;
  cout << "  -minc               Minimum concentration. Default 0." << endl;
  cout << "  -diam               Diameter of gradient. Default 1." << endl;
  cout << "  -power v            The power of the gradient slope.  Default is 1, linear." << endl;
  cout << "  -wormx              Worm initial x position. Default 1/2 diameter." << endl;
  cout << "  -wormy              Worm initial y position. Default 1/2 diameter." << endl;
  cout << "  -randomize          Randomizes the initial worm position. Off by default." << endl;
  cout << "  -wormtheta          Worm initial theta position. Default 0." << endl;
  cout << "  -center v           The radius from the center which is considered the center.  Default is 0.0" << endl;
  cout << endl ; 
 

  // worm parameters
  cout << "Worm parameters:" << endl;
  cout << "  -cluster            The likelihood of a worm to cluster, default 0." << endl;
  cout << "  -lofilter           The low filter, default 0" << endl;
  cout << "  -hifilter           The high filter, default 1" << endl;
  cout << "  -noise              Decision making noise." << endl;
  cout << "  -mprob v            The probability of doing a Pirouette when in the Midrange probability state between the 2 threshold.  Default is 0.5" << endl;
  cout << "  -pprob v            The probability of doing a Pirouette when in the Pirouette probability state.  Default is 1" << endl;
  cout << "  -fprob v            The probability of doing a turn when in the forward probability state.  Default is 0" << endl;
  cout << "  -pfor v             The forward velocity when in the Pirouette state.  Default is 0.01" << endl;
  cout << "  -ffor v             The forward velocity when in the Forward state.  Default is 0.01" << endl;
  cout << "  -lfwd v             Left turning bias (in degrees) during forward movement.   Default is 0 (straight)." << endl;
  cout << "  -rfwd v             Right turning bias (in degrees) during forward movement.   Default is 0 (straight)." << endl;
  cout << "  -turn v             The minimum sharp-turn ratio.  Default is 0.0" << endl;
  cout << endl ; 

  // movement parameters
  
  
  // output parameters 
  cout << "Output options:" << endl;
  cout << "  -v N                Verbosity output: lots (0), some (1), none (2)" << endl;
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

  dumpFileName       = opt.getOption("out", "");
  reportFile         = opt.getOption("report", "");
  reportDelimiter    = opt.getOption("rdl", " ");
  networkFile        = opt.getOption("net", "");
  verbosity          = opt.getInt("v", 0);
  outputPrecision    = opt.getInt("prec",12);
  outputWidth        = opt.getInt("wid",12);
  clusterCorrelation = opt.getDouble("cluster", 0.0);
  randomize          = opt.getDouble("random", -1.0);
  loFilter           = opt.getDouble("lofilter", 0.0);
  hiFilter           = opt.getDouble("hifilter", 1.0);
  timeStep           = opt.getDouble("dt", 1.0);
  numSteps           = opt.getInt("steps", 1);
  gradientPower      = opt.getDouble("power", 1.0);
  pirForward         = opt.getDouble("pfor", 0.01);
  forForward         = opt.getDouble("ffor", 0.01);
  pirProb            = opt.getDouble("pprob", 1);
  forProb            = opt.getDouble("fprob", 0);
  midProb            = opt.getDouble("mprob", 0.5);
  maxConc            = opt.getDouble("maxc", 1.0);
  minConc            = opt.getDouble("minc", 0.0);
  diameter           = opt.getDouble("diam", 1.0);
  startX             = opt.getDouble("wormx",diameter/(2.0));
  startY             = opt.getDouble("wormy",diameter/(2.0));
  wormTheta          = opt.getDouble("wormtheta",0.0);
  noise              = opt.getDouble("noise",0.0);
  minTurn            = (float) opt.getDouble("turn",0.0);
  centerRadius       = opt.getDouble("center",0.0);
  leftBias           = opt.getDouble("lfwd",0.0);
  rightBias          = opt.getDouble("rfwd",0.0);
  numWorms           = opt.getInt("N",1);
  mapType            = opt.getChar("map",'l');
  netList            = opt.getIntList("list", "");
  netFileList        = opt.createList(networkFile,netList,'%') ; 
  cout << "verbosity: "<< verbosity << endl ; 

  return true;
}


int main(int argc, char** argv){

  if (!init(argc, argv)) {
    cerr << "main: initialization errors" << endl;
    return 1;
  }
//    cout << setprecision(outputPrecision) ; 
//    cout << setw(outputWidth) ; 
//    cout.setprecision(outputPrecision) ; 
//    cout.setw(outputWidth) ; 

    cout.precision(outputPrecision) ; 
    cout.width(outputWidth) ; 

	runNSimulations() ;
    
//runSimulation() ;
//runTest() ;
//runMapTest() ;
}


