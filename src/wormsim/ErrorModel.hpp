
#ifndef _ErrorModel_hpp_
#define _ErrorModel_hpp_

#include <iostream>
using std::ostream ; 


#include <string>
using std::string ; 




// global reference to models this NeuralNet uses
const string ERROR_MODEL = "ABSTRACT" ; 
const string DIFF_SQUARED = "DIFFSQUARED" ; 
const string DUAL_LIMIT = "DUALLIMIT" ; 


class ErrorModel{

public:
    ErrorModel(){  } ; 
    virtual double getError(double best,double target,double *calcValue = 0 ) { return (double) 0 ; }   
    virtual string getType() { return ERROR_MODEL ; }   
    virtual void dump(ostream &s) const { 
      s << "ErrorModel type = [ " << ERROR_MODEL << " ]" ;  
    }

    
};


#endif



