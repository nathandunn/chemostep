// -*- C++ -*-
// FILE: "/Users/nathandunn/cvs/auto2/testclasses/source/TestAnnealer.hpp"
// LAST MODIFICATION: "Tue, 30 Sep 2003 16:36:51 -0700 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: TestAnnealer.hpp,v 1.1.1.1 2003/10/24 19:59:34 ndunn Exp $

#ifndef TEST_ANNEALER_HPP
#define TEST_ANNEALER_HPP

#include <float.h>
#include <stdlib.h>

#include <string>
using std::string; 

#include <AppInterface.hpp>
#include <InterfaceTypes.hpp>


class AnnealerObject ; 
class Command ;
class TestFeeder ; 

class TestAnnealer : public AppInterface, public InterfaceTypes{


public:
    TestAnnealer::TestAnnealer(string newInterfaceName,string newTypeName,AppInterface* newParent) ;
    virtual string getLocalOption(string name)  ; // sets name and value of option
    virtual bool setLocalOption(string name,string value)  ; // sets name and value of option
    virtual AppInterface* setLocalType(string theInterfaceName,string theTypeName)  ; // sets name and value of option
    virtual string doLocalCommand(Command* theCommand)  ;    
    virtual bool disposeLocalInterfaces()   ;  // creates the map here instead of constructure
    virtual bool createLocalMaps()     ;  // creates the map here instead of constructure
    virtual AppInterface* getLocalTypeForInterface(string theInterfaceName)   ; // need to check this for each class

    virtual bool startAnnealer() ; 

    static const string HIGH_TEMP  ; 
    static const string LOW_TEMP  ; 
    static const string ANNEALER_OBJECT ; 
    static const string TEST_NEURAL_NETWORK ; 
    static const string START_ANNEALER ; 
    static const string TEST_ANNEALER ; 
    static const string FILE_READER ; 

protected:
    AnnealerObject* annealerObject ;
    TestFeeder* fileReader ;
    float lowTemp  ; 
    float highTemp ; 

} ; 

#endif


