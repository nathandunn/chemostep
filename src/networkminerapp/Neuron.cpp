// -*- C++ -*-
// FILE: "/Users/nathandunn/svn/chemotrunk/src/networkminerapp/Neuron.cpp"
// LAST MODIFICATION: "Fri, 24 Feb 2006 14:10:21 -0800 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@idiom.com>
// $Id: Neuron.cpp,v 1.10 2003/03/28 00:54:45 ndunn Exp $

#include "Neuron.hpp"


void Neuron::addDownstreamConnection(int fromId, int toId, float weight,string newConnectionType) {
    Connection *newConnection = new Connection(fromId,toId,weight,newConnectionType) ; 
   downstreamConnections.push_back(newConnection) ; 
}

bool Neuron::haveViewed(int queryId){
    for(int i = 0 ; i < haveSeen.size() ; i++){
        if(haveSeen[i]==queryId){
            return true ; 
        }
    }

    return false ; 
}




Connection *Neuron::getFromConnectionByToId(int toId){
   int thisId = getId() ; 
   Connection *toConnection = NULL ; 
   for(int i = 0 ; i < downstreamConnections.size() ; i++){
     if(downstreamConnections[i]->getToId()==toId){
       toConnection = downstreamConnections[i] ; 
     }
   }
   return NULL ; 
}

Connection *Neuron::getConnectionByToIdAndNotType(int toId,string type){
    int id ;
    string theType ; 
   for(int i = 0 ; i < downstreamConnections.size() ; i++){
     id = downstreamConnections[i]->getToId() ; 
      theType = downstreamConnections[i]->getType() ;
     if(id==toId && theType!=type){
       return downstreamConnections[i] ; 
     }
   }
   return NULL ; 

}


Connection *Neuron::getConnectionByToIdAndType(int toId,string type){
    int id ;
    string theType ; 
   for(int i = 0 ; i < downstreamConnections.size() ; i++){
     id = downstreamConnections[i]->getToId() ; 
      theType = downstreamConnections[i]->getType() ;
     if(id==toId && theType==type){
       return downstreamConnections[i] ; 
     }
   }
   return NULL ; 

}



Connection *Neuron::getConnectionByToId(int toId){
   for(int i = 0 ; i < downstreamConnections.size() ; i++){
     if(downstreamConnections[i]->getToId()==toId){
       return downstreamConnections[i] ; 
     }
   }
   return NULL ; 
}


ostream& operator<<(ostream &s, const Neuron &neuron) 
{

    float multiple = 1.0 ; 
    int id = ((Neuron) neuron).getId() ; 
  s << id << Neuron::delimiter  ;  

  vector<Connection*> connections = ((Neuron) neuron).getConnections() ; 

  s << "(" << connections.size() << ")" << Neuron::delimiter ; 

  for(int i = 0 ; i < connections.size() ; i++){
	s << ((Connection *) connections[i])->getToId() << Neuron::delimiter ; 
	s << ((Connection *) connections[i])->getWeight() << Neuron::delimiter ; 
    multiple *= ((Connection *) connections[i])->getWeight() ; 
  }
  s << "(" << multiple << ")"   ; 
  return s;
}

const string Neuron::delimiter = " " ; 

