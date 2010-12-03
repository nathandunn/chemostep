/*
 * $Id$
 */
#ifndef NETDATAPARSER_HPP_
#  define NETDATAPARSER_HPP_


#include <string>
using std::string ; 

#include "ConnectionData.hpp"
#include <TiFlatBaseApp.hpp>


class NetDataParser : public TiFlatBaseApp{

public:
    NetDataParser(string newInterfaceName, string newTypeName, AppInterface* newParent) ; 
    virtual bool parseInput() ; 
    virtual map<string,ConnectionData*>* applyRule(vector<ConnectionData*>* origTable) = NULL; 
    virtual vector<ConnectionData*>* getInputTokens();
    virtual bool dumpParsedConnections(map<string,ConnectionData*>* connectionData);
    string getInputFile() {
        return(mInputFile);
    }
    void setInputFile(string _mInputFile) {
        mInputFile = _mInputFile;
        return;
    }
    string getOutputFile() {
        return(mOutputFile);
    }
    void setOutputFile(string _mOutputFile) {
        mOutputFile = _mOutputFile;
        return;
    }


    // autogui methods
    virtual bool createLocalMaps()  ; 
    virtual string doLocalCommand(Command* theCommand) ;


protected:
    string mInputFile ; 
    string mOutputFile ; 
    vector<ConnectionData*>* inputTokens ; 
} ;

#endif /* ifndef NETDATAPARSER_H */
// -*- C++ -*-
// FILE: "/Users/nathandunn/tla/auto3--dev--1.3.2--patch-8/src/netparserapp/NetDataParser.hpp"
// LAST MODIFICATION: "Wed, 17 Mar 2004 13:54:01 -0800 (nathandunn)"
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

