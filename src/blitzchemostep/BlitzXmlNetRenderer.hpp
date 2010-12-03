// -*- C+ -*-


#ifndef BLITZXMLNETRENDERER_HPP
#define BLITZXMLNETRENDERER_HPP

#include "BlitzNetRenderer.hpp"
#include "XmlNetInterface.hpp"

#include <sstream>
using std::ostringstream ; 

class BlitzNet ; 

class BlitzXmlNetRenderer : public BlitzNetRenderer , public XmlNetInterface {

public:
   BlitzXmlNetRenderer() ; 
   virtual string render(BlitzNet* net) ; 

protected:
   ostringstream *mOutputStream ; 

} ;

#endif


