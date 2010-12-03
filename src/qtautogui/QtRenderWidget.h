#ifndef QTRENDERWIDGET_HPP_
#  define QTRENDERWIDGET_HPP_

#include <CommandButton.hpp>
#include <NameHandler.hpp>
#include <qwidget.h>


class QtRenderWidget : public CommandButton , public QWidget {

public:
    QtRenderWidget(const QString & text, QWidget *parent, const char* name = 0 ,Renderer *referenceObject = 0,string type="") ;
    void updateOption()  ; 

} ;

#endif /* ifndef QTRENDERWIDGET_H */
// -*- C++ -*-
// FILE: "/Users/ndunn/cvs/auto3TWOINPUTSTEP/src/qtautogui/QtRenderWidget.h"
// LAST MODIFICATION: "Sat, 27 Dec 2003 18:37:28 -0800 (ndunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: QtRenderWidget.h,v 1.2 2004/01/13 20:43:36 ndunn Exp $

