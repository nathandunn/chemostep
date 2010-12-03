// -*- C++ -*-
// FILE: "/Users/nathandunn/cvs/auto2/testclasses/source/TestNN.hpp"
// LAST MODIFICATION: "Tue, 30 Sep 2003 16:35:02 -0700 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: TestNN.hpp,v 1.1.1.1 2003/10/24 19:59:35 ndunn Exp $

#ifndef TEST_NN_
#define TEST_NN_


#include <InterfaceTypes.hpp>
#include "AnnealerObject.hpp"
#include "feeder"


class TestNN : public AnnealerObject, public InterfaceTypes {


public:
//    TestNN(string newGroup="NOT_SET",string newName="NOT_SET") ; 
    TestNN(string newInterfaceName ,string newTypeName, AppInterface* newParent=NULL ) ;
    virtual bool createLocalMaps()   ;  // creates the map here instead of constructure
    virtual bool setLocalOption(string name,string value)  ; // sets name and value of option
    virtual bool disposeLocalInterfaces()   ;  // creates the map here instead of constructure
    virtual string getLocalOption(string name)  ; // gets value for name 
    virtual AppInterface* setLocalType(string interfaceName,string typeName)  ; // sets name and value of option
    virtual AppInterface* getLocalTypeForInterface(string theInterfaceName)   ; // need to check this for each class
    virtual string doLocalCommand(Command* theCommand)  ;    
    virtual bool perturb(double temperature)  ; 

    static const string STIM_FEEDER  ; 
    static const string TARGET_FEEDER  ; 
    static const string FILE_FEEDER  ; 
    static const string RANDOM_FEEDER  ; 
    static const string NETWORK_DATA; 
    static const string PERTURB_NET; 
    static const string TEMPERATURE_DATA ; 


protected:
    TestFeeder *stimFeeder ; 
    TestFeeder *targetFeeder ; 
    string theFile; 
    double theTempterature ; 

}  ; 

#endif


