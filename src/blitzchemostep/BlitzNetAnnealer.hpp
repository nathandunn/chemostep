#ifndef BLITZNETANNEALER_HPP_
#  define BLITZNNETANNEALER_HPP_

#include <iostream>
using std::ostream ;

class AnnealingTarget ; 
class BlitzNet ; 
class BlitzXmlNetRenderer ; 

#include "NetAnnealer.hpp" 
#include "blitzdefs.hpp" 


/** Extends the NetAnnealer class.
 * 
 *  \bug After annealing, the initNeuron seem to get set to 0 in the sequential case.
 *
 * \todo Use stl algs (for_each) to optimize loops for perturbation and annealing.
 * \todo Add struct or class for return-types versus doubles
 * \todo Reduce method calls for eval (preload feeder data and call array, if possible).
 *  \todo Get Vector class from feeder to reduce memory calls.
 *  \todo Dump annealer output to xml (JOEL).
 * \todo Add a qwt plotting application to the annealer (JOEL).
 */


class BlitzNetAnnealer : public NetAnnealer {

public:
    BlitzNetAnnealer() ; 
    virtual AnnealingTarget* anneal( ostream *toXML=NULL) ; 
    virtual void setAnnealingTarget(AnnealingTarget* annealingTarget) ; 
    virtual void setArguments(int newArgc,char** newArgv) ; 

private:
    BlitzNet *blitzNet; 
    BlitzXmlNetRenderer* renderer ;
    int totalIterations ; 
    int ARGC ; 
    char** ARGV ; 
    #if DOMPI 
    struct {
      double val;
      int node;
    } src, dest;
    double minDeltaT ;
    double maxDeltaT ; 
    int globalIters ;
    Matrix *bcastMatrix ; 
    Matrix *theseWeights ;
    Vector *theseBias ;
    Vector *theseTau;
    Vector *theseInitNeuron;
    #endif 

} ;

#endif /* ifndef NETANNEALER_H */
// -*- C++ -*-

