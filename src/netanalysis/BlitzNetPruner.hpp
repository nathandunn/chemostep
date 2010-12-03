#ifndef BLITZNETPRUNER_HPP_
#  define BLITZNETPRUNER_HPP_

#include <vector>
using std::vector ; 


class BlitzNet ; 

class BlitzNetPruner {

public:
    BlitzNetPruner() ; 
    BlitzNet* prune(BlitzNet* origNet, vector<double>* amplitudes, double threshold) ; 

protected:
    vector<double>* getActiveSet( vector<double>* activities,double threshold) ; 
    void printActiveNeurons( vector<double>* activities) ; 
    BlitzNet* strip( BlitzNet* origNet, vector<double>* activities) ; 
    bool connectionIsActive(vector<double>* activeNeurons,int testNeuron) ; 
    int getNewConnectionMapping(vector<double>* activeNeurons,int testNeuron) ; 

} ;

#endif /* ifndef BLITZNETPRUNER_H */
// -*- C++ -*-
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

