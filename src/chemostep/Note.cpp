
#include <iostream>
using std::cout ; 
using std::endl ; 

using std::pair ; 

#include <string>
using std::string ; 

#include <stdio.h>

#include <sstream>
using std::ostringstream ; 

#include <map>
using std::map ; 

#include "Note.hpp"


typedef pair<string, string> String_Pair;
char buffer[256] ; 

Note::Note(Note* newNote) : map<string,string>(*newNote)
,mStringStream(new ostringstream())
{
    
}


Note::Note():map<string,string>() 
,mStringStream(new ostringstream())
{

}

// returns a series of name-value pairs
string* Note::getText() 
{
    string* returnString = new string() ;  

    mHashIter = begin() ; 
    while( mHashIter != end() ) {
        *returnString  += mHashIter->first + mHashIter->second + "\n" ; 
        ++mHashIter ; 
    }
	return returnString ; 
}


void Note::toXML(ostream *s) 
{
    addSpacer(s,1) ; 
    *s <<  "<note>" << endl  ; 

    mHashIter = begin() ; 
    while( mHashIter != end() ) {
        addSpacer(s) ; 
        *s << "<" << mHashIter->first << " value=\"" << mHashIter->second << "\" />" << endl  ; 
        ++mHashIter ; 
    }
    decrementTabCount() ;
    addSpacer(s) ; 
    *s << "</note>" <<endl ; 
    
}


string Note::toXML(int numTabs) 
{
    mStringStream->str("") ; 
    toXML(mStringStream) ; 

    return mStringStream->str() ; 
}



void Note::clearNotes() 
{
    empty() ; 
}

void Note::addNote(string name,string value) 
{
    insert (  String_Pair(name,value))    ; 
}

void Note::setNote(string name,double value) 
{
    #ifdef MACOSX
    mStringStream->str("") ; // this doesn't seem to work for non-apple implementations
    *mStringStream << value ; 
    setNote( name, mStringStream->str() ) ; 
    #else 
    sprintf( buffer,"%f",value) ;
    setNote( name, string(buffer) ) ; 
    #endif
}


void Note::setNote(string name,string value) 
{
    if(getNote(name)==NULL){
//        cout << "adding: " << name << "["<<value << "]" << endl ; 
        addNote(name,value) ; 
    }
    else{
//        cout << "setting: " << name << "["<<value << "]" << endl ; 
        (*this)[name] = value ; 
    }
}


string* Note::getNote(string name) 
{
    mHashIter = find(name) ; 
    if(mHashIter==end()){
        return NULL ; 
    }
    else{
        return &(mHashIter->second) ; 
    }
}


/// The copy operator goes through all of its notes, copying any of its, or deleting it, then it goes through all of the other notes.  
Note& Note::operator=(Note &rhsNote){

    // lets us run through all of THEIR keys, first
    map<string,string>::iterator rhsNoteIter = rhsNote.begin() ; 

    // copy RHS from LHS and delete points that don't exist in the RHS
    mHashIter  = begin() ;
    while(mHashIter != end()){
        if( rhsNote.getNote( mHashIter->first ) == NULL){
            erase(mHashIter) ;  
        }
        else{
			setNote(mHashIter->first, *(rhsNote.getNote( mHashIter->first)) ) ; 
        }
        ++mHashIter ; 
    }

    // copy anything missing from RHS into LHS
    rhsNoteIter= rhsNote.begin() ; 
    while(rhsNoteIter != rhsNote.end()){
    		// should call addNote
			setNote(rhsNoteIter->first, *(rhsNote.getNote( rhsNoteIter->first))  ) ; 
//        }
        ++rhsNoteIter; 
    }

}


/* Function int main(int argc, char **argv) {{{ */
//int main(int argc, char **argv)
//{


//    return 0;
//} /* }}} */


/* Modeline for ViM {{{
 * vim:set ts=4:
 * vim600:fdm=marker fdl=0 fdc=3:
 * }}} */

// -*- C++ -*-
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$


