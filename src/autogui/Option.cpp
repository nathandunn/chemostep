#include <iostream>
using std::cout ; 
using std::endl ; 


#include <vector>
using std::vector ; 

#include <string>
using std::string ; 


#include "Option.hpp"

Option::Option(string newName,string newType,void* newRef, string newPath,string newLabel,vector<string>* newValue,bool set) 
:mValue(new vector<string>()) 
{
    cout << "vector constructor" << newValue->size() << endl ; 
        mName = newName ; 
        mType = newType ; 
        mRefVar = newRef ; 
        mPathToType = newPath ; 
        setValue(newValue) ; 
        mLabel = newLabel ; 
        mIsSet = set ; 
}



Option::Option(string newName,string newType,void* newRef, string newPath,string newLabel,string newValue,bool set) 
:mValue(new vector<string>()) 
{
        mName = newName ; 
        mType = newType ; 
        mRefVar = newRef ; 
        mPathToType = newPath ; 
        mLabel = newLabel ; 
        setValue(newValue) ; 
        mIsSet = set ; 
}

bool Option::setValue(vector<string>* _value) 
{
//    cout << "Option::setting vector of size: " << _value->size() << endl ; 
    if(mValue==NULL || mValue->size()!=_value->size()){
        mValue = new vector<string>(*_value) ; 
    }
    else
    if(mValue->size()==_value->size()){
        *mValue = *_value ; 
    }

    cout << "set to mValue->size(): " << mValue->size() << endl ; 
    return true ; 
    
}

vector<string>* Option::getValueVector() 
{
    cout << "returning valueVector of size: "<< mValue->size() << endl ; 
    return new vector<string>(*mValue) ; 
}


bool Option::setValue(string _value,int indexValue) 
{
    if(mValue==NULL){
        mValue = new vector<string>() ; 
    }


    if(mValue->size()<=indexValue){
        mValue->push_back(_value) ; 
    }else{
        (*mValue)[indexValue] = _value ; 
    }



    return true ;
}

string Option::getValue(int index) 
{
    if(mValue==NULL 
       || 
       index >= mValue->size()
        )
    {
        return "invalid index" ; 
    }
    return (*mValue)[index] ; 
}



/* Function int main(int argc, char **argv) {{{ */
//int main(int argc, char **argv)
//{


//    return 0;
//} /* }}} */



// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


