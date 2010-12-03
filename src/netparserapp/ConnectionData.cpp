/*
 * $Id$
 */

#include <iostream>
using std::cout ; 
using std::endl ; 

#include "ConnectionData.hpp"

ConnectionData::ConnectionData() :
mKey("")
{
}

void ConnectionData::setKey(string _key){
    mKey = _key ; 
}

string ConnectionData::getKey() 
{
    if(mKey==""){
        return mFromNeuron + mToNeuron + mConnectionType ; 
    }
    else{
        return mKey ; 
    }
}


ConnectionData::ConnectionData(ConnectionData* newConnectionData) 
{
   mFromNeuron=newConnectionData->getFromNeuron() ;  
   mToNeuron=newConnectionData->getToNeuron() ;  
   mConnectionSource=newConnectionData->getConnectionSource() ;  
   mConnectionType=newConnectionData->getConnectionType() ;  
   mNumConnections=newConnectionData->getNumConnections() ;  
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
// FILE: "/Users/nathandunn/tla/auto3--dev--1.3.2--base-0/src/netparserapp/ConnectionData.cpp"
// LAST MODIFICATION: "Fri, 12 Mar 2004 16:07:24 -0800 (nathandunn)"
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

