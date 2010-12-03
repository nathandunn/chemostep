/*
 * $Id: RNG.hpp,v 1.1.1.1 2003/10/24 19:59:28 ndunn Exp $
 */
#ifndef RNG_HPP_
#  define RNG_HPP_

#include <cmath>
#include <cstdlib>
#include <sys/time.h>

class RNG {

public:
  static int initSeed();
  static void setSeed(int seed);
  static double uniform();
  static bool coinToss();
  static double normal();
private:
  static bool first;
} ;

#endif /* ifndef RNG_H */
// -*- C++ -*-
// FILE: "/home/ndunn/svn/chemotrunk/src/utils/RNG.hpp"
// LAST MODIFICATION: "Wed, 27 Oct 2004 10:15:08 -0700 (ndunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: RNG.hpp,v 1.1.1.1 2003/10/24 19:59:28 ndunn Exp $

