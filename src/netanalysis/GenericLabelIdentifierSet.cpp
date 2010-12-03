#include <iostream>
using std::cout ; 
using std::endl ; 

#include "GenericLabelIdentifierSet.hpp"

#include "LabelSet.hpp"

GenericLabelIdentifierSet::GenericLabelIdentifierSet()  
    : mLabelModelVector(new vector<LabelFactory*>()) 
{
}

void GenericLabelIdentifierSet::addLabelFactory( LabelFactory* newLabelFactory  ) 
{
    mLabelModelVector->push_back(newLabelFactory) ; 
}





// for each label in the LabelFactory in the vector, iterate through and evaluate the best  label set for each
LabelSet* GenericLabelIdentifierSet::extractLabelSet( RawSignal* newRawSignal ) 
{
    vector<LabelSet*>* labelSetVector = new vector<LabelSet*>( mLabelModelVector->size()  ) ; 
    
    for(int i = 0 ; i < labelSetVector->size() ; i++){
        (*labelSetVector)[i] = ((*mLabelModelVector)[i])->extractLabelSet( newRawSignal)     ; 
    }

    return findBestLabelSet( labelSetVector)  ; 
}


/// Finds the LabelSets with the lowest error and returns a LabelSet based on this.  This will most likely provide a heterogeneous set of LabelSets.  
LabelSet* GenericLabelIdentifierSet::findBestLabelSet( vector<LabelSet*>*  newLabelSetVector ) 
{
    LabelSet* bestLabelSet = new LabelSet( *((*newLabelSetVector)[0]) ) ; 

    // Copy the first one over.  Is a reference copy persmissable?  I can't see why not.
	for(int modelCount = 1 ; modelCount < newLabelSetVector->size() ; ++modelCount){
        for(int labelCount = 0 ; labelCount < ((*newLabelSetVector)[0])->size() ; ++labelCount){
             // compare the bestLabelSet to the current one being explored and copyy the best one to bestLabelSet
			cout << "error A: " << ((*(*newLabelSetVector)[modelCount])[labelCount])->getAverageError() << " error B: " <<  (*bestLabelSet)[labelCount]->getAverageError()  << endl ; 
            if( ((*(*newLabelSetVector)[modelCount])[labelCount])->getAverageError() < (*bestLabelSet)[labelCount]->getAverageError() ){
                (*bestLabelSet)[labelCount] =  (*(*newLabelSetVector)[modelCount])[labelCount]  ;
            }
        }
    }
    
    return  bestLabelSet ; 
}




/* Function int main(int argc, char **argv) {{{ */
//int main(int argc, char **argv)
//{


//    return 0;
//} /* }}} */



// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


