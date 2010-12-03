
#include <iostream>
using std::cout ; 
using std::endl ; 
using std::ostream;
#include <string>
using std::string ; 

#include <fstream>
using std::ofstream;
using std::ios;


#include "alopextest1.hpp"
#include "TextEvalTrace.hpp" 
#include "NeuralNetwork.hpp" 
#include "BlitzNet.hpp" 
#include "BlitzNetAlopexPerturber.hpp"
#include "BlitzNetAlopexer.hpp"
#include "BlitzEulerNetEvaluator.hpp" 
#include "BinNetEvaluator.hpp" 
#include "FileFeeder.hpp" 
#include "StepFeeder.hpp" 
#include "SetFeeder.hpp" 

alopextest1::alopextest1()  
{
		
}


//test the alopex perturber.
bool alopextest1::test2() 
{
    try{
			
			net = new BlitzNet() ; 
			perturber = new BlitzNetAlopexPerturber(.002, .5) ;
			perturber->setBeta(1.8);
			optimizer = new BlitzNetAlopexer();
			optimizer->setMinError(.2);
			optimizer->setTotalIterations(30000);
			optimizer->setOutputPeriod(1);
			evaluator = new BlitzEulerNetEvaluator() ; 
			stimFeeder = new FileFeeder() ; 
			targetFeeder = new FileFeeder() ; 
			tracer = new TextEvalTrace() ; 
			
        stimFeeder = new SetFeeder() ; 
        targetFeeder = new SetFeeder() ; 
        StepFeeder *stimFeeder1 = new StepFeeder() ; 
        StepFeeder *stimFeeder2 = new StepFeeder() ; 
        FileFeeder* targetFile1 = new FileFeeder() ; 
        FileFeeder* targetFile2 = new FileFeeder() ; 
       stimFeeder1->setPreStepValue(40.0) ; 
       stimFeeder1->setPostStepValue(50.0) ; 
       stimFeeder1->setPreStepTime(120) ; 
       stimFeeder1->setPostStepTime(180) ; 
       stimFeeder2->setPreStepValue(50.0) ; 
       stimFeeder2->setPostStepValue(60.0) ; 
       stimFeeder2->setPreStepTime(120) ; 
       stimFeeder2->setPostStepTime(180) ; 
       targetFile1->setFile("../../DATA/CHEMOSTEP_DATA/bin10sec/N2_e40_50fwd.txt") ; 
       targetFile2->setFile("../../DATA/CHEMOSTEP_DATA/bin10sec/N2_e50_60fwd.txt") ; 

			 ofstream *outStream = new ofstream( "./xml_out.txt" , ios::out) ;
			 
       ( (SetFeeder*) stimFeeder)->addFeeder(stimFeeder1) ; 
       ( (SetFeeder*) stimFeeder)->addFeeder(stimFeeder2) ; 
       ( (SetFeeder*) targetFeeder)->addFeeder(targetFile1) ; 
       ( (SetFeeder*) targetFeeder)->addFeeder(targetFile2) ; 
       stimFeeder->setDeltaT(1.0) ; 
       targetFeeder->setDeltaT(10.0) ; 
       evaluator->setStimulus(stimFeeder) ; 
       evaluator->setTarget(targetFeeder) ; 
       net->setEvaluator(evaluator) ; 
			 net->setPerturber(perturber) ;
			 
			 net->setNumNeurons(2) ;  // resets everything
			 net->setNumNeurons(6) ;  // resets everything
			 
			 perturber->setDelta(.07);
			 perturber->setLambda(.55);
			 perturber->initTrace(net->getWeights(), net->getTau(), net->getBias());
			 
			 optimizer->setAlopexTarget(net);
			 optimizer->setMinError(1.0);
			 optimizer->setTotalIterations(30000);
			 
			 TextEvalTrace *tracer = new TextEvalTrace() ; 
			 tracer->setTimeDelimiter("\n") ; 
			 tracer->setValueDelimiter(" ") ; 
			 tracer->setEvaluator(evaluator) ;

			  cout << "------------\n-------------" << endl ; 
        cout << net->eval() << endl ;  
        cout << net->evalNorml() << endl ;  
        cout << "------------\n-------------" << endl ; 

				BlitzNet *greatNet = new BlitzNet((BlitzNet*) optimizer->alopex(outStream,"alopextestout.xml"));

				
        cout << greatNet->eval() << endl ;  
        cout << greatNet->evalNorml() << endl ;  
				cout << greatNet->render();
        cout << "------------\n-------------" << endl ; 

    }
    catch(string errorString){
        cout << "caught error: " << errorString << endl ; 
        return false ; 
    }
    catch(...){
        cout << "generic error" << endl ; 
        return false ; 
    }

    return true ; 
}

