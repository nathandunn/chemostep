
#include <iostream>
using std::cout ; 
using std::cin ; 
using std::endl ; 
#include <math.h>
#include <time.h>
#include <fstream>
using std::ofstream;
using std::ios;


#include <Note.hpp> 
#include <TextEvalTrace.hpp>
#include "BlitzNetAlopexer.hpp"
#include "NetAlopexer.hpp"
#include "BlitzNet.hpp"
#include "BlitzXmlNetRenderer.hpp" 

#ifdef DOMPI
#include "mpi.h"
int seq_myid  ; 
int seq_numprocs ; 
#endif 

BlitzNetAlopexer::BlitzNetAlopexer() : NetAlopexer() , blitzNet(NULL) ,renderer(new BlitzXmlNetRenderer())
#ifdef DOMPI 
,hereWeights(NULL)
#endif
{ 
	#ifdef DOMPI
		MPI_Comm_rank(MPI_COMM_WORLD,&seq_myid) ; 
		MPI_Comm_size(MPI_COMM_WORLD,&seq_numprocs) ; 
	#endif
}


void BlitzNetAlopexer::takeStats() 
{
	deltaError = deltaError - bestError;
	nextClock =  clock() ; 
	nextTime=  time(NULL) ; 
	deltaClock = difftime(nextClock , currentClock ) ; 
	deltaTime = difftime(nextTime , currentTime ) ; 
	wallTime += deltaTime ; 
	clockTime += deltaClock ;  
}

void BlitzNetAlopexer::resetTimers() 
{
	currentClock =  clock()  ; 
	currentTime =  time(NULL)  ; 
}

void BlitzNetAlopexer::initStats() 
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

void BlitzNetAlopexer::dumpNet(string networkFile) 
{
    if(&networkFile!=NULL){
      ofstream* netOutputXmlStream =   new ofstream( networkFile.c_str(), ios::out) ; 
      (bestNet->getNote())->setNote("error",bestError) ; 
      *netOutputXmlStream << renderer->render(bestNet) << endl ;   // pull this line later, maybe
      netOutputXmlStream->close() ; 
      netOutputXmlStream = NULL ; 
    }
}


AnnealingTarget* BlitzNetAlopexer::alopex(ostream *toXML,string netOutputFile) 
{
	
    cout.precision(10) ;  
    if(blitzNet==NULL) throw "blitzNet is NULL" ; 
    if(minError==0 && totalIterations==0) throw "stop condition not set";
		
		//for testing
//        ofstream *outStream = new ofstream( "./error_trace1.txt" , ios::out) ;
		
		initStats()  ;
    
    bestNet =  new BlitzNet(blitzNet) ; 
    BlitzNet* currentNet =   new BlitzNet(blitzNet) ; 
    iterCount=0 ;  
		
		double acceptVars[mAcceptModel->getNumVariables()] ; 

    bestError = currentError= bestNet->eval();
		bestSdev = bestNet->getSdev() ;
    bestCount = bestNet->getCount() ;

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
			
		
    while(iterCount < totalIterations && bestError > minError){
				
			
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
		
			currentNet->perturb(currentError) ; 
#ifdef DOMPI
			currentNet = syncNet(currentNet) ; 
#endif
			
			currentError = currentNet->eval() ;
			currentCount = currentNet->getCount() ;
			currentSdev = currentNet->getSdev() ; 
				
				//for testing only.
//                if (iterCount%2==0) {
//                    *outStream << currentError << endl;
//                }
        
				acceptVars[0] = currentError ;
				acceptVars[1] = bestError ;
				acceptVars[2] = currentSdev ;
				acceptVars[3] = bestSdev ;
				acceptVars[4] = currentCount ;
				acceptVars[5] = bestCount ;
        // if we have decreased the error level, make this network
        //  the best network
        if( mAcceptModel->accept(acceptVars) )  {
          *bestNet = *(currentNet) ; 
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
                    dumpNet( netOutputFile ) ; 
					
#ifdef DOMPI
					}
#endif
				} 
					
				
				
    }
		
		
		if (iterCount%outputPeriod!=0) {
			takeStats();
#ifdef DOMPI
			if(seq_myid==0){
#endif			
                dumpXmlStopStep(toXML);
                dumpNet( netOutputFile ) ; 
#ifdef DOMPI
            }
#endif
		}

				
#ifdef DOMPI
        if(seq_myid==0){
#endif				
            printFinal(&cout) ; 
            dumpXmlAlopexStop(toXML) ;
            dumpNet( netOutputFile ) ; 
#ifdef DOMPI
        }
#endif		
		
//        outStream->close();
   // cout << endl;
	 // cout <<"\n********Finished**********" << endl;
   // cout << "Finished Alopex process. \n in " << iterCount << " iterations." << endl;
	 // cout << "Final error: [" << bestError << "]" << endl; 
    return bestNet ; 
}

