/**
 */
#include <vector>
using std::vector ; 

#include <iostream>
using std::cout ; 
using std::endl ; 

#include <fstream>
using std::ifstream;
using std::ofstream;

#include <iostream>
using std::ios ;

#include <math.h>



#include "ScaledFileFeeder.hpp"

ScaledFileFeeder::ScaledFileFeeder() : FileFeeder() , mScaledMultiplier(0), INPUT_BUFF(30)
{
}

ScaledFileFeeder::ScaledFileFeeder(string newFile,int newScale,double newDeltaT,double newMinValue,double newMaxValue,double newFailValue) : FileFeeder(newFile,newMinValue,newMaxValue,newFailValue) , INPUT_BUFF(30) , mScaledMultiplier(newScale)
{

    deltaT = newDeltaT ; 
    
    setFile(newFile) ; 
    if(mScaledMultiplier>1){
        scaleFeeder(mScaledMultiplier) ; 
    }
}

/// This method scaled both the file feeder and the sig feeder. 
bool ScaledFileFeeder::scaleFeeder(int scaleMultiplier) 
{
    if(fileData==NULL) return false ;  // Exit if false. 

    mScaledMultiplier = scaleMultiplier ; 
    scaleFeederVector( fileData ) ; 

    // Scale the sig data if not NULL, too.
//    if(sigData!=NULL){
//        cout << "scaling sig data" << endl ;
//        scaleFeederVector(sigData) ; 
//    }

    return true ; 
}


bool ScaledFileFeeder::scaleFeederVector(vector<vector<double>*>* vectorToScale) 
{
    vector<vector<double>*>* origVector = new vector<vector<double>*>(*vectorToScale) ; 
    int origCount = 0 ; 
    int newCount = 0 ; 
    vectorToScale->resize( origVector->size() * mScaledMultiplier) ; 
    for(int origCount = 0 ;  origCount < origVector->size() ; ++origCount){
        for(int addCounter = 0  ; addCounter < mScaledMultiplier ; newCount++ ,addCounter++ ){
            (*vectorToScale)[newCount] = new vector<double>(  *((*origVector)[origCount]) ) ; 
        }
    }
    return true ; 
}



const string ScaledFileFeeder::FEEDER_NAME = "SCALED_FILE_FEEDER" ; 



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

