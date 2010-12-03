
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
#include <BlitzNet.hpp>
#include <SeqBlitzNetAnnealer.hpp>

#include "SeqOneWormBlitzNetAnnealer.hpp"
#include "OneWormSimEval.hpp"

#ifdef DOMPI
#include "mpi.h"
#endif 


SeqOneWormBlitzNetAnnealer::SeqOneWormBlitzNetAnnealer(int extraWormsToRun) : SeqBlitzNetAnnealer()
,mExtraWorms(extraWormsToRun) 
{

}


AnnealingTarget* SeqOneWormBlitzNetAnnealer::anneal( ostream *toXML,string netOutputFile) 
{
    if(&netOutputFile!=NULL){
        if(mNetOutputStream==NULL){
            mNetOutputStream = new ofstream( netOutputFile.c_str(), ios::out) ;
        }
    }

    int tempStep = 0 ; 
    cout.precision(10) ;  
    if(blitzNet==NULL) throw "blitzNet is NULL" ; 
    bestNet =  new BlitzNet(blitzNet) ; 
    overallBestNet = new BlitzNet(blitzNet) ; 

    initStats()  ; 

    // note that currentClock and nextClock are in seconds
    double acceptVars[mAcceptModel->getNumVariables()] ; 

    bestError = bestNet->eval() ;
    if(mExtraWorms>0){
        bestError =  ((OneWormSimEval*) bestNet->getEvaluator())->evaluateMoreWorms( mExtraWorms) ; 
    }

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


    // loop through all the values in the tempSchedule
    while(tempSchedule->hasMoreTemps()){

      *bestNet = *overallBestNet ; 
      bestError = overallBestNetError ; 

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

      *bestNet = *overallBestNet ; 
      
      // eval points
      bestError = bestNet->eval() ;
      bestSdev = bestNet->getSdev() ;
      bestCount = bestNet->getCount() ;

      for(iterCount = 0 ; iterCount < currentIterMax ; iterCount++){
	  
	  // TODO maybe initialize ahead of time instead of new memory calls or have operator=  be a copier
      *blitzNet = *bestNet ;
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

          // Accept blitzNet to bestNet within this temperature step.
          *bestNet = *blitzNet ; 
          bestError = currentError ; 
          currentIterMax += mSetBack ;  // add some more to this iteration

          // Accept bestNet to overallBestNet over all temperatures.
          // record network for future reference
          if( bestError < overallBestNetError ){

              #ifdef DOMPI
              if(seq_myid==0){
              #endif
//              cout << "old best error: " << bestError << endl ; 
				cout << "?" ; 
				cout.flush()  ; 
              #ifdef DOMPI
              }
              #endif
                  
              if(mExtraWorms>0)
              bestError =  ((OneWormSimEval*) bestNet->getEvaluator())->evaluateMoreWorms( mExtraWorms) ; 
//              #ifdef DOMPI
//              if(seq_myid==0)
//              #endif
//              cout << "new best error: " << bestError << endl ; 

              if( bestError < overallBestNetError){

                  overallBestNetError = bestError ; 
                  bestNet->eval() ; // we want a valid network, here when node 0 renders it to output
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
              else{
                  #ifdef DOMPI
                  if(seq_myid==0){
                  #endif
                    cout << "X" ;
                    cout.flush() ;
                  #ifdef DOMPI
                  }
                  #endif
              }
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





void SeqOneWormBlitzNetAnnealer::dumpXmlAnnealStart(ostream* s) 
{
    *s << "<annealingrun>" <<endl ;
    *s << "\t<annealer type=\"seqonewormblitznetannealer\">" << endl ; 
    *s << "\t\t<iterpertemp value=\"" << iterPerTemp << "\"/>" << endl ; 
    *s << "\t\t<setback value=\"" << mSetBack << "\"/>" << endl ; 
    *s << "\t\t<verificationworms value=\"" << mExtraWorms << "\"/>" << endl ; 
    tempSchedule->setNumTabs(2) ; 
    tempSchedule->toXML(s) ; 
    mAcceptModel->toXML(s) ; 
    (bestNet->getEvaluator())->toXML(s) ; 
    (bestNet->getPerturber())->toXML(s) ; 
    *s << (bestNet->getNote())->toXML() ; 
    *s << "\t</annealer>" << endl ; 
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

