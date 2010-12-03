
#include <iostream>
using std::cout ; 
using std::endl ; 

#include "NetAnnealer.hpp"
#include "TempSchedule.hpp"
#include "NeuralNetwork.hpp"

NetAnnealer::NetAnnealer() : Annealer() , currentNet(NULL) { }

AnnealingTarget* NetAnnealer::anneal() 
{
    if(currentNet==NULL) throw "currentNet feeder is NULL" ; 
    double bestError ; 
    double currentError ; 
    NeuralNetwork* bestNet = (NeuralNetwork*) currentNet; 
    tempSchedule->initTemps() ; 
    int iterCount ; 
    double currentTemp  ;
    double backStepCount = -1 ; 

// #if MPI flags here
    while(tempSchedule->hasMoreTemps()){
        if(backStepCount < 0){  // otherwise, just keep it at the same temperature
            currentTemp  =  tempSchedule->getNextTemp() ; 
        }
        for(iterCount = 0 ; iterCount < iterPerTemp  ; iterCount++, backStepCount--){
            cout << "eval at temp: " << currentTemp << " iter: " <<  iterCount << endl ; 
            currentNet  =   (NeuralNetwork*) bestNet->perturb(currentTemp) ; 
            cout << "perturbed net: " << currentNet->eval() << " versus best: " << bestNet->eval() << endl ; 
            currentError = currentNet->eval() ; 
            if(currentError < bestError )  {
                  bestNet = (NeuralNetwork*) currentNet ; 
                  bestError = currentError ; 
                  backStepCount += mBackStep ; 
                  iterCount -= mSetBack ;  // add some more to this iteration
             }
        }
    }
    return bestNet ; 
}


void NetAnnealer::setAnnealingTarget(AnnealingTarget* annealingTarget) 
{
    currentNet = (NeuralNetwork*) annealingTarget; 
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

