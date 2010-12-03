// -*- C++ -*-
// FILE: "/Users/nathandunn/cvs/auto2/AUTOGUI_2/source/Component.hpp"
// LAST MODIFICATION: "Tue, 21 Oct 2003 14:55:56 -0700 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@idiom.com>
// $Id: Component.hpp,v 1.1.1.1 2003/10/24 19:59:22 ndunn Exp $
//
// This method should be cake, since this is all handled locally.
//
//

#ifndef _COMPONENT_HPP_
#define _COMPONENT_HPP_

#include <string>
using std::string ; 

class Component{

public:
    Component(string newGroup="",string newName="",bool setToThis=false) {
        group = newGroup     ; 
        name = newName ; 
        isSet = setToThis ; 
    }; 
   void setGroup(string newGroup){
       group = newGroup ; 
   }
   string getGroup(){ return group ; } 
   void setName(string newName){
       name = newName ; 
   }
   string getName(){ return name ; } 
   bool isSetToThis(){ return isSet ; } 
   bool setSetToThis(bool setToThis){isSet = setToThis ; } 
   string getKey()  ;
   static const string makeKey(string newGroup,string newName) ; 

    static const string KEY_DELIMITER ; 


protected:
   string group ;   // "A.B.C.D"
   string name ;    // "D=oranges"  
   bool isSet ; 



} ; 

#endif



