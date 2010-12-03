#ifndef FILEFEEDER_HPP_
#  define FILEFEEDER_HPP_

#include <string>
using std::string ; 

#include <vector>
using std::vector ; 

#include <float.h>

#include "Feeder.hpp" 


class FileFeeder : public Feeder {

public:
    FileFeeder() ;
    FileFeeder(string newFile,double newMinValue=-DBL_MAX,double newMaxValue=DBL_MAX,double newFailValue=-DBL_MAX) ;
    virtual double getNextPoint(int pointAt=0) ;  // defaults to the first datapoint
    virtual int getNumPoints() ; 
    virtual bool isTimePointValid() ; 
    virtual bool hasMorePoints() ; 
    virtual bool setFile(string newFileName) ; 
    virtual bool loadSigFile(string sigFileName) ; 
    virtual string getFileName() ; 
    virtual double getNextTimeStep(double newTimeStep=1.0,int pointAt=0) ; 
    virtual string getName() {  return FEEDER_NAME ; }  
    
    static const string FEEDER_NAME ; // name of feeder 

protected:
    string mFileName ; 
    const int INPUT_BUFF ; 
    double mMinValue, mMaxValue,mFailValue ; 

} ;

#endif /* ifndef FILEFEEDER_H */
// -*- C++ -*-
