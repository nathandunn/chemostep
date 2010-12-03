
#ifdef DOMPI
    #include "mpi.h"
#endif

#include <iostream>
using std::cout ; 
using std::cin ; 
using std::endl ; 

#include <time.h>


#include "TextEvalTrace.hpp"
#include "BlitzNetAnnealer.hpp"
#include "TempSchedule.hpp"
#include "BlitzNet.hpp"
#include "BlitzXmlNetRenderer.hpp" 

BlitzNetAnnealer::BlitzNetAnnealer() : NetAnnealer() , blitzNet(NULL) ,ARGC(0),ARGV(0),renderer(new BlitzXmlNetRenderer())
, totalIterations(0) 
#if DOMPI
,bcastMatrix(new Matrix(0,0,MEM_POLICY))
,theseWeights(new Matrix(0,0,MEM_POLICY))
,theseTau(new Vector(0,MEM_POLICY))
,theseBias(new Vector(0,MEM_POLICY))
,theseInitNeuron(new Vector(0,MEM_POLICY))
#endif
{ }


void BlitzNetAnnealer::setArguments(int newArgc,char** newArgv) {
    ARGC = newArgc ; 
    ARGV = newArgv ; 
}

AnnealingTarget* BlitzNetAnnealer::anneal(ostream *toXML) 
{

    #ifdef DOMPI
        int myid  ;  
        int nprocs;
        MPI_Comm_rank(MPI_COMM_WORLD, &myid);
        MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

        cout << "in annealer myid: " << myid << endl ; 
        cout << "in annealer nprocs: " << nprocs << endl ; 
        
        MPI_Barrier(MPI_COMM_WORLD) ;     
        cout << "in annealer: done waiting: " << myid << endl; 

    #endif 

    cout.precision(10) ;  
    if(blitzNet==NULL) throw "blitzNet is NULL" ; 
    double bestError ; 
    double currentError ; 
    double initialError ;
    double deltaError = 0;
    BlitzNet* bestNet =  new BlitzNet(blitzNet) ; 
    BlitzNet* currentNet =   new BlitzNet(blitzNet) ; 
    int iterCount ; 
    double currentTemp  ;
    double backStepCount = -1 ; 
    int currentIterMax = 0   ; 

    // note that currentTime and nextTime are in seconds
    clock_t currentTime = 0 ; 
    clock_t nextTime    = 0 ; 
    double timer       = 0.0 ; 
    double deltaTime = 0.0 ; 
    clock_t initTime = clock()  ; 


    // bestError is the initial error of the bestNet NN
    //  ??? Will eval always return zero at this step?
    bestError = bestNet->eval() ;

    // keep track of the initial error for future comparison
    initialError = bestError;
    cout << "Initial Error = " << initialError << endl << endl ;

    // initTemps initializes all temperatures to zero (?)
    // that can't be right ... what would be the point?
    //  the temperatures eventually test the NN at a range
    //  of temperatures as the error level is reduced
    tempSchedule->initTemps() ; 


    // loop through all the values in the tempSchedule
    //  and ... ^??? Describe what happens here
    while(tempSchedule->hasMoreTemps()){

      // grab the current time. we will get the current time
      //  again at the end of each while loop and subtract
      //  the time now to get the time elapsed for each iteration
      //  not that this is done where it hasn't been divided by CLOCKS_PER_SEC
      currentTime =  clock()  ; 
      
      // ^??? What exactly is backStepCount?
      // otherwise, just keep it at the same temperature
      if(backStepCount <= 0){  
        currentTemp  =  tempSchedule->getNextTemp(deltaError) ; 
        // currentTemp  =  tempSchedule->getNextTemp() ; 
      }

      if(toXML!=NULL){
          *toXML << "\t<annealerstep";
          *toXML << "\tstep=\""        << iterCount << "\"";
          *toXML << "\ttemperature=\"" << currentTemp << "\"";
          *toXML << "\tbegin_error=\"" << bestError   << "\"";
      }

      --backStepCount ;

      // set deltaError to bestError for now, we'll subract
      //	bestError later to get the delta
      deltaError = bestError;

      // ^??? Where does iterPerTemp come from?
      currentIterMax = iterPerTemp ; 

      for(iterCount = 0 ; iterCount < currentIterMax ; iterCount++){

        // TODO maybe initialize ahead of time instead of new memory calls 
        // or have operator=  be a copier
        *blitzNet = *(currentNet) ;
        blitzNet->perturb(currentTemp) ; 
        
        currentError = blitzNet->eval() ; 
        
        // ^??? after each iteration we collect?
        // test speed, I guess, versus temperature

        // if we have decreased the error level, make this network
        //  the best network
        // in order to handle roundoff error in bits, convert to float, since
        //  we only care about the most significant bits
            if(   currentError <  bestError  ){
                blitzNet->setValid(false) ; 
                bestNet->setValid(false) ; 
                if( blitzNet->eval() < bestNet->eval() ) {
                      *bestNet = *(blitzNet) ; 
                      *currentNet = *(bestNet) ; 
                      bestError = currentError ; 

                      // ^??? how is mBackStep calculated?
                      backStepCount = mBackStep ; 
                      currentIterMax += mSetBack ;  // add some more to this iteration
                  }
            }
        }
	
        // ^??? does it make more sense to do it only after each temperature?  }        

	// get the new deltaError
	deltaError = deltaError - bestError;


      // grab the current time the time at the beginning of the
      //  while loop to get the length of time required for one iteration
      nextTime =  clock() ; 

      // take the difference in clock time to keep the most amount of detail
      deltaTime = difftime(nextTime , currentTime ) ; 
#ifndef DOMPI
      // if no MPI, otherwise we need the global values for both of these
      timer += deltaTime ; 
      totalIterations += currentIterMax ; 
#endif

      if(toXML!=NULL){
          *toXML << "\tend_error=\""   << bestError << "\"";
          *toXML << "\titerations=\""  << iterCount << "\"";
          *toXML << "\ttotal_iterations=\""  << totalIterations << "\"";
          *toXML << "\tcompute_time=\"" << (nextTime - currentTime ) / (double) CLOCKS_PER_SEC << "\"";


*toXML << ">" << endl ;   // close previous
*toXML << renderer->render(bestNet) ;   // pull this line
*toXML << "</annealerstep>" << endl ;   // close previous
//          *toXML << " />" << endl ;
      }


////////////////////////MPI stuff begin/////////////////////////////////
#ifdef DOMPI

      // timer code, prior to Barrier call
	  
      // 1. Sum the total number of iterations
      MPI_Allreduce(&currentIterMax, &globalIters, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
      totalIterations += globalIters ; 
//      // 2. Get the max time per processor
      MPI_Allreduce(&deltaTime, &maxDeltaT, 1, MPI_DOUBLE, MPI_MAX, MPI_COMM_WORLD);
      timer += maxDeltaT ; 
      // 3. Get the min time per processor
      MPI_Allreduce(&deltaTime, &minDeltaT, 1, MPI_DOUBLE, MPI_MIN, MPI_COMM_WORLD);
     
      // 3.a.  report shift at end (done at end)
      // 4. Get the average time per processor (done at end)
     
      // end of timing code


      // error from each source struct is minimized (first element?)
      // this goes onto the destination node
      src.val = bestError ; 
      src.node = myid;
      MPI_Allreduce(&src, &dest, 1, MPI_DOUBLE_INT, MPI_MINLOC, MPI_COMM_WORLD);
      MPI_Bcast(&deltaError, 1, MPI_DOUBLE, dest.node, MPI_COMM_WORLD);
      
      // this should ensure that we ALWAYS DO BACKSTEP if there 
      // is an improvement on ANY of the processors
      if( (float) dest.val < (float) bestError){
        backStepCount = mBackStep ; 
      }
      
      int numNeurons = currentNet->getNumNeurons() ; 
      //            if(myid==dest.node){
      bcastMatrix->resize( (numNeurons+3),numNeurons) ; 
      (*bcastMatrix)( Range(0, numNeurons - 1), Range(0, numNeurons - 1) ) =*(bestNet->getWeights()) ;
      (*bcastMatrix)( numNeurons, Range::all() ) = *(bestNet->getTau());
      (*bcastMatrix)( numNeurons + 1,  Range::all() ) = *(bestNet->getBias()) ; 
      (*bcastMatrix)( numNeurons + 2,  Range::all() ) = *(bestNet->getInitNeuron()) ; 
      
      // Broadcast the combined matrix
      // it comes ONLY from the dest.node, so only its root is dest.node
      // should it be behind the if statement?
      MPI_Bcast(bcastMatrix->data(), bcastMatrix->size(), MPI_DOUBLE, dest.node, MPI_COMM_WORLD);
      
      // collect the pieces
      if (myid != dest.node) {
        // Break apart the components
	//        blitzNet->setWeights( *(*bcastMatrix)( Range(0, numNeurons - 1), Range(0, numNeurons - 1) )  );
	if(theseTau->size()!=numNeurons){
	  theseWeights->resize(numNeurons,numNeurons) ; 
	  theseTau->resize(numNeurons) ; 
	  theseBias->resize(numNeurons) ; 
	  theseInitNeuron->resize(numNeurons) ; 
	}
        (*theseWeights) =   (*bcastMatrix)( Range(0, numNeurons - 1), Range(0, numNeurons - 1) )   ;
        (*theseTau) =   (*bcastMatrix)( numNeurons, Range::all() )   ;
        (*theseBias) =   (*bcastMatrix)( numNeurons+1, Range::all() )   ;
        (*theseInitNeuron) =   (*bcastMatrix)( numNeurons+2, Range::all() )   ;
        bestNet->setWeights( theseWeights ) ; 
        bestNet->setBias( theseBias) ; 
        bestNet->setTau( theseTau) ; 
        bestNet->setInitNeuron( theseInitNeuron) ; 
        bestNet->setNeurons( theseInitNeuron) ; 
    }
   
      bestError = bestNet->eval()  ; 
      *currentNet = *(bestNet) ; 
 #endif


      // From these lines dump output after each temperature.
      #ifdef DOMPI
      if(myid==0){
          cout << "best at temp: " << currentTemp << "\tbestError: " <<  bestError << " deltaError: " <<  deltaError << endl  ; 
          cout << "(max time)/(total iteration): " << ( (maxDeltaT / (double) CLOCKS_PER_SEC)) / (double) globalIters << " s for " << globalIters << " iterations and " << nprocs << " processors" << endl; 
          cout << "(average time)/(average iteration): " << ( (maxDeltaT + minDeltaT)/ ((double) CLOCKS_PER_SEC * 2.0)) / ((double) globalIters/ nprocs) << " s for " << ( (double)globalIters/ nprocs) << " average iterations over " << nprocs << " processors" << endl; 
          cout << "Time (max-min)/min: " << ((maxDeltaT-minDeltaT)/minDeltaT)*100.0 << "\%" << endl ; 
      }
      #else
////////////////////////MPI stuff end/////////////////////////////////
          cout << "best at temp: " << currentTemp << "\tbestError: " <<  bestError << endl  ; 
          cout << "time per iteration: " << ( (deltaTime / (double) CLOCKS_PER_SEC)) / (double) currentIterMax << " s for " << currentIterMax << " iterations" << endl; 
      #endif

    }
    
      #ifdef DOMPI
      if(myid==0){
      #endif
          cout << "total time for annealing: " <<  ( (difftime(clock(),initTime)/ (double) CLOCKS_PER_SEC))  << " s for " << totalIterations << " iterations or an average of " << ( (difftime(clock(),initTime)/ (double) CLOCKS_PER_SEC))/ (double) totalIterations << " s per iterations" << endl; 
          cout << "out of loop time (MPI?)  totalTime - loopTime =" <<  ( (difftime(clock(),initTime)-  (timer) ) / (double) CLOCKS_PER_SEC)   << endl ; 
      #ifdef DOMPI
      }
      #endif 
    // Find the average average time length of ^??? each perturbation
//    timer = timer / (double) totalIterations ; 
    cout << "----- Final Notes from BlitzNetAnnealer\t-----------------------------" << endl;
    cout << "average time for a perturbation: " << ( (timer / (double) CLOCKS_PER_SEC ) /(double) totalIterations) << "s" << endl << endl; 
    
    return bestNet ; 
}

void BlitzNetAnnealer::setAnnealingTarget(AnnealingTarget* annealingTarget) 
{
    blitzNet = (BlitzNet*) annealingTarget; 
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

