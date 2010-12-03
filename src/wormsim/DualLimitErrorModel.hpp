// -*- C++ -*-
// FILE: "/home/ndunn/cvs/dev/package555/DualLimitErrorModel.hpp"
// LAST MODIFICATION: "Fri, 08 Mar 2002 15:52:42 -0800 (ndunn)"
// (C) 2002 by Nathan Dunn, <ndunn@idiom.com>
// $Id: DualLimitErrorModel.hpp,v 1.1 2002/04/28 00:33:05 ndunn Exp $


#ifndef _DualLimitErrorModel_hpp_
#define _DualLimitErrorModel_hpp_

#include "ErrorModel.hpp" 


class DualLimitErrorModel : public ErrorModel {
public:
//    DualLimitErrorModel(double lowerLimit,double upperLimit) : ErrorModel()  ; 
//    DualLimitErrorModel(double lowerLimit,double upperLimit,double maxOutput, double minOutput) : ErrorModel()  ; 
    DualLimitErrorModel(double lowerLimit,double upperLimit,double maxOutput = 1 , double minOutput = 0 , double midOutput = 0.5)   ; 
    double getError(double best,double target,double *calcValue = 0) ; 
    virtual string getType() { return DUAL_LIMIT ; }   
    virtual double getMinOutput() ;   
    virtual double getMaxOutput() ;   
    virtual double getMidOutput() ;   
    virtual void setMaxOutput(double newMaxOutput) ;   
    virtual void setMidOutput(double newMidOutput) ;   
    virtual void setMinOutput(double newMinOutput) ;   
    virtual double getLowThresh() ;   
    virtual double getHighThresh() ;   
    virtual void dump(ostream &s) const { 
      s << "ErrorModel type = [ " << DUAL_LIMIT << " ]" << endl ; 
      s << " lowThresh = [ " << lowerLimit << " ]" << endl ;  
      s << " highThresh = [ " << upperLimit << " ]" << endl ;  
      s << " maxOutput = [ " << maxOutput << " ]" << endl ;  
      s << " midOutput = [ " << midOutput << " ]" << endl ;  
      s << " minOutput = [ " << minOutput << " ]" << endl ;  
    }

private:
    double lowerLimit ; 
    double upperLimit ; 
    double maxOutput ; 
    double minOutput ; 
    double midOutput ; 
    
};

#endif



