#ifndef ALOPEXER_HPP_
#  define ALOPEXER_HPP_


#include "AnnealingTarget.hpp"
#include "AcceptModel.hpp"
#include <iostream>
using std::ostream;

class AnnealingTarget; 



class Alopexer {

public:
    Alopexer(): mAcceptModel(new AcceptModel())
    {}
    virtual AnnealingTarget* alopex(ostream *toXML)=0 ; 
    virtual void setAlopexTarget(AnnealingTarget* alopexTarget)=0 ;
	virtual	double getMinError () const {return minError;}
    virtual int getTotalIterations () const {return totalIterations;}
    virtual void setMinError (double minErr) {minError=minErr;}
    virtual void setTotalIterations (int totalItr) {totalIterations=totalItr;}
    virtual void setAcceptModel(AcceptModel* newAcceptModel) {mAcceptModel = newAcceptModel ; } 

protected:
    double minError;
    int totalIterations;
    AcceptModel* mAcceptModel ; 
} ;

#endif /* ifndef ALOPEXER_H */


