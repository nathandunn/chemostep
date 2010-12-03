/*
 * $Id$
 */

#include <iostream>
using std::cout ; 
using std::endl ; 

#include <TinyAppInterfaceXmlEngine.hpp>
#include <AppInterface.hpp>
#include <Renderer.hpp>
#include <TiFlatBaseApp.hpp>
#include <TiAppParser.hpp>
#include <QtFlatRenderer.h>

// qt calls
#include <qapplication.h>
#include <qwidget.h>

#include "BaseFlatDriver.hpp"




BaseFlatDriver::BaseFlatDriver(AppInterface* newApp) :
mApp(newApp),
mRenderer(NULL),
mXmlRenderer(NULL),
mBaseAppName("APP/BASEAPP"),
mPrefName("baseflatdriver"),
mPrefUrl("uoregon.precog.edu")
{
}


string BaseFlatDriver::transmitXml(string xmlMessage) 
{
    return mXmlRenderer->doXmlCommand(xmlMessage,mApp) ; 
}

void BaseFlatDriver::setRenderer(Renderer* newRenderer) 
{
    mRenderer = newRenderer ; 
}

QWidget* BaseFlatDriver::initGui() {
    // create map for application 
    mApp->createLocalMaps() ; 
    
    // define xml engine for transmitterApp (can be done internally?)
    // so it knows who handles xml commands and who to pass them off to
    mXmlRenderer = new TinyAppInterfaceXmlEngine(mApp) ; 


    // define the renderer for the tranmitterApp 
    mRenderer  =  new QtFlatRenderer(this,new TiAppParser()) ;
    mRenderer->setPreferenceRoot(mPrefName) ; 
    mRenderer->setPreferenceURL(mPrefUrl) ; 
    mRenderer->loadAppToMap(mXmlRenderer->toXml()) ; 
    mRenderer->renderAppToGui() ; 
    ((QtFlatRenderer*) mRenderer)->setMinimumSize(550,400) ; 
    ((QtFlatRenderer*) mRenderer)->show() ; 

    // make sure the app knows about the renderer in order to save preferences
    // but only for that reason, maybe change this later
    ((TiFlatBaseApp*) mApp)->setRenderer(mRenderer) ; 
    mRenderer->loadPreferences() ; 

    // return the renderer
    return (QtFlatRenderer*) mRenderer ; 
}

void BaseFlatDriver::setXmlEngine(AppInterfaceXmlEngine* newXmlEngine) 
{
    mXmlRenderer = newXmlEngine ; 
}

void BaseFlatDriver::setApp(AppInterface* newApp) 
{
    mApp = newApp ; 
}


Renderer* BaseFlatDriver::getRenderer()  
{
    return mRenderer ; 
}







/* Modeline for ViM {{{
 * vim:set ts=4:
 * vim600:fdm=marker fdl=0 fdc=3:
 * }}} */

// -*- C++ -*-
// FILE: "/Users/nathandunn/tla/auto3--dev--1.3.2--patch-8/src/baseapps/BaseFlatDriver.cpp"
// LAST MODIFICATION: "Wed, 17 Mar 2004 18:05:15 -0800 (nathandunn)"
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

