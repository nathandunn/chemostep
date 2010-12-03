// -*- C++ -*-
// (C) 2003 by Nathan Dunn, <ndunn@idiom.com>
// $Id: SearchAutoGui.cpp,v 1.13 2003/07/16 00:37:12 ndunn Exp $

#include <ConnectionPath.hpp> 
#include <BaseFlatDriver.hpp>
#include <SearchDriver.hpp>

#include "SearchAutoGui.hpp"


SearchAutoGui::SearchAutoGui(AppInterface *newApp) : BaseFlatDriver(newApp)
{
}


int main(int argc, char **argv)
{
    QApplication *qapp = new QApplication(argc,argv,true) ; 
    SearchDriver* serverApp = new SearchDriver("APP","SearchDriver",NULL)  ; 
    SearchAutoGui* driver = new SearchAutoGui(serverApp) ; 
    driver->setBaseAppName("SearchDriver") ; 
    driver->setPrefName("searchdriver") ; 
    qapp->connect( qapp, SIGNAL( lastWindowClosed() ), qapp, SLOT( quit() ) );
    qapp->setMainWidget( driver->initGui()) ; 
    return qapp->exec();
}


