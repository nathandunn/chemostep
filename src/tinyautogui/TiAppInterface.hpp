/*
 * $Id$
 */
#ifndef TIAPPINTERFACE_HPP_
#  define TIAPPINTERFACE_HPP_

#include <AppInterface.hpp>
#include <InterfaceTypes.hpp>

class TiAppInterface : public AppInterface, public InterfaceTypes{

public:
    TiAppInterface(string interfaceName,string typeName,AppInterface* parent=0)  ;  /// creates the map here instead of constructure
    TiAppInterface() ; 
   bool setLocalOption(string name, string value) ;
   string getLocalOption(string name) ; 
   string doLocalCommand(Command *theCommand) ; 

} ;

#endif /* ifndef TIAPPINTERFACE_H */
// -*- C++ -*-
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

