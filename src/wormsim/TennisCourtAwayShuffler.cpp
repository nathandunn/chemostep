#include <iostream>
using std::cout ; 
using std::endl ; 

#include "TennisCourtMap.hpp"
#include "WormShuffler.hpp"
#include "BaseWorm.hpp"
#include "SimpleWorm.hpp"
#include "RNG.hpp"


#include "TennisCourtAwayShuffler.hpp"


TennisCourtAwayShuffler::TennisCourtAwayShuffler(float newWidth,float newHeight,float newTargetX, float newSpaceFromTarget) : WormShuffler()  
,mWidth(newWidth) 
,mHeight(newHeight) 
,mTargetX(newTargetX) 
,mSpaceFromTarget(newSpaceFromTarget) 
,mLeftSide(RNG::coinToss()) 
{
}

TennisCourtAwayShuffler::TennisCourtAwayShuffler(TennisCourtMap* newMap,float newSpaceFromTarget) :
mWidth(newMap->getWidth()) 
,mHeight(newMap->getHeight()) 
,mTargetX(newMap->getTargetX() ) 
,mSpaceFromTarget(newSpaceFromTarget) 
,mLeftSide(RNG::coinToss()) 
{
}


void TennisCourtAwayShuffler::shuffleWorm(BaseWorm* aWorm){

    float yPos = mHeight / 2.0 ; 
    float xPos  ; 
    float theta ; 

//    cout << "IN mLeftSide: " << mLeftSide << " yPos: " << yPos << " height:" << mHeight << endl ; 
    
    // on left-side
    if(mLeftSide==true){
        xPos = mTargetX - mSpaceFromTarget ; 
        theta = M_PI ; 
        mLeftSide = false ; 
    }
    // on right-side
    else{
        xPos = mTargetX + mSpaceFromTarget ; 
        theta = 0.0 ; 
        mLeftSide = true ; 
    }

    aWorm->setPosition( xPos,yPos, theta ) ;
    aWorm->setDied( false ) ; 
}

void TennisCourtAwayShuffler::toXML(ostream *s){
    addSpacer(s,1) ; 
    *s << "<wormshuffler type=\"tenniscourtawayshuffler\">" << endl ; 
    addSpacer(s) ; 
    *s << "<spacefromtarget value=\""<< mSpaceFromTarget << "\"/>" << endl ; 
    addSpacer(s) ; 
    *s << "<targetx value=\""<< mTargetX << "\"/>" << endl ; 
    addSpacer(s) ; 
    *s << "<width value=\""<< mWidth << "\"/>" << endl ; 
    addSpacer(s,-1) ; 
    *s << "<height value=\""<< mHeight << "\"/>" << endl ; 
    addSpacer(s) ; 
    *s << "</wormshuffler>"<< endl ; 
}

void TennisCourtAwayShuffler::reset()  
{
    mLeftSide = RNG::coinToss() ; 
}



/* Function int main(int argc, char **argv) {{{ */
//int main(int argc, char **argv)
//{


//    return 0;
//} /* }}} */



// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


