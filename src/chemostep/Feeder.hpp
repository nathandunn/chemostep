#ifndef FEEDER_HPP_
#  define FEEDER_HPP_

#include <vector>
using std::vector ; 

#include <string>
using std::string ; 

/** 
 *   \brief The base-class for providing time-dependant data to other classes.  
 *  
 *   Currently offset is the responsibility of the instantiated feeder to implement during getNextTimeStep or equivalent methods.  Scale is calculated first and then offest is applied.   
 *
 *   return value = (output * scale ) + offset 
 *
 */

class Feeder {

public:
    Feeder() ; 
    virtual double setDeltaT(double newDeltaT=1.0 ) ; 
    virtual double getDeltaT() ; 
    virtual double getTotalTime() ; 
    virtual double getCurrentTime() ; 
    virtual int getCurrentPoint() ; 
    virtual double getNextSigPoint() ; 
    virtual string getName() {  return FEEDER_NAME ; }  
    virtual double getNextSigTimeStep(double newTimeStep=1.0,int inputNum=0) ; 
    virtual bool setSigPoint(double newSignificance,int pointAt) ; 
    virtual bool calculateSigPoints() ; 
    virtual double getNextTimeStep(double newTimeStep=1.0, int pointAt=0)=0 ; 
//    virtual vector<double>* getNextTimeSteps(double newTimeStep=1.0)=0 ; 
    virtual double getNextPoint(int inputNum=0)=0 ;  // defaults to the first datapoint
//    virtual vector<double>* getNextPoints()=0 ;  
    virtual int getNumPoints()=0 ; 
//    virtual vector<double>* getAllPoints()=0 ; 
    virtual bool isTimePointValid()=0 ; 
    virtual bool reset() ; 
    virtual bool hasMorePoints()=0 ; 
    virtual bool isNewSet() ; 
    virtual void setScale(double newScale=1.0) ;  /// Sets the scale of the data from the feeder.  1.0 is the default, which is unchanged.
    virtual double getScale() ;  /// Gets the scale of the data.
    virtual void setOffset(double newOffset=0.0) ;  /// Sets the offset of the data from the feeder.  0.0 is the default, which is unchanged.
    virtual double getOffset() ;  /// Gets the offset of from the feeder output.
    virtual Feeder* getFeeder(int inputNum=0) ; // initially returns self 
    virtual void setFeeder(Feeder* newFeeder, int inputNum=0) ; 
    virtual vector<double>* getArray(int inputNum=0) ; 
    virtual int getNumSets() ;  /// Gets the number of sets, the default being 1.


    static const string FEEDER_NAME ; // name of feeder 

protected:
    double deltaT ;  /// this is the time between datapoints
    vector<vector<double>*>* fileData ;   /// multiple datapoints allowed per time-step
    vector<double>* sigData ;   /// multiple datapoints allowed per time-step
    int pointCounter ;   /// counts the position in the fileData
    int sigCounter ;   /// counts the position in the fileData for the significant data
    double timeCounter ;  /// counts the deltaT 
    double scale ; /// the scale of the output
    double offset; /// the scale of the output


} ;

#endif /* ifndef FEEDER_H */

