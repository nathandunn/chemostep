
#include <iostream>
using std::cout ; 
using std::endl ; 

#include <math.h>

#include "MapSpace.hpp"
#include "Logger.hpp"

   
//! Insert description here
/*  *********************************************************************************** */
MapSpace::MapSpace(MapData* newMap,int newWormSteps) :
	simState(SOME_RUNNING) ,
	mWormSteps(newWormSteps) ,
	mWormPositions(NULL) ,
	mStepCount(0) 
{
    // this method calls others methods, so don't implicitly set the mpa
	if(newMap!=NULL){
        setMap(newMap) ; 
    }
}


/*  ***********************************************************************************
    () */
   
//! Insert description here
/*  *********************************************************************************** */
MapData* MapSpace::getMap() 
{
    return map ; 
}

/// Returns the center of the map radius, so we know where we should be aimed.
double   MapSpace::getCenterX() 
{
    return map->getDiameter()/2.0 ; 
}


double   MapSpace::getCenterY() 
{
    return map->getDiameter()/2.0 ; 
}


/*  ***********************************************************************************
    () */
   
//! Insert description here
/*  *********************************************************************************** */
void MapSpace::clearStats(){
    wormVector.clear() ; 
}


/*  ***********************************************************************************
    () */
   
//! Insert description here
/*  *********************************************************************************** */
double MapSpace::getSumLinWormDistance(int fromWorm){
    double sumDistance = 0 ; 
    int size = wormVector.size() ; 

    for(int toWorm = 0 ; toWorm < size ; toWorm++){
        sumDistance += getLinWormDistance(fromWorm,toWorm) ; 
    }
    
    return sumDistance ; 
}


/*  ***********************************************************************************
    () */
   
//! Insert description here
/*  *********************************************************************************** */
double MapSpace::getLinWormDistance(int fromWorm,int toWorm){
    double distance = 0 ;
    distance = sqrt( pow(wormVector[fromWorm]->getX()-wormVector[toWorm]->getX(),2) + pow(wormVector[fromWorm]->getY()-wormVector[toWorm]->getY(),2) ) ; 
    return distance ; 
}


/*  ***********************************************************************************
    () */
   
//! Insert description here
/*  *********************************************************************************** */
Worm* MapSpace::getWorm(int wormNumber) 
{
    return (wormVector[wormNumber]) ; 
}

/// Returns a pair<double,double> position for each worm at each timestep.
vector<pair<double,double> >* MapSpace::getWormPositions(int timeStep){
    if(timeStep<0){
        return (*mWormPositions)[mStepCount] ; 
    }
    else{
        return (*mWormPositions)[timeStep] ; 
    }
}


/*  ***********************************************************************************
    () */
   
//! Insert description here
/*  *********************************************************************************** */
void MapSpace::setMap(MapData *newMap){
  map = newMap ; 
  setCenterRadius(0.0, map->getDiameter()/2.0,map->getDiameter()/2.0) ; 
}


/*  ***********************************************************************************
    () */
   
//! Insert description here
/*  *********************************************************************************** */
double MapSpace::getAverageConcentrationDiff(){
    double totalDiff = 0   ; 
    int size = wormVector.size() ;
    
    for(int i = 0 ; i < size ; i++){
	totalDiff += wormVector[i]->getAverageConcentrationDiff() ; 
    }
    
    return totalDiff/((double) size) ; 
}


/*  ***********************************************************************************
    () */
   
//! Insert description here
/*  *********************************************************************************** */
double MapSpace::getPirouetteDecisionRatio(){
    double ratio  = 0   ; 
    int size = wormVector.size() ; 

    for(int i = 0 ; i < size ; i++){
	ratio += wormVector[i]->getPirouetteDecisionAverage() ; 
    }

    return ratio/((double) size) ; 
}


/*  ***********************************************************************************
    () */
   
