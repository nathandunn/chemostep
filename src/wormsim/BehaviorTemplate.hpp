#ifndef BEHAVIORTEMPLATE_HPP_
#  define BEHAVIORTEMPLATE_HPP_

#include <XmlRenderable.hpp>

template <class WormType>
class BehaviorTemplate : public XmlRenderable{

public:
    BehaviorTemplate(){ }
    virtual int getBehavior() = 0  ; 	
    virtual float getProbability() = 0; 	

} ;

#endif /* ifndef BEHAVIORTEMPLATE_H */
// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


