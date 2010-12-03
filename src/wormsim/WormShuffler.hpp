/*
 * $Id$
 */
#ifndef WORMSHUFFLER_HPP_
#  define WORMSHUFFLER_HPP_

#include <iostream>
using std::ostream ; 

#include <XmlRenderable.hpp>

class BaseWorm ; 

///  This class is responsible for randomly re-arranging a worm on a plate.  
class WormShuffler : public XmlRenderable {

public:
    virtual void shuffleWorm(BaseWorm* aWorm) = 0 ; 
    virtual void reset() { } ;  /// Most methods don't need to implement this.

} ;

#endif /* ifndef WORMSHUFFLER_H */
// -*- C++ -*-
// FILE: "/Users/nathandunn/svn/chemotrunk/src/wormsim/WormShuffler.hpp"
// LAST MODIFICATION: "Mon, 24 Oct 2005 15:50:07 -0700 (nathandunn)"
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

