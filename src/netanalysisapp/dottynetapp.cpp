
#include <iostream>
using std::cout ; 
using std::endl ; 

#include <string>
using std::string ; 

#include <vector>
using std::vector ; 

#include <float.h>

#include "BlitzNet.hpp" 
#include "RNG.hpp" 
#include "StepFeeder.hpp"   
#include "SetFeeder.hpp"   
#include "FileFeeder.hpp"   
#include "AutoWKineticBlitzEulerEval.hpp"   
#include "BlitzNetAnnealer.hpp"   
#include "TempSchedule.hpp" 
#include "PowerTempSchedule.hpp" 
#include "NetPerturber.hpp" 
#include "RNG.hpp" 
#include "TextEvalTrace.hpp" 

#include <qapplication.h>
#include <QtFlatRenderer.h>
#include <TiAppParser.hpp>
#include <AppInterfaceXmlEngine.hpp>
#include <TinyAppInterfaceXmlEngine.hpp>
#include <Command.hpp>
#include <DottyNetDriver.hpp>
#include <BaseFlatDriver.hpp>

#include "dottynetapp.hpp"



/*  ***********************************************************************************
    Constructor */
   
//! Empty body. Sends "newApp" argument to BaseFlatDriver constructor.
/*  *********************************************************************************** */
dottynetapp::dottynetapp(AppInterface* newApp)  : BaseFlatDriver(newApp)
{
}


/*  ***********************************************************************************
    main() */
   
//! Creates GUI and sets an instance of DottyNetDriver as its application.
/*  *********************************************************************************** */
/** Function int main(int argc, char **argv) {{{ */
int main(int argc, char **argv)
{
    RNG::initSeed() ; 

    try{
        DottyNetDriver* newApp = new DottyNetDriver("APP","PRUNER",NULL) ;
        dottynetapp* driver = new dottynetapp(newApp) ;

	
        QApplication* qapp = new QApplication(argc,argv) ; 
        driver->setBaseAppName("PRUNER") ; 
        driver->setPrefName("dottynetapp") ; 
        driver->setPrefUrl("precog.uoregon.edu") ;
        qapp->setMainWidget(driver->initGui() ) ;
	return qapp->exec() ;
	
    }
    catch(string theErrorString){
        cout << "theErrorString: " << theErrorString << endl ; 
    }
    catch(const char* errorString){
        cout << "error: " << errorString << endl ; 
    }
    catch(...){
        cout << "general error" << endl ; 
    }





} /* }}} */



/* Modeline for ViM {{{
 * vim:set ts=4:
 * vim600:fdm=marker fdl=0 fdc=3:
 * }}} */

// -*- C++ -*-



