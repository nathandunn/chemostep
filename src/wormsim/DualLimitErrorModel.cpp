
#include <iostream.h>
#include <math.h>
#include "DualLimitErrorModel.hpp"


DualLimitErrorModel::DualLimitErrorModel(double newLowerLimit,double newUpperLimit, double newMaxOutput, double newMinOutput,double newMidOutput): ErrorModel() {
 	lowerLimit = newLowerLimit ;  
 	upperLimit = newUpperLimit ;  
    maxOutput = newMaxOutput ; 
    minOutput = newMinOutput ; 
    midOutput = newMidOutput ; 
}


double DualLimitErrorModel::getHighThresh(){
  return upperLimit ; 
}

double DualLimitErrorModel::getLowThresh(){
  return lowerLimit ; 
}

double DualLimitErrorModel::getMaxOutput(){
  return maxOutput; 
}

double DualLimitErrorModel::getMidOutput(){
  return midOutput; 
}

double DualLimitErrorModel::getMinOutput(){
  return minOutput; 
}

void DualLimitErrorModel::setMaxOutput(double newMaxOutput){
  maxOutput = newMaxOutput ; 
}

void DualLimitErrorModel::setMinOutput(double newMinOutput){
  minOutput = newMinOutput ; 
}

void DualLimitErrorModel::setMidOutput(double newMidOutput){
  midOutput = newMidOutput ; 
}


double DualLimitErrorModel::getError(double best, double target,double *calcValue){
    double derivedOutput = (double) 0 ; 


	if(best > upperLimit){
		derivedOutput = maxOutput ; 	
    }else if(best < lowerLimit){
		derivedOutput = minOutput ; 	
    }else {   // between lower and upper-limits
		derivedOutput = midOutput ; 	
    }

    if(calcValue != 0){
		*calcValue = derivedOutput ; 
    }

    
    return fabs((double) (derivedOutput - target)) ; 
}



//int main(){
//	cout <<" a test" << endl ; 
//    double *testOutputValue  ; 
//   
//    ErrorModel *model =  new DualLimitErrorModel(0.45,0.55,0.7,0.3,0.5) ; 
//    cout <<"the error: " << model->getError((double) 0.44,(double)  0.45,testOutputValue) << endl ; 
//
//    cout <<"the newly calculated value: " << *testOutputValue << endl ; 
//}


    /*
    cout <<"best: " << best << endl ; 
    cout <<"upperLimit: " << upperLimit << endl ; 
    cout <<"lowerLimit: " << lowerLimit << endl ; 
    cout <<"maxOutput: " << maxOutput << endl ; 
    cout <<"minOutput: " << minOutput << endl ; 
    */
