
#ifndef SEQBLITZNETANNEALER_HPP_
#  define SEQBLITZNETANNEALER_HPP_


#include <iostream>
using std::ostream ;


#include "BlitzNetAnnealer.hpp" 

class AnnealingTarget ; 
class BlitzNet ; 
class BlitzXmlNetRenderer ; 


class SeqBlitzNetAnnealer : public BlitzNetAnnealer {

public:
    SeqBlitzNetAnnealer() ;
    virtual AnnealingTarget* anneal( ostream *toXML=NULL,string netOutputFile=NULL) ; 
    virtual void setAnnealingTarget(AnnealingTarget* annealingTarget) ; 
    virtual void setMinInitialImprovement(double _mMinInitialImprovement)  ; 
    virtual void dumpNet(string networkFile) ; 

protected:
    virtual void takeStats() ; 
    virtual void takeClock() ; 
    virtual void resetTimers() ; 
    virtual void initStats() ; 
    BlitzNet *blitzNet; 
    int totalIterations ; 
    int totalTemps; 
    virtual void printFinal(ostream* s) ; 
    virtual void printStep(ostream* s) ; 
    virtual void dumpXmlStartStep(ostream* s) ; 
    virtual void dumpXmlStopStep(ostream* s) ; 
    virtual void dumpXmlAnnealStart(ostream* s) ; 
    virtual void dumpXmlAnnealStop(ostream* s) ; 
    ofstream* mNetOutputStream ; 
#ifdef DOMPI
    BlitzNet* syncNet(BlitzNet* origNet) ; 
    Matrix* bcastMatrix ; 
    Matrix* hereWeights ; 
    Vector* hereTau; 
    Vector* hereBias; 
    Vector* hereGain ; 
    Vector* hereInitNeurons; 
    Vector* hereVmem ; 
    int seq_myid  ; 
    int seq_numprocs ; 
#endif


    // variables for output
    double bestError, bestSdev, bestCount    ;   
    double currentError, currentSdev, currentCount  ; 
    double overallBestNetError ; 
    int currentIterMax    ; 
    double currentTemp  ;
    BlitzXmlNetRenderer* renderer ;
    BlitzNet* bestNet ;   /// This network is the "current" annealing best point.
    BlitzNet* overallBestNet ; /// This network is the "best" point which the annealing process has seen.

    // clock stats
    double totalClock ; 
    double deltaClock ; 
    time_t initTime ; 
    double deltaTime  ; 
    double wallTime ; 
    double clockTime ; 
    clock_t currentClock  ; 
    clock_t nextClock     ; 
    clock_t prevClock     ; 
    time_t currentTime  ; 
    time_t nextTime     ; 

    // other stats
    int stepCount ; 
    int iterCount ; 
    double initialError ;
    double deltaError ;

    // mMinInitialImprovement, if set to < 1.0, requires the network
    //  to improve at the initial temperature by the given percentage
    //  before continuing to additional temperatures.
    double mMinInitialImprovement ;


} ;

#endif /* ifndef SEQBLITZNETANNEALER_H */
// -*- C++ -*-
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

