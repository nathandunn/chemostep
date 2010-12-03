// -*- C++ -*-
// (C) 2003 by Nathan Dunn, <ndunn@idiom.com>
// $Id: DepthFirstSearch.cpp,v 1.40 2003/03/31 22:29:14 ndunn Exp $

#include "DepthFirstSearch.hpp" 

DepthFirstSearch::DepthFirstSearch(NeuronList newConnectionList, vector<int> start, vector<int> stop, int depth , bool newDoStopAtTerminus, bool newDoSelfConnections, bool newDoRecurrentConnections){
    connectionList = newConnectionList ; 
    startPoints = start ; 
    stopPoints = stop ; 
    globalStopPoints = stop ; 
    maxDepth = depth ; 
    doStopAtTerminus = newDoStopAtTerminus ; 
    doSelfConnections = newDoSelfConnections; 
    doRecurrentConnections = newDoRecurrentConnections ; 
    solutionCount = 0 ; 
}


void DepthFirstSearch::setStartPoints(vector<int> newStart){
    startPoints = newStart ; 
}

void DepthFirstSearch::setStopPoints(vector<int> newStop){
    stopPoints = newStop ; 
}

void DepthFirstSearch::setStopPoint(int newStopPoint){
    stopPoints.clear() ; 
    stopPoints.push_back(newStopPoint); 
}

void DepthFirstSearch::setStartPoint(int newStartPoint){
    startPoints.clear() ; 
    startPoints.push_back(newStartPoint); 
}


// init components and begin search
int DepthFirstSearch::doSearch(){

    if(maxDepth < INT_MAX){
        writer->writeHeader(maxDepth+1) ; 
    }else{
        writer->writeHeader(connectionList.size()) ; 
    }
    
  searchTree.clear()  ; 

  if(doStopAtTerminus){
     cout << "Search will stop at any terminal." << endl ; 
      for(int i = 0 ; i < startPoints.size()   ; i++){

          cout << "searching from: "<< LookupTable::findStringEntry(startPoints[i]) ; 
          cout << " to: " ;
          for(int j = 0 ; j < stopPoints.size() ; j++){
              cout << LookupTable::findStringEntry(stopPoints[j]) << " "  ; 
          }
          cout << endl ;

          Neuron neuron = connectionList.getNeuron(  ((Neuron) startPoints[i]).getId() ) ; 
          neuron.setParentId(-1) ; 
          neuron.setParentLocale(-1) ; 
          neuron.setParentConnectionType(GENERAL_CONNECTION) ; 
          neuron.setDepth(0) ; 
          neuron.addViewed(neuron.getId()) ; 
          singleSearch(neuron) ; 
      }
  }
  else
  {
     cout << "Search will look at each terminal individually." << endl ; 
      for(int i = 0 ; i < startPoints.size()   ; i++){

          for(int j = 0 ; j < globalStopPoints.size() ; j++){
              setStopPoint(globalStopPoints[j]) ; 
              cout << "searching from: "<< LookupTable::findStringEntry(startPoints[i]) ; 
              cout << " to: " ;
              for(int j = 0 ; j < stopPoints.size() ; j++){
                  cout << LookupTable::findStringEntry(stopPoints[j]) << " "  ; 
              }
              cout << endl ;

              Neuron neuron = connectionList.getNeuron(  ((Neuron) startPoints[i]).getId() ) ; 
              neuron.setParentId(-1) ; 
              neuron.setParentLocale(-1) ; 
              neuron.setParentConnectionType(GENERAL_CONNECTION) ; 
              neuron.setDepth(0) ; 
              neuron.addViewed(neuron.getId()) ; 
              singleSearch(neuron) ; 
          }
      }
  }


  return 1 ; 
}

bool DepthFirstSearch::isTerminus(Neuron terminusNeuron){

    int id = terminusNeuron.getId() ; 

    for(int i = 0 ; i < stopPoints.size() ; i++){
		if(stopPoints[i] == id){
           return true ; 
        }
    }

    return false ; 
}


