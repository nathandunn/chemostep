// -*- C++ -*-
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: QtTypeField.h,v 1.2 2004/01/13 20:43:36 ndunn Exp $

#ifndef QTTYPEFIELD_HPP_
#define QTTYPEFIELD_HPP_

#include <qcombobox.h>
#include "NameHandler.hpp"
#include "CommandButton.hpp"

#include <iostream>
using std::cout ; 
using std::endl ; 


#include <vector>
using std::vector ; 


/**
 *  An option field for Qt which will fire events to the 
 *  caller application when a field has been changed.  
 *  Additionally, it records where the field was within the interface.  
 *
 */
class QtTypeField : public QComboBox, public CommandButton {

    Q_OBJECT 

public:
    QtTypeField(vector<string> *valueMap, QWidget *parent, const char* name = 0 ,Renderer *referenceObject = 0,string type="") ; 

public slots:
    virtual void updateOption(int n=0) ; 
    virtual void updateOption(const QString & string) ; 
    virtual void setList(string xmlList) ; 
    virtual void setList(vector<string>* newList) ; 


protected:
	int mNumOptions ; 
    int mSelectedOption ; 
    vector<string>* mOptionVector  ; 


} ; 


#endif


