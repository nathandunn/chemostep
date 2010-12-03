
#include <iostream>
using std::cout ; 
using std::endl ; 
using std::ostream ; 

#include "Map.hpp"

#include "MovementModelTemplate.hpp"

template <class T>
RicochetMovementTemplate<T>::RicochetMovementTemplate( float newVelocity) : MovementModelTemplate<T>(newVelocity){ }


template <class T>
void RicochetMovementTemplate<T>::move(T* aWorm)   
{
//   cout << "ReflectMovementTemplate--PRE-move theta: " << aWorm->getTheta() << endl ;
//   cout << "aWorm->hitEdge(): " << aWorm->hitEdge() << endl; 
	 if(aWorm->hitEdge()==Map::EAST){
//     cout << "EAST" << endl ; 
			 aWorm->setTheta(M_PI-aWorm->getTheta());
	 }
	 else
	 if(aWorm->hitEdge()==Map::WEST){
//     cout << "WEST" << endl ; 
			 aWorm->setTheta(M_PI-aWorm->getTheta());
	 }
	 else
	 if(aWorm->hitEdge()==Map::NORTH){
//     cout << "NORTH" << endl ; 
		 aWorm->setTheta(2.0*M_PI-aWorm->getTheta());
	 }
	 else
	 if(aWorm->hitEdge()==Map::SOUTH){
//     cout << "SOUTH" << endl ; 
		 aWorm->setTheta(2.0*M_PI-aWorm->getTheta());
	 }
	 else{
		 cout << "HIT OTHER EDGE?" << endl ; 
	 }
	 
	 if(aWorm->getTheta()> 2.0*M_PI){
		aWorm->setTheta(aWorm->getTheta() - 2.0*M_PI) ; 
	 }
    

    mDeltaX = mVelocity * cos(aWorm->getTheta()) ;   // 3. set mDeltaX based on velocity and theta
    mDeltaY = mVelocity * sin(aWorm->getTheta()) ;   // 3. set mDeltaY based on velocity and theta
    aWorm ->setPosition((mDeltaX+aWorm->getX()), (mDeltaY+aWorm->getY())) ; // steps 4 and 6

//     cout << "POST-move X: " << aWorm->getX()  << " Y: " << aWorm->getY() << " theta: " << aWorm->getTheta() << endl ;

}

template <class T>
void RicochetMovementTemplate<T>::toXML(ostream *s)  
{
    addSpacer(s,1) ; 
    *s << "<movementmodel type=\"ricochetmovementtemplate\">" << endl ; 
    addSpacer(s,-1) ; 
    *s << "<velocity value=\""<< mVelocity<< "\"/>" << endl  ; 
    addSpacer(s) ; 
    *s << "</movementmodel>" << endl ; 
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



