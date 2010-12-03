// -*- C++ -*-

#ifndef _TIAPPPARSER_HPP_
#define _TIAPPPARSER_HPP_

#include "AppParser.hpp" 

#include <vector>
using std::vector ; 

class Type ;
class TiXmlElement ; 

class TiAppParser : public AppParser {

public:
    // this should simply be a series of calls to AddGuiType
    TiAppParser(Renderer* newRenderer=NULL) ; 
    virtual string parse(Renderer* newRenderer,string xmlString) ;



protected:
    virtual bool parseElement(TiXmlElement* theElement,Type* parentType,string interfacePath) ; 



} ; 

#endif


