
#define CHAR_LENGTH 256

#include <iostream>
using std::cout ; 
using std::endl ; 
using std::ostream ; 
using std::ostringstream ; 

#include <fstream>
using std::ofstream ; 

#include <string>
using std::string ; 

#include <vector>
using std::vector ; 

#include <memory>
using namespace std ;

#include <float.h>
#include <time.h>


// net stuff
#include "BlitzLiveNet.hpp"
#include "DotNetConverter.hpp"
//#include <Note.hpp> 


// gui stuff
#include <QtFlatRenderer.h>
#include <TiAppParser.hpp>
#include <TiListParser.hpp>
#include <Command.hpp>
#include <AppInterface.hpp>
#include <TinyBzNetParser.hpp>




#include "DottyNetDriver.hpp"




/*  ***********************************************************************************
    Constructor */
   
//! Description here.
/*  *********************************************************************************** */
DottyNetDriver::DottyNetDriver(string newInterfaceName,string newTypeName,AppInterface* newParent)  :
TiFlatBaseApp(newInterfaceName,newTypeName,newParent) 
{
   description = "Kinetic annealer.  Produces 1 to N." ; 
   RNG::initSeed();
}



bool DottyNetDriver::createLocalMaps() 
{
    string APP_NAME = "APP/PRUNER" ; 
    addCommandToMap(START_PLOTTER) ; 
    addOptionToMap("01_network",OPT_FILE_LOAD,&mNetworkFile,APP_NAME,"Network File") ; 
    addOptionToMap("02_outfile",OPT_FILE_SAVE,&mOutputFile,APP_NAME,"Output File") ; 
//    addOptionToMap("04_numinputs",OPT_INT,&mNumInputs,APP_NAME,"Num Inputs") ; 
//    addOptionToMap("05_numoutputs",OPT_INT,&mNumOutputs,APP_NAME,"Num Outputs") ; 

//    mTempType = new vector<string>() ; 
//    mTempType->push_back("none") ; 
//    mTempType->push_back("dotty") ; 
//    mTempType->push_back("omnigraffle") ; 
//    addOptionToMap("08_linetype",LIST_TYPE,&mActionType,APP_NAME,"Action",(new TiListParser())->createList(mTempType)) ; 



    return true ; 
}


/*  ***********************************************************************************
    doLocalCommand() */
   
//! Description here.
/*  *********************************************************************************** */
string DottyNetDriver::doLocalCommand(Command *theCommand) 
{
    mRenderer->savePreferences() ; 

    string theName = theCommand->getName()  ;

    if(theName==START_PLOTTER){
           startPlotter() ; 
    } 
    
    return "it runned  "; 
}



void* DottyNetDriver::startPlotter() 
{
    BlitzLiveNet* newNet = (BlitzLiveNet*) (new TinyBzNetParser())->parseFile(mNetworkFile) ;

    int titleHeader = mNetworkFile.find_last_of("/") ; 
    int titleSuffix = mNetworkFile.find_last_of(".xml")-4 ; 
    int outputHeader = mOutputFile.find_last_of("/")+1 ; 
    string newTitle =   mNetworkFile.substr( titleHeader+1, titleSuffix-titleHeader) ; 
    string newOutput = mOutputFile.substr(0,outputHeader)+newTitle+".dot" ;

    string dottyString = DotNetConverter::createGraph( newNet,newTitle) ; 

    ofstream *returnstream = new ofstream(newOutput.c_str(), ios::out) ; 
    *returnstream << dottyString << endl ; 
    returnstream->close() ; 

}


const string DottyNetDriver::START_PLOTTER = "START_PLOTTER"  ; 




/* Modeline for ViM {{{
 * vim:set ts=4:
 * vim600:fdm=marker fdl=0 fdc=3:
 * }}} */




