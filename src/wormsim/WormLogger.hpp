/*
 * $Id$
 */
#ifndef WORMLOGGER_HPP_
#  define WORMLOGGER_HPP_

#include "WormTrack.hpp"

#include <vector>
using std::vector ; 
using std::pair ; 

class SimpleWorm ; 
class WormTrack ; 

/// This class logs worm tracks for OneWormMapSpace.  A possible better system would be to have WormTrack be a "multi-worm" Track, so its one large blitz array which may be resized and preserved if more worms are ever run.   The logger must support efficient access to a series of different number of worms, so will need to handle memory in such a way, to clear if it gets real large, or to be able to use less worms when differences are readily apparent.  
class WormLogger {

public:
    WormLogger() ; 
    WormLogger(int numWormSteps,int defaultNumWorms) ; 
    void log(SimpleWorm* worm,int stepCount,int wormCount ) ; 
    virtual vector<WormTrack*>* getWormTracks() ; 
    virtual int getNumPoints(int ignoreSteps=0) ; 
    virtual void resetCounter() ; 
    virtual pair<double,double> getNextPoint() ; 


protected:
    virtual void initLogger() ; 
    vector<WormTrack*>* mWormPositions ; // each track for each worm
    int mNumWormSteps ; 
    int mDefaultNumWorms ; 
    int mStepCounter ;  /// This is the step of the worm.
    int mWormCounter ;  /// The is the worm that is being counted.
    double* mNextPoint ;  /// The is the worm that is being counted.

} ;

#endif /* ifndef WORMLOGGER_H */
// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


