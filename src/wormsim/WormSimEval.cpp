
#include <vector> 
using std::vector ; 

#include <iostream>
using std::ostream ; 
using std::cout ; 
using std::endl ; 

#include "WormSimEval.hpp"


#include "WormMapStats.hpp"
#include "NeuralNetwork.hpp"
#include "BlitzEulerLiveNetEvaluator.hpp"
#include "UniformFwdMovement.hpp"
#include "SharpTurnMovementModel.hpp"
//#include "TurnAroundMovementModel.hpp"
#include "DieMovementModel.hpp"
#include "ShuffleMovementModel.hpp"
#include "ShufflePreserveMovementModel.hpp"
#include "UniformNetBehaviorModel.hpp"
#include "UniformRadWormShuffler.hpp"
#include "EvenRadWormShuffler.hpp"
#include "MapSpace.hpp"
#include "MapData.hpp"
#include "BlitzLiveNet.hpp"

#ifdef DOMPI
  #include "mpi.h"
#endif


#include "ShortMemoryBehaviorModel.hpp"

WormSimEval::WormSimEval(int numWorms,int wormSteps, BlitzLiveNet* origNetwork,MapData* newMap,double newForwardVelocity, double newPiroutteVelocity, double newMinDeltaT ,double newOutputSigmoid,WormShuffler* newWormShuffler,bool newDieOnEdge)  

{
    mForwardVelocity = newForwardVelocity  ; 
    mPirouetteVelocity = newPiroutteVelocity ; 
    mMapSpace = new MapSpace(newMap,wormSteps) ; 
    mWormSteps = wormSteps ; 
    mOrigNetwork = origNetwork ; 
    mNetOutputSigmoid = newOutputSigmoid ; 
    if(newWormShuffler ==NULL){
        // init with a number of worms
        mWormShuffler = new UniformRadWormShuffler( newMap->getDiameter() )  ; 
    }
    else{
        mWormShuffler = newWormShuffler ; 
    }
    mDieOnEdge = newDieOnEdge ; 
#ifdef DOMPI
    MPI_Comm_rank(MPI_COMM_WORLD, &wormRank) ; 
    MPI_Comm_size(MPI_COMM_WORLD, &wormProcs) ;
    mNumWorms = numWorms / wormProcs ;
#else
    mNumWorms = numWorms ; 
#endif
    mWormNets = new vector<BlitzLiveNet*>() ; 
    mWormMapStats = new WormMapStats(mMapSpace) ; 
    mMinDeltaT = newMinDeltaT; 

    createNetworks() ;  // initialize vector network copies form origNetworks for mNumWorms
    addWorms() ;      // add worms using the afforementioned networks


    initTrackerVector() ; 

    // Print out initial positions of worms
    // mMapSpace->printWorms(MapSpace::VERB_SOME) ;
}

/// Initializes the vector mWormPositions
void WormSimEval::initTrackerVector() 
{
    mWormPositions = new vector< vector<pair<double,double> >* >(mWormSteps) ; 
    vector< pair<double,double> >* timeSliceVector = NULL ;  

    for(int i = 0 ; i < mWormSteps ; i++){
        timeSliceVector = new vector< pair<double,double> >(mNumWorms) ; 
        for(int j = 0 ; j < mNumWorms ; j++){
              (*timeSliceVector)[j] = pair<double,double>(0.0,0.0) ; 
        }
        (*mWormPositions)[i] = ( new vector<pair<double,double> >(*timeSliceVector)  ) ; 
    }

}


double WormSimEval::getMinDeltaT() 
{
    return mMinDeltaT  ; 
}

vector<vector<pair<double,double> >*>* WormSimEval::getWormTracks() 
{
    return mWormPositions ; 
}




/// Creates N networks from mOrigNetwork with BlitzEulerLiveNetEvaluator evaluators.  
void WormSimEval::createNetworks() 
{
    mOrigNetwork->setEvaluator(new BlitzEulerLiveNetEvaluator(mMinDeltaT,mNetOutputSigmoid)) ; 
    (mOrigNetwork->getEvaluator())->setRelaxTime(mRelaxTime) ; 
//    (mOrigNetwork->getEvaluator())->setRelaxLimit(mRelaxLimit) ; 
    for(int i = 0 ; i < mNumWorms ; i++){
        BlitzLiveNet* newNet = new BlitzLiveNet(mOrigNetwork) ; 
        newNet->setEvaluator(new BlitzEulerLiveNetEvaluator(mMinDeltaT,mNetOutputSigmoid)) ; 
        (newNet->getEvaluator())->setRelaxTime(mRelaxTime) ; 
//        (newNet->getEvaluator())->setRelaxLimit(mRelaxLimit) ; 
        mWormNets->push_back(newNet) ; 
    }
}

