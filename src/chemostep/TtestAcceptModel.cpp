
#include <iostream>
using std::cout ; 
using std::endl ; 
using std::ostream ; 


#include "TtestAcceptModel.hpp"

double acceptTable[] = {0.5,0.4,0.3,0.2,0.1,0.05,0.02,0.01,0.001}   ; 
double df50Table[] = {0.679,0.849,1.047,1.299,1.676,2.009,2.403,2.678,3.496}   ; 
double df100Table[] = {0.677,0.845,1.042,1.290,1.660,1.984,2.363,2.626,3.390}   ; 
double dfInfTable[] = {0.674,0.842,1.036,1.282,1.645,1.960,2.326,2.576,3.291}   ; 

TtestAcceptModel::TtestAcceptModel(double newCrit) : AcceptModel() 
{
    mCrit = newCrit ; 
}



/// Returns true if the significance of the difference between two groups is greater than the critical amount, and compare1 < compare2.   <compare1><compare2><sdev1><sdev2><crit>
//bool TtestAcceptModel::accept(double compare1,double compare2,double sdev1,double sdev2,int count1,int count2) 
bool TtestAcceptModel::accept(double* variables) 
{
//    cout << "compare1: " << variables[0] << " sdev1: " << variables[2] << " count1: " << variables[4] << endl ; 
//    cout << "compare2: " << variables[1] << " sdev2: " << variables[3] << " count2: " << variables[5] << endl ; 
//    cout << "mCrit: " << mCrit << endl ; 

    if(variables[0] >= variables[1]){
//        cout << "WORSE mean [fail]" << endl ; 
        return false ; 
    }
    else{
        // create tvalue
        mTvalue = ( variables[1] - variables[0]) ; 
        mTvalue = mTvalue / sqrt (  ( pow(variables[3],2.0) / variables[5]) + ( pow(variables[2],2.0) / variables[4]) ) ; 
//cout << "tvalue: " << mTvalue << endl ; 

        if( compareTValue( mCrit,mTvalue, (int) (variables[4]+variables[5]) )==true){
//cout << "BETTER mean [true]" << endl ; 
            return true ; 
        }
        else{
//cout << "BETTER mean [fail]" << endl ; 
            return false ; 
        }

    }
}

///  Returns true and false based on table values, the critical cutoff, the tvalue, and the total number of samples.  Initially just look at the 50df table only, as the values don't seem that close, really.
bool TtestAcceptModel::compareTValue(double crit, double tvalue, int count) 
{
    for(int i = 9 ; i > 0 ; i--){
        // exits immediately if true
        if(tvalue > df50Table[i-1]){
            return true ; 
        }
        else
        if(crit <= acceptTable[i-1]){
            if(tvalue > df50Table[i-1]){
                return true ; 
            }
            else{
                return false ; 
            }
        }
    }
    return false ; 
}


int TtestAcceptModel::getNumVariables() 
{
    return 6 ; 
}

void TtestAcceptModel::setCriticalCutoff(double newCrit) 
{
    mCrit = newCrit ; 
}

double TtestAcceptModel::getCriticalCutoff() 
{
    return mCrit ; 
}

void TtestAcceptModel::toXML(ostream *s) 
{
    addSpacer(s,1) ; 
    *s << "<acceptmodel type=\"ttestacceptmodel\">" << endl ; ;   
    addSpacer(s) ; 
    *s << "<numbervariables value=\"" << getNumVariables() << "\"/>" << endl ; ;   
    addSpacer(s,-1) ; 
    *s << "<cutoff value=\"" << mCrit << "\"/>" << endl ; ;   
    addSpacer(s) ; 
    *s << "</acceptmodel>" << endl ; ;   
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

