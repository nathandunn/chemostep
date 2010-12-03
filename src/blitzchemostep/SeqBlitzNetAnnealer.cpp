
#include <iostream>
using std::cout ; 
using std::ostream ; 
using std::endl ; 
using std::ostringstream ; 

#include <fstream>
using std::ofstream ; 
using std::ios; 

#include <time.h>


#include <TextEvalTrace.hpp>
#include <TempSchedule.hpp>
#include <Note.hpp>
#include <AcceptModel.hpp>

#include "BlitzNet.hpp"
#include "BlitzXmlNetRenderer.hpp" 
#include "SeqBlitzNetAnnealer.hpp"

#ifdef DOMPI
#include "mpi.h"
#endif 


SeqBlitzNetAnnealer::SeqBlitzNetAnnealer() : BlitzNetAnnealer()
,renderer(new BlitzXmlNetRenderer())
,blitzNet(NULL)
,totalIterations(0)
,stepCount(0)
,overallBestNetError(DBL_MAX)
,mNetOutputStream(NULL)
{
#ifdef DOMPI
MPI_Comm_rank(MPI_COMM_WORLD,&seq_myid) ; 
MPI_Comm_size(MPI_COMM_WORLD,&seq_numprocs) ; 
hereWeights = NULL ; // need to initialize this as NULL 
#endif 

}

void SeqBlitzNetAnnealer::setAnnealingTarget(AnnealingTarget* annealingTarget) 
{
    blitzNet = (BlitzNet*) annealingTarget; 
}



void SeqBlitzNetAnnealer::setMinInitialImprovement(double _mMinInitialImprovement)  
{
    mMinInitialImprovement = _mMinInitialImprovement;
}

void SeqBlitzNetAnnealer::takeClock() 
{
      prevClock = nextClock ; 
      nextClock =  clock()  ;
      deltaClock += difftime(nextClock , prevClock) ; 
      clockTime += deltaClock ; 
}


void SeqBlitzNetAnnealer::takeStats() 
{
      // take time
      deltaError = deltaError - bestError;
      nextTime=  time(NULL) ; 
      deltaTime = difftime(nextTime , currentTime ) ; 
      wallTime += deltaTime ; 

      // take clock
      takeClock() ; 

      // take iterations 
      totalIterations += currentIterMax ; 
      stepCount++ ; 
}

void SeqBlitzNetAnnealer::resetTimers() 
{
      currentClock =  clock()  ; 
      nextClock =  clock()  ; 
      prevClock =  clock()  ; 
      deltaClock =  0  ; 
      currentTime =  time(NULL)  ; 
}

void SeqBlitzNetAnnealer::initStats() 
{
    currentIterMax = 0   ; 
    deltaError = 0 ; 
    iterCount = 0 ; 
    stepCount = 0 ; 

    // timers
    currentClock = 0 ; 
    nextClock    = 0 ; 
    prevClock = 0 ; 
    currentTime = 0 ; 
    nextTime    = 0 ; 
    wallTime = 0.0 ; 
    clockTime = 0.0 ; 
    deltaTime = 0.0 ; 
    deltaClock = 0.0 ; 
    initTime = time(NULL)  ; 
}




