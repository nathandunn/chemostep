#ifndef BLITZGAALGORITHM_HPP_
#  define BLITZGAALGORITHM_HPP_


#include <GAAlgorithm.hpp>
#include <NeuralNetwork.hpp>

class BlitzGAAlgorithm : public GAAlgorithm{

public:
	BlitzGAAlgorithm() ; 
	NeuralNetwork run() ; 

protected:
	void mutate(double ratio=0.0)  ; 
	void cross()  ;   // crosss all of the network values
	void evaluate()  ;  // evluates networks




} ;

#endif /* ifndef BLITZGAALGORITHM_H */
// -*- C++ -*-

// (C) 2006 by Nathan Dunn, <ndunn@mac.com>


