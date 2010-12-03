// -*- C++ -*-
// FILE: "/Users/nathandunn/cvs/NETWORK_MINER/src/SearchForm2.hpp"
// LAST MODIFICATION: "Thu, 10 Jul 2003 17:02:57 -0700 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@idiom.com>
// $Id: SearchForm2.hpp,v 1.16 2003/07/10 23:46:03 ndunn Exp $

#ifndef _SEARCHFORM2_
#define _SEARCHFORM2_

#include "SearchDriver.hpp"

#include <iostream.h>



#include <qnamespace.h>
#include <qfiledialog.h>
#include <qframe.h>
#include <qsplitter.h>
#include <qvgroupbox.h>
#include <qhgroupbox.h>
#include <qgroupbox.h>
#include <qlayout.h>
#include <qframe.h>
#include <qvalidator.h>
#include <qhbox.h>
#include <qlineedit.h>
#include <qbuttongroup.h>
#include <qlayout.h>
#include <qcheckbox.h>
#include <qapplication.h>
#include <qmainwindow.h>
#include <qpushbutton.h>
#include <qgrid.h>
#include <qspinbox.h>
#include <qlabel.h>
#include <qmessagebox.h>

class SearchDriver ;  

class SearchForm2 : public QMainWindow {

    Q_OBJECT  

public:  
     SearchForm2(QWidget *parent, const char *name = 0, SearchDriver *driver = 0 ) ; 
     virtual void initGui() ; 
    void addMessageGUI(string message) ; 
    
public slots:
    int startSearchNotify() ; 
    void stopSearchNotify() ; 
    void updateConnectionFile() ; 
    void updateNeuronFile() ; 
    void updateOutputFile() ; 
    void updateEdgeReportFile() ; 
//    void updateNodeReportFile() ; 
    void setDoPadBoxTrue() ; 


private:
   SearchDriver *driver  ; 
   QWidget  *parent; 

   // set defaults
   int checkInputs() ; 
   int saveDefaults() ; 
   void loadDefaults() ; 
   const static string DEFAULT_FILE ; 
       
   // search controls 
   QLineEdit *connectionFileField  ; 
   QPushButton *chooseConnectionFileButton  ;
   QLineEdit *neuronFileField  ; 
   QPushButton *chooseNeuronFileButton  ;

   QLabel *depthLabel ; 
   QSpinBox *depthSpinBox ; 
   QLabel *eThreshLabel ; 
   QSpinBox *eThreshSpinBox ; 
   QLabel *cThreshLabel ; 
   QSpinBox *cThreshSpinBox ; 

   QLineEdit *startField ; 
   QLabel  *startLabel ; 
   QLineEdit *stopField ; 
   QLabel  *stopLabel ; 


   // output controls
   QLineEdit *outputFileField  ; 
   QPushButton *chooseOutputFileButton  ;

   QCheckBox *noStatsBox ; 
   QCheckBox *intOutputBox ; 
   QCheckBox *doPadBox ; 
   QCheckBox *showConnectionBox ; 
   QCheckBox *stopAtTerminusBox ; 

   QLabel  *padLabel  ;
   QLabel  *del1Label  ;
   QLabel  *del2Label  ;
   QLineEdit  *padLineEdit  ;
   QLineEdit  *del1LineEdit  ;
   QLineEdit  *del2LineEdit  ;

   // report options
   
   QLineEdit *edgeLineEdit; 
   QPushButton *edgeChooseOutputButton;
   QCheckBox *edgeDoDot; 
   QCheckBox *edgeDoTxt; 
   QCheckBox *edgeDoLabel; 

   // node stuff, not used, replace with more report options
//   QLineEdit *nodeLineEdit; 
//   QPushButton *nodeChooseOutputButton;
//   QCheckBox *nodeDoDot; 
//   QCheckBox *nodeDoTxt; 

   // do self and other connections
   QCheckBox *doSelfConnections; 
   QCheckBox *doRecurrentConnections; 


   // control buttons
   QPushButton *startButton  ;
   QPushButton *stopButton  ;
   QPushButton *quitButton  ;



} ;


#endif


