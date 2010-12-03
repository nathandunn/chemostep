#ifndef ANNEALXMLRENDERER_HPP_
#  define ANNEALXMLRENDERER_HPP_

#include <iostream>
using std::cout ; 
using std::endl ; 

#include "XmlRenderer.hpp"

/**
The AnnealXmlRenderer class is supposed handle
writing an XML representation of an annealing
run. It has not been implemented and its parent
class XmlRenderer has a very small portion
implemented.

When XML output is desired from an app, (perhaps
more likely a pointer to) an instance of this
class should be passed to the anneal() method
of a BlitzNetAnnealer object.

NOTE: It's probably too narrow to say that the
instance of this class should be passed to the
anneal() method of a BlitzNetAnnealer object.
It should be possible to send it to any ancestor
of BlitzNetAnnealer.

NOTE: I (JB) had planned to overload the constructors
to the different annealer objects to either take
the an instance of AnnealXmlRenderer or nothing.
The constructors that take no argument would then
create a null pointer which it would then pass to
the other version of the constructor. That version
of the constructor (the one that accepts an instance
of AnnealXmlRenderer as an argument) would then need
to check to see if the pointer is null or not before
trying to write out XML info.

Once the anneal() method has started, it should
output information concerning each temperature step.
The pointer to the AnnealXmlRenderer can also then
be passed on to any other objects that might need
to write out XML.

Also, the application (kineticanneal for example)
itself can also use the AnnealXmlRenderer to write
out any info before, during or after the annealing run.
For instance, when the annealing is complete, the app
can output a representation of the best network.

Finally, there will likely need to be an init() method
either here or in AnnealXmlRenderer's parent XmlRenderer
that outputs the opening XML tags. A similar close()
method could output the closing tags and close the file.
*/

class AnnealXmlRenderer : public XmlRenderer {
  
   public:
      AnnealXmlRenderer() ; 
  // ~AnnealXmlRenderer() ; 

};

#endif /* ifndef ANNEALXMLRENDERER_H */
// -*- C++ -*-xe

