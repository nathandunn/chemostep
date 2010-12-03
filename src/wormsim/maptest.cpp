// -*- C++ -*-
// FILE: "/home/ndunn/cvs/PETRIE_2/source/maptest.cpp"
// LAST MODIFICATION: "Thu, 18 Jul 2002 11:59:10 -0700 (ndunn)"
// (C) 2002 by Nathan Dunn, <ndunn@idiom.com>
// $Id: maptest.cpp,v 1.1 2002/07/18 19:00:38 ndunn Exp $

#include <iostream>


#include <fstream>
using std::ofstream ; 


#include "MapSpace.hpp"
#include "MapData.hpp"
#include "LinRadialMap.hpp"
#include "PowerRadialMap.h"
#include "GaussRadialMap.h"
#include "OptionList.h"

double sigma;		    // -sigma v 
char   mapType;		    // -map c 
double centerRadius;	// -center v 
int    outputPrecision; // -prec v
int    outputWidth;     // -wid v
int verbosity ;          // -v v
double gradientPower;   // -power v
double diameter;        // -diam v
double maxConc ;        // -maxc v
double minConc ;        // -minc v

MapData* getMap(){
   
    MapData* map = 0 ; 
    // get the write map type
    switch(mapType){
		
        
        case 'p': map = new PowerRadialMap(gradientPower,diameter,maxConc,minConc) ; 	
                  break ; 
        case 'g': map = new GaussRadialMap(diameter,maxConc,minConc,sigma) ; 	
                  break ; 
        default:
        case 'l': map = new PowerRadialMap(1,diameter,maxConc,minConc) ; 	
                  break ; 

    }
    return map ; 
    
} 


void printHelpAndExit() 
{
  cout << "Usage:" << endl;
  cout << "  main [commands]" << endl;
  cout << endl;

  // help commands
  cout << "Help options:" << endl  ;
  cout << "  -help           Print this message" << endl;
  cout << endl ; 

  cout << "Output options: " << endl ; 
  cout << "  -prec           Precision of output" << endl;
  cout << "  -wid            Width of output" << endl;
  cout << endl ; 

	// gradient parameters
  cout << "Gradient parameters:" << endl;
  cout << "  -map 			Map type, guassian 'g', power 'p', linear 'l'.  Default 'l'." << endl;
  cout << "  -sigma 		The sigma distribution value.  Default 1." << endl;
  cout << "  -maxc 			Maximum concentration.  Default 1." << endl;
  cout << "  -minc 			Minimum concentration.  Default 0." << endl;
  cout << "  -diam			Diameter of gradient.  Default 1." << endl;
  cout << "  -power v       The power of the gradient slope.  Default is 1, linear." << endl;
  cout << endl ; 
 

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

  sigma = opt.getDouble("sigma", 1.0);
  verbosity      = opt.getInt("v", 0);
  outputPrecision = opt.getInt("prec",12);
  outputWidth  = opt.getInt("wid",12);
  gradientPower = opt.getDouble("power", 1.0);
  maxConc = opt.getDouble("maxc", 1.0);
  minConc = opt.getDouble("minc", 0.0);
  diameter = opt.getDouble("diam", 1.0);
  mapType =  opt.getChar("map",'l');

  return true;
}


// tests the map functions
void runMapTest() {

    
	//MapData *map = new LinRadialMap(10,1,0) ; 	
//	MapData *map = new LinRadialMap(10,0.8,0) ; 	
	//MapData *map = new PowerRadialMap(6,1,0.8,0) ; 	
//MapData *map = new GaussRadialMap(10,0.8,0) ; 	
    MapData *map = new GaussRadialMap(diameter,maxConc,minConc,sigma) ; 	
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

    ofstream outStream ; 
	outStream.open("output.txt",ios::out) ;  
    

    x = diameter*0.5 ; 
    outStream << "xvalue yvalue concvalue" << endl ; 
    for(y = diameter ; y > 0 ; y -= diameter/100){
	  outStream <<  x << " " << y << " " <<  map->getValue(x,y) << endl ; 
    }

}



int main(int argc, char** argv){

  if (!init(argc, argv)) {
    cerr << "nndemo: initialization errors" << endl;
    return 1;
  }
//    cout << setprecision(outputPrecision) ; 
//    cout << setw(outputWidth) ; 


//	runNSimulations() ;
//runSimulation() ;
//	runTest() ;
runMapTest() ;
}


