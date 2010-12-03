// -*- C++ -*-
// FILE: "/Users/ndunn/cvs/auto3TWOINPUTSTEP/src/qtautogui/QtBoolField.h"
// LAST MODIFICATION: "Sat, 27 Dec 2003 19:18:22 -0800 (ndunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: QtBoolField.h,v 1.2 2004/01/13 20:43:36 ndunn Exp $

#ifndef QTBOOLFIELD_HPP_
#define QTBOOLFIELD_HPP_

#include <qcheckbox.h>
#include "NameHandler.hpp"
#include "CommandButton.hpp"

#include <iostream>
using std::cout ; 
using std::endl ; 

/**
 *  An option field for Qt which will fire events to the 
 *  caller application when a field has been changed.  
 *  Additionally, it records where the field was within the interface.  
 *
 */

class QtBoolField : public QCheckBox, public CommandButton {

    Q_OBJECT 

public:
    QtBoolField(const QString & text, QWidget *parent, const char* name = 0 ,Renderer *referenceObject = 0,string type="") ; 

public slots:
//    virtual void updateOption(const QString &) ; 
    virtual void updateOption(bool newOption) ; 



} ; 


#endif


