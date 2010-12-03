//
// Demo and test driver of neural network (NeuralNet) objects
//
// John Conery
// July 2001
//

#include <iostream>
using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;

#include <iomanip>

#include <string>
using std::string;

#include "blitzdefs.h"
#include "NeuralNet.h"
#include "OptionList.h"
#include "Worm.h"
#include "RNG.h"

// Initialization procedures -- the init() procedure uses an OptionList
// object to parse the Unix command line options.  For each option there
// is a global variable; main() will check the values of the variables
// to figure out which tests to perform.

double stimVal;			// -stim N
double outputBiasVal;		// -output_bias N
double tauVal;			// -tau N
double runDist;			// -run_dist N
double turnDist;		// -turn_dist N
int    timeVal;			// -time N
int    wormsVal;                // -worms N
int    debugging;               // -DEBUG N
bool   allNeurons;		// -all

const int NONE = 0;
const int SOME = 1;
const int LOTS = 2;

void printHelpAndExit() 
{
  cout << "Usage:" << endl;
  cout << "  nndemo [commands]" << endl;
  cout << endl;
  cout << "Commands:" << endl;
  cout << "  -help           Print this message" << endl;
  cout << "  -print          Show how network objects are printed" << endl;
  cout << "  -output_bias N  Set bias to output neuron in network tests" << endl;
  cout << "  -run_dist N     Set the distance of a run in network tests" << endl;
  cout << "  -turn_dist N    Set the distance of a turn in network tests" << endl;
  cout << "  -tau N          Set tau to N in network tests" << endl;
  cout << "  -worms N        Run tests for this many time steps" << endl;
  cout << "  -time N         Run tests for this many time steps" << endl;
  cout << "  -DEBUG N        Specify level of debugging info (0-2)" << endl;
  cout << "  -all            Print all neurons (otherwise only output neurons)" << endl;
  cout << endl;
  exit(1);
}

bool init(int argc, char *argv[]) 
{
  // create a command line parser object:
  OptionList opt(argc,argv);

  // if no command line arguments, or if -help speficied, print a 
  // message and exit
  if (opt.getFlag("help",false))
    printHelpAndExit();

  // Get the command line settings
  outputBiasVal = opt.getDouble("output_bias", -3.63343);
  stimVal       = opt.getDouble("stim", 0.0);
  tauVal        = opt.getDouble("tau", 1.0);
  timeVal       = opt.getInt("time", 20);
  wormsVal      = opt.getInt("worms", 500);
  debugging     = opt.getInt("DEBUG", 0);
  runDist       = opt.getDouble("run_dist", .5);
  turnDist      = opt.getDouble("turn_dist", .5);
  allNeurons    = opt.getFlag("all", false);

  return true;
}


/* ************************************************************************************
   netInit() */
   
//! Initialize a neural network from (for now) hard-wired data
/*  *********************************************************************************** */
void netInit(NeuralNet& nnet, int net_dimension, int time_steps)
// void createNet()
{/*
    int net_dimension = 10;
    NeuralNet nnet(net_dimension);
    int time_steps = 20;
 */
    
    Vector bias(net_dimension);
    bias = 6.16209,	3.08168,	0.794635,	15.0714,	19.7195,	27.5582,	3.70672,	-2.13187,	19.2251,	-3.63343;
    bias(net_dimension - 1) = outputBiasVal;
    nnet.setBias(bias);
    
    Vector tau(net_dimension);
    tau = 3.21886,	  14.04,	       3,	12.7378,	24.3589,	7.19963,	 12.228,	6.59415,	  20.37,	3.03526;
    nnet.setTau(tau);
    
    Vector vmem(net_dimension);
    vmem = 0.456541,	2.13413e-15,    	1,	       1,	      1,	      1,   	0.784804,	2.98565e-09,	      1,	0.415915;
    nnet.setNeurons(vmem);
    
    Matrix w(net_dimension,net_dimension);
    w = 
	-22.7367,	-11.7766,	-5.8711,	-4.20374,	-2.73035,	 4.39537,	 11.173,	 16.5427,	 25.5031,	 29.4805,	
	-10.3774,	-12.068,	 -8.426,	-3.91911,	 4.91394,	-6.3652,	 4.36541,	 14.655,	 21.5744,	 5.35642,	
	9.07521,	-13.0716,	 5.43465,	-8.25465,	 3.36841,	 0.822483,	-15.3479,	-13.9214,	 2.63041,	 8.5294,	
	10.1797,	 3.22533,	-12.1937,	-6.05113,	-7.67603,	-10.2029,	 12.1968,	 1.40991,	 15.3703,	 6.88067,	
	9.75885,	 23.5692,	-20.1609,	-3.01363,	 9.07425,	 26.5416,	 4.85506,	-15.9061,	-17.6382,	 15.9142,	
	-12.6686,	-5.46693,	 23.8187,	 39.1873,	 29.262,	 28.3634,	-6.96834,	 6.57286,	-7.88589,	-3.46688,	
	-12.1474,	-21.5028,	 8.33645,	 13.3569,	-0.793374,	-4.25858,	-2.69516,	 5.21466,	-0.606262,	-23.9406,	
	14.8128,	 9.03512,	 24.4486,	-6.31833,	 2.34094,	 1.69311,	 23.858,	 1.76455,	-3.9406,	 21.4138,	
	-2.51537,	-21.1696,	 30.9034,	 0.939272,	 19.5032,	-28.6204,	-4.58953,	 0.739031,	 8.40252,	-12.8764,	
	-1.92282,	-3.9668,	-8.45324,	 6.60467,	 7.57682,	-15.8214,	 10.6195,	-19.3457,	-3.69285,	-15.2863;
    nnet.setWeights(w);    
}


