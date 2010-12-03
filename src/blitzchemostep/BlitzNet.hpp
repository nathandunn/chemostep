#ifndef BLITZNET_HPP_
#  define BLITZNET_HPP_

#include "NeuralNetwork.hpp"
#include "BlitzEulerPerturber.hpp"
#include "BlitzNetPerturber.hpp"
#include "BlitzEulerNetEvaluator.hpp"
#include "blitzdefs.hpp"
#include "BlitzNetRenderer.hpp"
#include "BlitzReportNetRenderer.hpp"

#include <fstream>
using std::ofstream ; 

class BlitzNet : public NeuralNetwork {

public:
    BlitzNet(int newSize=0) ; 
    BlitzNet(BlitzNet* newNet); 
    ~BlitzNet() ; 
    BlitzNet& operator=(BlitzNet &net); 
    virtual int getNumNeurons() ; 
    virtual void setNumNeurons(int newSize) ; 
    virtual Matrix* getWeights(  )  { return mWeights ; } ; 
    virtual Matrix* getWeightMask( )  { return mWeightMask ; }; 
    virtual Vector* getBias() { return mBias ; }  ; 
    virtual Vector* getBiasMask() { return mBiasMask ; }  ; 
    virtual Vector* getTau() { return mTau ; }  ; 
    virtual Vector* getTauMask() { return mTauMask ; }  ; 
    virtual Vector* getGain() { return mGain ; }
    virtual Vector* getGainMask() { return mGainMask  ; }
    virtual Vector* getInitNeuron() { return mInitNeuron ; }  ; 
    virtual Vector* getInitNeuronMask() { return mInitNeuronMask ; }  ; 
    virtual Vector* getNeurons(){ return mNeurons ; } 
    virtual BlitzNetRenderer* getDefaultRenderer(){ return defaultRenderer ; } 
    virtual void  setWeights(Matrix* newSet ) ;
    virtual void  setWeightMask(Matrix* newSet )   ; 
    virtual void  setBias(Vector* newSet )   ; 
    virtual void  setBiasMask(Vector* newSet )   ; 
    virtual void  setTau(Vector* newSet )   ; 
    virtual void  setTauMask(Vector* newSet )   ; 
    virtual void   setGain(Vector* newVector) ; 
    virtual void   setGainMask(Vector* newVector) ; 
    virtual void  setInitNeuron(Vector* newSet )   ; 
    virtual void  setInitNeuronMask(Vector* newSet )   ; 
    virtual void  setNeurons(Vector* newNeurons) ;  
    virtual void  setDefaultRenderer(BlitzNetRenderer* newRenderer){ defaultRenderer = newRenderer ; } 
    virtual bool reset() ; 
    virtual string render() ; 
    virtual double getMinDeltaT() ; 
    virtual void setTrace(double newTrace) ; 
    virtual double getTrace() ; 

protected:
    Matrix *mWeights ; 
    Matrix *mWeightMask ; 
    Vector *mBias  ; 
    Vector *mBiasMask  ; 
    Vector *mTau  ; 
    Vector *mTauMask  ; 
    Vector *mGain ; 
    Vector *mGainMask ; 
    Vector *mInitNeuron  ; 
    Vector *mInitNeuronMask  ; 
    Vector *mNeurons ; 
    Vector *mRelaxTauVector ; 

    BlitzNetRenderer *defaultRenderer ; 
    double mTrace ; 

} ;


#endif /* ifndef BLITZNET_H */
// -*- C++ -*-

