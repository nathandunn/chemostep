#ifndef ALOPEXTHREAD_HPP_
#  define ALOPEXTHREAD_HPP_

#include <qthread.h>
#include <fstream>
using std::ofstream ; 

class AlopexDriver ; 
class BlitzNetAlopexer ; 
class BlitzLiveNet ; 

class AlopexThread : public QThread {

public:
    AlopexThread(AlopexDriver* newParent) ;
    ~AlopexThread() ;
    virtual void run() ;

    AlopexDriver* mParent ; 

protected:
    BlitzLiveNet *mNetwork; 
    BlitzNetAlopexer *mAlopexer ; 
    ofstream *mOutputStream  ; 
    ofstream *mNetworkStream ; 
    BlitzLiveNet* mFinalNet ;

} ;

#endif /* ifndef ANNEALERTHREAD_H */
// -*- C++ -*-
// FILE: "/home/ndunn/svn/chemostep-alopex/src/alopexapp/AlopexThread.hpp"
// LAST MODIFICATION: "Sat, 20 Nov 2004 13:44:49 -0800 (ndunn)"
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

