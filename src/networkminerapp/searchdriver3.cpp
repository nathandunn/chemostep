/*
 * $Id$
 */

#include <iostream>
using std::cout ; 
using std::endl ; 

#include "SymmParser.hpp"
#include "NetDataParser.hpp"
#include "searchdriver3.hpp"

#include <string>
using std::string ; 

#include <BaseFlatDriver.hpp>
#include <QtFlatRenderer.h>

#include <qapplication.h>

searchdriver3::searchdriver3(AppInterface *newApp)  : BaseFlatDriver(newApp)
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
            searchdriver3* driver = new searchdriver3(serverApp) ; 
            driver->setBaseAppName("searchdriver3") ; 
            driver->setPrefName("searchdriver3") ; 

            qapp->connect( qapp, SIGNAL( lastWindowClosed() ), qapp, SLOT( quit() ) );
            qapp->setMainWidget( driver->initGui()) ; 
            return qapp->exec();

} /* }}} */


/* Modeline for ViM {{{
 * vim:set ts=4:
 * vim600:fdm=marker fdl=0 fdc=3:
 * }}} */

// -*- C++ -*-
// FILE: "/Users/nathandunn/tla/auto3--dev--1.3.4--patch-1/src/networkminerapp/searchdriver3.cpp"
// LAST MODIFICATION: "Mon, 05 Apr 2004 11:39:21 -0700 (nathandunn)"
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

