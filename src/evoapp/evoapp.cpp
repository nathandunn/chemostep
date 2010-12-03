
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
#include <EvoDriver.hpp>
#include <BaseFlatDriver.hpp>

#include "evoapp.hpp"

#ifdef DOMPI
    #include "mpi.h"
    int mpi_myid ; 
    int mpi_nprocs ; 
#endif 


/*  ***********************************************************************************
    Constructor */
   
//! Empty body. Sends "newApp" argument to BaseFlatDriver constructor.
/*  *********************************************************************************** */
evoapp::evoapp(AppInterface* newApp)  : BaseFlatDriver(newApp)
{
}


/*  ***********************************************************************************
    main() */
   
//! Creates GUI and sets an instance of EvoDriver as its application.
/*  *********************************************************************************** */
/** Function int main(int argc, char **argv) {{{ */
int main(int argc, char **argv)
{
    #ifdef DOMPI
        MPI_Init(&argc,&argv) ; 
        MPI_Comm_rank(MPI_COMM_WORLD,&mpi_myid) ; 
        MPI_Comm_size(MPI_COMM_WORLD,&mpi_nprocs) ; 
        cout << "I am: " << mpi_myid << "/" << mpi_nprocs << endl ;  
        int seed ;
	
        if(mpi_myid==0){
	    seed = RNG::initSeed() ; 
        }
	
        MPI_Bcast(&seed, 1, MPI_INT, 0, MPI_COMM_WORLD);
        RNG::setSeed(seed+mpi_myid);
    #else
        RNG::initSeed() ; 
    #endif 

    try{
        EvoDriver* newApp = new EvoDriver("APP","ANNEALER",NULL) ; 
        evoapp* driver = new evoapp(newApp) ;

        QApplication* qapp = new QApplication(argc,argv) ; 
        driver->setBaseAppName("ANNEALER") ; 
        driver->setPrefName("evoapp") ; 
        driver->setPrefUrl("precog.uoregon.edu") ;
	// driver->setPrefUrl("gerromorpha.cs.uoregon.edu");
        qapp->connect( qapp, SIGNAL( lastWindowClosed() ), qapp, SLOT( quit() ) );
        qapp->setMainWidget(driver->initGui() ) ; 
        return qapp->exec();
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


