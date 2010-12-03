/*
 * $Id: QtRenderWidget.cpp,v 1.2 2004/01/13 20:43:36 ndunn Exp $
 */

#include <iostream>
using std::cout ; 
using std::endl ; 

#include "QtRenderWidget.h"


QtRenderWidget::QtRenderWidget(const QString & text, QWidget *parent, const char* name,Renderer *referenceObject, string newType) : CommandButton( NameHandler::getNameFromPath(name) ,NameHandler::getAllButNameFromPath(name) ,newType , referenceObject)
{
//    connect(this,SIGNAL(lostFocus()),this,SLOT(updateOption())) ; 
}

void QtOptionField::updateOption() 
{
    if(edited()){
        ((Renderer*) thisParent)->setOptionFromGui( this,text().ascii() ) ; 
    }
}

/* Function int main(int argc, char **argv) {{{ */
//int main(int argc, char **argv)
//{


//    return 0;
//} /* }}} */


/* Modeline for ViM {{{
 * vim:set ts=4:
 * vim600:fdm=marker fdl=0 fdc=3:
 * }}} */

// -*- C++ -*-
// FILE: "/Users/ndunn/cvs/auto3TWOINPUTSTEP/src/qtautogui/QtRenderWidget.cpp"
// LAST MODIFICATION: "Sat, 27 Dec 2003 17:55:18 -0800 (ndunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: QtRenderWidget.cpp,v 1.2 2004/01/13 20:43:36 ndunn Exp $

