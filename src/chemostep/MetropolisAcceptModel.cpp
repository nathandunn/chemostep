
#include <iostream>
using std::cout ; 
using std::endl ; 
using std::ostream ; 
using std::min; 

#include <RNG.hpp>

#include "MetropolisAcceptModel.hpp"

#include "AcceptModel.hpp"

#ifdef DOMPI
    #include "mpi.h"
    int met_myid ; 
    int met_nprocs ; 
#endif 


MetropolisAcceptModel::MetropolisAcceptModel(double newConst) : AcceptModel()
{
    mConst= newConst ; 
}

/**  If solution is better than take, other wise if it is only a little worse, than possibly take, as well.
 *
 */
bool MetropolisAcceptModel::accept( double* variables) 
{
//    return ( variables[0] < variables[1] ) ; 

    double probAcceptNew = min(1.0 , exp( ( variables[1]-variables[0] ) / ( mConst* variables[6] ) ) ) ;  

//    cout << "MetropolisAcceptModel: " << probAcceptNew << " current: " << variables[0] << " best: " << variables[1] << endl ; 

    return calcAccept( probAcceptNew) ; 
   
}

bool MetropolisAcceptModel::calcAccept(double probValue) 
{
    #ifdef DOMPI
        MPI_Comm_rank(MPI_COMM_WORLD,&met_myid) ; 
      randomValue = RNG::uniform() ; 
//      cout << met_myid << " probValue: " << probValue << endl ; 
//      cout << met_myid << " pre randomValue: " << randomValue << endl ; 
      MPI_Bcast(&randomValue, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
//      cout << met_myid << " post randomValue: " << randomValue << endl ; 
      if (  probValue >= randomValue )  {
//          cout << met_myid << " return true" << endl ; 
          return true ; 
      }
      else{
//          cout << met_myid << " return false" << endl ; 
          return false ; 
      }
    #else 
      if (  probValue >= RNG::uniform() ) {
          return true ; 
      }
      else{
          return false ; 
      }
    #endif 
}


int MetropolisAcceptModel::getNumVariables() 
{
    return 7 ; 
}

void MetropolisAcceptModel::setConstant(double newConst) 
{
    mConst = newConst ; 
}



void MetropolisAcceptModel::toXML(ostream *s) 
{
    addSpacer(s,1) ; 
    *s << "<acceptmodel type=\"metropolisacceptmodel\">" << endl ; ;   
    addSpacer(s) ; 
    *s << "<numbervariables value=\"" << getNumVariables() << "\"/>" << endl ; ;   
    addSpacer(s,-1) ; 
    *s << "<constant value=\"" << mConst << "\"/>" << endl ; ;   
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

