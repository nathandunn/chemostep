// -*- C++ -*-
// FILE: "/Users/nathandunn/cvs/auto2/AUTOGUI_2/source/FlatRenderer.hpp"
// LAST MODIFICATION: "Tue, 21 Oct 2003 14:56:15 -0700 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: FlatRenderer.hpp,v 1.1.1.1 2003/10/24 19:59:22 ndunn Exp $
//
//

#ifndef FLATRENDERER_hpp_
#define FLATRENDERER_hpp_


#include "Renderer.hpp" 


#include <string>
using std::string ; 

class ClickableObject ;
class AppParser ; 


/// This class just registers options, but with no ability to set/unset
/// types, simplying displaying options/methods for all instantiated types
/// on the same level.

class FlatRenderer : public Renderer {

public:
    FlatRenderer(TransmitterApp* newTransmitterApp,AppParser *newAppParser) : Renderer(newTransmitterApp) { 
        appParser = newAppParser  ; 
    }  

    /**************************
     * Instantiate from Renderer   
     */
    // MAP push to GUI
    virtual string renderAppToGui(string xmlString="")  ;  // may also render the previously loaded app


protected:
    AppParser* appParser ; 


} ;



#endif


