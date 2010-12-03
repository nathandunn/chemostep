// -*- C++ -*-

/**
 *  A Qt push-button class that allows itself to be looked up
 *  for both name and location within the Gui, so that it knows
 *  what commands will need to be passed.
 */

#ifndef QTCOMMANDBUTTON_HPP_
#define QTCOMMANDBUTTON_HPP_

#include <qpushbutton.h>

#include "CommandButton.hpp" 

class QtCommandButton : public QPushButton , public CommandButton {

    Q_OBJECT 

public:
    QtCommandButton(const QString & text, QWidget *parent, const char* name = 0 ,Renderer *referenceObject = 0,string type="") ; 

public slots:
    virtual void convertClicked() ; 


signals:
    virtual void clickedCommand() ; 

} ; 


#endif 




