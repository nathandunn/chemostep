#ifndef SEQADJUSTBLITZNETANNEALER_HPP_
#  define SEQADJUSTBLITZNETANNEALER_HPP_

#include "SeqBlitzNetAnnealer.hpp" 

#include <iostream>
using std::ostream ; 

class BlitzNet ; 

/** This class extends SeqBlitzNetAnnealer by adjusting the output self-connection weight to an optimal position.
 *
 *
 */
class SeqAdjustBlitzNetAnnealer : public SeqBlitzNetAnnealer{

public:
    SeqAdjustBlitzNetAnnealer() ; 
    virtual AnnealingTarget* anneal( ostream *toXML=NULL) ; 
    virtual AnnealingTarget* initAnneal() ; 

protected:
    virtual void dumpXmlAnnealStart(ostream* s) ; 
    virtual AnnealingTarget* shiftNet(BlitzNet* net) ; 

} ;

#endif /* ifndef SEQADJUSTBLITZNETANNEALER_H */
// -*- C++ -*-
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

