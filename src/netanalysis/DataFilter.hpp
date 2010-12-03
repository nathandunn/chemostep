#ifndef DATAFILTER_HPP_
#  define DATAFILTER_HPP_

#include "blitzdefs.hpp"
#include "RawSignal.hpp"

#include <string>
using std::string ; 

/**  The DataFilter gets data from neuron responses that are used by their associated modeler.  We use a Matrix to record signal because using RawSignal implies too much about what's in the data.
 *
 */
class DataFilter {

public:
    DataFilter() ; 
    virtual DataFilter* extractData(RawSignal* dataSignal) = 0 ; 
    virtual int getNumSignals() ; 
    virtual int getTotalTimePoints() ; 
    static string getType() ; 
    virtual void setFilter(DataFilter* newDataFilter) ; 
    virtual Matrix* getSignal() ; 

protected:
    Matrix* mRawSignal ; 

} ;

#endif /* ifndef DATAFILTER_H */
// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