AnnealingTarget* SeqBlitzNetAnnealer::anneal( ostream *toXML,string netOutputFile) 
{
    if(&netOutputFile!=NULL){
//        if(mNetOutputStream!=NULL){
//            mNetOutputStream->close() ; 
//            delete mNetOutputStream ; 
        delete mNetOutputStream ;     
        mNetOutputStream = new ofstream( netOutputFile.c_str(), ios::out) ;
//        }
//        if(mNetOutputStream!=NULL){
//            mNetOutputStream = new ofstream( ) ;
//        }
    }
    int tempStep = 0 ; 
    cout.precision(10) ;  
    if(blitzNet==NULL) throw "blitzNet is NULL" ; 
    bestNet =  new BlitzNet(blitzNet) ; 
    overallBestNet = new BlitzNet(blitzNet) ; 
    BlitzNet* currentNet =   new BlitzNet(blitzNet) ; 

    initStats()  ; 

    // note that currentClock and nextClock are in seconds
    double acceptVars[mAcceptModel->getNumVariables()] ; 

    bestError = bestNet->eval() ;
    overallBestNetError = bestError ; 
    bestSdev = bestNet->getSdev() ;
    bestCount = bestNet->getCount() ;

    // keep track of the initial error for future comparison
    initialError = bestError;


#ifdef DOMPI
if(seq_myid==0){
#endif
    cout << "Pre-Init Initial Error [" << initialError << "]" << endl ;
    dumpXmlAnnealStart(toXML) ; 
    dumpNet( netOutputFile ) ; 
#ifdef DOMPI
}
#endif

    // init error
    resetTimers() ; 
    tempSchedule->initTemps() ; 


    // eval points
    bestError = bestNet->eval() ;
    bestSdev = bestNet->getSdev() ;
    bestCount = bestNet->getCount() ;

    // keep track of the initial error for future comparison
    initialError = bestError;


    // loop through all the values in the tempSchedule
    while(tempSchedule->hasMoreTemps()){

      resetTimers() ; 

      // need to have a ratio in here to get interseting results
      currentTemp  =  tempSchedule->getNextTemp(deltaError) ; 
     
#ifdef DOMPI
      MPI_Bcast(&currentTemp,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
if(seq_myid==0)
#endif
      dumpXmlStartStep(toXML) ; 

      deltaError = bestError;
      currentIterMax = iterPerTemp ; 

#ifdef DOMPI
      if(seq_myid==0) {
#endif
	  cout << endl << "Iterations: " ;
      
#ifdef DOMPI
      }
#endif

      for(iterCount = 0 ; iterCount < currentIterMax ; iterCount++){
	  
	  // TODO maybe initialize ahead of time instead of new memory calls or have operator=  be a copier
	  *blitzNet = *(currentNet) ;
	  blitzNet->perturb(currentTemp) ; 
#ifdef DOMPI
	  blitzNet = syncNet(blitzNet) ; 
#endif
	  currentError = blitzNet->eval() ;
	  currentCount = blitzNet->getCount() ;
	  currentSdev = blitzNet->getSdev() ;
//        cout << seq_myid << ": currentError " << currentError << " iterCount: " << iterCount << endl ; 
//        cout << seq_myid << ": currentSdev " << currentSdev << " iterCount: " << iterCount << endl ; 
//        cout << seq_myid << ": currentCount " << currentCount << " iterCount: " << iterCount << endl ; 
	  
	  acceptVars[0] = currentError ;
	  acceptVars[1] = bestError ;
	  acceptVars[2] = currentSdev ;
	  acceptVars[3] = bestSdev ;
	  acceptVars[4] = currentCount ;
	  acceptVars[5] = bestCount ;
      if(mAcceptModel->getNumVariables()>=7){
          acceptVars[6] = currentTemp ;
      }
	  
	  if(   mAcceptModel->accept( acceptVars )  ){

          #ifdef DOMPI
          if(seq_myid==0){
          #endif
            cout << "+" ;
            cout.flush() ;
          #ifdef DOMPI
          }
          #endif
          *bestNet = *blitzNet ; 
          bestNet->eval() ; // we want a valid network, here when node 0 renders it to output
          *currentNet = *bestNet ; 
          bestError = currentError ; 
          currentIterMax += mSetBack ;  // add some more to this iteration


          // record network for future reference
          if( bestError < overallBestNetError ){
              overallBestNetError = currentError ; 
              *overallBestNet = *bestNet ; 
              (overallBestNet->getNote())->setNote("error",overallBestNetError) ; 
              (overallBestNet->getNote())->setNote("iteration",iterCount) ; 
              (overallBestNet->getNote())->setNote("tempstep",tempStep) ; 

              #ifdef DOMPI
              if(seq_myid==0){
              #endif
                cout << "!" ;
                cout.flush() ;
                dumpNet( netOutputFile ) ; 
              #ifdef DOMPI
              }
              #endif

          }


	  }
	  
	  // Print out indicators to let the user know that
	  //  the program is still running through iterations.
#ifdef DOMPI
	  if(seq_myid==0){
#endif
	      if(iterCount%1000==0){
		  cout <<  "(" << iterCount << ")" ;
		  cout.flush() ;
		  
	      } else if(iterCount%100==0){
		  cout << "*" ;
		  cout.flush() ;
	      }
#ifdef DOMPI
	  }
#endif
	  
      }
   
#ifdef DOMPI
      if(seq_myid==0)
#endif
	  // Finish the line of output indicating the number of iterations
	  cout << endl ;
      
      takeStats() ;
      ++tempStep ; 
      
#ifdef DOMPI
if(seq_myid==0){
#endif
      printStep(&cout) ; 
      dumpXmlStopStep(toXML) ; 
      dumpNet( netOutputFile ) ; 
#ifdef DOMPI
}
#endif
    }



#ifdef DOMPI
if(seq_myid==0){
#endif
    printFinal(&cout) ; 
    dumpXmlAnnealStop(toXML) ; 
    dumpNet( netOutputFile ) ; 
#ifdef DOMPI
}
#endif
    
    return bestNet ; 
}



void SeqBlitzNetAnnealer::dumpNet(string networkFile) 
{
//    if(&networkFile!=NULL){
        delete mNetOutputStream ;     
//      mNetOutputStream->open( networkFile.c_str(), ios::out) ;
      mNetOutputStream  = new ofstream( networkFile.c_str(), ios::out) ;
//      mNetOutputStream->flush() ;   
      *mNetOutputStream << renderer->render(overallBestNet) << endl ;   // pull this line later, maybe
      mNetOutputStream->close() ; // flushes, as well
//    }
      
}



#ifdef DOMPI
/// Synchronizes the networks from the original network.
BlitzNet* SeqBlitzNetAnnealer::syncNet(BlitzNet* origNet) 
{
      MPI_Comm_rank(MPI_COMM_WORLD,&seq_myid) ; 
      int numNeurons = origNet->getNumNeurons() ; 

      // just check one of the variables to see if its null
      if(hereWeights==NULL){
          bcastMatrix = new Matrix( (numNeurons+4),numNeurons) ; 
          hereWeights = new Matrix( (numNeurons+4),numNeurons) ; 
          hereTau = new Vector( numNeurons) ; 
          hereBias = new Vector( numNeurons) ; 
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
          origNet->setTau(  hereTau ) ; 
          origNet->setBias( hereBias ) ; 
          origNet->setGain( hereGain ) ; 
          origNet->setInitNeuron(  hereInitNeurons ) ; 
          origNet->setNeurons(  hereInitNeurons   ) ; 
      }

      return origNet ;
}
#endif 



void SeqBlitzNetAnnealer::printStep(ostream* s) 
{
  if(s!=NULL){
      *s << "temp[" << currentTemp << "]  error[" <<  bestError << "] overallBestError[" << overallBestNetError << "]" <<  endl  ; 
      *s << "time(s)/iter: clock[" << ( ( deltaClock / (double) CLOCKS_PER_SEC) / (double) currentIterMax ) << "] " ; 
      *s << "wall[" << ( deltaTime  / (double) currentIterMax ) << "] " ;
      *s << " iters["<< currentIterMax << "] " << endl; 
  }
}

void SeqBlitzNetAnnealer::dumpXmlStopStep(ostream* s) 
{
      if(s!=NULL){
          *s << "\tend_error=\""   << bestError << "\"";
          *s << "\tend_best_error=\""   << overallBestNetError << "\"";
          *s << "\titerations=\""  << iterCount << "\"";
          *s << "\ttotal_iterations=\""  << totalIterations << "\"";
          *s << "\twall_time=\"" << deltaTime  << "\"";
          *s << "\tclock_time=\"" << deltaClock/ (double) CLOCKS_PER_SEC << "\"";


          *s << ">" << endl ;   // close previous
//          *s << renderer->render(bestNet) ;   // pull this line later, maybe
          *s << "</annealerstep>" << endl ;   // close previous
      }
}

void SeqBlitzNetAnnealer::dumpXmlStartStep(ostream* s) 
{
      if(s!=NULL){
          *s << "<annealerstep";
          *s << "\tstep=\""        << stepCount << "\"";
          *s << "\ttemperature=\"" << currentTemp << "\"";
          *s << "\tbegin_error=\"" << overallBestNetError << "\"";
      }
}


void SeqBlitzNetAnnealer::printFinal(ostream* s) 
{

  if(s!=NULL){
      *s << endl << "----- START Final Notes from BlitzNetAnnealer\t-----------------------------" << endl;
      *s << "total time(s): " ; 
      *s << "wall[" <<  ( difftime(time(NULL),initTime) )  << "] "  ; 
      *s << "clock[" <<  ( totalClock / (double) CLOCKS_PER_SEC )  << "] "  ; 
      *s << endl ; 
      *s << "time(s)/iter: " ; 
      *s << "wall[" <<  ( difftime(time(NULL),initTime) / (double) totalIterations )  << "] "  ; 
      *s << "clock[" <<  ( totalClock / (double) CLOCKS_PER_SEC ) / ( (double) totalIterations)  << "] "  ; 
      *s << "iterations[" <<  ( totalIterations )  << "] "  ; 
      *s << endl << "----- STOP Final Notes from BlitzNetAnnealer\t-----------------------------" << endl;
      *s << endl ; 
  }

}

void SeqBlitzNetAnnealer::dumpXmlAnnealStart(ostream* s) 
{
    *s << "<annealingrun>" <<endl ;
    *s << "\t<annealer type=\"seqblitznetannealer\">" << endl ; 
    *s << "\t\t<mininitialimprovement value=\"" << mMinInitialImprovement << "\"/>" << endl ; 
    *s << "\t\t<iterpertemp value=\"" << iterPerTemp << "\"/>" << endl ; 
    *s << "\t\t<setback value=\"" << mSetBack << "\"/>" << endl ; 
    tempSchedule->setNumTabs(2) ; 
    tempSchedule->toXML(s) ; 
    mAcceptModel->toXML(s) ; 
    (bestNet->getEvaluator())->toXML(s) ; 
    (bestNet->getPerturber())->toXML(s) ; 
    *s << (bestNet->getNote())->toXML() ; 
//    renderer->render(bestNet) ; 
    *s << "\t</annealer>" << endl ; 
}

void SeqBlitzNetAnnealer::dumpXmlAnnealStop(ostream* s) 
{
    *s << "\t<summary>" << endl ;
    (bestNet->getNote())->setNote("error",overallBestNetError) ; 
    *s << renderer->render(bestNet)  << endl  ; 
    *s << "\t\t<iterations value=\"" << totalIterations <<  "\"/>" << endl ; 
    *s << "\t\t<numtemps value=\"" << stepCount <<  "\"/>" << endl ; 
    *s << "\t\t<finalerror value=\"" << bestError <<  "\"/>" << endl ; 
    *s << "\t\t<itersperstep value=\"" << ((double) totalIterations) / ((double) stepCount) <<  "\"/>" << endl ; 
#ifdef DOMPI
    *s << "\t\t<nprocs value=\"" << seq_numprocs  <<  "\"/>" << endl ; 
#endif
    *s << "\t\t<recordingtype value=\"total\" units=\"seconds\">" << endl ;
    *s << "\t\t\t<time type=\"wall\" value=\"" <<( difftime(time(NULL),initTime) )  <<  "\"/>" << endl ; 
    *s << "\t\t\t<time type=\"clock\" value=\"" << (  ( totalClock )/ (double) CLOCKS_PER_SEC )  <<  "\"/>" << endl ; 
    *s << "\t\t</recordingtype>" << endl ;
    *s << "\t\t<recordingtype value=\"avgperiter\" units=\"seconds/iter\">" << endl ;
    *s << "\t\t\t<time type=\"wall\" value=\"" << ( (difftime(time(NULL),initTime) ) / (double) totalIterations)  <<  "\"/>" << endl ; 
    *s << "\t\t\t<time type=\"clock\" value=\"" << ( ( (totalClock )/ (double) CLOCKS_PER_SEC ) / (double) totalIterations )   <<  "\"/>" << endl ; 
    *s << "\t\t</recordingtype>" << endl ;
    *s << "\t</summary>" << endl ; 
    *s << "</annealingrun>" <<endl ;
}





/* Function int main(int argc, char **argv) {{{ */
//int main(int argc, char **argv)
//{


//    return 0;
//} /* }}} */


/* Modeline for ViM {{{
 * vim:set ts=4:
 * vim600:fdm=marker fdl=0 fdc=3:
 * }}} */

// -*- C++ -*-
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

