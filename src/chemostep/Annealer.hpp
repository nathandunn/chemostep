#ifndef ANNEALER_HPP_
#  define ANNEALER_HPP_



class TempSchedule ; 
class AnnealingTarget; 
class AcceptModel ; 

class Annealer {

public:
    Annealer() ; 
    virtual AnnealingTarget* anneal()=0 ;
    virtual void setSetBack(int newSetBack) ;
    virtual void setBackStep(double newBackStep) ;
    virtual int getSetBack() ;
    virtual double getBackStep() ;
    virtual void setTempSchedule(TempSchedule* newTempSchedule) ; 
    virtual void setAnnealingTarget(AnnealingTarget* annealingTarget)=0 ; 
    
    virtual int getIterPerTemp() {
        return(iterPerTemp);
    }

    virtual void setIterPerTemp(int _iterPerTemp) {
        iterPerTemp = _iterPerTemp;
        return;
    }

    virtual void setAcceptModel(AcceptModel* newAcceptModel) {
        mAcceptModel = newAcceptModel ; 
    } 

protected:
    TempSchedule *tempSchedule ; 
    int iterPerTemp; 
    double mBackStep ; 
    int mSetBack ; 
    AcceptModel* mAcceptModel ; 
} ;

#endif /* ifndef ANNEALER_H */

// -*- C++ -*-

