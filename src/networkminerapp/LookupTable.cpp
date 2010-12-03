// -*- C++ -*-
// FILE: "/Users/nathandunn/cvs/NETWORK_MINER/src/LookupTable.cpp"
// LAST MODIFICATION: "Fri, 17 Jan 2003 10:36:25 -0800 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@idiom.com>
// $Id: LookupTable.cpp,v 1.3 2003/01/17 18:10:16 ndunn Exp $

#include <iostream>
using std::cout ; 
using std::cerr ; 
using std::endl ; 

#include "LookupTable.hpp"


void LookupTable::addEntry(string newEntry){

    LookupField newField(fields.size()+1,newEntry) ; 
    fields.push_back(newField) ; 
}

string LookupTable::findStringEntry(int findId){
    for(int i = 0 ; i < fields.size() ; i++){
	  if(((LookupField) fields[i]).getId()==findId){
		return ((LookupField) fields[i]).getName() ;
      }
    }

}

int LookupTable::findId(string findName){
    int compare = 0 ; 
    for(int i = 0 ; i < fields.size() ; i++){
        compare = strcmp(  (((LookupField) fields[i]).getName()).c_str(),findName.c_str()) ; 
	  if(compare==0){
//        cout << "at i: " << i << endl ; 
		return ((LookupField) fields[i]).getId() ;
      }
    }

    return -1 ; 
}

vector<LookupField> LookupTable::fields ; 

