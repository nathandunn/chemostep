/*
 * $Id$
 */
#ifndef SYMMPARSER_HPP_
#  define SYMMPARSER_HPP_

#include "NetDataParser.hpp"

class SymmParser : public NetDataParser{

public:
    SymmParser(string newInterfaceName, string newTypeName, AppInterface* newParent) ; 
    virtual map<string,ConnectionData*>* applyRule(vector<ConnectionData*>* origTable) ; 

} ;

#endif /* ifndef SYMMPARSER_H */
// -*- C++ -*-
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

