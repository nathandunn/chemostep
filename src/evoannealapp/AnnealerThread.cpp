
#include <iostream>
using std::cout ; 
using std::endl ; 

#include <fstream>
using std::ofstream ; 

#include "MapSpace.hpp"
#include "BlitzLiveNet.hpp"
#include "WormSimEval.hpp"  
#include "SeqBlitzNetAnnealer.hpp"  
#include "BlitzXmlNetRenderer.hpp"  
#include "XmlFileTokenizer.hpp"  

#include "EvoAnnealDriver.hpp"
#include "AnnealerThread.hpp"


#ifdef DOMPI
#include "mpi.h"
int thread_myid ; 
#endif 

AnnealerThread::AnnealerThread(EvoAnnealDriver* newParent) : QThread()
,mParent(newParent) 
,mOutputStream(NULL) 
,mNetworkStream(NULL) 
,mFinalNet(NULL) 
{ 

#ifdef DOMPI
MPI_Comm_rank(MPI_COMM_WORLD, &thread_myid) ; 
#endif 
}

AnnealerThread::~AnnealerThread() {
    // cout << "AT - destructor " << endl;
    // delete mNetwork ;
}

/// Over-ride thread to give run method a purpose.  It uses creation methods from the original gui, but has local variables.
void AnnealerThread::run() 
{


    vector<string>* outputAnnealerNames = NULL ; 
    vector<string>* outputNetworkNames =  NULL ; 

    outputAnnealerNames = XmlFileTokenizer::createFileNames( mParent->mOutputFile , mParent->mNumNetworks) ; 
    outputNetworkNames = XmlFileTokenizer::createFileNames( mParent->mBestNetworkFile, mParent->mNumNetworks) ; 


//  TODO:  create annealer, network, etc., here and just do a reset within the loop, making sure to change the output name

    int wormState = MapSpace::SOME_RUNNING ; 
    // init stuff
    mNetwork = new BlitzLiveNet(mParent->createNetwork()) ; 
    mParent->createAnnealer() ; 
    mAnnealer = mParent->mOrigAnneal ; 
    mParent->createEvaluator(mNetwork) ; 

    
    for(int i = 0 ; i < mParent->mNumNetworks ; i++){
        *mNetwork = *mParent->mOrigNet ; 
        mNetwork->setEvaluator( mParent->mOrigEval ) ; 
        mAnnealer->setAnnealingTarget(mNetwork)  ; 
        mOutputStream = mParent->createOutputFileStream( ((*outputAnnealerNames)[i]).c_str() ) ; 

        if(mFinalNet==NULL){
            mFinalNet =   new BlitzLiveNet( (BlitzLiveNet*) ( ((SeqBlitzNetAnnealer*) mAnnealer)->anneal(mOutputStream, (*outputNetworkNames)[i]  )  )  ) ; 
        }
        else{
            *mFinalNet =   *( (BlitzLiveNet*) ( ((SeqBlitzNetAnnealer*) mAnnealer)->anneal(mOutputStream, (*outputNetworkNames)[i]  )  )  ) ; 
        }
        mOutputStream->close() ; 
        mOutputStream = NULL ;

    }
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
// $Id:$

