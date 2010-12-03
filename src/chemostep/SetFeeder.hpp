/**  Returns data from sets of feeders.  Its assumed that scale and offset have 
 *   already been applied to lower-level feeders. 
 * 
 */
#ifndef SETFEEDER_HPP_
#  define SETFEEDER_HPP_

#include <iostream>
using std::ostream;

#include "XmlRenderable.hpp" 
#include "Feeder.hpp" 

class SetFeeder : public Feeder , public XmlRenderable {

public:
    SetFeeder() ; 
    virtual void addFeeder(Feeder* newFeeder) ; 
    virtual double getNextTimeStep(double newTimeStep=1.0, int pointAt=0) ; 
    virtual string getName() {  return FEEDER_NAME ; }  
//    virtual vector<double>* getNextTimeSteps(double newTimeStep=1.0) ; 
    virtual double getNextPoint(int pointAt=0) ;  /// defaults to the first datapoint
//    virtual vector<double>* getNextPoints() ;  
    virtual int getNumPoints() ; 
    virtual bool isTimePointValid() ; 
    virtual bool reset() ; 
    virtual bool hasMorePoints() ; 
    virtual bool isNewSet() ; 
    virtual double getTotalTime() ; 
    virtual double setDeltaT(double newDeltaT ) ;
    virtual double getDeltaT() ;
    virtual bool clearSets() ; 
    virtual double getNextSigPoint() ; 
    virtual double getNextSigTimeStep(double newTimeStep=1.0) ; 
    virtual bool setSigPoint(double newSignificance,int pointAt) ; 
    virtual bool calculateSigPoints() ; 
    virtual void setScale(double newScale=1.0) ;  /// Sets the scale of the data from the feeder.  1.0 is the default, which is unchanged.
    virtual double getScale() ;  /// Gets the scale of the data.
    virtual void setOffset(double newOffset=0.0) ;  /// Sets the offset of the data from the feeder.  0.0 is the default, which is unchanged.
    virtual double getOffset() ;  /// Gets the offset of from the feeder output.
    virtual int getNumSets() ;  /// Gets the number of sets.
    virtual void toXML(ostream *s) ;


    static const string FEEDER_NAME ; // name of feeder 

protected:
    vector<Feeder*>* feederList ; 
    int feederNum ; 

private:
    double previousSigStepValue ; 

} ;

#endif /* ifndef SETFEEDER_H */
// -*- C++ -*-
// FILE: "/Users/nathandunn/svn/chemotrunk/src/chemostep/SetFeeder.hpp"
// LAST MODIFICATION: "Wed, 12 Jan 2005 09:57:24 -0800 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>


