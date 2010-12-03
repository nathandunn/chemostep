/*
 * $Id$
 */
#ifndef ASYMMPARSER_HPP_
#  define ASYMMPARSER_HPP_

#include "SymmParser.hpp"

class ASymmParser : public SymmParser{

public:
    ASymmParser(string newInterfaceName, string newTypeName, AppInterface* newParent) ; 
    virtual map<string,ConnectionData*>* applyRule(vector<ConnectionData*>* origTable) ; 

} ;

#endif /* ifndef SYMMPARSER_H */
// -*- C++ -*-
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

