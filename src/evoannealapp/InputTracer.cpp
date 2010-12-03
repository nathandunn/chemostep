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

// output file stuff
#include <TextEvalTrace.hpp> 


// plotting stuff
#include <gnuplot_i.hpp>

#include "InputTracerAuto.hpp"

InputTracerAuto::InputTracerAuto() 
{
	RNG::initSeed() ; 
	 cout << "InputTracerAuto constructed" << endl ; 

	 // generate evaluator
}

int InputTracerAuto::generateTrace(string inputTrace,string inputNetwork,string outputTrace, bool doPlot) 
{
	// load input
	// excecpts endl delimited
  FileFeeder* stimFeeder = new FileFeeder(inputTrace) ; 
	 
	cout << "Num Points: " << stimFeeder->getNumPoints() << endl ; 

	// load network
	cout << "loading network[" << inputNetwork << "]" << endl ; 
  mOrigNet = (new TinyBzNetParser())->parseFile(inputNetwork) ;   
	cout << "network[" << inputNetwork << "] loaded" << endl ; 


	// set evaluator
  mOrigEval = new BlitzEulerLiveNetEvaluator( 1.0 ,30 ,mOrigNet)  ;
  mOrigNet->setEvaluator(mOrigEval) ; 

//  mOrigEval->setRelaxTime(mRelaxTime) ; 
//  mOrigEval->setRelaxLimit(mRelaxLimit) ; 
	mOrigEval->setRelaxTime(mRelaxTime) ; 
//  mOrigEval->setRelaxLimit(0.0001) ; 
  mOrigEval->resetTrace(  stimFeeder->getNumPoints(), stimFeeder->getNumPoints()) ; 

	// generate output
	vector<double>* pointVector = new vector<double>(2) ; 
	double point ; 
	for(int i = 0 ; i < stimFeeder->getNumPoints() ;i++){
	double point = stimFeeder->getNextPoint()  ; 
	  (*pointVector)[0]= point ; 
	  (*pointVector)[1]= point ; 
		mOrigEval->evalPoint(pointVector,true) ; 
	}
	vector<vector<double>*>* neuronTrace = mOrigEval->getLastFullTrace() ;

	// dump output
	if(outputTrace!=""){
		dumpOutput(neuronTrace,outputTrace) ; 
	}

	// plot?
  if(doPlot){
   cout << "plotting data" << endl ; 
	 mTitleName = inputTrace ; 
	 if(inputNetwork.size()> 100){
		 mTitleName += inputNetwork.substr(inputNetwork.size()-100,inputNetwork.size())  ; 
	 }
 	 vector<vector<double>*>* traceAsSeries= mOrigEval->getLastFullTraceAsSeries() ;
	 plot(traceAsSeries) ; 
	 int dump ; 
	 cin >> dump ; 
	}
	else{
   cout << "NOT plotting data" << endl ; 
	}

	return 1 ; 
}



void InputTracerAuto::dumpOutput(vector<vector<double>*>*  fullTrace,string outputTrace) 
{
	ofstream fileStream( outputTrace.c_str() , ios::out) ; 
	
	for(int i = 0 ; i < fullTrace->size() ; i++){
			for(int j = 0 ; j < (*fullTrace)[0]->size() ; j++){
					fileStream << (*(*fullTrace)[i])[j] << "," ; 
			}
			fileStream << endl ; 
	}

	fileStream.close() ;
}

void InputTracerAuto::plot(vector<vector<double>*>*  sliceTrace) 
{
		Gnuplot *plotter = new Gnuplot("points") ; 
		 
    plotter->cmd("set ytics(0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9)") ; 
    plotter->cmd("set grid") ; 
//    plotter->cmd("set title 'Neuron Pulse Response'") ; 
    plotter->cmd("set xlabel 'Time(s)'") ; 
    plotter->cmd("set ylabel 'Neural Activity'") ; 

    ostringstream *commands = new ostringstream() ; 
    *commands << "set title '" << mTitleName <<  "' ;" ; 
    plotter->cmd( (commands->str()).c_str()) ; 

		// assumes that hte trace is a series
    ostringstream* nameString = new ostringstream() ; 
    for(int i = 0 ; i < sliceTrace->size() ; i++){
        nameString->str("") ; 
        *nameString  << "neuron " << i ; 
        plotter->plot_x( *((*sliceTrace)[i]) ,nameString->str() ) ; 
    }
}




// -*- C++ -*-

// (C) 2006 by Nathan Dunn, <ndunn@mac.com>


