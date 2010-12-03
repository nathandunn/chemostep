// -*- C++ -*-
// FILE: "/Users/ndunn/cvs/auto3TWOINPUTSTEP/src/qtautogui/QtFileLoadList.h"
// LAST MODIFICATION: "Thu, 08 Jan 2004 14:24:20 -0800 (ndunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: QtFileLoadList.h,v 1.2 2004/01/13 20:43:36 ndunn Exp $

#ifndef QTFILELOADLIST_HPP_
#define QTFILELOADLIST_HPP_


#include "NameHandler.hpp"
#include "CommandButton.hpp"
#include <TiListParser.hpp> 


#include <iostream>
using std::cout ; 
using std::endl ; 

#include <vector>
using std::vector ; 

#include <qframe.h>
#include <qlayout.h>


class QPushButton ; 
class QListBox ; 
class QFileDialog ; 


/**
 *  An option field for Qt which will fire events to the 
 *  caller application when a field has been changed.  
 *  Additionally, it records where the field was within the interface.  
 *
 */
class QtFileLoadList :  public QFrame , public CommandButton {

    Q_OBJECT 

public:
    QtFileLoadList(const QString & text, QWidget *parent, const char* name = 0 ,Renderer *referenceObject = 0,string type="") ; 
    virtual string getListXml() ; 
    virtual vector<string>* getListVector() ; 
    virtual void setList(string xmlList) ; 
    virtual void setList(vector<string>* newList) ; 

public slots:
    virtual void updateOption() ; 
	virtual void editFile() ; 
	virtual void removeFile() ; 
	virtual void addFile() ; 
	virtual void moveSelectionDown() ; 
	virtual void moveSelectionUp() ; 
	virtual void clearFiles() ; 


protected:
    QPushButton* addFileButton ; 
    QPushButton* removeFileButton ; 
    QPushButton* clearFileButton ; 
    QPushButton* editFileButton ; 
    QPushButton* moveDownButton ; 
    QPushButton* moveUpButton ; 
    QBoxLayout* localLayout ; 
    QFileDialog* fileDialog ; 
    QListBox* fileBox ; 

} ; 


#endif


