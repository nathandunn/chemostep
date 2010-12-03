
#include <iostream>
using std::cout ; 
using std::endl ; 

#include "PerturbFrame.h"
#include <qframe.h>
#include <qlineedit.h>
#include <qpushbutton.h>

PerturbFrame::PerturbFrame(QWidget* parent) : QFrame(this)  
{
    QLineEdit* preN = new QLineEdit(parent) ; 
    QLineEdit* postN= new QLineEdit(parent) ; 
    QLineEdit* perturbValue = new QLineEdit(parent) ; 
    QPushButton* acceptButton = new QPushButton(parent) ; 

    connect ( acceptButton, SIGNAL( pressed() ), SLOT( hide() ) );

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
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>

