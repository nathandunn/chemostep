#ifndef PRUNEDRIVER_HPP_
#  define PRUNEDRIVER_HPP_


#include <TiFlatBaseApp.hpp>

#include <vector>
using std::vector ; 

#include <fstream>
using std::ofstream ; 



class TinyBzNetParser ; 
class TinyAppInterfaceXmlEngine ; 
class BlitzLiveNet ; 
/**
 *  This class runs that actual Pruner. 
 *
 */

class DottyNetDriver : public TiFlatBaseApp {

public:
    DottyNetDriver(string newInterfaceName, string newTypeName, AppInterface* newParent) ; 
    void* startPlotter() ; 

    // AppInterface classes
    bool createLocalMaps() ; 
    string doLocalCommand(Command *theCommand) ; 

    // commands
    const static string START_PLOTTER ; 

protected:
    string mNetworkFile, mOutputFile; 
    int mNumInputs,mNumOutputs  ; 

    // plotting options
    vector<string>* mTempType ; 
    string mActionType ; 



} ;

#endif /* ifndef PRUNEERDRIVER_HPP_ */
// -*- C++ -*-
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: DottyNetDriver.hpp,v 1.3 2004/01/27 20:27:19 ndunn Exp $

