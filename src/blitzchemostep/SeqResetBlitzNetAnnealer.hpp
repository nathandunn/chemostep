
#ifndef SEQRESETBLITZNETANNEALER_HPP_
#  define SEQRESETBLITZNETANNEALER_HPP_


#include <iostream>
using std::ostream ;


#include "SeqBlitzNetAnnealer.hpp" 

class AnnealingTarget ; 
class BlitzNet ; 
class BlitzXmlNetRenderer ; 


class SeqResetBlitzNetAnnealer : public SeqBlitzNetAnnealer {

public:
    SeqResetBlitzNetAnnealer() ;
    virtual AnnealingTarget* anneal( ostream *toXML=NULL,string netOutputFile=NULL) ; 

protected:
    virtual void dumpXmlAnnealStart(ostream* s) ; 



} ;

#endif /* ifndef SEQRESETBLITZNETANNEALER_H */
// -*- C++ -*-
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

