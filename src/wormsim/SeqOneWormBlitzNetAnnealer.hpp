
#ifndef SEQRESETBLITZNETANNEALER_HPP_
#  define SEQRESETBLITZNETANNEALER_HPP_


#include <iostream>
using std::ostream ;


#include "SeqBlitzNetAnnealer.hpp" 

class AnnealingTarget ; 
class BlitzNet ; 
class BlitzXmlNetRenderer ; 


/**  This class makes the assumption that the eval is a OneWormSimEval or a derivative class and has it run more worms prior to setting its best overall network.  This was added to wormsim, because it has dependencies in the wormsim directory.
 *
 */
class SeqOneWormBlitzNetAnnealer : public SeqBlitzNetAnnealer {

public:
    SeqOneWormBlitzNetAnnealer(int extraWormsToRun=0) ;
    virtual AnnealingTarget* anneal( ostream *toXML=NULL,string netOutputFile=NULL) ; 

protected:
    virtual void dumpXmlAnnealStart(ostream* s) ; 
    int mExtraWorms ; 



} ;

#endif /* ifndef SEQRESETBLITZNETANNEALER_H */
// -*- C++ -*-
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

