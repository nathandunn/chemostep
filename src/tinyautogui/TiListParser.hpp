// -*- C++ -*-
// FILE: "/home/ndunn/svn/chemotrunk/src/tinyautogui/TiListParser.hpp"
// LAST MODIFICATION: "Mon, 13 Dec 2004 10:10:14 -0800 (ndunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: TiListParser.hpp,v 1.2 2004/01/13 20:43:36 ndunn Exp $

#ifndef _TILISTPARSER_HPP_
#define _TILISTPARSER_HPP_

#include <string>
using std::string ; 

#include <vector>
using std::vector ; 

class Type ;
class TiXmlElement ; 

class TiListParser {

public:
    TiListParser() ; 
    // sets selected value if supplied
    static vector<string>* parseList(string xmlString,int *selectedValue=NULL) ;
    static string createList(vector<string>* list,string selectedValue="") ;
    static string getSelectedValue(string xmlString) ; 


    const static string LIST  ; 
    const static string ITEM  ; 
    const static string SELECTED ; 

protected:



} ; 

#endif


