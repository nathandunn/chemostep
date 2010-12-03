/*
 * $Id: FeederSet.cpp,v 1.2 2004/01/13 20:43:35 ndunn Exp $
 */

#include <iostream>
using std::cout ; 
using std::endl ; 

#include "SetFeeder.hpp" 
#include "Feeder.hpp" 
#include "FeederSet.hpp"



FeederSet::FeederSet() : Feeder()
//,feedVector(new vector<Feeder*>() )
{
    feedVector = new vector<Feeder*>()  ; 
    timeStepVector = NULL ; 
}

int FeederSet::getNumInputs() 
{
    if(feedVector==NULL){
        return 0 ; 
    }
    else{
        return feedVector->size() ; 
    }
}

vector<double>* FeederSet::getNextTimeStepVector(double newTimeStep) 
{

    if(feedVector==NULL){
        return NULL ; 
    }

    if(timeStepVector==NULL){
        timeStepVector = new vector<double>(feedVector->size()) ; 
//        cout << "timeStepVector->size(): " << timeStepVector->size() << endl ; 
    }

    if(timeStepVector->size() != feedVector->size()){
        timeStepVector = NULL ; 
        timeStepVector = new vector<double>(feedVector->size()) ; 
    }

    for(int i = 0 ; i < feedVector->size() ; i++){
        (*timeStepVector)[i] = getNextTimeStep(newTimeStep,i) ; 
    }
   
    return timeStepVector ; 
}


void FeederSet::setFeeder(Feeder* newFeeder, int inputNum) 
{
    if(feedVector->size() == inputNum){  // if one is added, adding 1
        feedVector->insert(feedVector->end(),newFeeder) ; 
    }
    else{
        (*feedVector)[inputNum] = newFeeder; 
    }
//    cout << "setFeeder size: " << feedVector->size() << endl ; 
}

Feeder* FeederSet::getFeeder(int inputNum) 
{
	if(inputNum < feedVector->size()){
        return (*feedVector)[0] ;  
    }
    else{
        cout << "stimNum: " << inputNum << " greater than feedVector->size(): "+feedVector->size() << endl ; 
        return NULL ; 
    }
}

double FeederSet::getDeltaT() 
{
    double returnDeltat = 0 ; 
    returnDeltat = (*feedVector)[0]->getDeltaT() ;  
    
    for(int i = 1 ; i < feedVector->size() ; i++){
         if((*feedVector)[0]->getDeltaT() != returnDeltat){
            cout << "getDeltaT values do not agree: (*feedVector)[0]->getDeltaT()" << (*feedVector)[0]->getDeltaT() << " returnDeltat: " << returnDeltat << endl ; 
            throw "getDeltaT values don't agree"; 
         }
    }

    return returnDeltat ; 
}

int FeederSet::getNumSets() 
{
    if(feedVector!=NULL){
        return (*feedVector)[0]->getNumSets() ; 
    }
    else{
        return 0 ; 
    }
}

bool FeederSet::reset() 
{
    for(int i = 0 ; i < feedVector->size() ; i++){
         if((*feedVector)[i]->reset() != true){
            cout << "error resetting feeder " << endl ; 
            throw "error resetting feeder"; 
         }
    }
    return true; 
}


bool FeederSet::isNewSet() {

    bool returnNewSet = (*feedVector)[0]->isNewSet() ; 

    for(int i = 1 ; i < feedVector->size() ; i++){
         if((*feedVector)[i]->isNewSet() != returnNewSet ){
            cout << "isNewSet values do not agree: (*feedVector)[0]->isNewSet()" << (*feedVector)[0]->isNewSet() << " returnNewSet: " << returnNewSet << endl ; 
            throw "isNewSet values don't agree"; 
         }
    }
    return returnNewSet; 
}

double FeederSet::getNextTimeStep(double newTimeStep, int inputNum)
{
    if(inputNum<feedVector->size()){
        return (*feedVector)[inputNum]->getNextTimeStep(newTimeStep) ; 
    }
    return 0 ; 
}

