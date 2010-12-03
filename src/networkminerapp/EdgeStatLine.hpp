// -*- C++ -*-
// FILE: "/Users/nathandunn/svn/chemotrunk/src/networkminerapp/EdgeStatLine.hpp"
// LAST MODIFICATION: "Mon, 27 Feb 2006 11:37:51 -0800 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@idiom.com>
// $Id: EdgeStatLine.hpp,v 1.8 2003/02/06 23:39:26 ndunn Exp $

#ifndef _EDGESTATLINE_
#define _EDGESTATLINE_

#include <string>
using std::string ; 

#include <vector>
using std::vector ; 

#include <iostream>
using std::iostream ; 


#include <float.h>

#include "Connection.hpp"
#include "CountRule.hpp"
#include "CountEachRule.hpp"
#include "CountWeightRule.hpp"
#include "EdgeStat.hpp"

class EdgeStatLine{

public:
    EdgeStatLine() {  } ;

    // return the number of paths added, 1 or 0
    int calcPath(Connection *cnxn) ; 
    void addRule(CountRule *newRule)  ; 

    // need to define later ?
    void setOutput() { }; 
    int numEdges() ; 
    int numRules() ; 
    void addPath(EdgeStat newEdge) ; 
    CountRule *getRule(string rule) ; 
    CountRule *getRule(int count) ; 
    EdgeStat *getEdge(int count) ; 
    float getMaxForRule(string rule) ; 
    float getMinForRule(string rule) ; 


protected:
    int getPathPosition(Connection *cnxn) ; 
    int getRulePosition(string rule) ; 

    // keep a list here, for when we add edges, add a blank copy
    vector<CountRule*> templateRules ; 
    vector<EdgeStat*> edges ; 
    const static int DOES_NOT_EXIST = -5 ; 

} ;

#endif

