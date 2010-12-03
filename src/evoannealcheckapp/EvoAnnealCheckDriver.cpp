
#define CHAR_LENGTH 256

#include <iostream>
using std::cout ; 
using std::endl ; 
using std::ostream ; 

#include <fstream>
using std::ofstream ; 

#include <string>
using std::string ; 

#include <vector>
using std::vector ; 

#include <float.h>
#include <time.h>

#include "SeqCheckBlitzNetAnnealer.hpp"
#include "MomentumPowerTempSchedule.hpp" 
#include <AcceptModel.hpp>

#ifdef DOMPI
    #include "mpi.h"
    int check_id ; 
    char realCheckCommand[128] = "wait"  ; 
#endif 

#include "EvoAnnealDriver.hpp"
#include "EvoAnnealCheckDriver.hpp"


/*  ***********************************************************************************
    Constructor */
   
//! Description here.
/*  *********************************************************************************** */
EvoAnnealCheckDriver::EvoAnnealCheckDriver(string newInterfaceName,string newTypeName,AppInterface* newParent)  :
EvoAnnealDriver(newInterfaceName,newTypeName,newParent) 
{
    /*
#ifdef DOMPI
    MPI_Comm_rank(MPI_COMM_WORLD,&check_id) ; 
#endif
    */
}

/*
BlitzNetAnnealer* EvoAnnealCheckDriver::createAnnealer() 
{
    MomentumPowerTempSchedule* tempSchedule= new MomentumPowerTempSchedule(mNumTempSteps,mPower,mTempConstant,mHighTemp,mLowTemp) ;

    BlitzNetAnnealer* returnAnnealer = new SeqCheckBlitzNetAnnealer() ;
    returnAnnealer->setSetBack(mSetBack) ; 
    returnAnnealer->setBackStep(mBackStep) ; 
    returnAnnealer->setTempSchedule(tempSchedule) ; 
    returnAnnealer->setIterPerTemp(mNumItersPerTemp) ;
    ((SeqCheckBlitzNetAnnealer *) returnAnnealer)->setNumChecks(mNumChecks) ; 
    ((SeqCheckBlitzNetAnnealer *) returnAnnealer)->setMinInitialImprovement(mMinInitialImprovement) ;
    // ! Need to change the acceptModel here
    returnAnnealer->setAcceptModel(new AcceptModel()) ; 
    return returnAnnealer ;
}
*/

/*  ***********************************************************************************
    creaetLocalMaps() */
   
//! Add items to GUI
/*  *********************************************************************************** */
/*
bool EvoAnnealCheckDriver::createLocalMaps() 
{
    EvoAnnealDriver::createLocalMaps();
    string APP_NAME = "APP/SIMWORM" ; 
    addOptionToMap("07a_network",OPT_INT,&mNumChecks,APP_NAME,"Number of Checks") ; 
    addOptionToMap("07b_network",OPT_DOUBLE,&mMinInitialImprovement,APP_NAME,"Min Initial Improvement (0,1)") ; 
    return true ; 
}


#ifdef DOMPI
void EvoAnnealCheckDriver::syncData() 
{
    char fileName[CHAR_LENGTH]; 

    MPI_Bcast(&mNumChecks,1,MPI_INT,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mMinInitialImprovement,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mNumWorms,1,MPI_INT,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mNumWormSteps,1,MPI_INT,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mForwardVelocity,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mTurnVelocity,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mDeltaT,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mHighMapValue,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mLowMapValue,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mDiameter,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mHighTemp,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mLowTemp,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mSetBack,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mPower,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mNumItersPerTemp,1,MPI_INT,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mTempConstant,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mNumTempSteps,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mNumNetworks,1,MPI_INT,0,MPI_COMM_WORLD) ; 
    MPI_Bcast(&mCriticalAcceptance,1,MPI_DOUBLE,0,MPI_COMM_WORLD) ; 
    mRelaxTime = 0.0 ; 
    if(check_id==0) sprintf(fileName,"%s",mOutputFile.c_str()) ; 
    MPI_Bcast(fileName, CHAR_LENGTH,MPI_CHAR,0,MPI_COMM_WORLD) ; 
    if(check_id!=0) mOutputFile=fileName ; 
    if(check_id==0) sprintf(fileName,"%s",mNetworkFile.c_str()) ; 
    MPI_Bcast(fileName, CHAR_LENGTH,MPI_CHAR,0,MPI_COMM_WORLD) ; 
    if(check_id!=0) mNetworkFile=fileName ; 

}

#endif

*/

/* Modeline for ViM {{{
 * vim:set ts=4:
 * vim600:fdm=marker fdl=0 fdc=3:
 * }}} */




