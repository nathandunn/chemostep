// -*- C++ -*-
// (C) 2003 by Nathan Dunn, <ndunn@idiom.com>
// $Id: Connection.cpp,v 1.4 2003/01/10 20:27:10 ndunn Exp $

#include "Connection.hpp" 
Connection::Connection(int newFromId, int newToId, float newWeight,string newType) {
    toId = newToId ; 
    fromId = newFromId ; 
    weight = newWeight ; 
    type = newType ; 
}

Connection::Connection(Connection *cnxn) {
   		fromId = cnxn->getFromId();  
   		toId = cnxn->getToId();  
   		weight = cnxn->getWeight() ; 
   		type = cnxn->getType() ; 
	} 

void Connection::reverseDirection() {
			int tempId = fromId ; 
			fromId = toId ; 
			toId = fromId ; 
	}

