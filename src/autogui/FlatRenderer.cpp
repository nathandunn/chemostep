// -*- C++ -*-
// FILE: "/Users/nathandunn/cvs/AUTOGUI_1/source/renderer/FlatRenderer.cpp"
// LAST MODIFICATION: "Mon, 22 Sep 2003 17:14:53 -0700 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: FlatRenderer.cpp,v 1.1.1.1 2003/10/24 19:59:22 ndunn Exp $

#include "FlatRenderer.hpp" 
#include "AppParser.hpp" 

string FlatRenderer::renderAppToGui(string xmlString)  
{
    if(xmlString!=""){
        loadAppToMap(xmlString) ; 
    }

    // now render this shit
    return appParser->parse(this,xmlMap) ; 
    
}




