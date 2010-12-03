

#include <iostream>
using std::ostream ; 
using std::cout ; 
using std::endl ; 

#include "EvenRadWormShuffler.hpp"
#include "RNG.hpp" 
#include "Worm.hpp" 

#ifdef DOMPI
    #include "mpi.h"
    int shuffle_myid ; 
    int shuffle_nprocs ; 
#endif 


EvenRadWormShuffler::EvenRadWormShuffler(double newDiameter ,double newNumWorms,double newEdgeBuffer) 
{
    mDiameter = newDiameter ; 
    mNumWorms = newNumWorms ; 
    mEdgeBuffer = newEdgeBuffer ; 
    mActiveRadius = mDiameter/2.0 - mEdgeBuffer ; 

    mRadSpace =  mActiveRadius /  mNumWorms  ; 

    #ifdef DOMPI
    MPI_Comm_size(MPI_COMM_WORLD,&shuffle_nprocs) ; 
    MPI_Comm_rank(MPI_COMM_WORLD,&shuffle_myid) ; 
    mRadSpace = mRadSpace * shuffle_nprocs ; 
//    cout << shuffle_myid << ": mRadSpace: " << mRadSpace << endl ; 
    #endif
    
    reset() ; 
}

void EvenRadWormShuffler::reset()  
{
    mCurrentRadius = RNG::uniform() * mActiveRadius  ; 

    #ifdef DOMPI
    // share start radius
    MPI_Bcast(&mCurrentRadius,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    
    // stagger start values
    mCurrentRadius = mCurrentRadius + (shuffle_myid * mRadSpace / shuffle_nprocs ) ; 
    #endif
}

double EvenRadWormShuffler::getCurrentRadius() 
{
    return mCurrentRadius ; 
}



/// Evenly distributes worm over radius and randomly orients angle and orientation a radial map.  Need a separate theta for position on the plate and the orientation of the worm.  
void EvenRadWormShuffler::shuffleWorm(BaseWorm* aWorm) 
{
        double radius =   mCurrentRadius ; 
        double theta = RNG::uniform() * M_PI * 2.0  ; 
        double xPos =   radius * sin(theta) + (mDiameter / 2.0) ; 
        double yPos =   radius * cos(theta) + (mDiameter / 2.0) ; 
        aWorm->setPosition(xPos , yPos );
        aWorm->setTheta(RNG::uniform() * M_PI * 2.0 ) ;

//        cout << "radius: " << radius << " x,y: " << xPos << "," << yPos << " value: " << aWorm->getValue() << endl ; 
//        cout << shuffle_myid << ": radius: " << radius << endl ;  


        // incremetn counter
        mCurrentRadius += mRadSpace ; 
        if(mCurrentRadius > mActiveRadius ){
            mCurrentRadius = mCurrentRadius - mActiveRadius  ; 
        }
}

void EvenRadWormShuffler::toXML(ostream *s) 
{
    addSpacer(s,1) ; 
    *s << "<wormshuffler type=\"evenradwormshuffler\">" << endl ; 
    addSpacer(s) ; 
    *s << "<diameter value=\"" << mDiameter << "\"/>" << endl ; 
    addSpacer(s) ; 
    *s << "<numworm value=\"" << mNumWorms << "\"/>" << endl ; 
    addSpacer(s) ; 
    *s << "<radspace value=\"" << mRadSpace<< "\"/>" << endl ; 
    addSpacer(s) ; 
    *s << "<edgebuffer value=\"" << mEdgeBuffer << "\"/>" << endl ; 
    addSpacer(s,-1) ; 
    *s << "<activerad value=\"" << mActiveRadius << "\"/>" << endl ; 
    addSpacer(s) ; 
    *s << "</wormshuffler>"<< endl ; 
}


/* Modeline for ViM {{{
 * vim:set ts=4:
 * vim600:fdm=marker fdl=0 fdc=3:
 * }}} */

// -*- C++ -*-
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$


