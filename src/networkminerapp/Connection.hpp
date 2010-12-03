// -*- C++ -*-
// (C) 2003 by Nathan Dunn, <ndunn@idiom.com>
// $Id: Connection.hpp,v 1.7 2003/03/28 00:54:45 ndunn Exp $

#ifndef _CONNECTION_
#define _CONNECTION_

#include "ConnectionTypes.hpp"

#include <string>
using std::string ;

class Connection{

public:
    Connection(Connection *cnxn) ; 

    Connection(int newFromId, int newToId, float newWeight, string type=GENERAL_CONNECTION) ; 

    virtual void reverseDirection() ;
    
    virtual int getFromId() {
        return fromId ;
    }  
    virtual int getToId() {
        return toId ;
    }  

    virtual void setToId(int newToId) {
        toId = newToId  ;
    }  

    virtual void setFromId(int newFromId) {
        fromId = newFromId  ;
    }  


    virtual float getWeight() {
        return weight;
    } 

    virtual void setType(string newType) {
        type = newType ; 
    }

    virtual string getType() {
        return type ; 
    }

    virtual bool isType(string compareType){
       return (compareType==type) ; 
    }


    
private:
    int fromId ; 
    int toId ; 
    float weight ; 
    string type ; 



} ;

#endif

