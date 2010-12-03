#include <iostream>
using std::cout ; 
using std::endl ; 

#include "RectMap.hpp"

RectMap::RectMap() 
:mWidth(0.0)
,mHeight(0.0)
{
}

RectMap::RectMap(float xWidth,float yHeight) 
:mWidth(xWidth)
,mHeight(yHeight)
{
}

bool RectMap::inBounds(float x, float y) const 
{
	if(x>=0 && x <= mWidth && y >=0 && y <= mHeight){
        return true ; 
    }
    else{
        return false ; 
    }
    
}

int RectMap::hitEdge(float x,float y) const 
{
   if( x > mWidth){
       return Map::EAST ; 
   }
   else
//   if( x < mWidth){
   if( x < 0 ){
       return Map::WEST ; 
   }
   else
   if( y > mHeight ){
       return Map::NORTH ; 
   }
   else
//   if( y < mHeight ){
   if( y < 0 ){
       return Map::SOUTH ; 
   }
   else{
       return Map::NONE ; 
   }
}




float RectMap::getWidth() const 
{
    return mWidth ; 
}

float RectMap::getHeight() const 
{
    return mHeight ; 
}




/* Function int main(int argc, char **argv) {{{ */
//int main(int argc, char **argv)
//{


//    return 0;
//} /* }}} */



// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


