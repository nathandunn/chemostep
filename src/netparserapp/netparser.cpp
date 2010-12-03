/*
 * $Id$
 */

#include <iostream>
using std::cout ; 
using std::endl ; 

#include "SymmParser.hpp"
#include "NetDataParser.hpp"
#include "netparser.hpp"

#include <string>
using std::string ; 

#include <BaseFlatDriver.hpp>
#include <QtFlatRenderer.h>

#include <qapplication.h>

netparser::netparser(AppInterface *newApp)  : BaseFlatDriver(newApp)
{
}




int usage(){
    cout << "Usage: parseData <inputfile> <outputfile>" << endl ; 
    return 1 ;  // fail code, I guess
}


/* Function int main(int argc, char **argv) {{{ */
int main(int argc, char **argv)
{
    QApplication *qapp = new QApplication(argc,argv,true) ; 
    SymmParser* serverApp = new SymmParser("APP","SymmParser",NULL)  ; 
    netparser* driver = new netparser(serverApp) ; 
    driver->setBaseAppName("NetParser") ; 
    driver->setPrefName("netparser") ; 

    qapp->connect( qapp, SIGNAL( lastWindowClosed() ), qapp, SLOT( quit() ) );
    qapp->setMainWidget( driver->initGui()) ; 
    return qapp->exec();
} /* }}} */


/* Modeline for ViM {{{
 * vim:set ts=4:
 * vim600:fdm=marker fdl=0 fdc=3:
 * }}} */

// -*- C++ -*-
// FILE: "/Users/ndunn/tla/auto3--updateminer--1.3.4--patch-3/src/netparserapp/netparser.cpp"
// LAST MODIFICATION: "Mon, 05 Apr 2004 20:42:32 -0700 (ndunn)"
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

