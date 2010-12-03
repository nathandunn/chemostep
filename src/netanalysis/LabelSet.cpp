#include <iostream>
using std::cout ; 
using std::endl ; 

#include "LabelSet.hpp"


LabelSet::LabelSet() : vector<Label*>()
{
}

LabelSet::LabelSet(int size) : vector<Label*>(size)
{
}

LabelSet::LabelSet(const LabelSet & newLabelSet)  : vector<Label*>(newLabelSet)
{
}


vector<vector<double>*>* LabelSet::getModelTraceAsSeries()  
{
    int numNeurons = (this)->size() ; // each neuron at time-point 0
    vector<vector<double>*>* returnTrace = new vector<vector<double>*>(numNeurons) ; 

    for(int i = 0 ; i < numNeurons ; i++){
        (*returnTrace)[i] = (new vector<double>(  *((*this)[i]->getModelTraceVector())  )  ) ; 
    }

    return returnTrace ; 

}


/// For each label, create a model series. 
vector<vector<double>*>* LabelSet::getErrorTraceAsSeries()  
{
    vector<vector<double>*>* returnTrace = new vector<vector<double>*>() ; 
    int numNeurons = (this)->size() ; // each neuron at time-point 0

    for(int i = 0 ; i < numNeurons ; i++){
        returnTrace->push_back(new vector<double>(  *((*this)[i]->getErrorVector())  )  ) ; 
    }

    return returnTrace ; 
}


//void LabelSet::setMaxTime(int newMaxTime) 
//{
//    mMaxTime = newMaxTime ; 
//}



/* Function int main(int argc, char **argv) {{{ */
//int main(int argc, char **argv)
//{


//    return 0;
//} /* }}} */



// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