/* ******************************************
   findDistribution() */
   
//!  Find the distribution produced by a network
/*   ****************************************** */
void findDistribution() 
{
    const int numNeurons = 10;		// number of neurons
    const int numWorms = wormsVal;      // number of worms
    const int timeSteps = timeVal;	// number of time steps
    
    double next_action, random_loc, new_loc, p0, move_distance;

    // "highTemp" is the high temperature" of our 1D environment.
    // For now the worm can be anywhere from 0 to highTemp.
    // NOTE: should be placed in an environment var
    const int highTemp = 20;
    
    NeuralNet net(numNeurons);

    netInit(net, numNeurons, timeSteps);

    // Create all the worms for our assay
    Worm testWorm[numWorms];

    // Give each worm a network and a random location
    // NOTE: This can be parallelized
    // NOTE: This should probably be in its own method
    // NOTE: I have had problems with RNG returning the
    //       same number twice in a row. It doesn't appear
    //       to be doing it any more though.
    for(int i = 0; i < numWorms; i++) {
	testWorm[i].setNet(net);
	testWorm[i].setLocation(abs(RNG::uniform()) * highTemp);
	testWorm[i].setDirection(abs(RNG::uniform()) > .5 ? -1 : 1);
    }

    // cout << "initial worm.dir = " << testWorm[0].getDirection() << endl;

    // Pass the worm's location (which in this case is also the
    // temperature) as input into the worm's network. The output
    // of the network is the probability the worm will run.
    // NOTE: Should these loops be integrated into loop above?
    // NOTE: Either way, this loop should be parallelized too
    for(int i = 0; i < numWorms; i++) {

	if(debugging > NONE) cout << "initial worm.loc = " << testWorm[i].getLocation() << "\t";
	for(int j = 0; j < timeSteps; j++) {

	    // supposed to be the distance the worm moves in any time step
	    move_distance = runDist; 
    
	    if(debugging > SOME) cout << "worm.loc = " << testWorm[0].getLocation() << endl;
	    // The worm's network = the probability of a run
	    p0 = testWorm[i].getNet().processInput(testWorm[i].getLocation());

	    next_action = RNG::uniform();

	    if(debugging > SOME) cout << "p0 = " << p0 << ", next_action = " << next_action << endl;
	    
	    // NOTE: Should turn this into a reverseDirection() method (?)
	    if(next_action > p0) {
		testWorm[i].setDirection(testWorm[i].getDirection() * -1);
		move_distance = turnDist;
	    }

	    new_loc = testWorm[i].getLocation() + (testWorm[i].getDirection() * move_distance);
	    
	    // The temperature distribution goes from 0 -> highTemp <- 0.
	    // This is handled by correcting the worm's position when it
	    //  passes the highTemp threshold and changing its direction
	    //  (because it's now pointing away from the highTemp).
	    // NOTE: Should the worms die at 0 degrees?
	    if(new_loc > highTemp) {
		new_loc = highTemp - (new_loc - highTemp);
		testWorm[i].setDirection(testWorm[i].getDirection() * -1);
	    }
	    else if (new_loc < 0)
		new_loc = 0;
	    
	    testWorm[i].setLocation(new_loc);
	}

	if(debugging > NONE)
	    cout << "final worm.loc = " << testWorm[i].getLocation() << endl;
	else
	    cout << testWorm[i].getLocation() << endl;
    }
}



/* ************************************************************************************
   main() */
   
//! Parse the command line arguments and call the method to find the distribution
/* ************************************************************************************ */

int main(int argc, char *argv[])
{
  if (!init(argc, argv)) {
    cerr << "nndemo: initialization errors" << endl;
    return 1;

  }

  RNG::initSeed();

  findDistribution();

  return 0;
}
