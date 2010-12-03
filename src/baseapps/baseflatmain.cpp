
#include <iostream>
using std::cout ; 
using std::endl ; 

#include <qapplication.h>

#include "BaseFlatDriver.hpp"

#include "TiFlatBaseApp.hpp"


/* Function int main(int argc, char **argv) {{{ */
int main(int argc, char **argv)
{
    cout << "running baseFlatdriver" << endl ; 
    // need to construct a QApplication object before any additional QWidget objects are constructed
    QApplication *qapp = new QApplication(argc,argv,true) ; 

//    // define THIS driver
//    // define application  TiFlatBaseApp
    BaseFlatDriver *driver = new BaseFlatDriver(new TiFlatBaseApp("APP","BASEAPP",NULL)) ; 
    driver->setBaseAppName("FLATBASEAPP") ;
    driver->setPrefName("tiflatbaseapp") ;
    driver->setPrefUrl("precog.uoregon.edu") ;

    qapp->connect( qapp, SIGNAL( lastWindowClosed() ), qapp, SLOT( quit() ) );
    qapp->setMainWidget(driver->initGui()) ; 
    return qapp->exec();
} /* }}} */


/* Modeline for ViM {{{
 * vim:set ts=4:
 * vim600:fdm=marker fdl=0 fdc=3:
 * }}} */

// -*- C++ -*-
// FILE: "/home/ndunn/tla/auto3--dev--1.3.3--base-0/src/baseapps/baseflatmain.cpp"
// LAST MODIFICATION: "Thu, 18 Mar 2004 12:00:06 -0800 (ndunn)"
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

