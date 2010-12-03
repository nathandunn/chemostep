// -*- C++ -*-
// FILE: "/Users/ndunn/tlalocal/auto3--localdev--1.3.3--base-0/src/qtautogui/QtFileSaveField.cpp"
// LAST MODIFICATION: "Thu, 18 Mar 2004 13:51:57 -0800 (ndunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: QtFileSaveField.cpp,v 1.2 2004/01/13 20:43:36 ndunn Exp $

#include "QtFileSaveField.h"

#include "NameHandler.hpp" 
#include "CommandButton.hpp" 
#include "Renderer.hpp" 

#include <qfiledialog.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qframe.h>
#include <qlayout.h>

#include "QtFileLoadField.h"

QtFileSaveField::QtFileSaveField(const QString & text, QWidget *parent, const char* name,Renderer *referenceObject, string newType) :   QtFileLoadField(   text,parent,name ,referenceObject,newType) 
{
}

void QtFileSaveField::loadFile() 
{
    QString fileName  = QFileDialog::getSaveFileName(fileNameField->text().ascii()) ; 
    // returns QString::null on cancel
    if(fileName != QString::null){
        fileNameField->setText(fileName) ; 
        updateOption() ;   
    }
    else{
        cout << "NOT SAVING" << endl ; 
    }
}






