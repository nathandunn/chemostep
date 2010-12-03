


/*--------------------------------------------------------------*/
/*  Copyright (c) 2000 by the University of Oregon.		*/
/*  See the COPYRIGHT file in this directory for permission	*/
/*  to use and distribute this software.			*/
/*--------------------------------------------------------------*/

// $Id: OptionList.cpp,v 1.3 2003/01/13 20:53:06 ndunn Exp $

// OptionList.C -- implementation of OptionList class			

// John Conery								
// University of Oregon							
// May 2000								

#include <sstream>
using std::ostringstream;

#include <vector>
using std::vector ;


#include <iostream>
using std::cerr ; 
using std::cout ; 
using std::endl ; 

#include <iterator>
using std::ostream_iterator ; 

#include <cstdlib>
#include <algorithm>
#include <limits.h>


#include "OptionList.hpp"

#include "StringTokenizer.hpp"
using gnuworld::StringTokenizer ; 



// Copy the command line arguments to a local list.  Start at
// argv[1] since we don't want the program name (argv[0]).

OptionList::OptionList(int argc, char *argv[]) {
  for (int i = 1; i < argc; i++)
    theList.push_back(string(argv[i]));
}

// Delete the list and any items left

OptionList::~OptionList() {
  theList.clear();
}

// Local procedures to search the list for command names.  One
// version is used when a command expects a value -- it returns
// the string that immediately follows the command, or else
// "" if the command isn't in the list.  For error checking,
// the procedure makes sure the argument exists (i.e. the user
// didn't give a command as the last item on the line) and the
// value doesn't start with a hyphen.  If the command is found,
// it is removed from the list, and if the argument is valid,
// it is also removed.

// The second procedure is used if a command is a simple flag; 
// if the command is in the list the procedure removes the command
// and returns true.
//
// Future addition: return a list of values up to but not
// including the next command.

string removeArg(const string &name, list<string> &L) {
  string argvalue = "";
  string argname = "-" + name;

  list<string>::iterator ptr = find(L.begin(), L.end(), argname);
  list<string>::iterator next = L.end();

  if (ptr != L.end()) {
    next = ptr;
    advance(next,1);
    L.erase(ptr);
    if ((next != L.end()) && ((*next)[0] != '-')) {
      argvalue = *next;
      L.erase(next);
    }
  }

  return argvalue;
}

bool removeFlag(const string &name, list<string> &L) {
  string argname = "-" + name;

  list<string>::iterator ptr = find(L.begin(), L.end(), argname);

  if (ptr != L.end()) {
    L.erase(ptr);
    return true;
  }
  else {
    return false;
  }
}


// create a list of strings by substituting the input string with a number
// where the token exists
vector<string> OptionList::createList(const string input, const vector<int> numList, char token){
	vector<string> stringList; 	
	stringList.clear() ; 
    if(numList.empty()){
        stringList.push_back(input) ; 
		return stringList ; 
    }


   
    // tokenize input
	StringTokenizer tokenizer(input,token) ; 
    if(tokenizer.size()<2){
		cerr << "input: '"<< input << "' does not contain token: " << token << endl ; 
		stringList.push_back(input) ; 
    }

	string startToken = tokenizer[0] ; 
	string endToken = tokenizer[1] ; 


    
    // put input back together with numList
   	int size = numList.size() ; 
    for(int i = 0 ; i < size ; i++){
		ostringstream buildStringStream ; 
        buildStringStream << startToken << numList[i] << endToken  ; 
        
        // put string in 
        stringList.push_back(buildStringStream.str()) ; 
    }
	

    
    // add it to stringList


    return stringList ; 
}


// tokenize list on char token
vector<string> OptionList::getTokenizedStringList(const string &name, char token){
	vector<string> stringList ;  	 // at least 1 entry
    string arg = removeArg(name,theList) ; 

    // tokenize strings on , 
	StringTokenizer tokenizer(arg,token) ; 

    int size = tokenizer.size() ; 

    for(int i = 0 ; i < size ; i++){
		stringList.push_back(tokenizer[i]) ; 
    }

    return stringList ; 
}


// public method to parse a list of ints into a list
// e.g., -numbers 1,2,5-8,12    yields 1,2,5,6,7,8,12
vector<int> OptionList::getIntList(const string &name, string iDefault) {
	vector<int> numList ;  	 // at least 1 entry

    if(name.length() < 1 ){
		return numList ; 
    }

    string arg = removeArg(name,theList) ; 

    // tokenize strings on , 
	StringTokenizer tokenizer(arg,',') ; 

    int size = tokenizer.size() ; 
    
    for(int i = 0 ; i < size ; i++ ) {
		StringTokenizer listtoken(tokenizer[i],'-') ; 
        if(listtoken.size()==2){
            int start = atoi(listtoken[0].c_str()) ; 
            int end = atoi(listtoken[1].c_str()) ; 
			for(int j = start ; j <= end ; j++){
				numList.push_back(j) ; 
            }
        }else 
        if(listtoken.size()==1){
            // only 1 entry
            numList.push_back(atoi(tokenizer[i].c_str())) ; 
        }else{
            cerr << "a problem with the list string " << endl ; 
            cerr << arg << " tokenizes as: "<< tokenizer[i] << endl ; 
			return numList ; 
        }
    }

    return numList ; 
}


// Public methods -- getInt(), getDouble(), and getOption() call
// removeArg() to locate and remove a command and its argument;
// getFlag() calls removeFlag() to locate and remove a single command.

int OptionList::getInt(const string &name, int idefault, int min, int max) {
  int argvalue = idefault;
  string arg = removeArg(name,theList);
  bool setNeg = false ; 
  if (arg.length() > 0){
	if(arg[0]=='#') {
		setNeg = true ; 
    	argvalue = -atoi(arg.substr(1).c_str());
	}
	else{
    	argvalue = atoi(arg.c_str());
	}

    if(arg[arg.length()-1]=='-'){
		argvalue *= -1 ; 
    }
  }
  return argvalue;
}

double OptionList::getDouble(const string &name, double ddefault, double min, double max) {
  double argvalue = ddefault;
  string arg = removeArg(name,theList);
  bool setNeg = false ; 
  if (arg.length() > 0){
	if(arg[0]=='@') {
		setNeg = true ; 
    	argvalue = -atof(arg.substr(1).c_str());
	}
	else{
    	argvalue = atof(arg.c_str());
	}
//    if(arg[arg.length()-1]=='-'){
//		argvalue *= -1 ; 
//    }
  }
  return argvalue;
}

bool OptionList::getFlag(const string &name, bool bdefault) {
  if (removeFlag(name,theList))
    return true;
  else
    return bdefault;
}

char OptionList::getChar(const string &name, const char &sdefault) {
  char argvalue = sdefault;
  string arg = removeArg(name,theList);
  if (arg.length() == 1 )
    argvalue = arg[0];
  return argvalue;
}


string OptionList::getOption(const string &name, const string &sdefault) {
  string argvalue = sdefault;
  string arg = removeArg(name,theList);
  if (arg.length() > 0)
    argvalue = arg;
  return argvalue;
}

// Debugging utility -- print the contents of the list:

void OptionList::print() const {
  copy(theList.begin(), theList.end(), ostream_iterator<string>(cout,"\n"));
}

// Return a copy of the list:

list<string> &OptionList::contents() {
  return theList;
}

// Return the next string in the list -- don't do this until
// all the options are removed...

string OptionList::next() {
  string s = theList.front();
  theList.pop_front();
  return s;
}

// See if the list is empty

bool OptionList::empty() const {
  return (theList.size() == 0);
}
