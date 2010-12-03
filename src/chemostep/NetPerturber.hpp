/*
 * $Id: NetPerturber.hpp,v 1.1.1.1 2003/10/24 19:59:27 ndunn Exp $
 */
#ifndef NETPERTURBER_HPP_
#  define NETPERTURBER_HPP_

#include <iostream>
using std::ostream; 

#include "XmlRenderable.hpp"

class NeuralNetwork ; 

class NetPerturber : public XmlRenderable {

public:
    NetPerturber() ; 
    virtual NeuralNetwork* perturb(double temp,NeuralNetwork* newNet) ; 
    virtual void toXML(ostream *s) ; 


} ;

#endif /* ifndef NETPERTURBER_H */
// -*- C++ -*-
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: NetPerturber.hpp,v 1.1.1.1 2003/10/24 19:59:27 ndunn Exp $

