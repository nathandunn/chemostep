#ifndef MapSpace_hpp
#define MapSpace_hpp

#include <vector>
using std::vector ;

#include <utility>
using std::pair ;

#include <numeric>

#include "Worm.hpp"
#include "MapData.hpp"
#include "Logger.hpp"

class Worm ; 

class MapSpace{

public:
    MapSpace(MapData* newMap=NULL,int newWormSteps=0) ;
    
    void     addWorm(Worm* newWorm) ; 
    Worm*    getWorm(int wormNumber) ; 
    void     setMap(MapData *newMap) ; 
    MapData* getMap() ; 
    virtual double   getCenterX() ; 
    virtual double   getCenterY() ; 
    double   getXPosition(int wormNumber) ; 
    double   getYPosition(int wormNumber) ; 
    int      moveWorms() ; 
    int      getSimState() ; 
    
    // get map data
    double   getSumLinWormDistance(int fromWorm) ; 
    double   getLinWormDistance(int fromWorm, int toWorm) ; 
    bool     inCenter(double x,double y) ; 
    void     setCenterRadius(double centerRadius,double centerX,double centerY) ; 
    double   getCenterRadius() {  return centerRadius ; } 
    float    getMapValue(float x,float y) ; 

    // stat values
    void   printWorms(int verbosity) ; 
    void   printWorms() ; 
    double getAverageTimeAtCenter() ; 
    double getAverageTimeToCenter() ; 
    double getAverageReachedCenter() ;
    double getProbabilityAverage() ; 
    double getPirouetteDecisionRatio() ;
    double getMiddleDecisionRatio() ;
    double getRunDecisionRatio() ;
    double getSharpTurnBehaviorRatio() ;
    double getRunBehaviorRatio() ;
    int    getNumDied() ;
    double getAverageWormDies() ;
    double getAverageConcentrationDiff() ;
    bool   hitEdge(float x, float y) ;
    void   clearWormStats() ; 

    void   setVerbosity(int newVerbosity){
	verbosity = newVerbosity ;
    }

    int    getWormCount(){
        return wormVector.size() ; 
    }
    
    void   clearStats() ; 
    
    void   setWormsMoved(bool newMoved) ; /// lets us know whether or not worms moved since the last time
    bool   getWormsMoved() ; /// lets us know whether or not worms moved since the last time
    double getDistanceFromCenter(double x,double y) ; 
    double getDistanceFromRadius(double x,double y) ;
    double getDistanceFromRadius(pair<double,double> point)  ;
    vector< pair<double,double> >* getWormPositions(int timeStep=-1) ; 
        
    static const int NO_RUNNING= 1 ; 
    static const int SOME_RUNNING= 2 ; 
    static const int VERB_LOTS = 3 ; 
    static const int VERB_SOME = 2 ; 
    static const int VERB_NONE = 0 ; 
    // static const int ALL_RUNNING = 3 ; 

protected:
    virtual void initWormPositionVector() ; 
    // the worms on the plate
    vector<Worm*> wormVector ; 
    int width  ; 
    int height ; 
    Logger *aLog ; 
    int simState ; 
    int verbosity ;
    int numDied ;
    double centerRadius ; 
    double centerX ; 
    double centerY ; 
    // the physical representation of the dish
    MapData *map ; 

    bool mWormMoved ; /// Records if we recorded the worms last move.
    vector<vector<pair<double,double> >*>* mWormPositions ; /// Records if we recorded the worms last move.
    int mWormSteps ; 
    int mStepCount; 
} ;


#endif