//! Insert description here
/*  *********************************************************************************** */
double MapSpace::getMiddleDecisionRatio(){
    double ratio  = 0   ; 
    int size = wormVector.size() ; 

    for(int i = 0 ; i < size ; i++){
	ratio += wormVector[i]->getMiddleDecisionAverage() ; 
    }

    return ratio/((double) size) ; 
}


/*  ***********************************************************************************
    () */
   
//! Insert description here
/*  *********************************************************************************** */
double MapSpace::getRunDecisionRatio(){
    double ratio  = 0   ; 
    int size = wormVector.size() ; 

    for(int i = 0 ; i < size ; i++){
	ratio += wormVector[i]->getRunDecisionAverage() ; 
    }

    return ratio/((double) size) ; 
}


/*  ***********************************************************************************
    () */
   
//! Insert description here
/*  *********************************************************************************** */
double MapSpace::getSharpTurnBehaviorRatio(){
    double ratio  = 0   ; 
    int size = wormVector.size() ; 

    for(int i = 0 ; i < size ; i++){
	ratio += wormVector[i]->getSharpTurnBehaviorAverage() ; 
    }

    return ratio/((double) size) ; 
}


/*  ***********************************************************************************
    () */
   
//! Insert description here
/*  *********************************************************************************** */
double MapSpace::getRunBehaviorRatio(){
    double ratio  = 0   ; 
    int size = wormVector.size() ; 

    for(int i = 0 ; i < size ; i++){
	ratio += wormVector[i]->getRunBehaviorAverage() ; 
    }

    return ratio/((double) size) ; 
}


/*  ***********************************************************************************
    () */
   
//! Insert description here
/*  *********************************************************************************** */
double MapSpace::getProbabilityAverage(){
    double probabilityTotal  = 0   ; 
    int size = wormVector.size() ; 

    for(int i = 0 ; i < size ; i++){
	probabilityTotal += wormVector[i]->getProbabilityAverage() ; 
    }

    return probabilityTotal/((double) size) ; 
}


/*  ***********************************************************************************
    () */
   
//! Iterate through the vector and run
/*  *********************************************************************************** */
double MapSpace::getAverageReachedCenter() {
    double numReachedCenter = 0 ; 
    int size = wormVector.size() ;
    
    for(int i = 0 ; i < size ; i++){
	numReachedCenter += wormVector[i]->getReachedCenter() ; 
    }
    
    return numReachedCenter/((double) size) ; 
}

/*  ***********************************************************************************
    getAverageWormDies() */
   
//! Return the percentage of worms that died
/*  *********************************************************************************** */
double MapSpace::getAverageWormDies(){
    int size = wormVector.size() ;

    return numDied/((double) size) ; 
}


/*  ***********************************************************************************
    getAverageWormDies() */
   
//! Determine the percentage of worms that died
/*  *********************************************************************************** */
int MapSpace::getNumDied(){
    int size = wormVector.size() ;

    // Reset numDied
    numDied = 0;
    
    for(int i = 0 ; i < size ; i++){
	numDied += (wormVector[i])->getDied() ; 
    }
    
    return numDied; 
}


/*  ***********************************************************************************
    () */
   
//! Iterate through the vector and run
/*  *********************************************************************************** */
double MapSpace::getAverageTimeAtCenter() {
    double totalTimeAtCenter = 0 ; 
    int total = 0 ; 
    int size = wormVector.size() ; 
	
    for(int i = 0 ; i < size ; i++){
	if(wormVector[i]->getReachedCenter() ) {
	    totalTimeAtCenter += wormVector[i]->getTimeAtCenter() ; 
	    ++total ; 
	}
    }
    
    return totalTimeAtCenter/((double) total ) ; 
}


/*  ***********************************************************************************
    () */
   
//! Insert description here
/*  *********************************************************************************** */
double MapSpace::getAverageTimeToCenter() {
    double totalTimeToCenter = 0 ; 
    int total = 0 ; 
    int size = wormVector.size() ; 
    
    for(int i = 0 ; i < size ; i++){
	if(wormVector[i]->getReachedCenter() ) {
	    totalTimeToCenter += wormVector[i]->getTimeToCenter() ; 
	    ++total ; 
	}
    }
    
    return totalTimeToCenter/((double) total ) ; 
}


