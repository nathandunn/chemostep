
#include <iostream>
using std::cout ; 
using std::endl ; 

#include <sstream>
using std::ostringstream ; 

#include "TextEvalTrace.hpp"
#include "NetEvaluator.hpp"
#include "Feeder.hpp"
#include "SetFeeder.hpp"
#include "FeederSet.hpp"

TextEvalTrace::TextEvalTrace() : EvalTrace()
    ,fullTrace(NULL)
    ,singleTrace(NULL)
{
}


string TextEvalTrace::allNeuronTrace() 
{
    ostringstream stringStream(ostringstream::out) ; 
    fullTrace = evaluator->getLastFullTrace() ; 
    for(int i = 0 ; i < fullTrace->size() ; i++){
        for(int j = 0 ; j < (*fullTrace)[0]->size() ; j++){
            stringStream << (*(*fullTrace)[i])[j] << valueDelimiter ; 
        }
        stringStream << timeDelimiter ; 
    }
    return stringStream.str() ; 
}

string TextEvalTrace::lastNeuronTrace() 
{
    singleTrace = evaluator->getLastTrace() ; 
    return dumpSingleTrace() ; 
}

string TextEvalTrace::neuronTrace(int neuronNum) 
{
    singleTrace = evaluator->getLastTrace(neuronNum) ; 
    return dumpSingleTrace() ; 
}

string TextEvalTrace::errorTrace() 
{
    singleTrace = evaluator->getLastErrorTrace() ; 
    return dumpSingleTrace() ; 
}

string TextEvalTrace::dumpSingleTrace() 
{
    ostringstream stringStream(ostringstream::out) ; 
    for(int i = 0 ; i < singleTrace->size() ; i++){
        stringStream << (*singleTrace)[i] << timeDelimiter ; 
    }
    return stringStream.str() ; 
}


string TextEvalTrace::stimTrace() 
{
    // assume that the first time-step is it
    ostringstream stringStream(ostringstream::out) ; 
    vector<Feeder*>* feeder = evaluator->getFullStimulus() ; 
    double deltaT = (*feeder)[0]->getDeltaT() ;  
    for(int j = 0 ; j < feeder->size() ; j++){
        (*feeder)[j]->reset() ; 
    }
//    for(int i = 0 ; i < (*feeder)[0]->getTotalTime() ; i++ ){
    for(int i = 0 ; i < (*feeder)[0]->getNumPoints() ; i++ ){
        for(int j = 0 ; j < feeder->size() ; j++){
            stringStream << (*feeder)[j]->getNextTimeStep(deltaT) << valueDelimiter ; 
        }
        stringStream << timeDelimiter ; 
    }
    return stringStream.str() ; 
}

string TextEvalTrace::targetTrace() 
{
    // assume that the first time-step is it
    ostringstream stringStream(ostringstream::out) ; 
    vector<Feeder*>* feeder = evaluator->getFullTarget() ; 
    double deltaT = (*feeder)[0]->getDeltaT() ;  
    for(int j = 0 ; j < feeder->size() ; j++){
        (*feeder)[j]->reset() ; 
    }
    for(int i = 0 ; i < (*feeder)[0]->getNumPoints() ; i++ ){
        for(int j = 0 ; j < feeder->size() ; j++){
            stringStream << (*feeder)[j]->getNextTimeStep(deltaT) << valueDelimiter ; 
        }
        stringStream << timeDelimiter ; 
    }
    return stringStream.str() ; 
}

string TextEvalTrace::dumpFeederTrace(Feeder* feeder){
    ostringstream stringStream(ostringstream::out) ; 
    feeder->reset() ; 
    while(feeder->hasMorePoints()){
         stringStream << feeder->getNextPoint() << timeDelimiter ;  
    }
    return stringStream.str()  ; 
}


string TextEvalTrace::stimTimeTrace() 
{
    double theDeltaT = (evaluator->getStimulus())->getDeltaT() ; 
    return dumpTimeStep(theDeltaT) ; 
}

string TextEvalTrace::dumpTimeStep(double timeStep){
    ostringstream stringStream(ostringstream::out) ; 
    double time = 0 ; 
    for(int i = 0 ; i < singleTrace->size() ; i++){
         stringStream <<  time << timeDelimiter ;  
         time += timeStep ; 
    }
    return stringStream.str()  ; 
}

string TextEvalTrace::targetTimeTrace() 
{
    double theDeltaT = (evaluator->getTarget())->getDeltaT() ; 
    return dumpTimeStep(theDeltaT) ; 
}


// ideally we want to stack these side by side
string TextEvalTrace::combineTrace(string trace1,string trace2) 
{
    return "" ; 
}

string TextEvalTrace::lastTimeStepNeurons() 
{
    fullTrace = evaluator->getLastFullTrace() ; 
    return neuronsAtTargetPoint(fullTrace->size()-1) ; 
}

string TextEvalTrace::neuronsAtTargetPoint(int point) 
{
    ostringstream stringStream(ostringstream::out) ; 
    fullTrace = evaluator->getLastFullTrace() ; 
    if(point>= fullTrace->size()){
        stringStream << "point: " << point << " is out of bounds" << endl ; 
        throw stringStream.str() ; 
    }
    for(int j = 0 ; j < (*fullTrace)[point]->size() ; j++){
        stringStream << (*(*fullTrace)[point])[j] << valueDelimiter ; 
    }
    return stringStream.str() ; 
}

string TextEvalTrace::timeDelimiter = "\n" ; 
string TextEvalTrace::valueDelimiter = " " ; 


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
// FILE: "/Users/ndunn/cvs/auto3TWOINPUTSTEP/src/chemostep/TextEvalTrace.cpp"
// LAST MODIFICATION: "Sun, 14 Dec 2003 01:01:53 -0800 (ndunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>

