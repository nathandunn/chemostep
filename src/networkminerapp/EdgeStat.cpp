// -*- C++ -*-
// FILE: "/Users/nathandunn/cvs/NETWORK_MINER/src/EdgeStat.cpp"
// LAST MODIFICATION: "Tue, 01 Apr 2003 13:25:08 -0800 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@idiom.com>
// $Id: EdgeStat.cpp,v 1.11 2003/04/01 21:24:00 ndunn Exp $

#include "EdgeStat.hpp"


float EdgeStat::getStatFromRule(int count) {
	return rules[count]->getCount() ; 
}


float EdgeStat::getStatFromRule(string rule) {
    for(int i = 0 ; i < rules.size() ; i++){
      if(rule==rules[i]->getType()){
        return rules[i]->getCount() ; 
      }
    }
    cout << "rule not found" << endl ;
    exit(1) ; 
    return 0.0; 
}



EdgeStat::EdgeStat() {
    from = "NONE" ; 
    to = "NONE" ; 
    rules = *(new vector<CountRule*>()) ; 
}


EdgeStat::EdgeStat(Connection* cnxn) {
    EdgeStat() ; 
    from = LookupTable::findStringEntry(cnxn->getFromId()) ; 
    to = LookupTable::findStringEntry(cnxn->getToId()) ; 
    type = cnxn->getType() ; 
}


string EdgeStat::getTo(){
   return to ; 
}

string EdgeStat::getType(){
   return type ; 
}

string EdgeStat::getFrom(){
   return from ; 
}

string EdgeStat::getRuleType(int count) {
       return  rules[count]->getType() ;
}

void EdgeStat::calcStats(Connection *cnxn){
//    cout << "at " ; 
//    cout << LookupTable::findStringEntry(cnxn->getFromId()) << " " ;
//    cout << LookupTable::findStringEntry(cnxn->getToId()) << " " ; 
//    cout << cnxn->getWeight() << endl ; 

   for(int i = 0 ; i < numRules() ; i++){
       rules[i]->countValue(cnxn) ;
//       cout << "rule " << i+1 << " new value: "<< rules[i]->getCount() << " " << endl ; 
   }
}


string EdgeStat::getStats(){

   string returnString = "" ; 
   returnString += from + " " + to ; 

   return returnString ; 
}


void EdgeStat::resetRules() {
    for(int i = 0 ; i < rules.size() ; i++){
		rules[i]->reset() ; 
    }
}
  
void EdgeStat::addRule(CountRule *newRule) {
    
    CountRule *rule = new CountRule(newRule) ; 

    if(newRule->getType()==CountRule::COUNT_TYPE){
       rule = new CountRule(newRule) ; 
       rules.push_back(rule) ; 
    }
    else
    if(newRule->getType()==CountRule::COUNT_EACH){
       rule =   new CountEachRule() ; 
       rules.push_back(rule) ; 
    }
    else
    if(newRule->getType()==CountRule::COUNT_WEIGHT){
       rule =  new CountWeightRule() ; 
       rules.push_back(rule) ; 
    }
    else
    if(newRule->getType()==CountRule::COUNT_WEIGHT_ONLY){
       rule =  new CountWeightOnlyRule() ; 
       rules.push_back(rule) ; 
    }

}

CountRule *EdgeStat::getRule(int ruleNum) {
    return rules[ruleNum] ;
}

void EdgeStat::addRules(vector<CountRule*> newRules) {
    rules.clear() ; 
    for(int i = 0 ; i < newRules.size() ; i++){
        addRule(newRules[i]) ; 
    }
}


int EdgeStat::numRules(){
  return rules.size() ; 
}



