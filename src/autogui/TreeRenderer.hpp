// -*- C++ -*-
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>

#ifndef TREERENDERER_hpp_
#define TREERENDERER_hpp_

#include <string>
using std::string ; 

#include "Renderer.hpp" 

class ClickableObject ; 

/**  A class which renders applications similar to QtFlatRenderer, but allows
 * the selection of types.
 *
 * \todo Implement from auto2 implemenation.
 *
 */ 

class TreeRenderer : public Renderer {

public:

    // update MAP
    virtual string addMapInterface(string pathToType)  ; 
    virtual string addMapType(string pathToType)  ; 
    virtual string setMapType(string pathToType)  ; 
    virtual string unSetMapType(string pathToType) ; 

    
    // update GUI
    virtual string addGuiInterface(string pathToType)   =0 ; 
    virtual string addGuiType(string pathToType)   =0 ; 
    virtual string setGuiType(string pathToType) =0 ; 
    virtual string unSetGuiType(string pathToType) = 0; 
    virtual string updateViewer(ClickableObject *object)  ; // the rhs of the splitter calls viewType, viewInterface
    virtual string updateTree(ClickableObject *object)  ; // the lhs of the splitter
    virtual string viewType(ClickableObject* object)  ;  // maybe GuiType
    virtual string viewInterface(ClickableObject* object)  ;  // maybe GuiInterface


    /**************************
     * Instantiate from Renderer   
     */
    // MAP push to GUI
    virtual string renderAppToGui(string xmlString="")  ;  // may also render the previously loaded app


	// update GUI
    virtual string view(ClickableObject* object) ; 
    virtual string clearGui()  ; 
    virtual string clearViewer()  ; 
    virtual string clearTree()  ; 
} ;



#endif