//  searches for a 
int DepthFirstSearch::singleSearch(Neuron parentNeuron){
    int parentLocale = parentNeuron.getParentLocale() ; 
    string parentConnectionType = parentNeuron.getParentConnectionType() ; 

    int parentId = parentNeuron.getParentId()  ; 


    parentNeuron.setLocale(searchTree.size()) ; 

    searchTree.addNeuron(parentNeuron) ; 


    
    
    if(isTerminus(parentNeuron)){

      ConnectionPath path ; 
      Connection *connection = NULL ; 
      Connection *parallelConnection = NULL ; 
      Connection *selfConnection = NULL ; 
      Connection *recurrentConnection = NULL ; 
      ++solutionCount ; 

      // let's traverse!
      Neuron tNeuron  = parentNeuron ; 


      // create the connection
      int j = 0 ; 
      int childId = parentNeuron.getId() ; 
      parentLocale = parentNeuron.getParentLocale() ; 

      if(doSelfConnections){
        selfConnection = tNeuron.getConnectionByToId(parentNeuron.getId()) ; 
        if(selfConnection!=NULL){
//            cout << "adding self: " << tNeuron.getId() << endl ; 
            path.addConnection(selfConnection) ; 
        }
      }

      // swim upstream (towards starting point) to create a path 
      while(parentId >=0 && parentLocale >=0 && j < maxDepth ){
        parentConnectionType = tNeuron.getParentConnectionType() ; 
        tNeuron = searchTree.getNeuronAt(parentLocale) ; 
//		cout << "1: adding connection type: " << connection->getType() << endl ; 
        
        // add the normal connection from the path
        connection = tNeuron.getConnectionByToIdAndType(childId,parentConnectionType) ; 
//        cout << "adding forward connection from: " << tNeuron.getId() << " to " << childId << endl ; 
        path.addConnection(connection) ; 
				// TODO: look up parallel connection and add
				// see if there is a parallel connection of not the same type
				parallelConnection = tNeuron.getConnectionByToIdAndNotType(childId,parentConnectionType) ; 
				if(parallelConnection!=NULL){
//          cout << "adding parallel connection to: " << parallelConnection->getFromId() << "-" << parallelConnection->getToId() << ": " << parallelConnection->getWeight() << endl ; 
					path.addConnection(parallelConnection) ; 
				}


        // if self-connection exists, we can add it here
        if(doSelfConnections){
			// add self-connection
            // does self-connection exist, look at self-connection?, lookup original table
            selfConnection = tNeuron.getConnectionByToId(tNeuron.getId()) ; 
            if(selfConnection!=NULL){
                cout << "adding self: " << tNeuron.getId() << endl ; 
                path.addConnection(selfConnection) ; 
            }
        }


//        // if recurrent connections exist, we can add it here
        if(doRecurrentConnections && connection->getType()!="e"){
            // the from id is tNeuron
            int thisFromId = tNeuron.getId() ;

            // tNeuron is the parent neuron, we want to see if the child neuron 
            // exists, and then add it
            // 1. get the ending neuron
            recurrentConnection = tNeuron.getConnectionByToIdAndType(childId,parentConnectionType) ; 
            Neuron endNeuron  = connectionList.getNeuron(recurrentConnection->getToId())  ; 
            // 2. see if a connection can reach the beginning from the ending neuron
            recurrentConnection = endNeuron.getConnectionByToId( thisFromId) ; 
//                cout << "looking for recurrent from: " << endNeuron.getId() << " to " << thisFromId << endl ; 
           
            // 3. add the first connection that it comes across
            if(recurrentConnection!=NULL ){
//                cout << "adding recurrent from: " << endNeuron.getId() << " to " << thisFromId << endl ; 
                path.addConnection(recurrentConnection) ; 
            }
        }


        
		childId = tNeuron.getId() ; 
		parentLocale = tNeuron.getParentLocale() ; 
        ++j ; 
      }
      writer->writeConnection(path) ; 
      writer->write("\n") ; 

      addSolutionPath(path) ; 


      return 1 ; 
    }

    return processChildren(parentNeuron) ; 

}


void DepthFirstSearch::addSolutionPath(ConnectionPath path){
    solutionPaths.push_back(path) ; 
}

// looks at the children, of a parent
int DepthFirstSearch::processChildren(Neuron parentNeuron){
    int parentId = parentNeuron.getId() ; 
    int parentLocale = parentNeuron.getLocale() ; 
    Neuron child ; 
    Connection *downstreamConnection ; 
    int childId ; 

    for(int i = 0 ;  (parentNeuron.getDepth() < maxDepth) && i < parentNeuron.numConnections() ; i++){

        downstreamConnection =  parentNeuron.getConnection(i) ; 
        childId = downstreamConnection->getToId() ; 

        if(!parentNeuron.haveViewed(childId)){
          child = connectionList.getNeuron(childId) ; 
          child.setParentId(parentId) ; 
          child.setParentLocale(parentLocale) ; 
          child.setParentConnectionType(downstreamConnection->getType()) ; 
          child.setViewed(parentNeuron.getViewed()) ; 
          child.addViewed(child.getId()) ; 
          child.setDepth(parentNeuron.getDepth()+1) ; 
          singleSearch(child) ; 
        }
    }
    return 1 ; 
}




// recursively iterate from root, up through parents
void DepthFirstSearch::makeList(Neuron leafNeuron) {

    Neuron thisNeuron  ; 
    Connection* aConnection ; 
    vector<Connection*> aConnectionList ; 
    float sum = 0 ; 
    float prod = 1 ; 
    int hops = 0 ; 
    int parentId = leafNeuron.getParentId() ; 
    int childId = leafNeuron.getId() ; 

   int i = 0 ;  

    while(parentId>=0){
      ++i ; 
        thisNeuron = searchTree.getNeuron(parentId) ; 

        // compile stats
        ++hops ; 

        // 1 - clear all connections
        // 2 - add only the downstream connection from where we came
        aConnection = thisNeuron.getConnectionByToId(childId) ; 

        sum += aConnection->getWeight() ; 
        prod *= aConnection->getWeight() ; 
        
        parentId = thisNeuron.getParentId() ;
        childId  = thisNeuron.getId() ;
    }

}


