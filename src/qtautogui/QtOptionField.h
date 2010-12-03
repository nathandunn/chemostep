// -*- C++ -*-

#ifndef QTOPTIONFIELD_HPP_
#define QTOPTIONFIELD_HPP_

#include <qlineedit.h>
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

class QtOptionField : public QLineEdit , public CommandButton {

    Q_OBJECT ;

public:
    QtOptionField(const QString & text, QWidget *parent, const char* name = 0 ,Renderer *referenceObject = 0,string type="") ; 
    virtual void updateOption() ; 

public slots:
    virtual void updateOption(const QString &) ; 





} ; 


#endif


