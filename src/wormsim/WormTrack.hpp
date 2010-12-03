#ifndef WORMTRACK_HPP_
#  define WORMTRACK_HPP_

#include "Position.hpp" 

#include "blitzdefs.hpp" 

using std::pair ; 

///  This class extends a blitz Matrix.  
class WormTrack : public Matrix {

public:
    WormTrack(int newNumTracks) ; 
    virtual bool recordPosition(double xPos,double yPos,int stepCount) ; 
    virtual bool recordPosition(Position* newPosition,int stepCount) ; 
    virtual pair<double,double> getStep(int stepCount) ; 



} ;

#endif /* ifndef WORMTRACK_H */
// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


