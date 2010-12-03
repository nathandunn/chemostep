#ifndef EVODRIVER_HPP_
#  define EVODRIVER_HPP_


#include <TiFlatBaseApp.hpp>

#include <vector>
using std::vector ; 


class Worm ; 
class MapData ; 
class MapSpace ; 
class TinyBzNetParser ; 
class TinyAppInterfaceXmlEngine ;
class SetRadWormShuffler ;
/**
 *  This class runs that actual Annealer. 
 *
 *  \todo Add MapSpace
 *  \todo Add Make sure worms are being added.
*   \todo Are worms running?
*   \todo Train dem worms!
 *
 */

class EvoDriver : public TiFlatBaseApp {

public:
//    EvoDriver() ; 
    EvoDriver(string newInterfaceName, string newTypeName, AppInterface* newParent) ; 
    bool runapp() ; 
    int message(string caption,string text) ; 
    void setRenderer(Renderer* newRenderer) ; 


    // AppInterface classes
    bool createLocalMaps() ; 
    string doLocalCommand(Command *theCommand) ; 


    // commands
    const static string START_SIMWORM ; 

protected:
    string mNetworkFile; 
    double mStimDeltaT ; 
    double mRelaxTime ; 
    int mNumWorms ; 
    double mHighTemp ; 
    double mLowTemp ; 
    double mDiameter ; 
    int mNumIters ; 
    double mFwdVelocity ;
    double mPirVelocity ;
    double mOutputBias ;
    vector<string>* mTestType ; 
    string mTestValue ; 
    string mDescript ; 
    
private:
    // simulation variables 
    MapData* mMap  ; 
    MapSpace *mMapSpace  ; 
    TinyBzNetParser* mParser ;
    SetRadWormShuffler* mWormShuffler ;
    void initWorms() ; 
    void initMap() ; 
    NetEvaluator* createEvaluator() ; 



} ;

#endif /* ifndef ANNEALERDRIVER_H */
// -*- C++ -*-
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: EvoDriver.hpp,v 1.3 2004/01/27 20:27:19 ndunn Exp $

