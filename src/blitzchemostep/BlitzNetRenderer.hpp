/*
 * $Id: BlitzNetRenderer.hpp,v 1.1.1.1.12.1 2004/02/10 03:01:18 ndunn Exp $
 */
#ifndef BLITZNETRENDERER_HPP_
#  define BLITZNETRENDERER_HPP_



#include <string>
using std::string ; 

class BlitzNet ; 

/**  Class renders BlitzNet into a string format.
 * 
 * \todo Should pull values from NetEvaluator and render.
 *
 */

class BlitzNetRenderer {

public:
    BlitzNetRenderer() {}; 
    virtual string render(BlitzNet* net)=0 ; 

    
} ;

#endif /* ifndef BLITZNETRENDERER_H */
// -*- C++ -*-
// FILE: "/Users/nathandunn/cvs/auto3OPTIM_1/src/blitzchemostep/BlitzNetRenderer.hpp"
// LAST MODIFICATION: "Mon, 09 Feb 2004 19:03:42 -0800 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: BlitzNetRenderer.hpp,v 1.1.1.1.12.1 2004/02/10 03:01:18 ndunn Exp $