/*  ***********************************************************************************
    () */
   
//! Insert description here
/*  *********************************************************************************** */
void MapSpace::addWorm(Worm* newWorm){
    newWorm->setWormNumber( wormVector.size()) ; 
    wormVector.push_back(newWorm) ; 		
    // cout << "wormVector: " << wormVector.size() << endl ;
}


/*  ***********************************************************************************
    () */
   
//! Insert description here
/*  *********************************************************************************** */
float MapSpace::getMapValue(float x,float y){
    return  map->getValue(x,y) ; 
}


/*  ***********************************************************************************
    hitEdge() */
   
//! Determines whether passed coordinates are beyond the edge of the space.
/*  *********************************************************************************** */
bool MapSpace::hitEdge(float x, float y){
    
    /* I left this code in here for future debugging if necessary
    bool hitIt;

    hitIt = getDistanceFromCenter(x,y) >= (map->getDiameter()/2.0) ;

    if(hitIt) {
	cout << "HIT THE EDGE (x,y) = (" << x << "," << y << "), DFC = " << getDistanceFromCenter(x,y) << endl;
    }

    return (hitIt)
    */
    
    return (getDistanceFromCenter(x,y) >= (map->getDiameter()/2.0)) ;
}


/*  ***********************************************************************************
    () */
   
//! Insert description here
/*  *********************************************************************************** */
void MapSpace::setCenterRadius(double newCenterRadius,double newCenterX,double newCenterY) {
    centerX = newCenterX ; 
    centerY = newCenterY ; 
    centerRadius = newCenterRadius ; 
}




///  Initializes the vector which contains all of the worm objects. 
void MapSpace::initWormPositionVector() 
{
        mWormPositions = new vector<vector<pair<double,double> >*>(mWormSteps) ; 
        int numWorms = getWormCount() ; 
        
		vector< pair<double,double> >* timeSliceVector = NULL ;  
        
        for(int i = 0 ; i < mWormSteps ; i++){
            timeSliceVector = new vector< pair<double,double> >(numWorms) ; 
            for(int j = 0 ; j < numWorms ; j++){
                  (*timeSliceVector)[j] = pair<double,double>(0.0,0.0) ; 
            }
            (*mWormPositions)[i] = ( new vector<pair<double,double> >(*timeSliceVector)  ) ; 
        }
}

/// Moves worms a single time-point in space.  
int MapSpace::moveWorms(){

    int numWorms = wormVector.size() ; 
    
    // Set up a temporary worm to make this more readable
    Worm* testWorm = NULL ;
    vector<pair<double,double> >* positionVector = new vector<pair<double,double> >(numWorms) ;  
    
    int theWormState = 0 ; 
    simState = MapSpace::NO_RUNNING ; 

    // Iterate through the vector and move the worms.
    for(int i = 0 ; i < numWorms ; i++){
        testWorm = getWorm(i);
        (*positionVector)[i] =  testWorm->getPosition() ;
//        (*((*positionVector)[i])).first  =  (testWorm->getPosition()).first ;
//        (*((*positionVector)[i])).second  =  (testWorm->getPosition()).second ;

        // If the worm isn't already dead
        if(!testWorm->getDied()) {
            // Move the worm
            theWormState = testWorm->move() ; 	
            
            if(simState == MapSpace::NO_RUNNING) {
                simState = MapSpace::SOME_RUNNING ; 
            }
        }
    }

    if(mWormPositions!=NULL){
        // add another time-slice of every worm
        
        *((*mWormPositions)[mStepCount]) = *positionVector ;
    }

    delete positionVector ; // clean up
    
    mWormMoved = true ; 
    ++mStepCount ; 

    // Return the state: Whether some or no worms are running
    return simState ;
}


/*  ***********************************************************************************
    () */
   
//! Insert description here
/*  *********************************************************************************** */
double MapSpace::getXPosition(int wormNumber) {
    return (wormVector[wormNumber])->getX() ; 	
}


