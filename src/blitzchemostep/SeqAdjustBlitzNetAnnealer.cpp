/*
 * $Id$
 */

#include <iostream>
using std::cout ; 
using std::endl ; 
using std::ostream ; 

#ifdef DOMPI
#include "mpi.h"
int adj_myid  ; 
int adj_numprocs ; 
#endif 

#include "BlitzNet.hpp" 
#include "AcceptModel.hpp" 
#include "TempSchedule.hpp" 
#include "BlitzXmlNetRenderer.hpp" 
#include "SeqAdjustBlitzNetAnnealer.hpp"

SeqAdjustBlitzNetAnnealer::SeqAdjustBlitzNetAnnealer() : SeqBlitzNetAnnealer() 
{
#ifdef DOMPI
MPI_Comm_rank(MPI_COMM_WORLD,&adj_myid) ; 
MPI_Comm_size(MPI_COMM_WORLD,&adj_numprocs) ; 
#endif 
}


/**  Inits over bestNet.
 *
 */
AnnealingTarget* SeqAdjustBlitzNetAnnealer::initAnneal() 
{
    if(blitzNet==NULL) throw "blitzNet is NULL" ; 
    // blitzNet comes from file or starting point
    bestNet = new BlitzNet(blitzNet) ; 
    BlitzNet *currentNet = new BlitzNet(blitzNet)   ; 

    double acceptVars[mAcceptModel->getNumVariables()] ; 

    (*currentNet) = *bestNet ; 
    currentIterMax = iterPerTemp ; 
#ifdef DOMPI
if(adj_myid==0)
#endif
    cout << "initAnneal minImprovevement: " << mMinInitialImprovement*100 << "% * " << bestError << " = " << mMinInitialImprovement*bestError << endl ; 


    // iterate until we improve enough
    for(iterCount = 0 ; iterCount < currentIterMax ; iterCount++){
        *blitzNet = *(currentNet) ;
        blitzNet->perturb(currentTemp) ; 
#ifdef DOMPI
        blitzNet = syncNet(blitzNet) ; 
#endif
        currentError = blitzNet->eval() ;
        currentCount = blitzNet->getCount() ;
        currentSdev = blitzNet->getSdev() ;

         acceptVars[0] = currentError ;
    //     acceptVars[1] = bestError ;
         acceptVars[1] = mMinInitialImprovement * bestError ; // the minimal initial improvement
         acceptVars[2] = currentSdev ;
         acceptVars[3] = bestSdev ;
         acceptVars[4] = currentCount ;
         acceptVars[5] = bestCount ;

         if(   mAcceptModel->accept( acceptVars )  ){
              *bestNet = *blitzNet ; 
              bestNet->eval() ; // we want a valid network, here when node 0 renders it to output
              *currentNet = *bestNet ; 
              bestError = currentError ; 
              bestCount = currentCount ; 
              bestSdev = currentSdev  ;
              currentIterMax = iterCount ;  // this should stop the functioning
          }
         // haven't run enough points, yet
         else{

             // ADJUST THE NETWORK
             blitzNet = (BlitzNet*) shiftNet(blitzNet) ;            

             acceptVars[0] = currentError ;
        //     acceptVars[1] = bestError ;
             acceptVars[1] = mMinInitialImprovement * bestError ; // the minimal initial improvement
             acceptVars[2] = currentSdev ;
             acceptVars[3] = bestSdev ;
             if(   mAcceptModel->accept( acceptVars )  ){
                  *bestNet = *blitzNet ; 
                  bestNet->eval() ; // we want a valid network, here when node 0 renders it to output
                  *currentNet = *bestNet ; 
                  bestError = currentError ; 
                  bestCount = currentCount ; 
                  bestSdev = currentSdev  ;
                  currentIterMax = iterCount ;  // this should stop the functioning
              }
             ++currentIterMax ; 
         }

#ifdef DOMPI
         if(adj_myid==0){
#endif
             if(iterCount%1000==0){
                 cout <<  iterCount << " " ;
                 cout.flush() ;
             }
             else
             if(iterCount%100==0){
                 cout << "*" ;
                 cout.flush() ;
             }
#ifdef DOMPI
         }
#endif

    }

    return currentNet ;
}

/**  This method takes the steady-state input into the output weight, and shifts it so that the they should cancel out each other.
 *
 */
AnnealingTarget* SeqAdjustBlitzNetAnnealer::shiftNet(BlitzNet* net) 
{
    double preValue = net->eval() ; 
    double avgHValue = (blitzNet->getEvaluator())->getHAvg()  ; 
    double oldSelfWt  ; 
    double newValue  ; 

    Matrix* netWeights = net->getWeights() ; 
    Vector* netNeurons = net->getNeurons() ; 
    Vector* netBias = net->getBias() ; 
    oldSelfWt = (*netWeights) (   (netWeights->size()-1),(netWeights->size()-1)  ) ;
    // solve for 0.5 = sigma(h + w * A + b)  , where A = 0.5, and w is the selff-connection
    (*netWeights) (   (netWeights->size()-1),(netWeights->size()-1)  ) =  - 2.0  *  ( avgHValue +  (*netBias)(netWeights->size()-1)  )       ;  // assume that the weight will be 0.5, or close enough
//    cout << "new weight: " <<  (*netWeights) (   (netWeights->size()-1),(netWeights->size()-1)  ) << endl ; 
    net->setWeights(netWeights) ; 
    net->setValid(false) ; 
    newValue = net->eval() ; 

//    cout << "newValue: " << newValue << " versus old " << preValue << endl ; 

    // if not better than revert back
    if(newValue  >= preValue ){
        (*netWeights) (   (netWeights->size()-1),(netWeights->size()-1)  ) = oldSelfWt ;
        net->setWeights(netWeights) ; 
        net->setValid(false) ; 
    }

    return net ; 
}




