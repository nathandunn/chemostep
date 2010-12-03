// -*- C++ -*-
// FILE: "/home/ndunn/cvs/NETWORK_MINER/src/NeuronList.cpp"
// LAST MODIFICATION: "Mon, 13 Jan 2003 07:52:13 -0800 (ndunn)"
// (C) 2003 by Nathan Dunn, <ndunn@idiom.com>
// $Id: NeuronList.cpp,v 1.11 2003/01/13 20:53:06 ndunn Exp $


#include "NeuronList.hpp"

NeuronList::NeuronList() {
}

NeuronList::NeuronList(vector<Neuron> newList) {
   list = newList ; 
}

Neuron NeuronList::getNeuron(int id){

    Neuron newNeuron ; 
    for(int i = 0 ; i < list.size() ;  i++){
//        cout << i << ": " << ((Neuron) list[i]).getId() << endl ; 
		if( ((Neuron) list[i]).getId()==id){
//            cout << "found neuron: " << id << endl ; 
			newNeuron = (Neuron) list[i] ; 
            return newNeuron ; 
        }
    }

    cout << "failed to find neuron: " << id << " in connection list" << endl ; 
    return newNeuron ; 
}

void NeuronList::setNeuronById(Neuron newNeuron){
    int id = newNeuron.getId() ;
    for(int i = 0 ; i < list.size() ;  i++){
		if( ((Neuron) list[i]).getId()==id){
			list[i] = newNeuron ; 
        }
    }
}


int NeuronList::addNeuron(Neuron newNeuron){
   list.push_back(newNeuron) ; 
//   cout << "adding neuron id: " << newNeuron.getId() << " parentId: " << newNeuron.getParentId()  << " locale: "<< newNeuron.getLocale() << " parentLocale: "<< newNeuron.getParentLocale() << endl ; 
   return list.size() ; 
}

ostream& operator<<(ostream &s, const NeuronList &list) 
{

  for(int i = 0 ; i < ((NeuronList) list).size() ; i++){
//	 s << list.getNeuronAt(i) << Neuron::delimiter ; 
	 s << i << ": " <<  ((NeuronList) list).getNeuronAt(i) << Neuron::delimiter << endl ; 
  }

  return s;
}



