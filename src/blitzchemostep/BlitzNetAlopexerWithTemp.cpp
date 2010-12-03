
#include <iostream>
using std::cout ; 
using std::cin ; 
using std::endl ; 
#include <math.h>
#include <time.h>
#include <fstream>
using std::ofstream;
using std::ios;


#include "TextEvalTrace.hpp"
#include "BlitzNetAlopexerWithTemp.hpp"
#include "BlitzNet.hpp"
#include "BlitzXmlNetRenderer.hpp" 

#ifdef DOMPI
#include "mpi.h"
int seq_myid  ; 
int seq_numprocs ; 
#endif 

BlitzNetAlopexerWithTemp::BlitzNetAlopexerWithTemp() : blitzNet(NULL) ,renderer(new BlitzXmlNetRenderer())
{ 
	#ifdef DOMPI
		MPI_Comm_rank(MPI_COMM_WORLD,&seq_myid) ; 
		MPI_Comm_size(MPI_COMM_WORLD,&seq_numprocs) ; 
	#endif
}


void BlitzNetAlopexerWithTemp::takeStats() 
{
	deltaError = deltaError - bestError;
	nextClock =  clock() ; 
	nextTime=  time(NULL) ; 
	deltaClock = difftime(nextClock , currentClock ) ; 
	deltaTime = difftime(nextTime , currentTime ) ; 
	wallTime += deltaTime ; 
	clockTime += deltaClock ;  
}

void BlitzNetAlopexerWithTemp::resetTimers() 
{
	currentClock =  clock()  ; 
	currentTime =  time(NULL)  ; 
}

void BlitzNetAlopexerWithTemp::initStats() 
{
	deltaError= 0 ;
	iterCount = 0 ;
	
	// timers
	currentClock = 0 ; 
	nextClock    = 0 ; 
	currentTime = 0 ; 
	nextTime    = 0 ; 
	wallTime = 0.0 ; 
	clockTime = 0.0 ; 
	deltaTime = 0.0 ; 
	deltaClock = 0.0 ; 
	initClock = clock()  ; 
	initTime = time(NULL)  ; 
}


AnnealingTarget* BlitzNetAlopexerWithTemp::alopex(ostream *toXML) 
{
	
    cout.precision(10) ;  
    if(blitzNet==NULL) throw "blitzNet is NULL" ; 
    if(minError==0 && totalIterations==0) throw "stop condition not set";
		
		//creating filestream for tracing error...testing.
		ofstream *outStream = new ofstream( "./error_trace1.txt" , ios::out) ;
		
		initStats()  ;
    
    bestNet =  new BlitzNet(blitzNet) ; 
    BlitzNet* currentNet =   new BlitzNet(blitzNet) ; 
    iterCount=0 ;  
		
		double acceptVars[mAcceptModel->getNumVariables()] ; 

    bestError = currentError= bestNet->eval() ;

    // keep track of the initial error for future comparison
    initialError = bestError;
		
#ifdef DOMPI
		if(seq_myid==0){
#endif		
		cout << "Initial Error [" << initialError << "]" << endl ;
		dumpXmlAlopexStart(toXML);
		cout << "******starting Alopex process******" << endl ;
#ifdef DOMPI
		}
#endif
		
		resetTimers();
    // loop untill a stop condition is reached 
    while(iterCount < totalIterations && currentError > minError){
				
			
			if (iterCount%outputPeriod == 0) {
				resetTimers();
#ifdef DOMPI
			if(seq_myid==0){
#endif			
				dumpXmlStartStep(toXML);
#ifdef DOMPI
      }
#endif
			}
			
				blitzNet->perturb(iterCount) ; 
#ifdef DOMPI
			blitzNet = syncNet(blitzNet) ; 
#endif
			
				currentError = blitzNet->eval() ; 
				
				//for testing only.
				if (iterCount%10==0 ) {
					*outStream << currentError << endl;
				}
        
				acceptVars[0] = currentError;
				acceptVars[1] = bestError;
        // if we have decreased the error level, make this network
        //  the best network
        if( mAcceptModel->accept(acceptVars) )  {
          *bestNet = *(blitzNet) ; 
					bestNet->eval(); //need valid net for output.
          bestError = currentError ; 
        }
				iterCount++;
				
				// Print out indicators to let the user know that
				//  the program is still running through iterations.
#ifdef DOMPI
				if(seq_myid==0){
#endif
					
				if(iterCount%1000==0){
					cout <<  iterCount << " " ;
					cout.flush() ;
					
	      } else if(iterCount%100==0){
					cout << "*" ;
					cout.flush() ;
				}	
#ifdef DOMPI
				}
#endif
				
				if (iterCount%outputPeriod == 0) {
#ifdef DOMPI
					if(seq_myid==0)
#endif
						// Finish the line of output indicating the number of iterations
					cout << endl ;		
					takeStats();
#ifdef DOMPI
					if(seq_myid==0){
#endif					
					dumpXmlStopStep(toXML);
					printStep(&cout);
					
#ifdef DOMPI
					}
#endif
				} 
					
				
				
    }
		
		
		if (iterCount%outputPeriod!=0) {
			takeStats();
#ifdef DOMPI
			if(seq_myid==0)
#endif			
			dumpXmlStopStep(toXML);
		}
				
#ifdef DOMPI
				if(seq_myid==0){
#endif				
		printFinal(&cout) ; 
    dumpXmlAlopexStop(toXML) ;
#ifdef DOMPI
				}
#endif		
		
		//closing testing output stream.
		outStream->close();
   // cout << endl;
	 // cout <<"\n********Finished**********" << endl;
   // cout << "Finished Alopex process. \n in " << iterCount << " iterations." << endl;
	 // cout << "Final error: [" << bestError << "]" << endl; 
    return bestNet ; 
}



