
#include <iostream>
using std::cout ; 
using std::endl ; 

#include <vector>
using std::vector ; 


#include "Feeder.hpp"

Feeder::Feeder() : 
pointCounter(0)
,sigCounter(0)
,timeCounter(0.0) 
,deltaT(1.0) 
,fileData(new vector<vector<double>*>()) 
,sigData(NULL) 
,scale(1.0) 
,offset(0.0) 
{
}

bool Feeder::reset() 
{
    pointCounter = 0 ; 
    timeCounter = 0 ; 
    sigCounter = 0 ; 
    return true ; 
}

double Feeder::setDeltaT(double newDeltaT){ 
	deltaT = newDeltaT ; 
    return deltaT ; 
}

double Feeder::getDeltaT(){ 
    return deltaT  ; 
}


void Feeder::setScale(double newScale) 
{
    scale = newScale ; 
}


double Feeder::getScale() 
{
    return scale ; 
}


double Feeder::getNextSigTimeStep(double newTimeStep,int inputNum) 
{
    if(  (sigData==NULL) || (sigData->size()<sigCounter))  {
        return 1.0 ; 
    }
    double returnValue = (*sigData)[sigCounter] ; 
    sigCounter =  ((int) (timeCounter/deltaT)) ; 
    return ((returnValue*scale) + offset)  ; 
}


bool Feeder::setSigPoint(double newSignificance,int pointAt) 
{
    if(fileData==NULL){
        return false ; 
    }
    if(sigData==NULL){
        if(!calculateSigPoints()) return false ; 
    }
    if(pointAt>=sigData->size()){
        throw "pointAt is greater than size" ; 
    }
    (*sigData)[pointAt] = newSignificance ; 
    return true ; 
}


bool Feeder::calculateSigPoints() 
{
    if(fileData==NULL){
        return false ; 
    }
    if(sigData==NULL){
        sigData = new vector<double>(fileData->size()) ; 
    }
    for(int i = 0 ; i < sigData->size() ; i++){
        (*sigData)[i] = 1.0 ; 
    }
    return true ; 
}


double Feeder::getCurrentTime() 
{
    return timeCounter ; 
}

int Feeder::getCurrentPoint() 
{
    return pointCounter ; 
}

bool Feeder::isNewSet() 
{
    return (timeCounter==0.0) ; 
}

Feeder* Feeder::getFeeder(int inputNum) 
{
    return this ; 
}

void Feeder::setFeeder(Feeder* newFeeder, int inputNum) 
{
   deltaT = newFeeder->getDeltaT() ; 
   fileData = newFeeder->fileData ; 
   sigData= newFeeder->sigData ; 
   scale = newFeeder->getScale() ; 
   offset = newFeeder->getOffset() ; 

   reset() ; 
}



double Feeder::getNextSigPoint() 
{
    if(( sigData==NULL) || ( sigCounter >= sigData->size())  ) {
        return 1.0 ;
    }
    double returnValue = (*sigData)[sigCounter] ; 
//   ++sigCounter ; 
   // don't recalculate time
   return ((returnValue*scale) + offset)  ; 
}


double Feeder::getTotalTime() 
{
    return ((double) getNumPoints())*deltaT  ;
}

void Feeder::setOffset(double newOffset/*0.0*/) 
{
    offset = newOffset ; 
}/// Sets the offset of the data from the feeder.  0.0 is the default, which is unchanged.

double Feeder::getOffset() 
{
    return offset ; 
}

vector<double>* Feeder::getArray(int inputNum) 
{
    vector<double>* returnArray = new vector<double>(getNumPoints()) ; 
    for(int i = 0 ; i < getNumPoints() ; i++){
//        (*returnArray)[i] = getNextTimeStepVector(inputNum) ; 
        (*returnArray)[i] = getNextTimeStep(inputNum) ; 
    }
    return returnArray ; 
}

int Feeder::getNumSets() 
{
    return 1 ; 
}



const string Feeder::FEEDER_NAME = "FEEDER" ; 


/* Function int main(int argc, char **argv) {{{ */
//int main(int argc, char **argv)
//{


//    return 0;
//} /* }}} */



