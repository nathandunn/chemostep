// -*- C++ -*-
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>


#ifndef _OPTION_HPP_
#define _OPTION_HPP_

#include <vector>
using std::vector ; 

class Option{

public:
//    Option()  ; 
    Option(string newName,string newType,void* newRef =NULL, string newPath="",string newLabel="",string newValue="",bool set=false) ; 
    Option(string newName,string newType,void* newRef =NULL, string newPath="",string newLabel="",vector<string>* newValue=NULL,bool set=true) ; 

    /// Returns teh label
    virtual string Option::getLabel(){
        if(mLabel!=""){
            return mLabel ; 
        }
        else{
            return mName ; 
        }
    }

    /// Set the label that will be displayed.  
    virtual void Option::setLabel(string newLabel){
        mLabel = newLabel ; 
    }

    virtual string getName()
    {
        return(mName);
    }
                                                         
              
    virtual void setName(string _name)
    {
        mName= _name;
    }

    virtual string getType()
    {
        return(mType);
    }

    virtual void setType(string _type)
    {
        mType = _type;
        return;
    }


    virtual vector<string>* getValueVector() ; 
    virtual string getValue(int index=0) ; 
    virtual bool setValue(string _value,int indexValue=0) ; 
    virtual bool setValue(vector<string>* _value) ; 

    virtual bool getIsSet()
    {
        return(mIsSet);
    }


    virtual void setIsSet(bool _isSet)
    {
        mIsSet = _isSet;
        return;
    }

    virtual void* getRef() {
        return(mRefVar);
    }

    virtual void setRef(void* _mRef) {
        mRefVar = _mRef;
        return;
    }
    
    virtual string getPath() {
        return(mPathToType);
    }

    virtual void setPath(string _mPathToType) {
        mPathToType = _mPathToType;
        return;
    }





protected:
    string mName ; 
    string mType ; 
    vector<string>* mValue ; 
    string mLabel ; 
    string mPathToType ; 
    bool mIsSet ; 
    void* mRefVar ; /// This value hold any complex datatypes.


} ;


#endif

