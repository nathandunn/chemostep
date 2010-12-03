/*
 * $Id$
 */

#include <iostream>
using std::cout ; 
using std::endl ; 
using std::ios ;

#include <fstream>
using std::ifstream ; 
using std::ofstream ; 

#include <string>
using std::string ; 

#include <vector>
using std::vector ; 

#include <Command.hpp>
#include <InterfaceXmlString.hpp>
#include <TiFlatBaseApp.hpp>
#include <Renderer.hpp>

#include <StringTokenizer.hpp>
using gnuworld::StringTokenizer ; 


#include "NetDataParser.hpp"


NetDataParser::NetDataParser(string newInterfaceName, string newTypeName, AppInterface* newParent) : TiFlatBaseApp(newInterfaceName,newTypeName,newParent) 
{
    description = "Parses raw connectivity data into a searchable archive." ; 
}

vector<ConnectionData*>* NetDataParser::getInputTokens(){

    // open input file
    ifstream inFile ; 
	try{
        inFile.open(mInputFile.c_str(),ios::in) ; 
    }catch(const char* error){
        throw "failed to open file" + mInputFile+ "  error " + error +"\n"; 
    }
    catch(...){
        throw "failed to open sig: " + mInputFile ; 
    }

    if(!inFile)
    {
       throw "failed to read file: " + mInputFile ;
    }

    int charCount = 0 ; 
    static const int INPUT_BUFF = 256 ; 
    char *buffer = new char[INPUT_BUFF] ; 
    const char linedelimeter = '\n' ;  
    StringTokenizer *tokenizerOut = NULL ; 
    ConnectionData *newConnectionData = new ConnectionData() ; 

  try{

      inputTokens = new vector<ConnectionData*>() ; 
      while( inFile.getline(buffer,INPUT_BUFF,'\n') ){
          // just read a single line for now
//          cout << "adding to file: " << buffer << endl ; 

          /// the files are tab delimited
          tokenizerOut = new StringTokenizer(buffer,'\t') ; 
//          cout << "num tokens: " << tokenizerOut->size() << endl ; 
          newConnectionData->setFromNeuron( (*tokenizerOut)[0]) ; 
          newConnectionData->setToNeuron( (*tokenizerOut)[1]) ; 
          newConnectionData->setConnectionType( (*tokenizerOut)[2]) ; 
          newConnectionData->setConnectionSource( (*tokenizerOut)[3]) ; 
          newConnectionData->setNumConnections( atof(  ((*tokenizerOut)[4]).c_str()  )) ; 
          inputTokens->push_back(new ConnectionData(newConnectionData)) ; 
      }
  }
  catch(const char *error){
      cout << "error reading sigdata file: " << error << endl ; 
  }
  catch(...){
      cout << "unspecified reading sigdata file: " << mInputFile << endl ; 
  }


    return inputTokens ; 
}



bool NetDataParser::parseInput() 
{
    cout << "parsing input " << endl ; 
       
    // get tokens
    inputTokens = getInputTokens() ; 
    
    // apply rules while tallying
    // 0 = from, 1 = to, 2 = type, 3 = source, 4 = numconnections
    cout << "number of connections: " << inputTokens->size() <<  endl ; 

    map<string,ConnectionData*>* uniqueConnections = applyRule(inputTokens) ; 
    

    // send resultant table to output
    dumpParsedConnections(uniqueConnections) ; 
    

    return true ; 
}

bool NetDataParser::dumpParsedConnections(map<string,ConnectionData*>* connectionData)
{
    ofstream outFile ;
	try{
        outFile.open(mOutputFile.c_str(),ios::out) ; 
    }catch(const char* error){
        throw "failed to open file" + mOutputFile+ "  error " + error +"\n"; 
    }
    catch(...){
        throw "failed to open file: " + mOutputFile ; 
    }

    if(!outFile)
    {
       throw "failed to write file: " + mOutputFile ;
    }

    map<string,ConnectionData*>::iterator mapIter ;
    mapIter = connectionData->begin() ; 
    ConnectionData* tmpConnectionData ; 
    while(mapIter != connectionData->end()){
        tmpConnectionData = mapIter->second ; 
        outFile << tmpConnectionData->getFromNeuron()  ; 
        outFile << " " ; 
        outFile << tmpConnectionData->getToNeuron()  ; 
        outFile << " " ; 
        outFile << tmpConnectionData->getConnectionType()  ; 
        outFile << " " ; 
        outFile << tmpConnectionData->getNumConnections()  ; 
        outFile << endl ; 
        ++mapIter ; 
    }

    return true ; 
}

bool NetDataParser::createLocalMaps()  
{
    addOptionToMap( "INPUT_FILE", OPT_FILE_LOAD,&mInputFile,"APP/SymmParser","input raw connections") ; 
    addOptionToMap( "OUTPUT_FILE", OPT_FILE_SAVE,&mOutputFile,"APP/SymmParser","parsed output") ; 
    addCommandToMap( "parse") ; 
//    addCommandToMap( "parse",*(parseInput())) ; 
    return true ; 
}

string NetDataParser::doLocalCommand(Command *theCommand) 
{
    cout << "doing command: " << theCommand->getName() << endl ; 
    mRenderer->savePreferences() ; 

    // eventually this should be start and stop annealer
    string theName  = theCommand->getName() ; 
    string returnString = "" ; 
    if(theName=="parse"){
        if(parseInput()==true){
            returnString += InterfaceXmlString::COMMANDSTATUS_SUCCESS; 
        }
        else{
            returnString += InterfaceXmlString::COMMANDSTATUS_FAILURE ; 
        }
    }
    cout << "the return string" << endl ; 
    return returnString ; 
}


/* Function int main(int argc, char **argv) {{{ */
//int main(int argc, char **argv)
//{


//    return 0;
//} /* }}} */


/* Modeline for ViM {{{
 * vim:set ts=4:
 * vim600:fdm=marker fdl=0 fdc=3:
 * }}} */

// -*- C++ -*-
// FILE: "/Users/ndunn/tlalocal/auto3--localdev--1.3.3--base-0/src/netparserapp/NetDataParser.cpp"
// LAST MODIFICATION: "Thu, 18 Mar 2004 20:08:51 -0800 (ndunn)"
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