double FeederSet::getNextSigTimeStep(double newTimeStep, int inputNum) 
{
    if(inputNum<feedVector->size()){
//        return ( (SetFeeder*)(*feedVector)[inputNum])->getNextSigTimeStep(newTimeStep) ; 
//        cout << "name from class: " << (*feedVector)[inputNum]->getName() << "SetFeeder::FEEDER_NAME: " << SetFeeder::FEEDER_NAME << endl ; 
        if(  (*feedVector)[inputNum]->getName() == SetFeeder::FEEDER_NAME){
            return ( (SetFeeder*)(*feedVector)[inputNum])->getNextSigTimeStep(newTimeStep) ; 
        }
        return  (*feedVector)[inputNum]->getNextSigTimeStep(newTimeStep) ; 
    }
    return 1 ; 
}


double FeederSet::getNextPoint(int inputNum)
{
    if(inputNum<feedVector->size()){
        return (*feedVector)[inputNum]->getNextPoint() ; 
    }
    return 0 ; 
}

int FeederSet::getNumPoints() 
{
    int returnPoints = (*feedVector)[0]->getNumPoints() ; 
    
    for(int i = 1 ; i < feedVector->size() ; i++){
       if((*feedVector)[i]->getNumPoints()!=returnPoints){
           char* errormsg = "Number of points does not agree" ; 
           cout << errormsg << endl ; 
           throw errormsg ; 
       }
    }
    return returnPoints ; 
}





double FeederSet::getTotalTime() 
{
    double returnTotalTime = 0 ; 
    returnTotalTime = (*feedVector)[0]->getTotalTime() ;  
    
    for(int i = 1 ; i < feedVector->size() ; i++){
         if((*feedVector)[0]->getTotalTime() != returnTotalTime){
            cout << "getTotalTime values do not agree: (*feedVector)[0]->getTotalTime()" << (*feedVector)[0]->getTotalTime() << " returnTotalTime: " << returnTotalTime << endl ; 
            throw "getTotalTime values don't agree"; 
         }
    }

    return returnTotalTime ; 
}


double FeederSet::getCurrentTime() 
{
    double returnCurrentTime = 0 ; 
    returnCurrentTime = (*feedVector)[0]->getCurrentTime() ;  
    
    for(int i = 1 ; i < feedVector->size() ; i++){
         if((*feedVector)[0]->getCurrentTime() != returnCurrentTime){
            cout << "getCurrentTime values do not agree: (*feedVector)[0]->getCurrentTime()" << (*feedVector)[0]->getCurrentTime() << " returnCurrentTime: " << returnCurrentTime << endl ; 
            throw "getCurrentTime values don't agree"; 
         }
    }

    return returnCurrentTime ; 
}


bool FeederSet::hasMorePoints() 
{
    bool returnHasMorePoints = (*feedVector)[0]->hasMorePoints() ; 

    for(int i = 1 ; i < feedVector->size() ; i++){
         if((*feedVector)[i]->hasMorePoints() != returnHasMorePoints ){
            cout << "isHasMorePoints values do not agree: (*feedVector)[0]->isHasMorePoints()" << (*feedVector)[0]->hasMorePoints() << " returnHasMorePoints: " << returnHasMorePoints << endl ; 
            throw "isHasMorePoints values don't agree"; 
         }
    }
    return returnHasMorePoints; 
}


bool FeederSet::isTimePointValid() 
{
    bool returnTimePointValid = (*feedVector)[0]->isTimePointValid() ; 

    for(int i = 1 ; i < feedVector->size() ; i++){
         if((*feedVector)[i]->isTimePointValid() != returnTimePointValid ){
            cout << "isTimePointValid values do not agree: (*feedVector)[0]->isTimePointValid()" << (*feedVector)[0]->isTimePointValid() << " returnTimePointValid: " << returnTimePointValid << endl ; 
            throw "isTimePointValid values don't agree"; 
         }
    }
    return returnTimePointValid; 
}


const string FeederSet::FEEDER_NAME = "FEEDER_SET" ; 


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
// FILE: "/Users/nathandunn/svn/chemotrunk/src/chemostep/FeederSet.cpp"
// LAST MODIFICATION: "Wed, 12 Jan 2005 09:56:17 -0800 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: FeederSet.cpp,v 1.2 2004/01/13 20:43:35 ndunn Exp $

