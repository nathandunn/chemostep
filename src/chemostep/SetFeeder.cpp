
#include <vector>
using std::vector ; 

#include <iostream>
using std::cout ; 
using std::endl ; 

#include "FileFeeder.hpp"
#include "Feeder.hpp"

#include "SetFeeder.hpp"

SetFeeder::SetFeeder():Feeder(),feederList(new vector<Feeder*>()),feederNum(0)
{
}

bool SetFeeder::clearSets() 
{
    feederList->clear() ; 
    return feederList->empty() ; 
}

void SetFeeder::addFeeder(Feeder* newFeeder) 
{
    // first is first
    feederList->push_back(newFeeder) ; 
//    feederList->insert(feederList->begin(),newFeeder) ; 
}

double SetFeeder::getTotalTime() 
{

    double totalTime = 0 ; 
    int counter = 0 ; 
    while(counter < feederList->size()){
        totalTime += (*feederList)[counter]->getTotalTime() ; 
        ++counter ; 
    }

    return totalTime ; 
}

bool SetFeeder::isTimePointValid() 
{
    if(feederNum < feederList->size() ) {
        return (*feederList)[feederNum]->isTimePointValid() ; 
    }
    return false ; 
}



double SetFeeder::getNextTimeStep(double newTimeStep, int pointAt) 
{
    double returnValue = (*feederList)[feederNum]->getNextTimeStep(newTimeStep) ; 
    previousSigStepValue = (*feederList)[feederNum]->getNextSigTimeStep(newTimeStep) ; 
    timeCounter = timeCounter + newTimeStep ; 
    pointCounter = ((int) (timeCounter/deltaT)) ; 
    sigCounter = ((int) (timeCounter/deltaT)) ; 
    if(! (*feederList)[feederNum]->hasMorePoints()){
        (*feederList)[feederNum]->reset() ; 
        ++feederNum ; 
    }
//    cout << "returning next value: " << returnValue << endl ; 
    return returnValue ; 
}

double SetFeeder::getOffset() 
{
    return offset ; 
}

double SetFeeder::getScale() 
{
    return scale ; 
}

void SetFeeder::setScale(double newScale/*1.0*/) 
{
    scale = newScale ; 
    for(int i = 0 ; i < feederList->size() ; i++){
        (*feederList)[i]->setScale(newScale) ; 
    }

}/// Sets the scale of the data from the feeder.  1.0 is the default, which is unchanged.


void SetFeeder::setOffset(double newOffset/*0.0*/) 
{
    offset = newOffset ; 
    for(int i = 0 ; i < feederList->size() ; i++){
        (*feederList)[i]->setOffset(newOffset) ; 
    }

}/// Sets the offset of the data from the feeder.  0.0 is the default, which is unchanged.


double SetFeeder::setDeltaT(double newDeltaT ) 
{
    deltaT = newDeltaT ; 
    for(int i = 0 ; i < feederList->size() ; i++){
        (*feederList)[i]->setDeltaT(deltaT) ; 
    }
}

double SetFeeder::getDeltaT() 
{
    return deltaT ; 
}


//vector<double>* SetFeeder::getNextTimeSteps(double newTimeStep) 
//{
//    vector<double>* returnVector = (*feederList)[feederNum]->getNextTimeSteps(newTimeStep) ; 
//
//    timeCounter = timeCounter + newTimeStep ; 
//    pointCounter = ((int) (timeCounter/deltaT)) ; 
//    if(! (*feederList)[feederNum]->hasMorePoints()){
//        (*feederList)[feederNum]->reset() ; 
//        ++feederNum ; 
//        (*feederList)[feederNum]->reset() ; 
//    }
//    return returnVector ; 
//}

double SetFeeder::getNextPoint(int pointAt) 
{
    double returnValue = (*feederList)[feederNum]->getNextPoint(pointAt) ; 
    previousSigStepValue = (*feederList)[feederNum]->getNextSigPoint() ; 
    ++pointCounter   ; 
    ++sigCounter; 
    timeCounter = timeCounter + deltaT ; 
//    pointCounter = ((int) (timeCounter/deltaT)) ; 
    if(! (*feederList)[feederNum]->hasMorePoints()){
        (*feederList)[feederNum]->reset() ; 
        ++feederNum ; 
    }
    return returnValue ; 
}