/// Add N worms to 0,0 with unique networks from mOrigNetwork 
void WormSimEval::addWorms() 
{
    for(int i = 0 ; i < mNumWorms ; i++){
        Worm* newWorm = new Worm(mMapSpace) ; 
        newWorm->setForwardMovementModel(new UniformFwdMovement(mMinDeltaT*2.5,mMinDeltaT*2.5,mForwardVelocity)) ;  // left and right turning bias
        newWorm->setTurningMovementModel(new SharpTurnMovementModel(mMinDeltaT*50.0,mPirouetteVelocity)) ; // sharp-turn value
        if(mDieOnEdge==true){
            newWorm->setBounceModel(new DieMovementModel()) ; // sharp-turn value
        }
        else{
//            newWorm->setBounceModel(new TurnAroundMovementModel()) ; // sharp-turn value
//            newWorm->setBounceModel(new ShuffleMovementModel(mWormShuffler)) ; // sharp-turn value
            newWorm->setBounceModel(new ShufflePreserveMovementModel(mWormShuffler)) ; // sharp-turn value
        }
        newWorm->setTurningThreshold(mMinDeltaT*50.0) ;
        newWorm->setForwardVelocity(mForwardVelocity * mMinDeltaT) ;
        newWorm->setPirouetteVelocity(mPirouetteVelocity * mMinDeltaT) ;
        newWorm->setPosition( 0, 0 ); // set in the center

        // use the network which is already set
        newWorm->setBehaviorModel(new UniformNetBehaviorModel( (*mWormNets)[i],newWorm) ) ;
//        newWorm->setBehaviorModel(new ShortMemoryBehaviorModel( newWorm) ) ;
        mMapSpace->addWorm(newWorm) ; 
    }
}

/// Randomly shuffles worms around.  This could later be delagated to another class for additional flexibility. 
void WormSimEval::shuffleWorms() 
{
    mWormShuffler->reset() ; 
//    MPI_Comm_rank(MPI_COMM_WORLD, &wormRank) ; 
//    MPI_Comm_size(MPI_COMM_WORLD, &wormProcs) ;
//    cout << wormRank << ": init radius: " << ((EvenRadWormShuffler*) mWormShuffler)->getCurrentRadius() << endl ; 
    for(int i = 0 ; i < mNumWorms ; i++){
        mWormShuffler->shuffleWorm( mMapSpace->getWorm(i)) ; 
    }
//    cout << wormRank << ": final radius: " << ((EvenRadWormShuffler*) mWormShuffler)->getCurrentRadius() << endl ; 
}



/// Run each N network in the network (or worm) vector over P times or until the change in error is below alpha. 
void WormSimEval::relaxNet(bool doTrace) 
{
    if(mRelaxTime==0) {
        return ; 
    }


    // take the network from each worm and simply run relaxNet on them
//    vector<double>* relaxVector = new vector<double>() ; // initialize the relax vector
//    relaxVector->push_back(0.5) ; 
    BlitzEulerLiveNetEvaluator* tempEvaluator = NULL ; 
    for(int i = 0 ; i < mNumWorms ; i++){
        tempEvaluator = (BlitzEulerLiveNetEvaluator*) ((*mWormNets)[i])->getEvaluator() ; 
        tempEvaluator->setRelaxValue( (mMapSpace->getWorm(i))->getValue()  ) ; 
        tempEvaluator->resetTrace( mWormSteps,mWormSteps) ; 
        currentNeuronPoint = 0 ; 
        tempEvaluator->relaxNet() ; 
    }


}

