
#include <iostream>
using std::cout ; 
using std::endl ; 
using std::ostream ; 

#include "TempSchedule.hpp"

TempSchedule::TempSchedule(int newNumPoints, double newHighTemp,double newLowTemp) :
lazyVector(NULL)
{

    numPoints = newNumPoints ; 
    highTemp = newHighTemp ; 
    lowTemp = newLowTemp ; 
}

double TempSchedule::getNextTemp(double deltaError,double doubleVar)
{
    if(lazyVector==NULL){
        lazyVector = new vector<double>(1) ; 
    }
    (*lazyVector)[0] = doubleVar ; 
    return getNextTemp(deltaError,lazyVector) ; 
}


void TempSchedule::setHighTemp(double newHighTemp) 
{
    highTemp = newHighTemp ; 
}

void TempSchedule::setLowTemp(double newLowTemp) 
{
    lowTemp = newLowTemp ; 
}


bool TempSchedule::hasMoreTemps() 
{
    if (counter< (tempSchedule)->size()) { 

        return true ; 
    }
    else{
        hasInitTemps = false  ; 
        return false ; 
    }
}

// {{{
/*!
 * \brief	Get numPoints.
 *
 * \return	numPoints as a int.
 */ // }}}
int TempSchedule::getNumPoints()
{
	return(numPoints);
}


// {{{
/*!
 * \brief	Set numPoints.
 *
 * \param	_numPoints	The new value for numPoints (as a int).
 */ // }}}
void TempSchedule::setNumPoints(int _numPoints)
{
	numPoints = _numPoints;
	return;
}

// {{{
/*!
 * \brief	Get highTemp.
 *
 * \return	highTemp as a double.
 */ // }}}
double TempSchedule::getHighTemp()
{
	return(highTemp);
}


// {{{
/*!
 * \brief	Get lowTemp.
 *
 * \return	lowTemp as a double.
 */ // }}}
double TempSchedule::getLowTemp()
{
	return(lowTemp);
}

void TempSchedule::toXML(ostream *s) 
{
  addSpacer(s,1) ; 
  *s << "<tempschedule type=\"tempschedule\">" << endl ;
  addSpacer(s) ; 
  *s << "<numpoints value=\"" << numPoints << "\" />" << endl ;
  addSpacer(s) ; 
  *s << "<hightemp value=\"" << highTemp << "\" />" << endl ;
  addSpacer(s,-1) ; 
  *s << "<lowtemp value=\"" << lowTemp << "\" />" << endl ;
  addSpacer(s) ; 
  *s << "</tempschedule>" << endl ;
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
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: TempSchedule.cpp,v 1.1.1.1 2003/10/24 19:59:28 ndunn Exp $

