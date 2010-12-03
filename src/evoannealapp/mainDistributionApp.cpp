#include <iostream>
using std::cout ; 
using std::endl ; 
using std::cerr ; 

#include <OptionList.hpp>
#include "DistributionApp.hpp"
#include "AutoOptionList.hpp"

string inputTrace , inputNetwork, outputTrace ; 
bool doPlot ;

int generateTrace(){
	cout << "inputTrace["  << inputTrace << "]" << endl ;
	cout << "outputTrace["  << outputTrace << "]" << endl ;
	cout << "inputNetwork["  << inputNetwork << "]" << endl ;
	cout << "doPlot["  << doPlot << "]" << endl ;
	DistributionApp* newTracer  = new DistributionApp() ; 
	return newTracer->generateTrace(inputTrace,inputNetwork,outputTrace, doPlot ) ; 
}

int printHelpAndExit() 
{
  cout << "Usage:" << endl;
  cout << "  mainInputTrace [commands]" << endl;
  cout << endl;

  // help commands
  cout << "Help options:" << endl  ;
  cout << "  -help           Print this message" << endl;

  // file options commands
  cout << "  -input          Name of input file" << endl;
  cout << "  -network        Name of network file" << endl;
  cout << endl ; 

  // output parameters 
  cout << "Output options:" << endl;
  cout << "  -output         Name of output file" << endl;
  cout << "  -plot           Do plot (default false)" << endl;
  cout << endl;

  exit(1);
}


bool init(int argc, char *argv[]) 
{
  // create a command line parser object:
  OptionList opt(argc,argv);
  
  // if no command line arguments, or if -help speficied, print a 
  // message and exit

  if ((argc == 1) || (opt.getFlag("help",false))){
    printHelpAndExit();
	}
  // Get the command line settings

  outputTrace = opt.getOption("output", "default.txt");
  inputTrace  = opt.getOption("input", "");
  inputNetwork = opt.getOption("network", "");
  doPlot      = opt.getFlag("plot", false);

  return true;
}


int main(int argc, char** argv){

  if (!init(argc, argv)) {
    cerr << "nndemo: initialization errors" << endl;
    return 1;
  }

	return generateTrace() ; 
	
}



// -*- C++ -*-

// (C) 2006 by Nathan Dunn, <ndunn@mac.com>


