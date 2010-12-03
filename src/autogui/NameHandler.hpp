// -*- C++ -*-
// FILE: "/Users/nathandunn/cvs/AUTOGUI_1/source/appinterface/NameHandler.hpp"
// LAST MODIFICATION: "Mon, 22 Sep 2003 13:50:56 -0700 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: NameHandler.hpp,v 1.1.1.1 2003/10/24 19:59:23 ndunn Exp $

#ifndef NAMEHANDLER_HPP_
#define NAMEHANDLER_HPP_

#include <string>
using std::string ; 

class NameHandler{


public:
    // *********************************
    //   Name handler methods
    // *********************************
    static string getInterfaceFromPair(string pairName)  ;
    static string getLastInterfacePair(string pathName)  ;
    static string getLastInterface(string pathName)  ;
    static string getAllButLastInterfacePair(string pathName)  ;
    static string getTypeFromPair(string pairName)  ;
    static string getFirstInterface(string pairName)  ;
    static string getFirstType(string pairName)  ;
    static string getAllButFirstInterfacePair(string pairName)  ;
    static string getFirstInterfacePair(string pairName)  ;
    static bool   firstPairHasType(string pairName)  ;
    static bool   lastPairHasType(string pairName)  ;
    static bool   pairHasType(string pairName)  ;
    static bool   hasSubInterface(string pairName)  ;
    static string getNameFromPath(string pathToType)  ;
    static string getAllButNameFromPath(string pathToType)  ;

    static const string TYPE_DELIMITER  ; 
    static const string INTERFACE_DELIMITER  ; 
    static const string NAME_DELIMITER  ; 
} ; 


#endif 


