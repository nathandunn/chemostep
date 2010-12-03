#ifndef ANNEALERTHREAD_HPP_
#  define ANNEALERTHREAD_HPP_

#include <qthread.h>
#include <fstream>
using std::ofstream ; 

class EvoAnnealDriver ; 
class BlitzNetAnnealer ; 

class AnnealerThread : public QThread {

public:
    AnnealerThread(EvoAnnealDriver* newParent) ;
    ~AnnealerThread() ;
    virtual void run() ;

    EvoAnnealDriver* mParent ; 

protected:
    BlitzLiveNet *mNetwork; 
    BlitzNetAnnealer *mAnnealer ; 
    ofstream *mOutputStream  ; 
    ofstream *mNetworkStream ; 
    BlitzLiveNet* mFinalNet ;

} ;

#endif /* ifndef ANNEALERTHREAD_H */
// -*- C++ -*-
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