#ifdef DOMPI
/// Synchronizes the networks from the original network.
BlitzNet* BlitzNetAlopexer::syncNet(BlitzNet* origNet) 
{
	MPI_Comm_rank(MPI_COMM_WORLD,&seq_myid) ; 
	int numNeurons = origNet->getNumNeurons() ; 
	
	// just check one of the variables to see if its null
	if(hereWeights==NULL){
		bcastMatrix = new Matrix( (numNeurons+4),numNeurons) ; 
		hereWeights = new Matrix( (numNeurons+4),numNeurons) ; 
		hereBias = new Vector( numNeurons) ; 
		hereTau = new Vector( numNeurons) ; 
		hereGain = new Vector( numNeurons) ; 
		hereInitNeurons = new Vector( numNeurons) ; 
		hereVmem = new Vector( numNeurons) ; 
	}
	(*bcastMatrix)( Range(0, numNeurons - 1), Range(0, numNeurons - 1) ) =*(origNet->getWeights()) ;
	(*bcastMatrix)( numNeurons, Range::all() ) = *(origNet->getTau());
	(*bcastMatrix)( numNeurons + 1,  Range::all() ) = *(origNet->getBias()) ; 
	(*bcastMatrix)( numNeurons + 2,  Range::all() ) = *(origNet->getInitNeuron()) ; 
	(*bcastMatrix)( numNeurons + 3,  Range::all() ) = *(origNet->getGain()) ; 
	MPI_Bcast(bcastMatrix->data(), bcastMatrix->size(), MPI_DOUBLE, 0, MPI_COMM_WORLD);
	if(seq_myid != 0){
		(*hereWeights) = (*bcastMatrix) ( Range(0,numNeurons-1),Range(0,numNeurons-1)  ) ;
		(*hereTau) = (*bcastMatrix) (numNeurons,Range::all() ) ; 
		(*hereBias) = (*bcastMatrix) (numNeurons+1,Range::all() ) ; 
		(*hereInitNeurons) = (*bcastMatrix) (numNeurons+2,Range::all() ) ; 
		(*hereGain) = (*bcastMatrix) (numNeurons+3,Range::all() ) ; 
		
		origNet->setWeights( hereWeights     ) ; 
		origNet->setBias( hereBias ) ; 
		origNet->setTau(  hereTau ) ; 
		origNet->setInitNeuron(  hereInitNeurons ) ; 
		origNet->setGain( hereGain ) ; 
		origNet->setNeurons(  hereInitNeurons   ) ; 
	}
	
	return origNet ;
}
#endif 


void BlitzNetAlopexer::printStep(ostream* s) 
{
  if(s!=NULL){
		*s << "error[" <<  bestError << "] "  << endl  ; 
		*s << "time(s)/iter: clock[" << ( ( deltaClock / (double) CLOCKS_PER_SEC) / (double) outputPeriod ) << "] " ; 
		*s << "wall[" << ( deltaTime  / (double) outputPeriod ) << "] " ;
		*s << " totalIters["<< iterCount << "] " << endl; 
  }
}

void BlitzNetAlopexer::dumpXmlStopStep(ostream* s) 
{
	if(s!=NULL){
		*s << "\tend_error=\""   << bestError << "\"";
		*s << "\titerations=\""  << iterCount << "\"";
		*s << "\twall_time=\"" << deltaTime  << "\"";
		*s << "\tclock_time=\"" << deltaClock/ (double) CLOCKS_PER_SEC << "\"";
		
		
		*s << ">" << endl ;   // close previous
//        *s << renderer->render(bestNet) ;   // pull this line later, maybe
		*s << "</annealerstep>" << endl ;   // close previous
	}
}

void BlitzNetAlopexer::dumpXmlStartStep(ostream* s) 
{
	if(s!=NULL){
		*s << "<annealerstep";
		*s << "\tbegin_error=\"" << bestError   << "\"";
	}
}


void BlitzNetAlopexer::printFinal(ostream* s) 
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

void BlitzNetAlopexer::dumpXmlAlopexStart(ostream* s) 
{
	*s << "<annealingrun>" <<endl ;
	*s << "\t<alopexer>" << endl ; 
    mAcceptModel->setNumTabs(1) ; 
	mAcceptModel->toXML(s) ; 
	renderer->render(bestNet) ; 
    (bestNet->getEvaluator())->toXML(s) ; 
    *s << (bestNet->getNote())->toXML() ; 
	*s << "\t</alopexer>" << endl ; 
}

void BlitzNetAlopexer::dumpXmlAlopexStop(ostream* s) 
{
	*s << "\t<summary>" << endl ;
    (bestNet->getNote())->setNote("error",bestError) ; 
    *s << renderer->render(bestNet)  << endl  ; 
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

void BlitzNetAlopexer::setOutputPeriod(int period)
{
	outputPeriod=period;
}

void BlitzNetAlopexer::setAlopexTarget(AnnealingTarget* alopexTarget) 
{
    blitzNet = (BlitzNet*) alopexTarget; 
}


