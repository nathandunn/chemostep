#ifndef TINYBZNETPARSER_HPP_
#  define TINYBZNETPARSER_HPP_

#include <string>
using std::string ; 

#include "BzNetParser.hpp" 
#include "XmlNetInterface.hpp" 

class BlitzNet ; 

class TinyBzNetParser : public BzNetParser , public XmlNetInterface {

public:
    TinyBzNetParser() ; 
    virtual BlitzNet* parseFile(string fileName) ; 
    virtual BlitzNet* parse(string xmlString) ; 

protected:
    string *mFileName ; 
    static const int MAX_FILENAME ; 

} ;

#endif /* ifndef TINYBZNETPARSER_H */
// -*- C++ -*-
// FILE: "/Users/ndunn/svn/chemotrunk/src/tinyblitzchemostep/TinyBzNetParser.hpp"
// $Id: TinyBzNetParser.hpp,v 1.2 2004/01/13 20:43:36 ndunn Exp $