//vector<double>* SetFeeder::getNextPoints() 
//{
//    vector<double>* returnVector =  (*feederList)[feederNum]->getNextPoints() ; 
//    timeCounter = timeCounter + deltaT ; 
//    pointCounter = ((int) (timeCounter/deltaT)) ; 
//    if(! (*feederList)[feederNum]->hasMorePoints()){
//        (*feederList)[feederNum]->reset() ; 
//        ++feederNum ; 
//        (*feederList)[feederNum]->reset() ; 
//    }
//    return returnVector ; 
//}

int SetFeeder::getNumSets() {
    return feederList->size() ; 
}


int SetFeeder::getNumPoints() 
{
    int totalPoints = 0 ; 
    int counter = 0 ; 
    while(counter < feederList->size()){
        totalPoints += (*feederList)[counter]->getNumPoints() ; 
        ++counter ; 
    }

    return totalPoints ; 
}


bool SetFeeder::reset() 
{
    for(int i = 0 ; i < feederList->size() ; i++){
        (*feederList)[i]->reset() ;
    }
    feederNum = 0 ;  // aim to the first one
    timeCounter = 0 ;  
    pointCounter =  0 ; 
    sigCounter =  0 ; 

    return true ; 
}

bool SetFeeder::hasMorePoints() 
{
    if(feederNum < feederList->size() ) {
        if(( (*feederList)[feederNum])->hasMorePoints()){
            return true ; 
        }
    }
    return false ; 
}

bool SetFeeder::isNewSet() 
{
    if(feederNum < feederList->size() ){
        if( (*feederList)[feederNum]->isNewSet()){
            return true ; 
        }
    }
    return false ; 
}

double SetFeeder::getNextSigPoint() 
{
    // hopefully getNumPoint is called
    return previousSigStepValue ; 
}

double SetFeeder::getNextSigTimeStep(double newTimeStep) 
{
//    double returnValue = (*feederList)[feederNum]->getNextSigTimeStep(newTimeStep) ; 
    return previousSigStepValue ; 
}


bool SetFeeder::setSigPoint(double newSignificance,int pointAt) 
{
    int thisFeederNum  = 0 ; 
    int thisTotalTime = 0 ; 
    try{
        while( pointAt > ((*feederList)[thisFeederNum]->getNumPoints() + thisTotalTime) ){
            thisTotalTime += (*feederList)[thisFeederNum]->getNumPoints() ; 
            ++thisFeederNum ; 
        }
    }
    catch(...){
        throw "point is out of bounds in SetFeeder for setSigPoint" ; 
    }


    (*feederList)[thisFeederNum]->setSigPoint(newSignificance, (pointAt-thisTotalTime)) ; 
    return true ; 
}

void SetFeeder::toXML(ostream *s)  {

    int feederNum = 0 ; 
    addSpacer(s,1) ; 
    *s << "<setfeeder>" << endl ;
    addSpacer(s) ; 

    *s << "<feederlist-size value=\"" << feederList->size() << "\"/>" << endl;
    while(feederNum < feederList->size()){
	
	if ((*feederList)[feederNum] != NULL) {
      addSpacer(s,1) ; 
	  *s << "<feederlist>" << endl;
      addSpacer(s) ; 
	  *s << "<feedernum value=\"" << feederNum << "\"/>" << endl;
      addSpacer(s) ; 
	  *s << "<numpoints value=\"" << (*feederList)[feederNum]->getNumPoints() << "\"/>" << endl;
	  
	  if((*feederList)[feederNum]->getName() == "FILE_FEEDER") {
        addSpacer(s,-1) ; 
	    *s << "<filename value=\"" << ((FileFeeder *) (*feederList)[feederNum])->getFileName() << "\"/>" << endl;
        addSpacer(s,-1) ; 
	    *s << "</feederlist>" << endl;	  
	  }
	}	  
        ++feederNum ; 
    }
 
    addSpacer(s) ; 
    *s << "</setfeeder>" << endl ;
}



// calculate for each point
bool SetFeeder::calculateSigPoints() 
{
    int counter = 0 ; 
    while((counter < feederList->size())  && ((*feederList)[counter]->calculateSigPoints())){
        ++counter ; 
    }
    if(counter >=feederList->size()){
        return true ; 
    }else{
        return false ; 
    }
}

const string SetFeeder::FEEDER_NAME = "SET_FEEDER" ; 


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

