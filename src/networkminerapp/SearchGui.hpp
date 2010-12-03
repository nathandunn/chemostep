// -*- C++ -*-
// FILE: "/Users/nathandunn/svn/chemotrunk/src/networkminerapp/SearchGui.hpp"
// LAST MODIFICATION: "Wed, 19 Jan 2005 16:46:29 -0800 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@idiom.com>
// $Id: SearchGui.hpp,v 1.11 2003/07/16 00:37:12 ndunn Exp $

#ifndef _SEARCH_GUI_
#define _SEARCH_GUI_

#include <iostream>
using std::cout ; 
using std::endl ; 

#include <string>
using std::string; 

#include <qapplication.h>
//#include <qwindowsstyle.h>
//#ifdef MACOSX
//    #include <qmacstyle_mac.h>
//#endif

//#include "SearchDriver.hpp" 
#include "ConnectionPath.hpp" 
#include "SearchForm2.hpp" 

class SearchForm2 ; 

//class SearchGui: public SearchDriver  {
class SearchGui: public QObject {

    Q_OBJECT 

public:
    virtual void solutionPath(ConnectionPath *path)  ;
    // this will include all of the options
    virtual void stopSearch() ; 
    virtual int startApp(int numArgs,char** theArgs) ; 
    virtual void logTheMessage(string message) ; 
    void logGUIMessage(string message) ; 
    
public slots:
    virtual void startSearchNotify() ; 
    virtual void startSearchNotify2(string testText) ; 
    



private:
    string messageText ; 
    SearchForm2 *searchForm ; 


} ;

#endif

