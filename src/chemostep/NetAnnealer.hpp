/*
 * $Id: NetAnnealer.hpp,v 1.1.1.1 2003/10/24 19:59:27 ndunn Exp $
 */
#ifndef NETANNEALER_HPP_
#  define NETANNEALER_HPP_

#include "Annealer.hpp" 

class NeuralNetwork ; 

class NetAnnealer : public Annealer {

public:
    NetAnnealer() ; 
    virtual AnnealingTarget* anneal() ; 
    virtual void setAnnealingTarget(AnnealingTarget* annealingTarget) ; 

private:
    NeuralNetwork* currentNet ; 

} ;

#endif /* ifndef NETANNEALER_H */
// -*- C++ -*-
// FILE: "/Users/nathandunn/svn/chemotrunk/src/chemostep/NetAnnealer.hpp"
// LAST MODIFICATION: "Thu, 14 Oct 2004 16:04:49 -0700 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: NetAnnealer.hpp,v 1.1.1.1 2003/10/24 19:59:27 ndunn Exp $

