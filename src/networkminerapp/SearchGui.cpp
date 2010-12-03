// -*- C++ -*-
// FILE: "/Users/nathandunn/tla/auto3--updateminer--1.3.4--base-0/src/networkminerapp/SearchGui.cpp"
// LAST MODIFICATION: "Mon, 05 Apr 2004 18:20:43 -0700 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@idiom.com>
// $Id: SearchGui.cpp,v 1.13 2003/07/16 00:37:12 ndunn Exp $

#include "SearchGui.hpp"
#include "SearchForm2.hpp"


// the gui driver class, used to update progress in gui
void SearchGui::solutionPath(ConnectionPath *path) {

    cout << "solution path being called" << endl ; 

    // update the progress bar
    // update any status labels
}


void SearchGui::startSearchNotify2(string testText) {

    cout << "test: " << testText << endl ; 

}




void SearchGui::startSearchNotify(){

    cout << "startSearchNotify" << endl ; 

}


void SearchGui::stopSearch() {

}

void SearchGui::logGUIMessage(string message) 
{
     searchForm->addMessageGUI(message) ; 
}

void SearchGui::logTheMessage(string message) 
{
    logGUIMessage(message) ; 
}


int SearchGui::startApp(int numArgs,char** theArgs){

//  SearchDriver *driver = new SearchDriver(this) ; 
//    
//  cout <<"running gui " << endl ;
//  QApplication theapp(numArgs, theArgs);
//
////  theapp.setStyle(new QWindowsStyle()) ;  
//
//  #ifdef MACOSX
//  theapp.setStyle(new QMacStyle()) ;  
//  #endif 
//
////  SearchForm *searchForm = new SearchForm();
////  SearchForm2 *searchForm = new SearchForm2((QWidget*)this,"new form", driver);
//  searchForm = new SearchForm2((QWidget*)this,"new form", driver);
//
//  searchForm->setCaption("Network Connectivity Search");
//  theapp.setMainWidget(searchForm);
//  searchForm->show();
//
//  theapp.connect(&theapp, SIGNAL(lastWindowClosed()), &theapp, SLOT(quit()));
//
//  return theapp.exec();

    return 0 ; 
}

int main(int argc, char** argv){
    SearchGui gui  ; 
    gui.startApp(argc,argv) ;

}


