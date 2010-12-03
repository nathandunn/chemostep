#ifndef GAALGORITHM_HPP_
#  define GAALGORITHM_HPP_


#include <vector>
using std::vector ; 

#include <NeuralNetwork.hpp>
#include <NetworkParameter.hpp>

class GAAlgorithm {

public:
	GAAlgorithm()  :
		mParameterVector(NULL)
	{ }; 
	virtual NeuralNetwork run() =0 ; 
	int getNumIterations() {
		return(mNumIterations);
	}
	void setNumIterations(int _mNumIterations) {
		mNumIterations = _mNumIterations;
		return;
	}
	int getPopulationSize() {
		return(mPopulationSize);
	}
	void setPopulationSize(int _mPopulationSize) {
		mPopulationSize = _mPopulationSize;
		return;
	}
	int getReplacementSize() {
		return(mReplacementSize);
	}
	void setReplacementSize(int _mReplacementSize) {
		mReplacementSize = _mReplacementSize;
		return;
	}





protected:
	virtual void mutate(double ratio=1.0) =0 ; 
	virtual void cross() =0 ; 
	virtual void evaluate() =0 ; 
	int mNumIterations ; 
	int mPopulationSize ; 
	int mReplacementSize ; 
	// yadda yadda
	vector<NetworkParameter>* mParameterVector ; 

} ;

#endif /* ifndef GAALGORITHM_H */
// -*- C++ -*-

// (C) 2006 by Nathan Dunn, <ndunn@mac.com>


