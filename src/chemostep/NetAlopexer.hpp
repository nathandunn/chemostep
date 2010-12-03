
#ifndef NETALOPEXER_HPP_
#  define NETALOPEXER_HPP_

#include "Alopexer.hpp"
#include <iostream>
using std::ostream;

class NeuralNetwork ; 

class NetAlopexer : public Alopexer {

public:
    NetAlopexer() ; 
    virtual AnnealingTarget* alopex(ostream *toXML) ; 
    virtual void setAlopexTarget(AnnealingTarget* alopexTarget) ; 

private:
    NeuralNetwork* currentNet ; 

} ;

#endif /* ifndef NETALOPEXER_H */


