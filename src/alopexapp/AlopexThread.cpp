
#include <iostream>
using std::cout ; 
using std::endl ; 

#include <fstream>
using std::ofstream ; 

#include "MapSpace.hpp"
#include "BlitzLiveNet.hpp"
#include "WormSimEval.hpp"  
#include "BlitzNetAlopexer.hpp"  
#include "BlitzXmlNetRenderer.hpp"  
#include "XmlFileTokenizer.hpp"  

#include "AlopexDriver.hpp"
#include "AlopexThread.hpp"


#ifdef DOMPI
#include "mpi.h"
int thread_myid ; 
#endif 

AlopexThread::AlopexThread(AlopexDriver* newParent) : QThread()
,mParent(newParent) 
,mOutputStream(NULL) 
,mNetworkStream(NULL) 
{ 

#ifdef DOMPI
MPI_Comm_rank(MPI_COMM_WORLD, &thread_myid) ; 
#endif 
}

AlopexThread::~AlopexThread() {
    // cout << "AT - destructor " << endl;
    // delete mNetwork ;
}


/// Over-ride thread to give run method a purpose.  It uses creation methods from the original gui, but has local variables.
void AlopexThread::run() 
{

    vector<string>* outputAnnealerNames = NULL ; 
    vector<string>* outputNetworkNames =  NULL ; 

    outputAnnealerNames = XmlFileTokenizer::createFileNames( mParent->mOutputFile , mParent->mNumNetworks) ; 
    outputNetworkNames = XmlFileTokenizer::createFileNames( mParent->mBestNetworkFile, mParent->mNumNetworks) ; 


//  TODO:  create annealer, network, etc., here and just do a reset within the loop, making sure to change the output name

    int wormState = MapSpace::SOME_RUNNING ; 
    // init stuff
    mNetwork = new BlitzLiveNet(mParent->createNetwork()) ; 
    mParent->createAlopexer() ; 
    mAlopexer = mParent->mOrigAlopex ; 
    mParent->createEvaluator(mNetwork) ; 

   
    for(int i = 0 ; i < mParent->mNumNetworks ; i++){
        mNetwork = mParent->createNetwork() ; 
        mNetwork->setEvaluator( mParent->createEvaluator(mNetwork)) ; 
        mAlopexer = mParent->createAlopex() ; 
        mAlopexer->setAlopexTarget(mNetwork)  ; 
        mOutputStream = mParent->createOutputFileStream( ((*outputAnnealerNames)[i]).c_str() ) ; 

        if(mFinalNet==NULL){
//            mFinalNet =   new BlitzLiveNet( (BlitzLiveNet*) ( ((SeqBlitzNetAnnealer*) mAlopexer)->alopex(mOutputStream, (*outputNetworkNames)[i]  )  )  ) ; 
            mFinalNet =   new BlitzLiveNet( (BlitzLiveNet*) ( mAlopexer->alopex(mOutputStream  )  )  ) ; 
        }
        else{
//            *mFinalNet =   *( (BlitzLiveNet*) ( ((SeqBlitzNetAnnealer*) mAlopexer)->anneal(mOutputStream, (*outputNetworkNames)[i]  )  )  ) ; 
            *mFinalNet =   *( (BlitzLiveNet*) ( mAlopexer->alopex(mOutputStream )  )  ) ; 
        }
        mOutputStream->close() ; 
        mOutputStream = NULL ;

    }
}



/// Over-ride thread to give run method a purpose.  It uses creation methods from the original gui, but has local variables.
//void AlopexThread::run() 
//{
//
//
//    vector<string>* outputAnnealerNames = NULL ; 
//    vector<string>* outputNetworkNames =  NULL ; 
//
//    outputAnnealerNames = XmlFileTokenizer::createFileNames( mParent->mOutputFile , mParent->mNumNetworks) ; 
//#ifdef DOMPI
//// we only want to do this for the thread that writes it out
//if (thread_myid==0)
//#endif
//    outputNetworkNames = XmlFileTokenizer::createFileNames( mParent->mBestNetworkFile, mParent->mNumNetworks) ; 
//
//
//
//    int wormState = MapSpace::SOME_RUNNING ; 
//    for(int i = 0 ; i < mParent->mNumNetworks ; i++){
//        mNetwork = mParent->createNetwork() ; 
//        mNetwork->setEvaluator( mParent->createEvaluator(mNetwork)) ; 
//        mAlopexer = mParent->createAlopexer() ; 
//        mAlopexer->setAlopexTarget(mNetwork)  ; 
//#ifdef DOMPI
//if (thread_myid==0)
//#endif
//        mOutputStream = mParent->createOutputFileStream( ((*outputAnnealerNames)[i]).c_str() ) ; 
//
//        // ALL PROCS 
////        BlitzLiveNet* finalNet = (BlitzLiveNet*) (mAlopexer)->anneal(mOutputStream) ; 
//        BlitzLiveNet* finalNet = (BlitzLiveNet*) (mAlopexer)->alopex(mOutputStream) ; 
//#ifdef DOMPI
//if (thread_myid==0){
//#endif
//        mNetworkStream = mParent->createOutputFileStream( ((*outputNetworkNames)[i]).c_str() ) ; 
//        *mNetworkStream << (new BlitzXmlNetRenderer())->render(finalNet) << endl ;  
//        mNetworkStream->close() ; 
//        mNetworkStream = NULL ; 
//#ifdef DOMPI
//}
//#endif 
//        mOutputStream->close() ; 
//        mOutputStream = NULL ;
//
//    }
//}


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

