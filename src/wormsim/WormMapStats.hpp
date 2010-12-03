/*
 * $Id$
 */
#ifndef WORMMAPSTATS_HPP_
#  define WORMMAPSTATS_HPP_

class MapSpace ; 

/**  This class calculates distribution values based on the vector of worm's in MapSpace.
 *
 */
class WormMapStats {

public:
    WormMapStats(MapSpace* newSpace) ; 
    // Calculates stats.
    virtual void calcStats() ; 
    virtual int getCount() ; 

    // Stats for all worms.
    virtual double getMeanValue() ; 
    virtual double getSdevValue() ; 
    virtual double getMeanDistanceFromCenter() ; 
    virtual double getMeanSqrtDistanceFromCenter() ; 
    virtual double getMeanDistanceFromRadius() ; 
    virtual double getSdevDistanceFromRadius() ; 
    virtual double getMeanSqrtDistanceFromRadius() ; 
    virtual double getSdevSqrtDistanceFromRadius() ; 
    virtual double getSdevDistanceFromCenter() ; 
    virtual double getSdevSqrtDistanceFromCenter() ; 

    // Stats for live worms.
    virtual double getMeanLiveValue() ; 
    virtual double getSdevLiveValue() ; 
    virtual double getMeanLiveDistanceFromCenter() ;
    virtual double getMeanLiveDistanceFromRadius() ;

protected:
    MapSpace* mMapSpace ; 

    // values to calculate
    double mMeanValue  ; 
    double mMeanDistanceFromCenter ;
    double mMeanSqrtDistanceFromCenter ;
    double mMeanDistanceFromRadius ;
    double mMeanSqrtDistanceFromRadius ;
    double mSdevValue ;
    double mSdevDistanceFromCenter  ;
    double mSdevSqrtDistanceFromCenter  ;
    double mSdevDistanceFromRadius  ;
    double mSdevSqrtDistanceFromRadius ;
    int mCount ; 

    // "Live" values exclude dead worms
    double mMeanLiveValue  ; 
    double mSdevLiveValue  ; 
    double mMeanLiveDistanceFromCenter ; 
    double mMeanLiveDistanceFromRadius ; 


} ;

#endif /* ifndef WORMMAPSTATS_H */
// -*- C++ -*-
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

