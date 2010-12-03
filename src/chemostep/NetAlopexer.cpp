
#include <iostream>
using std::cout ; 
using std::endl ; 

#include "Alopexer.hpp"
#include "NetAlopexer.hpp"
#include "NeuralNetwork.hpp"

NetAlopexer::NetAlopexer() : Alopexer() 
,currentNet(NULL) 
{ }

AnnealingTarget* NetAlopexer::alopex(ostream *toXML) { }


void NetAlopexer::setAlopexTarget(AnnealingTarget* alopexTarget) 
{
    currentNet = (NeuralNetwork*) alopexTarget; 
}


