/*
 * $Id$
 */

#include <iostream>
using std::cout ; 
using std::endl ; 

#include "ASymmParser.hpp"

ASymmParser::ASymmParser(string newInterfaceName, string newTypeName, AppInterface* newParent) : SymmParser(newInterfaceName,newTypeName,newParent)
{
}


map<string,ConnectionData*>* ASymmParser::applyRule(vector<ConnectionData*>* origTable) 
{
    map<string,ConnectionData*>* returnTable = new map<string,ConnectionData*>() ; 
    vector<ConnectionData*>::iterator vectorIter ; 
    map<string,ConnectionData*>::iterator mapIter ; 
    vectorIter = origTable->begin() ; 

    ConnectionData* tmpConnection = NULL ; 
    cout << "mapIter->size(): " << origTable->size() << endl ; 

    while(vectorIter!=origTable->end()){
        tmpConnection= *vectorIter ; 


        // we found a previous version in there, so handle it. 
        if(tmpConnection->getConnectionType()=="Gap_junction"){
            tmpConnection->setConnectionType("e") ; 
            mapIter = returnTable->find(tmpConnection->getKey()) ; 
            if(mapIter!=returnTable->end()){
                (mapIter->second)->setNumConnections( (mapIter->second)->getNumConnections() +tmpConnection->getNumConnections()) ;
            }
            else{
                returnTable->insert(pair<string,ConnectionData*>(tmpConnection->getKey(),tmpConnection))   ; 
            }
        }
        else
        if(tmpConnection->getConnectionType()=="Send"){
            tmpConnection->setConnectionType("c") ; 
            mapIter = returnTable->find(tmpConnection->getKey()) ; 
            if(mapIter!=returnTable->end()){
                (mapIter->second)->setNumConnections( (mapIter->second)->getNumConnections() +tmpConnection->getNumConnections()) ;
            }
            else{
                returnTable->insert(pair<string,ConnectionData*>(tmpConnection->getKey(),tmpConnection))   ; 
            }
        }
        else
        if(tmpConnection->getConnectionType()=="Receive"){
            tmpConnection->setConnectionType("c") ; 
            tmpConnection->setKey(tmpConnection->getToNeuron()+tmpConnection->getFromNeuron()+tmpConnection->getConnectionType()) ; 
            mapIter = returnTable->find(tmpConnection->getKey()) ; 
            if(mapIter!=returnTable->end()){
                (mapIter->second)->setNumConnections( (mapIter->second)->getNumConnections() +tmpConnection->getNumConnections() ) ;
            }
            else{
                returnTable->insert(pair<string,ConnectionData*>(tmpConnection->getKey(),tmpConnection))   ; 
            }
        }
        else
        if(tmpConnection->getConnectionType()=="Send_joint"){
            tmpConnection->setNumConnections(0.5 * tmpConnection->getNumConnections()) ; 
            tmpConnection->setConnectionType("c") ; 
            mapIter = returnTable->find(tmpConnection->getKey()) ; 
            if(mapIter!=returnTable->end()){
                (mapIter->second)->setNumConnections( (mapIter->second)->getNumConnections() +tmpConnection->getNumConnections()) ;
            }
            else{
                returnTable->insert(pair<string,ConnectionData*>(tmpConnection->getKey(),tmpConnection))   ; 
            }
        }
        else
        if(tmpConnection->getConnectionType()=="Receive_joint"){
            tmpConnection->setNumConnections(0.5 * tmpConnection->getNumConnections()) ; 
            tmpConnection->setConnectionType("c") ; 
            tmpConnection->setKey(tmpConnection->getToNeuron()+tmpConnection->getFromNeuron()+tmpConnection->getConnectionType()) ; 
            mapIter = returnTable->find(tmpConnection->getKey()) ; 
            if(mapIter!=returnTable->end()){
                (mapIter->second)->setNumConnections( (mapIter->second)->getNumConnections() +tmpConnection->getNumConnections() ) ;
            }
            else{
                returnTable->insert(pair<string,ConnectionData*>(tmpConnection->getKey(),tmpConnection))   ; 
            }
        }
        else{
            cout << "type not found: " << tmpConnection->getConnectionType() << endl ; 
        }
        ++vectorIter ; 
    }

//    for(int i = 0 ; i < inputTokens->size() ; i++){
//        tempCnxnData = new ConnectionData(  (*origTable)[i] ) ; 
//        returnTable->insert( pair<string,ConnectionData*>(tempCnxnData->getKey(),  tempCnxnData)   ) ; 
//    }
    
    delete tmpConnection ; 
    return returnTable ; 
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
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

