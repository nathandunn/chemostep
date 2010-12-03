#include <iostream>
using std::cout ; 
using std::endl ; 

#include "TennisCourtMap.hpp"
#include "WormShuffler.hpp"
#include "BaseWorm.hpp"
#include "SimpleWorm.hpp"
#include "RNG.hpp"


#include "TennisCourtSetPositionShuffler.hpp"


TennisCourtSetPositionShuffler::TennisCourtSetPositionShuffler(float newWidth,float newHeight,float newTargetX, float newSpaceFromTarget) : WormShuffler()  
,mWidth(newWidth) 
,mHeight(newHeight) 
,mTargetX(newTargetX) 
,mStartX(newSpaceFromTarget) 
{
}

TennisCourtSetPositionShuffler::TennisCourtSetPositionShuffler(TennisCourtMap* newMap,float newSpaceFromTarget) :
mWidth(newMap->getWidth()) 
,mHeight(newMap->getHeight()) 
,mTargetX(newMap->getTargetX() ) 
,mStartX(newSpaceFromTarget) 
{
}


void TennisCourtSetPositionShuffler::shuffleWorm(BaseWorm* aWorm){

    float yPos = mHeight / 2.0 ; 
    float xPos  ; 
    float theta ; 

    
		xPos = mStartX ; 
		theta = M_PI ; 

    aWorm->setPosition( xPos,yPos, theta ) ;
    aWorm->setDied( false ) ; 
}

void TennisCourtSetPositionShuffler::toXML(ostream *s){
    addSpacer(s,1) ; 
    *s << "<wormshuffler type=\"tenniscourtsetpositionshuffler\">" << endl ; 
    addSpacer(s) ; 
    *s << "<startx value=\""<< mStartX << "\"/>" << endl ; 
    addSpacer(s) ; 
    *s << "<targetx value=\""<< mTargetX << "\"/>" << endl ; 
    addSpacer(s) ; 
    *s << "<width value=\""<< mWidth << "\"/>" << endl ; 
    addSpacer(s,-1) ; 
    *s << "<height value=\""<< mHeight << "\"/>" << endl ; 
    addSpacer(s) ; 
    *s << "</wormshuffler>"<< endl ; 
}




/* Function int main(int argc, char **argv) {{{ */
//int main(int argc, char **argv)
//{


//    return 0;
//} /* }}} */



// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


