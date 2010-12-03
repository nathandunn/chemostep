/// Code to support operations with Blitz++ array objects

#include <float.h>

#include "blitzdefs.hpp"
#include <vector>
using std::vector ; 

/// Overload the * operator for matrix-vector products
//Range all = Range::all();		// specifies complete row or column

Vector& operator *(const Vector v, const Matrix m) {
  int vSize = v.size() ; 
  static Vector temp(vSize);			// will return reference to this vector
  
  // VERY SLOW
//  for (int i = 0; i < vSize ; i++){
//    temp(i) = sum(v*m(all,i));
//  }

  double somme  = 0.0 ; 
  for (int i = 0; i < vSize ; i++){
    somme = 0.0 ; 
    for (int j = 0; j < vSize ; j++){
        somme += m(j,i)*v(j);
    }
    temp(i) = somme ; 
  }

  return temp;
}

vector<double>* getSTLVector(const Vector v) 
{
    vector<double>* returnVector = new vector<double>(v.size()) ; 
    for(int i = 0 ; i < v.size() ; i++){
        (*returnVector)[i] =  v(i)  ; 
    }
    return returnVector ; 
}

/// Assume that rows are time and neurons are columns.  
vector<vector<double>*>* getSTLMatrix(const Matrix v) 
{
    vector<vector<double>*>* returnVector = new vector<vector<double>*>(v.columns()) ; 

    int numNeurons = v.columns() ; //  number of neurons
    int numPoints = v.rows() ;  // over time

    for(int neuronCounter = 0 ; neuronCounter < numNeurons ; neuronCounter++){
        vector<double>* timeVec = new vector<double>() ; 
        for(int timeCounter = 0 ; timeCounter < numPoints  ; timeCounter++){
            timeVec->push_back (  v(timeCounter,neuronCounter)    ) ; 
        }
        returnVector->push_back( timeVec) ; 
    }

    return returnVector ; 
}




bool operator ==(const Vector v,const Vector w){ /// Run a loop to compare all of the values.
//    cout << " comparing: " << v << " to " << w << endl ; 
    for(int i = 0 ; i < v.size() ; i++){
        if(v(i)!=w(i)){
            return false ; 
        }
    }
    return true ; 
}

bool operator ==(const Matrix v,const Matrix w){ /// Run a loop to compare all of the values.
//    cout << " comparing: " << v << " to " << w << endl ; 
    for(int i = 0 ; i < v.rows() ; i++){
        for(int j = 0 ; j < v.columns() ; j++){
            if(v(i,j)!=w(i,j)){
                return false ; 
            }
        }
    }
    return true ; 
}



double getMax(const Matrix v, int position[2]){
    double maximum = DBL_MIN ; 
	for(int rowNum = 0 ; rowNum < v.rows() ; rowNum++){
        for(int columnNum = 0 ; columnNum < v.columns() ; columnNum++){
            if(v(rowNum,columnNum) > maximum) {
             maximum = v(rowNum,columnNum) ;    
             if(position!=NULL){
                 position[0] = rowNum ;
                 position[1] = columnNum ;
             }
            }
        }
    }
    return maximum ; 
}

//double getMax(const Vector v){
//    double maximum = DBL_MIN ; 
//	for(int i = 0 ; i < v.size() ; i++){
//		if(v(i) > maximum) maximum = v(i) ; 
//    }
//    return maximum ; 
//}

//int getMaxPos(const Vector v){
//    double maximum = DBL_MIN ; 
//    int maximumPosition = -1 ; 
//	for(int i = 0 ; i < v.size() ; i++){
//		if(v(i) > maximum) {
//            maximum = v(i) ; 
//            maximumPosition= i ; 
//        }
//    }
//    return maximumPosition ; 
//}
//

double getMin(const Matrix v, int position[2]){
    double minimum = DBL_MAX ; 
	for(int rowNum = 0 ; rowNum < v.rows() ; rowNum++){
        for(int columnNum = 0 ; columnNum < v.columns() ; columnNum++){
   			if(v(rowNum,columnNum) < minimum){
				minimum = v(rowNum,columnNum) ; 
                 if(position!=NULL){
                     position[0] = rowNum ;
                     position[1] = columnNum ;
                 }
            }
        }
    }
    return minimum ; 
}


double getMax(const Vector v){
    double maximum = DBL_MIN ; 
	for(int i = 0 ; i < v.size() ; i++){
		if(v(i) > maximum) maximum = v(i) ; 
    }
    return maximum ; 
}



const Matrix shift(const Matrix theMatrix, int numToShift)
{
	Vector replaceValue(theMatrix.columns()) ; 
    if(numToShift >0){
        for(int i = 0 ; i < replaceValue.size() ; i++){
            (replaceValue)(i)  = (theMatrix)(i,0) ; 
        }
    }
    else 
    if(numToShift <0){
        for(int i = 0 ; i < replaceValue.size() ; i++){
            (replaceValue)(i)  = (theMatrix)(i,(theMatrix.rows()-1)) ; 
        }
    }
    else{
		return theMatrix ; 
    }

    return shift(theMatrix,numToShift,replaceValue) ; 
}// + is right, 

const Matrix shift(const Matrix theMatrix, int numToShift,Vector replace)
{
    int numRows = theMatrix.rows() ; 
    int numColumns = theMatrix.columns() ; 
    Matrix newMatrix(numRows,numColumns) ; 
    
    for(int i = 0 ; i < numRows ; i++){
        for(int j = 0 ; j < numColumns ; j++){
			if( ((i-numToShift) < 0) || ((i-numToShift) > (numRows -1)) ) {
                (newMatrix)((i),j) = (replace)(j) ;
            }else{
                (newMatrix)((i),j) = (theMatrix)((i-numToShift),j) ;
            }
        }
    }
    
	return (const Matrix) newMatrix ; 
}


double getMin(const Vector v){
    double minimum = DBL_MAX ; 
	for(int i = 0 ; i < v.size() ; i++){
		if(v(i) < minimum) minimum = v(i) ; 
    }
    return minimum ; 
}





//double getMin(const Vector v){
//    double minimum = DBL_MAX ; 
//	for(int i = 0 ; i < v.size() ; i++){
//		if(v(i) < minimum) minimum = v(i) ; 
//    }
//    return minimum ; 
//}



//int getMinPosition(const Vector v){
//    double minimum = DBL_MAX ; 
//    int minimumPosition= -1 ; 
//	for(int i = 0 ; i < v.size() ; i++){
//		if(v(i) < minimum) {
//            minimum = v(i) ; 
//            minimumPosition = i ; 
//        }
//    }
//    return minimumPosition ; 
//}



