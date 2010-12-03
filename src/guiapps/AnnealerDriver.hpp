#ifndef ANNEALERDRIVER_HPP_
#  define ANNEALERDRIVER_HPP_


#include <TiFlatBaseApp.hpp>



class TinyAppInterfaceXmlEngine ; 
/**
 *  This class runs that actual Annealer. 
 *
 */

class AnnealerDriver : public TiFlatBaseApp {

public:
//    AnnealerDriver() ; 
    AnnealerDriver(string newInterfaceName, string newTypeName, AppInterface* newParent) ; 
    bool runapp() ; 
    int message(string caption,string text) ; 
    void setRenderer(Renderer* newRenderer) ; 
    #ifdef DOMPI
    void waitForCommand(char* command) ; 
    void syncData() ; 
    #endif



    // AppInterface classes
    bool createLocalMaps() ; 
    string doLocalCommand(Command *theCommand) ; 

    // options
    const static string HIGH_TEMP  ; 
    const static string LOW_TEMP  ; 
    const static string NUM_ITERS ; 
    const static string NUM_TEMPS ; 
    const static string SETBACK ; 
    const static string BACK_STEP ; 
    const static string VERBOSE ; 
    const static string NETWORK ; 
    const static string OUTPUT_NET ; 
    const static string LEFT_STIM_DELTAT; 
    const static string RIGHT_STIM_DELTAT; 
    const static string TARGET_DELTAT; 
    const static string LEFT_STIM_FILES; 
    const static string RIGHT_STIM_FILES; 
    const static string TARGET_FILES; 
    const static string RELAX_TIME ; 
    const static string NUM_NETWORKS ; 
    const static string SIG_LIMIT ; 
    const static string RELAX_DELTA_LIMIT ; 


    // commands
    const static string START_ANNEALER ; 

protected:
    double mHighTemp ; 
    double mLowTemp ; 
    double mBackStep ; 
    int mSetBack ; 
    int mNumIters ; 
    int mNumTemps; 
    bool mVerbose; 
    string mNetworkFile; 
    string mOutputNet ; 
    double mLeftStimDeltaT ; 
    double mRightStimDeltaT ; 
    double mTargetDeltaT ; 
    double mRelaxTime ; 
    vector<string>* mLeftStim ; 
    vector<string>* mRightStim ; 
    vector<string>* mTarget ; 
    int mNumNetworks; 
    double mSigLimit ; 
    double mRelaxDeltaLimit ; 

private:
    int procId ; 
    int gArgc  ; 
    char** gArgv  ; 
    bool doWait ; 
    int testInt ; 

} ;

#endif /* ifndef ANNEALERDRIVER_H */
// -*- C++ -*-
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: AnnealerDriver.hpp,v 1.3 2004/01/27 20:27:19 ndunn Exp $

