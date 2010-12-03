// -*- C++ -*-
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>

#include<iostream>
using std::cout ; 
using std::endl ; 

#include <float.h>

#include "NeuralNetwork.hpp"
#include "NetPerturber.hpp"
#include "NetEvaluator.hpp"
#include "Note.hpp"

NeuralNetwork::NeuralNetwork() : AnnealingTarget()
    ,evaluator(NULL)
    ,perturber(NULL)
    ,value(DBL_MAX)
    ,valid(false)
    ,mNote(new Note() )
{
}

Note* NeuralNetwork::getNote() 
{
    return mNote ; 
}



AnnealingTarget* NeuralNetwork::perturb(double temp)
{
    perturber->perturb(temp,this) ; 
    valid = false ;
    return this ;
}

double NeuralNetwork::eval() {
    if(evaluator==NULL) throw "NetEvaluator is NULL" ; 
    value = (evaluator->eval(this)); 
    valid = true ; 
    mNote->setNote("error",value) ; 
    return value ; 
}

void NeuralNetwork::setNote(Note* newNote) 
{
    if(mNote==NULL){
        mNote = new Note(newNote) ; 
    }
    else{
        *mNote = *newNote ; 
    }
}


/// Gets standard deviation, forcing another evaluation if not evaluated.
double NeuralNetwork::getSdev() {
    if(evaluator==NULL) throw "NetEvaluator is NULL" ; 
    value = (evaluator->eval(this)); 
    valid = true ; 
    return evaluator->getSdev() ; 
}

int NeuralNetwork::getCount() 
{
    if(evaluator==NULL) throw "NetEvaluator is NULL" ; 
    value = (evaluator->eval(this)); 
    valid = true ; 
    return evaluator->getCount() ; 
}



/// This method implies that eval() is called, so there is no need to recall it. 
double NeuralNetwork::evalNorml() 
{
    if(evaluator==NULL) throw "NetEvaluator is NULL" ; 
    return (evaluator->evalNorml(this)); 
}

bool NeuralNetwork::getValid() {
	return(valid);
}


void NeuralNetwork::setValid(bool _valid) {
	valid = _valid;
	return;
}

double NeuralNetwork::getValue() {
	return(value);
}


void NeuralNetwork::setValue(double _value) {
	value = _value;
	return;
}


void NeuralNetwork::setEvaluator(NetEvaluator *newEvaluator) {
  evaluator = newEvaluator ; 
  valid = false ; 
}





