
#include <iostream.h>
#include <math.h>
#include "DiffSquaredErrorModel.hpp"

double DiffSquaredErrorModel::getError(double best, double target,double *calcValue){
  *calcValue = best ; 
  return pow((best - target), 2.0) ;
}

//int main(){
	//cout <<" a test" << endl ; 
    //ErrorModel *model =  new DiffSquaredErrorModel ; 
    //cout <<"the error: " << model->getError((double) 7,(double)  3) << endl ; 
//}