/// Sets eval* to newNetwork, sets mOrigNetwork, and makes sure that each network is the worm vector is set.  For each network vector in the vector list, we need to make sure its evaluator get setNetwork called on it, since this is what the worms will use to direct theirbehavior. 
void WormSimEval::setNetwork(NeuralNetwork* newNetwork) 
{
    mOrigNetwork = (BlitzLiveNet*) newNetwork ; 
    for(int i = 0 ; i < mWormNets->size() ; i++){
        ((*mWormNets)[i]->getEvaluator())->setNetwork(newNetwork) ; 
    }
}

double WormSimEval::getSdevValue() 
{
    return mWormMapStats->getSdevLiveValue() ; 
}

int WormSimEval::getCountValue() 
{
    return mWormMapStats->getCount() ; 
}


/*  ***********************************************************************************
    getMeanValue() */
   
//! Calls WormMapStats::getMeanLiveValue() which calls WormMapStats::calcStats()
/*  *********************************************************************************** */
double WormSimEval::getMeanValue() 
{
    return mWormMapStats->getMeanLiveValue() ; 
}/// Method does not use evalPoint and evaluates over N worms.  Returns mMeanValue, here, I guess.


///  Need to relax the network and then calculate over N iteration, using mMapSpace handle. 
double WormSimEval::eval(NeuralNetwork* newNetwork) 
{
    if(newNetwork->getValid() == true){
        return meanValue ; 
    }

    evaluateWorms(newNetwork) ; 
    return meanValue ; 
}

bool WormSimEval::evaluateWorms(NeuralNetwork* newNetwork) 
{
    setNetwork(newNetwork) ; 
    mMapSpace->clearWormStats() ; 
    shuffleWorms() ; 
    relaxNet() ; 
    mMapSpace->clearWormStats() ; 
   
    for(int i = 0 ; i < mWormSteps ; i++){
        (*mWormPositions)[i] = mMapSpace->getWormPositions()   ; 
        mMapSpace->moveWorms() ; 
    }

    (*mWormPositions)[mWormSteps] = mMapSpace->getWormPositions()   ; 

#ifdef DOMPI
    // Each processor gets the mean value of its worms.
    procMeanValue = getMeanValue() ;

    // The sums of these means are added together.
    MPI_Allreduce( &procMeanValue, &meanValue , 1, MPI_DOUBLE,MPI_SUM, MPI_COMM_WORLD) ;  

    // The mean of the means is then calculated.
    meanValue = meanValue / (double) wormProcs ;

    // Grabs only the number of valid worms (e.g., don't die).
    procCountValue = getCountValid() ;

    // The total number of valid worms from all processors is totalled.
    MPI_Allreduce( &procCountValue, &countValue, 1, MPI_INT,MPI_SUM, MPI_COMM_WORLD) ;
    
    procSdevValue = getSdevValue()  ; 
    sdevValue = 0.0 ;
    
    // Gets the values for the worms on only the processor.
    for(int j = 0 ; j < getCountValue(); j++){
        if( getIndividualValid(j)==true ) { 
            procSdevValue += pow(  (getIndividualValue(j) - meanValue)  , 2.0) ; 
        }
    }
    
    MPI_Allreduce( &procSdevValue, &sdevValue, 1, MPI_DOUBLE,MPI_SUM, MPI_COMM_WORLD) ;  
    sdevValue = sqrt( sdevValue) / countValue ; 
    // cout << wormRank << ": meanValue[" << meanValue << "] " << endl ; 
    // cout << wormRank << ": sdevValue[" << sdevValue << "] " << endl ; 
    // cout << wormRank << ": countValue[" << countValue << "] " << endl ;
    
#else
   
    
    meanValue = getMeanValue() ; 
    sdevValue = getSdevValue() ; 
    countValue = getCountValid() ;  // count only those that we used.
    
#endif
    
    newNetwork->setValue(meanValue) ; 
    newNetwork->setValid(true) ; 

    return true ; 
}/// Method does not use evalPoint and evaluates over N worms.  Returns mMeanValue, here, I guess.

double WormSimEval::getIndividualValue(int wormNumber) 
{
    return (mMapSpace->getWorm( wormNumber) ) ->getValue()  ; 
}

