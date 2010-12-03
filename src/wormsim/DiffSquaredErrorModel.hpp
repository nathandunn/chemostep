
#ifndef _DiffSquaredErrorModel_hpp_
#define _DiffSquaredErrorModel_hpp_

#include "ErrorModel.hpp" 


class DiffSquaredErrorModel : public ErrorModel {
public:
    DiffSquaredErrorModel() : ErrorModel() {  } ; 
    double getError(double best,double target,double *calcValue = 0 ) ; 
    virtual string getType() { return DIFF_SQUARED ; }   
    virtual void dump(ostream &s) const { 
      s << "ErrorModel type = [ " << DIFF_SQUARED << " ]" ;  
    }

};

#endif
