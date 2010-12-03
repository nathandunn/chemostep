#ifndef LABEL_HPP_
#  define LABEL_HPP_

#include <string>
using std::string ; 


#include <vector>
using std::vector ; 

#include "blitzdefs.hpp"

class DataFilter ; 

class Label {

public:
    Label(int newLabelCount) ;  
    virtual string print() ; 
    virtual void setError( double newError) ;  
    virtual int getLabelCount() ; 
    virtual double getError() ; 
    virtual double getAverageError() ; 
    virtual int getErrorPoints() ; 
    virtual vector<double>* getErrorVector() ; 
    virtual void setErrorVector(vector<double>* newErrorVector) ; 
    virtual vector<double>* getModelTraceVector() ; 
    virtual void setModelTraceVector(vector<double>* newModelTraceVector) ; 

protected:
    virtual double testError(double error) ; 
    int mLabelCount ;  /// Where is this label in the labelset.  Analogous to neuron number.
    double mError ; 
    vector<double>* mErrorVector ;
    vector<double>* mModelTraceVector ;
 

} ;

#endif /* ifndef LABEL_H */
// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


