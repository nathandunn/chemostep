// -*- C++ -*-
// FILE: "/Users/nathandunn/tla/auto3--updateminer--1.3.4--base-0/src/networkminerapp/SearchForm3.hpp"
// LAST MODIFICATION: "Mon, 05 Apr 2004 17:52:12 -0700 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@idiom.com>
// $Id: SearchForm3.hpp,v 1.16 2003/07/10 23:46:03 ndunn Exp $
//


#ifndef _SEARCHFORM3_
#define _SEARCHFORM3_

#include "SearchDriver.hpp"

#include <iostream.h>

#include <qapplication.h>

class SearchDriver ;  

/**  An application which integrates the autogui library to build an additional application.
 *
 *  \todo Extend the autogui BaseApp, applications, similar to NetParser.
 *  \todo Scan all neurons instead of load an individual file. 
 *  \todo Implement the code from NetParser and add options to parse as symmetrical versus assymmyetrical.  
 *
 */

class SearchForm3 : public TiFlatBaseApp{

public:  
     SearchForm3(string newInterfaceName, string newTypeName, AppInterface* newParent = NULL ) ; 



private:
   SearchDriver *driver  ; 
   QWidget  *parent; 

   // variables to keep
   // set 1 - search variables

       


} ;


#endif


