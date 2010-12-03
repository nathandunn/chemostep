

#ifndef ONEWORMMAPSPACE_HPP_
#  define ONEWORMMAPSPACE_HPP_

#include <iostream>
using std::ostream ; 

#include <XmlRenderable.hpp>

class SimpleWorm ; 
class Map; 
class WormLogger ; 
class WormShuffler ; 

class OneWormMapSpace : public XmlRenderable{

public:
    OneWormMapSpace() ; 

    // logger access
    virtual WormLogger* getLogger() ; 
    virtual void clearStats() ; 

    // move worms
    virtual bool moveWorms(int newAdditionalWorms=0) ; 

    // worm 
    virtual SimpleWorm* getWorm() ; 
    virtual void setWorm(SimpleWorm* newWorm) ; 
    virtual WormShuffler* getWormShuffler() ; 
    virtual void setWormShuffler(WormShuffler* newWormShuffler) ; 

    // mapdata
    virtual Map* getMap() ; 
    virtual void setMap(Map* newMap) ; 
    virtual void toXML(ostream *s) ; 

    virtual int getMaxWormCount() {
        return(mMaxWormCount);
    }
    virtual void setMaxWormCount(int _mMaxWormCount) {
        mMaxWormCount = _mMaxWormCount;
        return;
    }
//    virtual int getTempMaxWormCount(){
//        return mTempMaxWormCount ; 
//    }
	virtual int getNumPoints(){
        return mTempMaxWormCount * mWormStepCount ; 
    }
    virtual int getWormStepCount() {
        return(mWormStepCount);
    }
    virtual void setWormStepCount(int _mWormStepCount) {
        mWormStepCount = _mWormStepCount;
        return;
    }



protected:
    SimpleWorm* mWorm ; 
    Map* mMap; 
    WormLogger *mLogger ; 
    WormShuffler *mWormShuffler ; 
    int mWormRunCount ; 
    int mWormStepCount ; 
    int mMaxWormCount ; 
    int mTempMaxWormCount ;  // this is set according to the # of processors

    #ifdef DOMPI
    int mNumProcs ; 
    int mProcNum ; 
    #endif


} ;

#endif /* ifndef ONEWORMMAPSPACE_H */
// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


