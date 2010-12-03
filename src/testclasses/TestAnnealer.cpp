// -*- C++ -*-
// FILE: "/Users/nathandunn/cvs/auto2/testclasses/source/TestAnnealer.cpp"
// LAST MODIFICATION: "Tue, 30 Sep 2003 16:36:30 -0700 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: TestAnnealer.cpp,v 1.1.1.1 2003/10/24 19:59:34 ndunn Exp $

#include "TestAnnealer.hpp"
#include "TestNN.hpp"
#include "feeder"
#include "AnnealerObject.hpp"

#include <InterfaceXmlString.hpp>

#include <stdio.h>
#include <strstream>
using std::ostrstream;

TestAnnealer::TestAnnealer(string newInterfaceName,string newTypeName,AppInterface* newParent) : AppInterface(newInterfaceName,newTypeName,newParent) {
  annealerObject  = NULL ; 
  fileReader = NULL ; 
  lowTemp = DBL_MAX ; 
  highTemp = DBL_MIN ; 
  description = "A test annealer" ; 
}



bool TestAnnealer::setLocalOption(string name,string value)  
{
    cout << "TestAnnealer setting local option: " << name << " to: "  << value << endl ; 
    if(name==HIGH_TEMP){
        cout << "TestAnnealer HIGHTEMP set" << endl ; 
        highTemp= atof(value.c_str()) ; 
        return true ; 
    }
    else
    if(name==LOW_TEMP){
        lowTemp = atof(value.c_str()) ; 
        return true ; 
    }

    return false ; 
}

string TestAnnealer::getLocalOption(string name)  
{
    if(name==HIGH_TEMP){
        ostrstream returnString ; 
        returnString << highTemp ; 
        return returnString.str() ; 
    }
    else
    if(name==LOW_TEMP){
        ostrstream returnString ; 
        returnString << lowTemp ; 
        return returnString.str() ; 
    }
    return NULL ; 
}



AppInterface* TestAnnealer::setLocalType(string theInterfaceName,string theTypeName)
{
//    cout << "TestAnnealer setting object theInterfaceName: " << theInterfaceName << " theTypeName: " << theTypeName << endl ;
    if(theInterfaceName==ANNEALER_OBJECT){
        annealerObject = NULL ; 
        if(theTypeName==TEST_NEURAL_NETWORK){
            annealerObject = new TestNN(ANNEALER_OBJECT,TEST_NEURAL_NETWORK) ; 
        }
        return annealerObject ; 
    }
    else
    if(theInterfaceName==FILE_READER){
        fileReader = NULL  ; 
        if(theTypeName==TestNN::FILE_FEEDER){
            fileReader = new TestFileFeeder(FILE_READER,TestNN::FILE_FEEDER) ; 
        }
        if(theTypeName==TestNN::RANDOM_FEEDER){
            fileReader = new TestRandomFeeder(FILE_READER,TestNN::RANDOM_FEEDER) ; 
        }
        return fileReader ; 
    }
    return NULL ; 
}


bool TestAnnealer::createLocalMaps()     
{
    addInterfaceToMap(FILE_READER) ; 
    addTypeToInterfaceMap(FILE_READER,TestNN::RANDOM_FEEDER) ; 
    addTypeToInterfaceMap(FILE_READER,TestNN::FILE_FEEDER) ; 
    addInterfaceToMap(ANNEALER_OBJECT) ; 
    addTypeToInterfaceMap(ANNEALER_OBJECT,TEST_NEURAL_NETWORK) ; 
    addOptionToMap(HIGH_TEMP,OPT_DOUBLE) ; 
    addOptionToMap(LOW_TEMP,OPT_DOUBLE) ; 
    Command* theCommand = new Command(START_ANNEALER,OPT_BOOL) ; 
    theCommand->addCommandArgument(HIGH_TEMP,OPT_DOUBLE,"",HIGH_TEMP,false) ; 
    theCommand->addCommandArgument(LOW_TEMP,OPT_DOUBLE,"",LOW_TEMP,false) ; 
    addCommandToMap(START_ANNEALER,theCommand) ; 
    return true ; 
}

AppInterface* TestAnnealer::getLocalTypeForInterface(string theInterfaceName)   
{
    cout <<"trying to return: "<< theInterfaceName << endl ;
       
    if(theInterfaceName==ANNEALER_OBJECT){
        cout << "returned" << endl ;
      return  annealerObject ; 
    }
    if(theInterfaceName==FILE_READER){
      return  fileReader ; 
    }

    return NULL ; 
}

bool TestAnnealer::startAnnealer() 
{
    cout << "running the annealer from:" << highTemp << " to " << lowTemp <<  endl ; 
    return true ; 
}

string TestAnnealer::doLocalCommand(Command* theCommand)  
{
    string theName  = theCommand->getName() ; 
    string returnString = "" ; 
    cout << "running command in annealer" << endl ; 
    if(theName==START_ANNEALER){
        if(startAnnealer()) { 
            returnString += InterfaceXmlString::COMMANDSTATUS_SUCCESS ; 
        }
        else{
            returnString += InterfaceXmlString::COMMANDSTATUS_FAILURE ; 
        }
    }
    return returnString ; 
}

bool TestAnnealer::disposeLocalInterfaces()   
{
    annealerObject  = NULL ; 
    fileReader = NULL ; 
    lowTemp = DBL_MAX ; 
    highTemp = DBL_MIN ; 
    return true  ; 
}



const string TestAnnealer::HIGH_TEMP = "HIGH_TEMP" ; 
const string TestAnnealer::LOW_TEMP = "LOW_TEMP" ; 
const string TestAnnealer::ANNEALER_OBJECT = "ANNEALER_OBJECT" ; 
const string TestAnnealer::TEST_NEURAL_NETWORK = "TEST_NEURAL_NETWORK" ; 
const string TestAnnealer::START_ANNEALER = "START_ANNEALER" ; 
const string TestAnnealer::TEST_ANNEALER = "TEST_ANNEALER" ; 
const string TestAnnealer::FILE_READER = "FILE_READER" ; 

