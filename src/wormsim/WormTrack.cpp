
#include <iostream>
using std::cout ; 
using std::endl ; 

#include "WormTrack.hpp"

WormTrack::WormTrack(int newNumTracks) : Matrix(newNumTracks,2) 
{
}

bool WormTrack::recordPosition(double xPos,double yPos,int stepCount) 
{
    if(stepCount> rows()){
        return false ; 
    }
    else{
        (*this)(stepCount,0) = xPos ; 
        (*this)(stepCount,1) = yPos ; 
        return true ; 
    }
}

bool WormTrack::recordPosition(Position* newPosition,int stepCount) 
{
    return recordPosition( newPosition->getX(),newPosition->getY(),stepCount) ; 
}

pair<double,double> WormTrack::getStep(int stepCount) 
{
    return pair<double,double>( (*this)(stepCount,0) ,  (*this)(stepCount,1)  ) ; 
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


