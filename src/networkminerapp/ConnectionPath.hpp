// -*- C++ -*-
// FILE: "/Users/nathandunn/cvs/NETWORK_MINER/src/ConnectionPath.hpp"
// LAST MODIFICATION: "Wed, 15 Jan 2003 18:54:41 -0800 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@idiom.com>
// $Id: ConnectionPath.hpp,v 1.6 2003/01/16 02:50:54 ndunn Exp $

#ifndef _CONNECTION_PATH_
#define _CONNECTION_PATH_

#include <vector.h>
using std::vector ; 

#include "Connection.hpp"

class ConnectionPath  {

public:
    ConnectionPath() ; 
    ConnectionPath(vector<Connection*> *path) ; 
    void addConnection(Connection *connection) ; 
    void empty() ; 
    int size() ; 
    float sumWeights() ; 
    float prodWeights() ; 
    int getStartId() ; 
    int getEndId() ; 
    int hasConnection(int fromId,int toId) ; 
    int hasConnection(int fromId,int toId, string connectionType) ; 
    vector<float> returnWeights() ; 
    Connection *getConnectionAt(int i) ; 
    Connection *removeConnectionAt(int i ) ; 



// ConnectionPath getPaths(int* rootIds,int* terminalIds) ; 
    
    
private:
    vector<Connection*> path ; 

} ;

#endif