/*  ***********************************************************************************
    () */
   
//! Insert description here
/*  *********************************************************************************** */
double MapSpace::getYPosition(int wormNumber) {
    return (wormVector[wormNumber])->getY() ; 	
}


/*  ***********************************************************************************
    getDistanceFromCenter() */
   
//! Returns the distance from the passed coordinates to the center of the space.
/*  *********************************************************************************** */
double MapSpace::getDistanceFromCenter(double x,double y){
    return  sqrt( pow((x - centerX), 2.0) + pow((y - centerY), 2.0)) ; 
}

double MapSpace::getDistanceFromRadius(pair<double,double> point)  
{
    return getDistanceFromRadius(point.first,point.second) ; 
}


/*  ***********************************************************************************
    getDistanceFromRadius(double x,double y) */
   
//! Returns the distance from the passed coordinates to the radius of the space.
/*  *********************************************************************************** */
double MapSpace::getDistanceFromRadius(double x,double y){
    // This is my way of getting the absolute value of a double
    double distance = centerRadius - getDistanceFromCenter(x,y);
    return  (distance >= 0) ? distance : -1 * distance;
}


/*  ***********************************************************************************
    inCenter() */
   
//! Determine if the passed coordinates are inside the center (?)
/*  *********************************************************************************** */
bool MapSpace::inCenter(double x,double y){
    return (getDistanceFromCenter(x,y) < centerRadius) ;  
}


/*  ***********************************************************************************
    printWorms() */
   
//! Iterates over all worms and prints out pertinent information
/*  *********************************************************************************** */
void MapSpace::printWorms(){
    aLog = Logger::getLogger() ; 

    // Iterate through the vector and print
    for(int i = 0 ; i < wormVector.size() ; i++){
        if(aLog->outStream==NULL) verbosity = VERB_NONE ; 
	
	switch(verbosity){	
            default:
	    case VERB_SOME:
                aLog->outStream << wormVector[i]->getX() << "\t" ;
                aLog->outStream << wormVector[i]->getY() << "\t" ;
                aLog->outStream << wormVector[i]->getValue() << "\t" ; 
                aLog->outStream << endl ;
                break ; 
            case VERB_LOTS:
                aLog->outStream << wormVector[i]->getX() << "\t" ; 
                aLog->outStream << wormVector[i]->getY() << "\t" ;
                aLog->outStream << wormVector[i]->getValue() << "\t" ; 
                aLog->outStream << (wormVector[i]->getBehaviorModel())->getProbability() << "\t" ; 
                aLog->outStream << (wormVector[i]->getBehaviorModel())-> getCurrentDecision() << "\t"  ; 
                aLog->outStream << (wormVector[i]->getBehaviorModel())-> getCurrentBehavior() << "\t"  ; 
                aLog->outStream << endl ; 
                break ; 
            case VERB_NONE:
                // do nothing
                break ; 
        }
    }
 
//  aLog->outStream << endl ; 
}


/*  ***********************************************************************************
    () */
   
//! Calculate the distance from the center
/*  *********************************************************************************** */
void MapSpace::setWormsMoved(bool newMoved) 
{
    mWormMoved = newMoved ; 
}



/*  ***********************************************************************************
    () */
   
//! Calculate the distance from the center
/*  *********************************************************************************** */
bool MapSpace::getWormsMoved() 
{
    return mWormMoved ; 
}


/*  ***********************************************************************************
    () */
   
//! Calculate the distance from the center
/*  *********************************************************************************** */
void MapSpace::printWorms(int verbosity){
    setVerbosity(verbosity) ; 
    printWorms() ; 
}

void   MapSpace::clearWormStats() 
{
    for(int i = 0 ; i < wormVector.size() ; i++){
        getWorm(i)->clearStats();
    }
    mStepCount = 0 ; 
    // here, we init the logger
    if(mWormSteps>0 && mWormPositions==NULL){
        initWormPositionVector() ; 
    }
}



