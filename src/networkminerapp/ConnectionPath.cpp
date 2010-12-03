// -*- C++ -*-
// FILE: "/Users/ndunn/cvs/NETWORK_MINER/src/ConnectionPath.cpp"
// LAST MODIFICATION: "Wed, 26 Mar 2003 18:30:11 -0800 (ndunn)"
// (C) 2003 by Nathan Dunn, <ndunn@idiom.com>
// $Id: ConnectionPath.cpp,v 1.6 2003/03/28 00:54:45 ndunn Exp $

#include "ConnectionPath.hpp" 

ConnectionPath::ConnectionPath() {

}
 
ConnectionPath::ConnectionPath(vector<Connection*> *path) {
  *this = path ; 
}
 
float ConnectionPath::sumWeights() {
    float sum = 0.0 ;  
    for(int i = 0 ; i < path.size() ; i++){
         sum +=  ((Connection*)path[i])->getWeight() ; 
    }
    return sum ; 
}

Connection *ConnectionPath::removeConnectionAt(int i) {
    vector<Connection*>::iterator counter ; 
    Connection* returnConnection = path[i] ; 
    counter = path.begin() ; 
    counter = counter + i ; 
    path.erase(counter) ; 
   return path[i] ;  
}

Connection *ConnectionPath::getConnectionAt(int i) {
   return path[i] ;  
}
 
float ConnectionPath::prodWeights() {
    float prod = 1.0 ;  
    for(int i = 0 ; i < path.size() ; i++){
         prod *=  ((Connection*)path[i])->getWeight() ; 
    }
    return prod ; 
}

int ConnectionPath::hasConnection(int fromId,int toId){
   int returnAt = -1 ; 
   Connection *aCnxn ; 
   for(int i = 0 ; i < path.size() ; i++){
       aCnxn = path[i] ; 
       if( (aCnxn->getFromId() == fromId) &&
         (aCnxn->getToId() == toId) )
       {
		  return i ; 
       }
   }

   return returnAt ; 
}


int ConnectionPath::hasConnection(int fromId, int toId, string connectionType){
   int returnAt = -1 ; 
   Connection *aCnxn ; 
   for(int i = 0 ; i < path.size() ; i++){
       aCnxn = path[i] ; 
       if( (aCnxn->getFromId() == fromId) &&
         (aCnxn->getToId() == toId)  &&
         (aCnxn->getType() == connectionType ) ) 

       {
		  return i ; 
       }
   }

   return returnAt ; 
}

int ConnectionPath::getStartId() {
    Connection *connection  ; 
    connection =  path[0] ; 
    return connection->getFromId() ; 
}
 
int ConnectionPath::getEndId() {
    Connection *connection = path[path.size()-1] ; 
    connection->getToId() ; 
}
 
vector<float> ConnectionPath::returnWeights() {

    vector<float> weights ; 
    for(int i = 0 ; i < path.size() ; i++){
         weights.push_back(((Connection*)path[i])->getWeight()) ; 
    }
    return weights ; 
}
 
void ConnectionPath::addConnection(Connection *connection) {
   path.push_back(connection) ; 
}

void ConnectionPath::empty() {
   path.empty() ; 
}

int ConnectionPath::size(){
   return path.size() ; 
}


