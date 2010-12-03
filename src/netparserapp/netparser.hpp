/*
 * $Id$
 */
#ifndef NETPARSER_HPP_
#  define NETPARSER_HPP_

#include <string>
using std::string ; 


#include <BaseFlatDriver.hpp>
#include <AppInterface.hpp>

/** This is a driver and gui class for parsing C. elegans neural network data.
 *
 * It extends BaseFlatDriver. 
 */
class netparser : public BaseFlatDriver{

public:
    netparser(AppInterface *newApp)  ; 

protected:

} ;

#endif /* ifndef NETPARSER_H */
// -*- C++ -*-
// FILE: "/Users/nathandunn/tla/auto3--dev--1.3.2--patch-8/src/netparserapp/netparser.hpp"
// LAST MODIFICATION: "Wed, 17 Mar 2004 12:32:43 -0800 (nathandunn)"
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