void BlitzNetAlopexerWithTemp::printStep(ostream* s) 
{
  if(s!=NULL){
		*s << "error[" <<  bestError << "] "  << endl  ; 
		*s << "time(s)/iter: clock[" << ( ( deltaClock / (double) CLOCKS_PER_SEC) / (double) outputPeriod ) << "] " ; 
		*s << "wall[" << ( deltaTime  / (double) outputPeriod ) << "] " ;
		*s << " totalIters["<< iterCount << "] " << endl; 
  }
}

void BlitzNetAlopexerWithTemp::dumpXmlStopStep(ostream* s) 
{
	if(s!=NULL){
		*s << "\tend_error=\""   << bestError << "\"";
		*s << "\titerations=\""  << iterCount << "\"";
		*s << "\twall_time=\"" << deltaTime  << "\"";
		*s << "\tclock_time=\"" << deltaClock/ (double) CLOCKS_PER_SEC << "\"";
		
		
		*s << ">" << endl ;   // close previous
		*s << renderer->render(bestNet) ;   // pull this line later, maybe
		*s << "</annealerstep>" << endl ;   // close previous
	}
}

void BlitzNetAlopexerWithTemp::dumpXmlStartStep(ostream* s) 
{
	if(s!=NULL){
		*s << "<annealerstep";
		*s << "\tbegin_error=\"" << bestError   << "\"";
	}
}


void BlitzNetAlopexerWithTemp::printFinal(ostream* s) 
{
	
  if(s!=NULL){
		*s << "----- START Final Notes from BlitzNetAnnealer\t-----------------------------" << endl;
		*s << "final error[" << bestError << "]" << endl;
		*s << "total time(s): " ; 
		*s << "wall[" <<  ( difftime(time(NULL),initTime) )  << "] "  ; 
		*s << "clock[" <<  ( difftime(clock(),initClock) / (double) CLOCKS_PER_SEC )  << "] "  ; 
		*s << endl ; 
		*s << "time(s)/iter: " ; 
		*s << "wall[" <<  ( difftime(time(NULL),initTime) / (double) iterCount)  << "] "  ; 
		*s << "clock[" <<  ( difftime(clock(),initClock) / (double) CLOCKS_PER_SEC ) / ( (double) iterCount)  << "] "  ; 
		*s << "iterations[" <<  ( iterCount )  << "] "  ; 
		*s << "----- STOP Final Notes from BlitzNetAnnealer\t-----------------------------" << endl;
		*s << endl ; 
  }
	
}

void BlitzNetAlopexerWithTemp::dumpXmlAlopexStart(ostream* s) 
{
	*s << "<annealingrun>" <<endl ;
	*s << "\t<annealer>" << endl ; 
	mAcceptModel->toXML(s) ; 
	renderer->render(bestNet) ; 
	*s << "\t</annealer>" << endl ; 
}

void BlitzNetAlopexerWithTemp::dumpXmlAlopexStop(ostream* s) 
{
	*s << "\t<summary>" << endl ;
	*s << "\t\t<iterations value=\"" << iterCount <<  "\"/>" << endl ; 
	*s << "\t\t<finalError balue=\"" << bestError <<  "\"/>" << endl ;
#ifdef DOMPI
	*s << "\t\t<nprocs value=\"" << seq_numprocs  <<  "\"/>" << endl ; 
#endif
	*s << "\t\t<recordingtype value=\"total\" units=\"seconds\">" << endl ;
	*s << "\t\t\t<time type=\"wall\" value=\"" <<( difftime(time(NULL),initTime) )  <<  "\"/>" << endl ; 
	*s << "\t\t\t<time type=\"clock\" value=\"" << (( difftime(clock(),initClock) )/ (double) CLOCKS_PER_SEC )  <<  "\"/>" << endl ; 
	*s << "\t\t</recordingtype>" << endl ;
	*s << "\t\t<recordingtype value=\"avgperiter\" units=\"seconds/iter\">" << endl ;
	*s << "\t\t\t<time type=\"wall\" value=\"" << ( (difftime(time(NULL),initTime) ) / (double) iterCount)  <<  "\"/>" << endl ; 
	*s << "\t\t\t<time type=\"clock\" value=\"" << (  (( difftime(clock(),initClock) )/ (double) CLOCKS_PER_SEC ) / (double) iterCount )   <<  "\"/>" << endl ; 
	*s << "\t\t</recordingtype>" << endl ;
	*s << "\t</summary>" << endl ; 
	*s << "</annealingrun>" <<endl ;
}

void BlitzNetAlopexerWithTemp::setOutputPeriod(int period)
{
	outputPeriod=period;
}

void BlitzNetAlopexerWithTemp::setAlopexTarget(AnnealingTarget* alopexTarget) 
{
    blitzNet = (BlitzNet*) alopexTarget; 
}


