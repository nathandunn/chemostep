#ifndef EVOANNEALCHECKDRIVER_HPP_
#  define EVOANNEALCHECKDRIVER_HPP_


#include "EvoAnnealDriver.hpp"

#include <vector>
using std::vector ; 

#include <fstream>
using std::ofstream ; 


class SeqCheckBlitzNetAnnealer ; 

class EvoAnnealCheckDriver : public EvoAnnealDriver {

public:
    EvoAnnealCheckDriver(string newInterfaceName, string newTypeName, AppInterface* newParent) ; 

    // Moved from private to protected to here
    // virtual BlitzNetAnnealer* createAnnealer() ; 
    // virtual bool createLocalMaps() ;
#ifdef DOMPI
    // void syncData() ; 
#endif

protected:
    // annealer data
    int mNumChecks ; 
    double mMinInitialImprovement ;
private:

/*
 */

} ;

#endif /* ifndef EVOANNEALERDRIVER_HPP_ */
// -*- C++ -*-
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: EvoAnnealDriver.hpp,v 1.3 2004/01/27 20:27:19 ndunn Exp $

