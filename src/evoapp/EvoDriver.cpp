
#include <iostream>
using std::cout ; 
using std::endl ; 

#include <fstream>
using std::ofstream ; 

#include <string>
using std::string ; 

#include <vector>
using std::vector ; 

#include <float.h>

#include "BlitzLiveNet.hpp"
#include "RNG.hpp" 
#include "StepFeeder.hpp"   
#include "SetFeeder.hpp"   
#include "FileFeeder.hpp"   
#include "UniformNetBehaviorModel.hpp"   
#include "BlitzNetAnnealer.hpp"   
#include "BlitzEulerLiveNetEvaluator.hpp"   
#include "TempSchedule.hpp" 
#include "MomentumTempSchedule.hpp" 
#include "UniformFwdMovement.hpp" 
#include "SharpTurnMovementModel.hpp"
#include "SetRadWormShuffler.hpp"
#include "RNG.hpp" 
#include "TextEvalTrace.hpp" 
#include "TinyBzNetParser.hpp" 
#include "BlitzXmlNetRenderer.hpp" 
#include "GaussRadialMap.hpp" 
#include "LinRadialMap.hpp" 
#include "QtFlatRenderer.h" 
#include "WormMapStats.hpp" 

#include <qmessagebox.h>
#include <TiAppParser.hpp>
#include <TiListParser.hpp>
#include <AppInterfaceXmlEngine.hpp>
#include <TinyAppInterfaceXmlEngine.hpp>
#include <Command.hpp>
#include <AppInterface.hpp>
#include <Option.hpp>
#include <Worm.hpp>
#include <WormMapStats.hpp>

#include "EvoDriver.hpp"

#define CHAR_LENGTH 256


/*  ***********************************************************************************
    Constructor */
   
//! Description here.
/*  *********************************************************************************** */
EvoDriver::EvoDriver(string newInterfaceName,string newTypeName,AppInterface* newParent)  :
TiFlatBaseApp(newInterfaceName,newTypeName,newParent) 
{
   description = "Kinetic annealer.  Produces 1 to N." ; 
   RNG::initSeed();
}


/*  ***********************************************************************************
    initMap() */
   
//! Description here.
/*  *********************************************************************************** */
void EvoDriver::initMap() {
//  mMap = new GaussRadialMap(mDiameter,mHighTemp,mLowTemp) ; 
    mMap = new LinRadialMap(mDiameter,mHighTemp,mLowTemp) ; 
    mMapSpace = new MapSpace() ; 
    mMapSpace->setMap(mMap) ; 
    mMapSpace->setCenterRadius(0, mDiameter/2.0,mDiameter/2.0) ; 
}


/*  ***********************************************************************************
    initWorms() */
   
//! Give the worms appropriate properties and set them randomly about the plate.
/*  *********************************************************************************** */
void EvoDriver::initWorms() 
{
    float radius,theta, xPos,yPos ; 
    TinyBzNetParser* netParser = new TinyBzNetParser() ; 
    cout << "Running " << mNumWorms << " worms." << endl ; 

    // This is the code used in WormSimEval (used by EvoAnnealDriver).
    // mWormShuffler = new SetRadWormShuffler(newMap->getDiameter(),newMap->getDiameter()/4.0) ;
    mWormShuffler = new SetRadWormShuffler(mDiameter, mDiameter/4.0) ; 

    for(int i = 0; i < mNumWorms ; i++) {

        // Create an instance of a network and an evaluator
        BlitzLiveNet *blitzLiveNet = new BlitzLiveNet( netParser->parseFile( mNetworkFile ) ); 
        blitzLiveNet->setEvaluator(createEvaluator()) ; 
        (  ( (BlitzEulerLiveNetEvaluator*) blitzLiveNet->getEvaluator() ) )->setNetwork(blitzLiveNet) ; 
        Worm* newWorm = new Worm(mMapSpace) ; 
        newWorm->setForwardMovementModel(new UniformFwdMovement(0.0,0.0)) ; 
        newWorm->setTurningMovementModel(new SharpTurnMovementModel(50.0)) ;
	
        newWorm->setTurningThreshold(50.0) ;
	newWorm->setForwardVelocity(mFwdVelocity) ; // 0.015
        newWorm->setPirouetteVelocity(mPirVelocity) ; // 0.011
        newWorm->setBehaviorModel(new UniformNetBehaviorModel( blitzLiveNet,newWorm) ) ;

	// Give the worm a random position and direction
	mWormShuffler->shuffleWorm( newWorm) ; 

        mMapSpace->addWorm(newWorm) ;
    }

    delete mWormShuffler ;

    // Print out initial positions of worms
    // mMapSpace->printWorms(MapSpace::VERB_SOME) ;
}


/************************************************************************************
*    createEvaluator() 
*/
NetEvaluator* EvoDriver::createEvaluator() 
{
    BlitzEulerLiveNetEvaluator* evaluator = new BlitzEulerLiveNetEvaluator() ;    
    vector<double>* relaxVector = new vector<double>(1) ; 
    (*relaxVector)[0] = 0.5 ; 
    evaluator->setRelaxValue(relaxVector) ; 
    evaluator->setRelaxTime(mRelaxTime) ; 
    evaluator->setRelaxDeltaT(1.0) ; 
    evaluator->setRelaxTau(3.0) ; 
//    evaluator->setRelaxLimit(0.001) ; 
//    evaluator->setGlobalSigLimit(8.0) ; 
    evaluator->resetTrace(mNumIters,mNumIters) ; 
    return evaluator ;
}


