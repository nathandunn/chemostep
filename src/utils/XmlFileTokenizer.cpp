
#include <iostream>
using std::cout ; 
using std::endl ; 

#include <vector>
using std::vector ; 

#include <string>
using std::string ; 

#include "StringTokenizer.hpp" 
using gnuworld::StringTokenizer ; 

#include "XmlFileTokenizer.hpp"


char newName[256] ; 

/// Plan A, separate files, using the token.  If the token does not exist in the initFile, than go to plan B.  
vector<string>* XmlFileTokenizer::createFileNames( string initFile, int numFiles, char token) 
{
    int returnFind  ; 
    returnFind = initFile.find(token,0) ; 
    if(returnFind==string::npos){
        returnFind = initFile.find(".xml",0) ; 
        // no tokens found.
        if(returnFind==string::npos){
            cout << "[FAIL] no valid tokens found in XmlFileTokenizer: " << initFile << endl ; 
            return NULL ; 
        }
        return createUsingFile(initFile,numFiles) ; 
    }
    else{
        return createUsingToken(initFile,numFiles,token) ; 
    }
}

vector<string>* XmlFileTokenizer::createUsingToken(string initFile,int numFiles,char token) 
{
    StringTokenizer *tokenizerOut = new StringTokenizer(initFile,token) ; 
    vector<string>* returnNames = new vector<string>() ; 
    for(int i = 0 ; i < numFiles ; i++){
        sprintf(newName,"%s%i%s", ((*tokenizerOut)[0]).c_str(),i, ((*tokenizerOut)[1]).c_str() ) ; 
        returnNames->push_back(newName) ; 
    }
    return returnNames ; 
}

vector<string>* XmlFileTokenizer::createUsingFile(string initFile,int numFiles) 
{
    StringTokenizer *tokenizerOut = new StringTokenizer(initFile,'.') ; 
    if( (*tokenizerOut)[1]!="xml"){
        cout << "[FAIL] end token is: " << (*tokenizerOut)[1] << endl ; 
        return NULL ; 
    }
    vector<string>* returnNames = new vector<string>() ; 
    for(int i = 0 ; i < numFiles ; i++){
        sprintf(newName,"%s%s%i%s%s", ((*tokenizerOut)[0]).c_str(),"_",i,".", ((*tokenizerOut)[1]).c_str() ) ; 
        returnNames->push_back(newName) ; 
    }
    return returnNames ; 
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

