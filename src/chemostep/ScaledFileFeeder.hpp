#ifndef SCALEDFILEFEEDER_HPP_
#  define SCALEDFILEFEEDER_HPP_

#include <string>
using std::string ; 

#include <vector>
using std::vector ; 

#include "FileFeeder.hpp" 


class ScaledFileFeeder : public FileFeeder {

public:
    ScaledFileFeeder() ;
    ScaledFileFeeder(string newFile,int newScale=1,double newDeltaT=1.0,double newMinValue=-DBL_MAX,double newMaxValue=DBL_MAX,double newFailValue=-DBL_MAX) ;
    virtual string getName() {  return FEEDER_NAME ; }  
    virtual bool scaleFeeder(int scaleMultiplier) ;  /// Only multiply up for now.
    
    static const string FEEDER_NAME ; // name of feeder 

protected:
    virtual bool scaleFeederVector(vector<vector<double>*>* vectorToScale) ;  /// Only multiply up for now.
    int mScaledMultiplier ; 
    const int INPUT_BUFF ; 


} ;

#endif /* ifndef SCALEDFILEFEEDER_HPP_ */
// -*- C++ -*-
