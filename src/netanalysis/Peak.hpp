#ifndef PEAK_HPP_
#  define PEAK_HPP_


using std::pair ; 

/** Description:  Class Peak.
 *
 */
class Peak : public pair<int,double>{

public:
    Peak() ; 
    Peak(int timePoint,double pointValue) ; 
    virtual int getPeakTime() ; 
    virtual double getPeakValue() ; 
    virtual void setTimePoint(int newPeakTime) ; 
    virtual void setPointValue(double newPeakValue) ; 


} ;

#endif /* ifndef PEAK_H */

