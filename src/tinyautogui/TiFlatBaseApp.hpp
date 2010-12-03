/*
 * $Id$
 */
#ifndef TIFLATBASEAPP_HPP_
#  define TIFLATBASEAPP_HPP_

#include "TiAppInterface.hpp"

class Renderer ; 
class TinyAppInterfaceXmlEngine ; 

/**  A base-class for generating a basic application.  
 *
 * Only createLocalMap and doLocalMap() need to be defined.
 *  
 */
class TiFlatBaseApp : public TiAppInterface {

public:
    TiFlatBaseApp(string interfaceName,string typeName,AppInterface* parent=0)  ;  
    void setRenderer(Renderer* newRenderer) ; 
    virtual bool createLocalMaps()  ;  /// creates the map here instead of constructure
    virtual bool disposeLocalInterfaces()  ;  /// deletes the map here instead of constructure
    virtual string doLocalCommand(Command* theCommand)  ;    /// processes a command not in the optionInterface API
    void setXmlRenderer(TinyAppInterfaceXmlEngine* newXmlRenderer ) ; 
    AppInterface* setLocalType(string theInterfaceName,string theTypeName) ; 
    virtual AppInterface* getLocalTypeForInterface(string theInterfaceName)   ; /// accepts int.int.int (where it grabs the approriate link) or int/type.int/type
    void setBaseApp(string newBaseAppName) ; 
    string getBaseApp() ; 

    string getBaseAppName() {
        return(mBaseAppName);
    }
    void setBaseAppName(string _mBaseAppName) {
        mBaseAppName = _mBaseAppName;
        return;
    }



protected:
    Renderer* mRenderer  ; 
    TinyAppInterfaceXmlEngine* mXmlRenderer ; 
    bool mTestBool ; 
    string mTestString; 

    // from the default
    string mBaseAppName ; 

} ;

#endif /* ifndef TIFLATBASEAPP_H */
// -*- C++ -*-
// FILE: "/Users/nathandunn/tla/auto3--dev--1.3.2--patch-8/src/tinyautogui/TiFlatBaseApp.hpp"
// LAST MODIFICATION: "Wed, 17 Mar 2004 17:59:36 -0800 (nathandunn)"
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

