// -*- C++ -*-
// FILE: "/Users/nathandunn/cvs/auto2/AUTOGUI_2/source/ClickableObject.hpp"
// LAST MODIFICATION: "Tue, 21 Oct 2003 14:55:25 -0700 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: ClickableObject.hpp,v 1.1.1.1 2003/10/24 19:59:22 ndunn Exp $
//
/// This object is responsible for making sure that all objects which get
/// clicked are named.
//
// 


#ifndef CLICKABLEOBJECT_HPP_
#define CLICKABLEOBJECT_HPP_

class ClickableObject{

public:
     ClickableObject(string newPathToType,string newObjectName="") ; 
     // {{{
     /*!
      * \brief	Get pathToType.
      *
      * \return	pathToType as a string.
      */ // }}}
     string getPathToType()
     {
         return(pathToType);
     }
     // {{{
     /*!
      * \brief	Set pathToType.
      *
      * \param	_pathToType	The new value for pathToType (as a string).
      */ // }}}
     void setPathToType(string _pathToType)
     {
         pathToType = _pathToType;
         return;
     }

     // {{{
     /*!
      * \brief	Get objectName.
      *
      * \return	objectName as a string.
      */ // }}}
     string getObjectName()
     {
         return(objectName);
     }
     // {{{
     /*!
      * \brief	Set objectName.
      *
      * \param	_objectName	The new value for objectName (as a string).
      */ // }}}
     void setObjectName(string _objectName)
     {
         objectName = _objectName;
         return;
     }



protected:
     string pathToType ; 
     string objectName ; 
} ; 


#endif


