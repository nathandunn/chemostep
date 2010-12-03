
#include <iostream>
using std::cout ; 
using std::endl ; 

#include "ShuffleMovementModel.hpp"
#include "WormShuffler.hpp"
#include "BaseWorm.hpp"


ShuffleMovementModel::ShuffleMovementModel(WormShuffler* newWormShuffler) 
{
    mWormShuffler = newWormShuffler ; 
}

void ShuffleMovementModel::move(BaseWorm* aWorm)   
{
    mWormShuffler->shuffleWorm((BaseWorm*) aWorm) ; 
}



/* Function int main(int argc, char **argv) {{{ */
//int main(int argc, char **argv)
//{


//    return 0;
//} /* }}} */


/* Modeline for ViM {{{
 * vim:set ts=4:
 * vim600:fdm=marker fdl=0 fdc=3:
 * }}} */

// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


