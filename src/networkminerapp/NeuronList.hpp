// -*- C++ -*-
// FILE: "/Users/nathandunn/cvs/NETWORK_MINER/src/NeuronList.hpp"
// LAST MODIFICATION: "Wed, 08 Jan 2003 17:39:44 -0800 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@idiom.com>
// $Id: NeuronList.hpp,v 1.4 2003/01/09 01:16:36 ndunn Exp $

#ifndef _NeuronList_
#define _NeuronList_

// this is a wrapper around vector<Neuron>
//
#include "Neuron.hpp"

#include <vector>
using std::vector ; 

class NeuronList : public vector<Neuron> {

public:
	NeuronList() ; 
	NeuronList(vector<Neuron> newList) ; 
    Neuron getNeuron(int id);
    Neuron getNeuronAt(int arrayMark){
      return list[arrayMark] ;     
    };
     
    void setNeuronById(Neuron newNeuron) ;

    int size(){
  		return list.size() ; 
    }
   
    void setNeuron(Neuron newNeuron, int newId){
       list[newId] = newNeuron ; 
    }
    int addNeuron(Neuron newNeuron);


private:
    vector<Neuron> list ; 
} ;

ostream& operator<<(ostream &s, const NeuronList &list) ;

#endif

