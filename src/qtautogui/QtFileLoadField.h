// -*- C++ -*-
// FILE: "/Users/ndunn/cvs/auto3TWOINPUTSTEP/src/qtautogui/QtFileLoadField.h"
// LAST MODIFICATION: "Thu, 08 Jan 2004 13:41:08 -0800 (ndunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: QtFileLoadField.h,v 1.2 2004/01/13 20:43:36 ndunn Exp $

#ifndef QTFILELOADFIELD_HPP_
#define QTFILELOADFIELD_HPP_


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
class QtFileLoadField :  public QFrame , public CommandButton {

    Q_OBJECT 

public:
    QtFileLoadField(const QString & text, QWidget *parent, const char* name = 0 ,Renderer *referenceObject = 0,string type="") ; 

public slots:
    virtual void updateOption() ; 
	virtual void loadFile() ; 
	virtual string getFileName() ; 
	virtual void setFileName(string newFileName) ; 


protected:
	QLineEdit* fileNameField ; 
    QPushButton* loadFileNameButton ; 
    QBoxLayout* localLayout ; 
} ; 


#endif