AnnealingTarget* SeqAdjustBlitzNetAnnealer::anneal( ostream *toXML) 
{
    cout.precision(10) ;  
    if(blitzNet==NULL) throw "blitzNet is NULL" ; 
    bestNet =  new BlitzNet(blitzNet) ; 
    BlitzNet* currentNet =   new BlitzNet(blitzNet) ; 

    initStats()  ; 

    // note that currentClock and nextClock are in seconds
    double acceptVars[mAcceptModel->getNumVariables()] ; 

    bestError = bestNet->eval() ;
    bestSdev = bestNet->getSdev() ;
    bestCount = bestNet->getCount() ;

    // keep track of the initial error for future comparison
    initialError = bestError;



#ifdef DOMPI
if(adj_myid==0){
#endif
    cout << "Initial Error [" << initialError << "]" << endl ;
    dumpXmlAnnealStart(toXML) ; 
#ifdef DOMPI
}
#endif

    tempSchedule->initTemps() ; 
    currentTemp  =  tempSchedule->getNextTemp(0) ; 

    // init error
    resetTimers() ; 
#ifdef DOMPI
    if(adj_myid==0)
#endif
    dumpXmlStartStep(toXML) ; 
    bestNet = (BlitzNet*) initAnneal() ; 
    takeStats() ; 
#ifdef DOMPI
    if(adj_myid==0){
#endif
        printStep(&cout) ;
        dumpXmlStopStep(toXML) ; 
#ifdef DOMPI
    }
#endif

    
    // eval points
    bestError = bestNet->eval() ;
    bestSdev = bestNet->getSdev() ;
    bestCount = bestNet->getCount() ;

    // keep track of the initial error for future comparison
    initialError = bestError;

#ifdef DOMPI
bestNet->eval() ; 
if(adj_myid==0){
#endif
    cout << "After: InitAnneal[" << initialError << "]" << endl ;
    dumpXmlAnnealStart(toXML) ; 
#ifdef DOMPI
}
#endif

    // loop through all the values in the tempSchedule
    while(tempSchedule->hasMoreTemps()){

      resetTimers() ; 

      currentTemp  =  tempSchedule->getNextTemp(deltaError) ; 
     
#ifdef DOMPI
if(adj_myid==0)
#endif
      dumpXmlStartStep(toXML) ; 

      deltaError = bestError;
      currentIterMax = iterPerTemp ; 

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
//        cout << adj_myid << ": currentError " << currentError << " iterCount: " << iterCount << endl ; 
//        cout << adj_myid << ": currentSdev " << currentSdev << " iterCount: " << iterCount << endl ; 
//        cout << adj_myid << ": currentCount " << currentCount << " iterCount: " << iterCount << endl ; 

         acceptVars[0] = currentError ;
         acceptVars[1] = bestError ;
         acceptVars[2] = currentSdev ;
         acceptVars[3] = bestSdev ;
         acceptVars[4] = currentCount ;
         acceptVars[5] = bestCount ;
         if(   mAcceptModel->accept( acceptVars )  ){
              *bestNet = *blitzNet ; 
              bestNet->eval() ; // we want a valid network, here when node 0 renders it to output
              *currentNet = *bestNet ; 
              bestError = currentError ; 
              currentIterMax += mSetBack ;  // add some more to this iteration
          }
      }
   
      takeStats() ;


#ifdef DOMPI
if(adj_myid==0){
#endif
      dumpXmlStopStep(toXML) ; 
      printStep(&cout) ; 
#ifdef DOMPI
}
#endif
    }

#ifdef DOMPI
if(adj_myid==0){
#endif
    printFinal(&cout) ; 
    dumpXmlAnnealStop(toXML) ; 
#ifdef DOMPI
}
#endif
    
    return bestNet ; 
}


void SeqAdjustBlitzNetAnnealer::dumpXmlAnnealStart(ostream* s) 
{
    *s << "<annealingrun>" <<endl ;
    *s << "\t<annealer type=\"SeqAdjustBlitzNetAnnealer\">" << endl ; 
    *s << "\t\t<setback value=\"" << mSetBack << "\"/>" << endl ; 
    tempSchedule->setNumTabs(2) ; 
    tempSchedule->toXML(s) ; 
    mAcceptModel->toXML(s) ; 
    (bestNet->getEvaluator())->toXML(s) ; 
    (bestNet->getPerturber())->toXML(s) ; 
//    renderer->render(bestNet) ; 
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