double WormSimEval::getHAvg() 
{
    avgHValue = 0 ; 
#ifdef DOMPI
    for(int i = 0 ; i < getCountValue() ; i++){
        procAvgHValue += ((BlitzEulerLiveNetEvaluator*) ((*mWormNets)[i]->getEvaluator()))->getSumH() ; 
    }
    MPI_Allreduce( &procAvgHValue , &avgHValue, 1, MPI_DOUBLE,MPI_SUM,MPI_COMM_WORLD) ; 
    avgHValue = avgHValue / ( (double) wormProcs * getCountValue())  ; 
#else
    for(int i = 0 ; i < getCountValue() ; i++){
        avgHValue += ((BlitzEulerLiveNetEvaluator*) (*mWormNets)[i]->getEvaluator())->getSumH() ; 
    }
    avgHValue = avgHValue / getCountValue() ; 
#endif

    return avgHValue ; 
}


int WormSimEval::getCountValid() 
{
    return (mMapSpace->getWormCount() - mMapSpace->getNumDied()) ; 
}


bool WormSimEval::getIndividualValid(int wormNumber) 
{
    return  (   (mMapSpace->getWorm(wormNumber))->getDied()==false) ; 
}



int WormSimEval::getCount() 
{
    return countValue ;
}




double WormSimEval::getSdev() 
{
    return sdevValue ; 
}




///  Sets the MapSpace and re-calculates the worm count.  
void WormSimEval::setMapSpace(MapSpace* newMapSpace) 
{
    mMapSpace = newMapSpace ; 
    mNumWorms = mMapSpace->getWormCount() ; 
}



void WormSimEval::toXML(ostream *s) 
{
  // open the XML
  addSpacer(s,1) ; 
  *s << "<evaluator type=\"wormsimeval\">" << endl ;
  // add a blurb about a worm shuffler
  baseWormXML(s) ; 
  // close the XML
  addSpacer(s) ; 
  *s << "</evaluator>" << endl ;
}

/// We extend this method for the wormy methods. 
void WormSimEval::baseWormXML(ostream *s) 
{
#if DOMPI
    MPI_Comm_size(MPI_COMM_WORLD,&wormProcs) ; 
    addSpacer(s) ; 
  *s << "<numworms value=\""<< mNumWorms * wormProcs << "\"/>" << endl ;
#else
    addSpacer(s) ; 
  *s << "<numworms value=\""<< mNumWorms << "\"/>" << endl ;
#endif
  addSpacer(s) ; 
  *s << "<wormsteps value=\""<< mWormSteps << "\"/>" << endl ;
  addSpacer(s) ; 
  *s << "<forwardvelocity value=\""<< mForwardVelocity << "\"/>" << endl ;
  addSpacer(s) ; 
  *s << "<pirouettevelocity value=\""<< mPirouetteVelocity << "\"/>" << endl ;
  addSpacer(s) ; 
  *s << "<outputsigmoid value=\""<< mNetOutputSigmoid << "\" />" << endl ;
  addSpacer(s) ; 
  *s << "<dieonedge value=\""<< mDieOnEdge << "\" />" << endl ;
  mMapSpace->getMap()->toXML(s) ; 
  mWormShuffler->toXML(s) ; 
  doBaseXML(s) ; 
}

//void WormSimEval::setRelaxLimit(double _mRelaxLimit) 
//{
//    mRelaxLimit = _mRelaxLimit ; 
//    for(int i = 0 ; i < mWormNets->size() ; i++){
//        (((*mWormNets)[i])->getEvaluator())->setRelaxLimit(mRelaxLimit) ; 
//    }
//}

void WormSimEval::setRelaxTime(double _mRelaxTime) 
{
    mRelaxTime = _mRelaxTime ; 
    for(int i = 0 ; i < mWormNets->size() ; i++){
        (((*mWormNets)[i])->getEvaluator())->setRelaxTime(mRelaxTime) ; 
    }
}

void WormSimEval::setRelaxDeltaT(double newRelaxDeltaT) 
{
    mRelaxDeltaT = newRelaxDeltaT ; 
    for(int i = 0 ; i < mWormNets->size() ; i++){
        (((*mWormNets)[i])->getEvaluator())->setRelaxDeltaT(mRelaxDeltaT) ; 
    }
}

void WormSimEval::setRelaxTau(double newRelaxTau) 
{
    mRelaxTau = newRelaxTau ; 
    for(int i = 0 ; i < mWormNets->size() ; i++){
        (((*mWormNets)[i])->getEvaluator())->setRelaxTau(mRelaxTau) ; 
    }
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
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