//test the alopex perturber.
bool alopextest1::test3() 
{
	try{
		stimFeeder = new SetFeeder() ; 
		targetFeeder = new SetFeeder() ; 
		StepFeeder *stimFeeder1 = new StepFeeder() ; 
		StepFeeder *stimFeeder2 = new StepFeeder() ; 
		FileFeeder* targetFile1 = new FileFeeder() ; 
		FileFeeder* targetFile2 = new FileFeeder() ; 
		stimFeeder1->setPreStepValue(40.0) ; 
		stimFeeder1->setPostStepValue(50.0) ; 
		stimFeeder1->setPreStepTime(120) ; 
		stimFeeder1->setPostStepTime(180) ; 
		stimFeeder2->setPreStepValue(50.0) ; 
		stimFeeder2->setPostStepValue(60.0) ; 
		stimFeeder2->setPreStepTime(120) ; 
		stimFeeder2->setPostStepTime(180) ; 
		targetFile1->setFile("../../DATA/CHEMOSTEP_DATA/bin10sec/N2_e40_50fwd.txt") ; 
		targetFile2->setFile("../../DATA/CHEMOSTEP_DATA/bin10sec/N2_e50_60fwd.txt") ; 
		
		( (SetFeeder*) stimFeeder)->addFeeder(stimFeeder1) ; 
		( (SetFeeder*) stimFeeder)->addFeeder(stimFeeder2) ; 
		( (SetFeeder*) targetFeeder)->addFeeder(targetFile1) ; 
		( (SetFeeder*) targetFeeder)->addFeeder(targetFile2) ; 
		stimFeeder->setDeltaT(1.0) ; 
		targetFeeder->setDeltaT(10.0) ; 
		evaluator->setStimulus(stimFeeder) ; 
		evaluator->setTarget(targetFeeder) ; 
		net->setEvaluator(evaluator) ; 
			 net->setPerturber(perturber) ;
			 
			 
			 TextEvalTrace *tracer = new TextEvalTrace() ; 
			 tracer->setTimeDelimiter("\n") ; 
			 tracer->setValueDelimiter(" ") ; 
			 tracer->setEvaluator(evaluator) ;
			 
			 net->setNumNeurons(2) ;  // resets everything
			 net->setNumNeurons(6) ;  // resets everything
			 
			 
			 perturber->setDelta(.02);
			 perturber->setLambda(.55);
			 cout << "------------\n-------------" << endl ; 
			 cout << net->eval() << endl ;  
			 cout << net->evalNorml() << endl ;  
			 cout << "------------\n-------------" << endl ; 
			 double out = net->eval();
			 perturber->initTrace(net->getWeights(), net->getTau(), net->getBias());
			 net->perturb(out);
			 for (int l=0; l <30000 ; l++) {
				 if (net->eval()<=.1)
					 break;
				 cout << net->eval() << endl;
				 net->perturb(net->eval());
				 
			 }
			 cout << net->render();
			 cout << net->eval() << endl ;  
			 cout << net->evalNorml() << endl ;  
			 cout << "------------\n-------------" << endl ; 
			 
	}
	catch(string errorString){
		cout << "caught error: " << errorString << endl ; 
		return false ; 
	}
	catch(...){
		cout << "generic error" << endl ; 
		return false ; 
	}
	
	return true ; 
}

/* Function int main(int argc, char **argv) {{{ */
int main(int argc, char **argv)
{

    alopextest1 *test = new alopextest1() ; 
    if(test->test2()){
       cout << "passed " << endl; 
    }else{
       cout << "failed " << endl; 
    }
    cout << "test2" << endl ; 
         


    return 0;
} 

