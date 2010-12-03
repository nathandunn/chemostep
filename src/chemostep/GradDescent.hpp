/*
 * $Id: GradDescent.hpp,v 1.2 2004/01/13 20:43:35 ndunn Exp $
 */
#ifndef GRADDESCENT_HPP_
#  define GRADDESCENT_HPP_

class TrainingTarget ; 

class GradDescent {

public:
    GradDescent() ; 
    virtual TrainingTarget* train() ; 



protected:
    TrainingTarget* trainee ;


} ;

#endif /* ifndef GRADDESCENT_H */

// -*- C++ -*-
// FILE: "/Users/ndunn/cvs/auto3TWOINPUTSTEP/src/chemostep/GradDescent.hpp"
// LAST MODIFICATION: "Mon, 29 Dec 2003 19:43:19 -0800 (ndunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: GradDescent.hpp,v 1.2 2004/01/13 20:43:35 ndunn Exp $

