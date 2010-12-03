
#include <iostream>
using std::cout ; 
using std::endl ; 

#include <string>
using std::string ; 


#include <fstream>
using std::ifstream ; 
using std::ios ; 


#include "TinyBzNetParser.hpp"
#include <BlitzNet.hpp> 
#include <tinyxml.h>
#include <Note.hpp>


TinyBzNetParser::TinyBzNetParser() : mFileName(NULL)
{
}

BlitzNet* TinyBzNetParser::parseFile(string fileName) 
{
    string xmlString = "" ;

    ifstream inputFileStream(fileName.c_str(),ios::in) ; 
    char* buffer = new char[256] ; 

    while(! inputFileStream.eof()){
        inputFileStream.getline(buffer,100) ; 
        xmlString += buffer ; 
    }

    mFileName = new string(fileName) ; 
    return parse(xmlString) ; 
}



BlitzNet* TinyBzNetParser::parse(string xmlString) 
{
    BlitzNet* returnNet = new BlitzNet() ; 
    if(mFileName!=NULL){
        if(mFileName->size() >= MAX_FILENAME){
            mFileName = new string("..."+mFileName->substr(mFileName->size()-MAX_FILENAME, MAX_FILENAME-1-3 )) ;
        }
        (returnNet->getNote())->setNote("filename", string(*mFileName)) ; 
    }
    else{
        cout << "file name NOT set" << endl ; 
        throw "file name not set" ; 
    }

    TiXmlDocument *doc = new TiXmlDocument() ;
    doc->Parse( xmlString.c_str()  ) ; 
    if ( doc->Error() )
    {
        printf( "Error in %s: %s\n", doc->Value(), doc->ErrorDesc() );
        return NULL ; 
    }
    TiXmlElement* rootElement = doc->RootElement() ; 
    TiXmlNode* node = NULL ; 
    TiXmlNode* nodeValues = NULL ; 


    node = doc->FirstChild() ;  
//    cout << "doc: " << doc->Value() << endl ; 
    string argName = "" ; 
    string argValue = "" ; 
    string argType = "" ; 

    // make sure that the root element is network, and set the size
    string nodeValueName = "" ; 
    string nodeName = "" ; 
    returnNet->setNumNeurons( atoi(node->ToElement()->Attribute( NET_SIZE)) ); 
//    cout << "setting num neurons: " << returnNet->getNumNeurons() << endl ; 


    int nodeNumber = 0 ; 
    Vector* bias = returnNet->getBias() ; 
    Vector* biasMask = returnNet->getBiasMask() ; 
    Vector* tau = returnNet->getTau() ; 
    Vector* tauMask = returnNet->getTauMask() ; 
    Vector* gain = returnNet->getGain() ; 
    Vector* gainMask = returnNet->getGainMask() ; 
    Matrix* weights = returnNet->getWeights() ; 
    Matrix* weightMask = returnNet->getWeightMask() ; 
    Vector* initNeurons = returnNet->getInitNeuron() ; 
    Vector* vmem = returnNet->getNeurons() ; 
    int nodeFrom = -1 ; 
    int nodeTo = -1 ; 

    node = node->FirstChild() ; 

    while(node!=NULL) {
        nodeName = node->ToElement()->Value() ; 
        if(nodeName=="node"){
            nodeNumber = atoi( node->ToElement()->Attribute( NET_NODE_NUMBER )  ) ; 
//            cout << "nodeNumber: " << nodeNumber << endl ; 
            nodeValues = node->FirstChildElement() ; 
            while(nodeValues!=NULL){
                nodeValueName = nodeValues->ToElement()->Value() ;
//                cout << "nodeValueName: "  << nodeValueName << endl ; 
                if(nodeValueName==NET_BIAS){
                    (*bias)(nodeNumber) =  atof(nodeValues->ToElement()->Attribute(NET_VALUE)) ;
                    (*biasMask)(nodeNumber) = atof(nodeValues->ToElement()->Attribute(NET_MASK)) ;
                }else 
                if(nodeValueName==NET_TAU){
                    // get tau
                    // get tau mask
                    (*tau)(nodeNumber) = atof(nodeValues->ToElement()->Attribute(  NET_VALUE )) ;
                    (*tauMask)(nodeNumber) = atof(nodeValues->ToElement()->Attribute(  NET_MASK ) ) ;
                }else 
                if(nodeValueName==NET_GAIN){
                    (*gain)(nodeNumber) = atof(nodeValues->ToElement()->Attribute(  NET_VALUE )) ;
                    (*gainMask)(nodeNumber) = atof(nodeValues->ToElement()->Attribute(  NET_MASK )) ;
                }
                else
                if(nodeValueName==NET_VMEM){
                    // get vmem 
                    (*vmem)(nodeNumber) = atof(nodeValues->ToElement()->Attribute(  NET_VALUE)) ;
                }else 
                if(nodeValueName==NET_VINIT){
                    // get vinit
                    (*initNeurons)(nodeNumber) = atof(nodeValues->ToElement()->Attribute(  NET_VALUE )) ;
                }
                else{
                    cout << "TinyBzNetParser unrecognized node name: " << nodeValueName << endl ; 
                }
                nodeValues = nodeValues->NextSiblingElement() ; 
            }
            
        }
        else
        if(nodeName==NET_WEIGHT){
            // handle weights, here
            // get nodeFrom, get nodeto
            nodeFrom = atoi(node->ToElement()->Attribute(NET_NODE_FROM)) ; 
            nodeTo = atoi(node->ToElement()->Attribute(NET_NODE_TO)) ; 

            // assign the weight
            (*weights)(nodeFrom,nodeTo) = atof(node->ToElement()->Attribute(NET_WEIGHT)) ; 
            
            // assign the mask
            (*weightMask)(nodeFrom,nodeTo) = atof(node->ToElement()->Attribute(NET_MASK)) ; 
        }
        node = node->NextSiblingElement() ; 
    }

    return returnNet ; 
}

const int TinyBzNetParser::MAX_FILENAME = 70 ; /// reader blows up if filename in xml is longer than this


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
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: TinyBzNetParser.cpp,v 1.2 2004/01/13 20:43:36 ndunn Exp $







