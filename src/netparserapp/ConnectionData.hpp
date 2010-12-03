/*
 * $Id$
 */
#ifndef CONNECTIONDATA_HPP_
#  define CONNECTIONDATA_HPP_

#include <string>
using std::string ; 


class ConnectionData {

public:
    ConnectionData() ; 
    ConnectionData(ConnectionData* newConnectionData) ; 
    string getKey() ; 
    void setKey(string _key) ; 
    string getFromNeuron() {
        return(mFromNeuron);
    }
    void setFromNeuron(string _mFromNeuron) {
        mFromNeuron = _mFromNeuron;
        return;
    }
    string getToNeuron() {
        return(mToNeuron);
    }
    void setToNeuron(string _mToNeuron) {
        mToNeuron = _mToNeuron;
        return;
    }
    string getConnectionType() {
        return(mConnectionType);
    }
    void setConnectionType(string _mConnectionType) {
        mConnectionType = _mConnectionType;
        return;
    }
    string getConnectionSource() {
        return(mConnectionSource);
    }
    void setConnectionSource(string _mConnectionSource) {
        mConnectionSource = _mConnectionSource;
        return;
    }
    float getNumConnections() {
        return(mNumConnections);
    }
    void setNumConnections(float _mNumConnections) {
        mNumConnections = _mNumConnections;
        return;
    }







protected:
    string mFromNeuron ; 
    string mToNeuron ; 
    string mConnectionType ; 
    string mConnectionSource  ; 
    float mNumConnections ; 
    string mKey; 

} ;

#endif /* ifndef CONNECTIONDATA_H */
// -*- C++ -*-
// FILE: "/Users/nathandunn/tla/auto3--dev--1.3.2--base-0/src/netparserapp/ConnectionData.hpp"
// LAST MODIFICATION: "Fri, 12 Mar 2004 16:06:36 -0800 (nathandunn)"
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

