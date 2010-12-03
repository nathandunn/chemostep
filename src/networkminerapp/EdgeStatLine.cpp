// -*- C++ -*-
// FILE: "/Users/nathandunn/svn/chemotrunk/src/networkminerapp/EdgeStatLine.cpp"
// LAST MODIFICATION: "Mon, 27 Feb 2006 12:17:13 -0800 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@idiom.com>
// $Id: EdgeStatLine.cpp,v 1.11 2003/04/01 21:24:00 ndunn Exp $

#include "EdgeStatLine.hpp" 

EdgeStat *EdgeStatLine::getEdge(int count){
    return edges[count] ; 
}

int EdgeStatLine::numEdges(){
   return edges.size() ; 
}

int EdgeStatLine::numRules(){
   return templateRules.size() ; 
}

CountRule *EdgeStatLine::getRule(int count) {
	return templateRules[count] ; 
}

int EdgeStatLine::getRulePosition(string rule) {
    for(int i = 0 ; i < templateRules.size() ; i++){
      if(rule==templateRules[i]->getType()){
        return i ; 
      }
    }
    cout << "rule not found" << endl ;
    exit(1) ; 
    return NULL ; 
}


CountRule *EdgeStatLine::getRule(string rule) {
    
    for(int i = 0 ; i < templateRules.size() ; i++){
      if(rule==templateRules[i]->getType()){
        return templateRules[i] ; 
      }
    }
    cout << "rule not found" << endl ;
    exit(1) ; 
    return NULL ; 
}

float EdgeStatLine::getMinForRule(string rule){
   int ruleNumber = getRulePosition(rule) ; 
   float min = DBL_MAX ; 

   for(int i = 0 ; i < edges.size() ; i++){
     if((edges[i]->getRule(ruleNumber))->getCount() < min){
		min = (edges[i]->getRule(ruleNumber))->getCount() ; 
     }
   }
   return min ; 
}

float EdgeStatLine::getMaxForRule(string rule){
   int ruleNumber = getRulePosition(rule) ; 

   float max = 0 ; 
   for(int i = 0 ; i < edges.size() ; i++){
          
     if((edges[i]->getRule(ruleNumber))->getCount() > max){
		max = (edges[i]->getRule(ruleNumber))->getCount() ; 
     }
   }
   return max ; 
}


int EdgeStatLine::calcPath(Connection *cnxn){

    string fromString = LookupTable::findStringEntry(cnxn->getFromId()) ;
    string toString = LookupTable::findStringEntry(cnxn->getToId()) ; 
	float weightString = cnxn->getWeight() ; 
	string cnxnType = cnxn->getType() ; 

    int added = 0 ; 
    int path = 0 ; 

    path = getPathPosition(cnxn) ; 

    // add an edge
    if(path==DOES_NOT_EXIST){
		    EdgeStat *newEdge = new EdgeStat(cnxn) ;
        newEdge->addRules(templateRules) ; 
        newEdge->resetRules() ; 
        edges.push_back(newEdge) ; 
			  path = getPathPosition(cnxn) ; 
        ++added ; 
//        cout << "just added path: " << cnxn->getFromId() << "-" << cnxn->getToId() << " type: " << cnxn->getType() << endl ; 
    }
//    else{ 
			// do nothing
//        cout << "path exists: " << cnxn->getFromId() << "-" << cnxn->getToId() << " type: " << cnxn->getType() << endl ; 
				// if there is only one type, or path exists for both types, do nothing
				// if there is another path/connection type, then create an edge and push back
//    }
    edges[path]->calcStats(cnxn) ; 

    return added  ; 
}

void EdgeStatLine::addRule(CountRule *newRule) {
    templateRules.push_back(newRule) ; 
}

int EdgeStatLine::getPathPosition(Connection *cnxn) {

    string fromCompare = LookupTable::findStringEntry(cnxn->getFromId()) ;
    string toCompare = LookupTable::findStringEntry(cnxn->getToId()) ;
		string theType = cnxn->getType() ; 

    EdgeStat edgeStat ; 
    for(int i = 0 ; i < edges.size() ; i++){
        edgeStat = *edges[i] ; 
        if( edgeStat.getFrom()==fromCompare  && 
            edgeStat.getTo()==toCompare  && 
            edgeStat.getType()==theType )
        {
                return i ; 
        }
    }

    return DOES_NOT_EXIST ; 
}



