#include <iostream>
using std::cout ; 
using std::endl ; 
using std::ostringstream ; 

#include "DotNetConverter.hpp"


string DotNetConverter::createGraph( BlitzLiveNet* newNet,string title) 
{
    string returnString = "" ; 
    ostringstream tempStream ; 

    returnString = "digraph dotgraph { \n " ; 

    // create the title
	if(title!=""){
        tempStream.str("") ; 
        tempStream << "\t" << "\"" << title << "\"" << "[shape=box] ; \n" ; 
        returnString += tempStream.str() ; 
    }

    int numNeurons = newNet->getNumNeurons() ; 
    vector<string>* neuronStrings = new vector<string>(numNeurons)  ; 
    Vector* tau = newNet->getTau() ; 
    Vector* bias = newNet->getBias() ; 
    Vector* gain = newNet->getGain() ; 
    Matrix* weights = newNet->getWeights() ; 

    for(int i = 0 ; i < numNeurons ; i++){
        tempStream.str("") ; 
        tempStream << "\"" ; 
        tempStream << "id[" << i << "]\\n" ; 
        tempStream << "tau[" << (*tau)(i) << "]\\n" ; 
        tempStream << "bias[" << (*bias)(i) << "]\\n" ; 
        if( (*gain)(i)!=1){
            tempStream << "gain[" << (*gain)(i) << "]" ; 
        }
        tempStream << "\"" ; 
        (*neuronStrings)[i] = tempStream.str() ; 
    }

    for(int i = 0 ; i < numNeurons ; i++){
        for(int j = 0 ; j < numNeurons ; j++){
            if( (*weights)(i,j)!=0){
                tempStream.str("") ; 
                // the connections
                 tempStream <<  "\t" << (*neuronStrings)[i] << "->" << (*neuronStrings)[j] ;
                // the label
                tempStream << "[" ;
                tempStream << "label=\"" << (*weights)(i,j) << "\"" ;
                tempStream << "," ; 
                tempStream << "style=bold" ;
                 tempStream <<   "] " ;
                    
                tempStream <<  " ; " << endl ;
                 returnString += tempStream.str() ; 
            }
        }
    }

    returnString += "}\n" ; 

//    cout << returnString << endl;  

    return returnString ; 
}



/* Function int main(int argc, char **argv) {{{ */
//int main(int argc, char **argv)
//{


//    return 0;
//} /* }}} */



// -*- C++ -*-

// (C) 2005 by Nathan Dunn, <ndunn@mac.com>