/*  ***********************************************************************************
    runapp() */
   
//! Create a network and an evaluator. Make the call to evaluate the network.
/*  *********************************************************************************** */
bool EvoDriver::runapp(){

    cout << "A" << endl ; 
    cout << "mNumIters: '" << mNumIters << "'" << endl ; 
    cout << "B" << endl ; 
    cout << "mDescript: '" << mDescript << "'" << endl ; 
    cout << "C" << endl ; 
    cout << "mTestType: '" << mTestValue << "'" << endl ; 

    int wormState = MapSpace::SOME_RUNNING ; 

    // init mapdata to space
    initMap() ; 

    // init worms
    initWorms() ; 

    WormMapStats* statMachine = new WormMapStats(mMapSpace) ; 
    Logger* theLogger = Logger::getLogger("trace.txt") ; 
    string header = "x\ty\tmapvalue\tprob\tdecision\tbehavior" ; 
    theLogger->log(header) ; 

    // Run worms for N iterations
    for(int i = 0 ; i < mNumIters ; i++){
        wormState = mMapSpace->moveWorms() ; 
        // mMapSpace->printWorms(MapSpace::VERB_LOTS) ;  // to output every turn
    }

    cout << mMapSpace->getNumDied() << " worms died" << endl;
    cout << "mean value: " << statMachine->getMeanValue() << endl ; 
    cout << "distance from center: " << statMachine->getMeanDistanceFromCenter() << endl ; 
    cout << "distance from radius: " << statMachine->getMeanDistanceFromRadius() << endl ; 
    cout << "mean live value: " << statMachine->getMeanLiveValue() << endl ; 
    cout << "live distance from center: " << statMachine->getMeanLiveDistanceFromCenter() << endl ; 
    cout << "live distance from radius: " << statMachine->getMeanLiveDistanceFromRadius() << endl ; 

    // Prints worms to trace.txt
    mMapSpace->printWorms(MapSpace::VERB_LOTS) ; 
}


/*  ***********************************************************************************
    message() */
   
//! Description here.
/*  *********************************************************************************** */
int EvoDriver::message(string caption,string text) 
{
    return QMessageBox::information((QtFlatRenderer*) mRenderer,caption.c_str(),text.c_str(),QMessageBox::Ok) ; 
}


/*  ***********************************************************************************
    setRenderer() */
   
//! Description here.
/*  *********************************************************************************** */
void EvoDriver::setRenderer(Renderer* newRenderer) 
{
    mRenderer = newRenderer ; 
}


/*  ***********************************************************************************
    creaetLocalMaps() */
   
//! Add items to GUI
/*  *********************************************************************************** */
bool EvoDriver::createLocalMaps() 
{
    string APP_NAME = "APP/SIMWORM" ; 
    addCommandToMap(START_SIMWORM) ;

    // The number in the first parameter ("##_") indicates the order of placement in the GUI
    addOptionToMap("01_network",OPT_FILE_LOAD,&mNetworkFile,APP_NAME,"Network File") ; 
    addOptionToMap("02_diameter",OPT_DOUBLE,&mDiameter,APP_NAME,"Map Diameter") ; 
    addOptionToMap("03_hightemp",OPT_DOUBLE,&mHighTemp,APP_NAME,"High Temp on Map") ; 
    addOptionToMap("04_lowtemp",OPT_DOUBLE,&mLowTemp,APP_NAME,"Low Temp on Map") ; 
    addOptionToMap("05_fvelocity",OPT_DOUBLE,&mFwdVelocity,APP_NAME,"Forward Velocity of Worms") ; 
    addOptionToMap("06_pvelocity",OPT_DOUBLE,&mPirVelocity,APP_NAME,"Pirouette Velocity of Worms") ; 
    addOptionToMap("08_relaxtime",OPT_DOUBLE,&mRelaxTime,APP_NAME,"Time to relax network.") ; 
    addOptionToMap("09_numworms",OPT_INT,&mNumWorms,APP_NAME,"Number of Worms") ; 
    addOptionToMap("10_numiters",OPT_INT,&mNumIters,APP_NAME,"Number of Iterations") ;

    mTestType = new vector<string>() ; 
    mTestType->push_back("item change") ; 
    mTestType->push_back("item 1") ; 
    mTestType->push_back("item last") ; 
    addOptionToMap("12b_type",LIST_TYPE,&mTestValue,APP_NAME,"Test Type", (new TiListParser())->createList(mTestType) ) ; 
    addOptionToMap("13_descript",OPT_STRING,&mDescript,APP_NAME,"Description Text") ; 

    return true ; 
}


/*  ***********************************************************************************
    doLocalCommand() */
   
//! Description here.
/*  *********************************************************************************** */
string EvoDriver::doLocalCommand(Command *theCommand) 
{
    mRenderer->savePreferences() ; 

    string theName = theCommand->getName()  ;
    if(theName==START_SIMWORM){
         runapp() ; 
    }
    return "it runned  "; 
}




const string EvoDriver::START_SIMWORM = "START_SIMWORM"  ; 




/* Modeline for ViM {{{
 * vim:set ts=4:
 * vim600:fdm=marker fdl=0 fdc=3:
 * }}} */


