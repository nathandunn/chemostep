// -*- C++ -*-
// FILE: "/Users/ndunn/cvs/auto3TWOINPUTSTEP/src/qtautogui/QtFileSaveField.h"
// LAST MODIFICATION: "Sun, 28 Dec 2003 17:14:58 -0800 (ndunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: QtFileSaveField.h,v 1.2 2004/01/13 20:43:36 ndunn Exp $

#ifndef QTFILESAVEFIELD_HPP_
#define QTFILESAVEFIELD_HPP_

#include "QtFileLoadField.h"

#include "NameHandler.hpp"
#include "CommandButton.hpp"

#include <qframe.h>

#include <iostream>
using std::cout ; 
using std::endl ; 


class QFileDialog ; 
class QPushButton ; 
class QLineEdit ; 
class QBoxLayout ; 


/**
 *  An option field for Qt which will fire events to the 
 *  caller application when a field has been changed.  
 *  Additionally, it records where the field was within the interface.  
 *
 */
class QtFileSaveField :  public QtFileLoadField{

    Q_OBJECT 

public:
    QtFileSaveField(const QString & text, QWidget *parent, const char* name = 0 ,Renderer *referenceObject = 0,string type="") ; 

public slots:
	virtual void loadFile() ; 

} ; 


#endif


