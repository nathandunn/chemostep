#ifndef BLITZNETEVALUATOR_HPP_
#  define BLITZNETEVALUATOR_HPP_

#include "blitzdefs.hpp" 
#include "BinNetEvaluator.hpp" 
#include <float.h>

class BlitzNetRenderer ; 


class BlitzNetEvaluator : public BinNetEvaluator{

public:
    BlitzNetEvaluator() ;
    ~BlitzNetEvaluator() ;
    virtual void relaxNet(bool doTrace=false) ; 
    virtual bool resetNet() ;  
    virtual bool resetRelax()  ; 
    virtual Vector* getNetworkValues() ; 
    virtual void resetTrace(int numPoints,int errorPoints) ;
    virtual double sigLimit(double input,double limit=DBL_MAX) ; 
    virtual Vector* sigLimitVector(Vector *v,double limit=DBL_MAX) ; 
    virtual void setGlobalSigLimit(double _mGlobalSigLimit) ;
    virtual double getGlobalSigLimit() ;
    virtual void toXML(ostream *s) ;
    

protected:
    virtual double getAvgLastNeuronChange(int currentPoint) ; 
    virtual double calcNetworkChange(vector<double>* set1,vector<double>* set2) ; 
    double mGlobalSigLimit ; 
    Matrix *evalWeights ; 
    Matrix *evalWeightMask ; 
    Vector *evalBias  ; 
    Vector *evalBiasMask  ; 
    Vector *evalTau  ; 
    Vector *evalTauMask  ; 
    Vector *evalGain  ; 
    Vector *evalGainMask  ; 
    Vector *evalInitNeuron  ; 
    Vector *evalNeurons  ; 
    BlitzNetRenderer *defaultRenderer ; 
    double mRelaxTau ; 
    Vector *mOriginalTau ; 
    double oldLocalDeltaT ; 
    double currentRelaxValue ; 
    double prevRelaxValue ; 
    double relaxDelta ;
	int relaxCounter  ; 
    int relaxPoints  ; 
    Vector *relaxedNeurons ; 



} ;

#endif /* ifndef BLITZNETEVALUATOR_H */
// -*- C++ -*-

