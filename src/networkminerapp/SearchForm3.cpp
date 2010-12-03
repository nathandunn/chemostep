// -*- C++ -*-
// FILE: "/Users/nathandunn/tla/auto3--updateminer--1.3.4--base-0/src/networkminerapp/SearchForm3.cpp"
// LAST MODIFICATION: "Mon, 05 Apr 2004 17:54:11 -0700 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@idiom.com>
// $Id: SearchForm3.cpp,v 1.31 2003/07/21 03:19:29 ndunn Exp $


#include <Command.hpp>
#include <InterfaceXmlString.hpp>
#include <TiFlatBaseApp.hpp>
#include <Renderer.hpp>

#include "SearchForm3.hpp"

//SearchForm3::SearchForm3(QWidget *newParent, const char *name,SearchDriver *newDriver)  {
//    driver = newDriver ; 
//    parent = newParent; 
//    initGui() ; 
//    loadDefaults() ; 
//}

//SearchForm3::SearchForm3(string newInterfaceName, string newTypeName, AppInterface* newParent) : TiFlatBaseApp(newInterfaceName,newTypeName,newParent) 
//{
//    description = "Searches a map of electrical and chemical connections using a depth-first search." ; 
//}


//void SearchForm3::addMessageGUI(string message) 
//{
//    QString messageString = QString((char *) &message) ; 
//    QMessageBox::warning(this,QString("SearchForm3"), messageString, 0,1) ;
//}




//int SearchForm3::doSearch(){
//
////    if(checkInputs()==false){
////        return false ; 
////    }
////    saveDefaults() ; 
//
//
//    cout << "SearchForm3:: starting the search here" << endl ;
//
//    driver->startSearch(
//        mStartNeurons,
//        mStopNeurons,
//        mNeuronFile,
//        mConnectivityFile,
//        mEdgeTextOutput,
//        mSearchDepth,
//        mChemDepth,
//        mElecDepth,
//        mDel1,
//        mDel2,
//        mPadding,
//        mDoPadding,
//        mDoStats,
//        mIntOutput,
//        mShowConnection,
//        mStopAtTerminus,
//        mEdgeLineEdit,
//        mEdgeTextOutput,
//        mEdgeDotOutput,
//        mDoSelfConnections,
//        mDoRecurrentConnections,
//        mLabelConnections
//        ) ;
//    driver->startSearch(
//        (startField->text()).upper().remove(' '),
//        (stopField->text()).upper().remove(' '),
//        neuronFileField->text(),
//        connectionFileField->text(),
//        outputFileField->text(),
//        atoi(depthSpinBox->text()) ,
//        atoi(cThreshSpinBox->text()) ,
//        atoi(eThreshSpinBox->text()) ,
//        del1LineEdit->text(),
//        del2LineEdit->text(),
//        padLineEdit->text(),
//        doPadBox->isChecked(),
//        noStatsBox->isChecked(),
//        intOutputBox->isChecked(),
//        showConnectionBox->isChecked(),
//        stopAtTerminusBox->isChecked(),
//        edgeLineEdit->text(),
//        edgeDoTxt->isChecked(),
//        edgeDoDot->isChecked(),
//        doSelfConnections->isChecked(),
//        doRecurrentConnections->isChecked(),
//        edgeDoLabel->isChecked()
//        ) ;

//        return true ; 
//}







