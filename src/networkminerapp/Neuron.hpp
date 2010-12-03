// -*- C++ -*-
// LAST MODIFICATION: "Fri, 24 Feb 2006 14:10:57 -0800 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@idiom.com>
// $Id: Neuron.hpp,v 1.12 2003/03/28 00:54:45 ndunn Exp $

#ifndef _Neuron_
#define _Neuron_

#include <vector.h>
using std::vector ; 

#include <string>
#include <string.h>
using std::string ; 


#include "Connection.hpp" 

class Neuron{

public:
    Neuron(int newId = -1, int newParentId = -1, int newDepth= -1 ){
      id = newId ; 
      parentId = newParentId ; 
      depth = newDepth ; 
    }  

    Connection *getConnectionByToId(int toId) ; 
    Connection *getConnectionByToIdAndType(int toId,string type) ; 
    Connection *getConnectionByToIdAndNotType(int toId,string type) ; 
    Connection *getFromConnectionByToId(int toId) ; 


    void setId(int newId) {
		id = newId ; 
    }
    int getId(){
      return id ;    
    } 
    void setParentId(int parentNode){
       parentId = parentNode ;  
    }
    int getParentId(){
	   return parentId ; 
    }

    void addDownstreamConnection(int fromId,int toId, float weight,string newConnectionType= GENERAL_CONNECTION) ; 
    bool haveViewed(int queryId) ;

    void setDepth(int newDepth  ){
        depth = newDepth ; 
    }

    void setParentLocale(int newLocale){
        parentLocale = newLocale ; 
    }

    int getParentLocale(){
        return parentLocale ; 
    }

    string getParentConnectionType(){
        return parentConnectionType ; 
    }

    void setParentConnectionType(string newParentConnectionType){
        parentConnectionType = newParentConnectionType ; 
    }


    int getDepth(){
		return depth ; 
    }

    Connection *getConnection(int connectionNumber){
       return downstreamConnections[connectionNumber] ; 
    }

    vector<Connection*> clearConnections(){
       downstreamConnections.clear() ; 
       return downstreamConnections ;     
    }

    int  getLocale(){
       return locale ; 
    }
    
    void setLocale(int newLocale){
       locale = newLocale ; 
    }
   
    vector<Connection*> getConnections(){
       return downstreamConnections ;     
    } 

    void setConnections(vector<Connection*> aConnectionList) {
       downstreamConnections = aConnectionList ; 
    }

    int numConnections(){
       return downstreamConnections.size() ;
    }

    vector<int> addViewed(int seenId){
		haveSeen.push_back(seenId) ; 
        return haveSeen ; 
    }

    vector<int> setViewed(vector<int> viewedIds ){
		haveSeen = viewedIds ; 
        return haveSeen ; 
    }

    vector<int> getViewed(){
        return haveSeen ; 
    }

    static const string delimiter  ;

private:
    int id ; 
    int locale ; 
    int depth ; 
    int parentId ; // this id in the vector to the ONLY parent for this node 
    int parentLocale ; 
    vector<Connection*> downstreamConnections ; 
    string parentConnectionType ;

    // the paths that are valid for this
    vector<int> validPaths ; 
    vector<int> haveSeen ; 

} ;

ostream& operator<<(ostream &s, const Neuron &neuron) ;

#endif 

