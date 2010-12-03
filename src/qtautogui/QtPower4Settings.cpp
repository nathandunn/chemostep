
#include <iostream>
using std::cout ; 
using std::endl ; 

#include <string>
using std::string ; 

#include <fstream>
using std::ifstream ; 
using std::ofstream ; 
using std::ios ; 

#include <qdir.h>

#include "QtPower4Settings.hpp"

QtPower4Settings::QtPower4Settings() : QSettings() {
//   mHomeFile = "/home/.qt/rc" ; 
   mHomeFile = QDir::homeDirPath()+"/.qt/rc" ; 
//   mHomeFile = "/home/users/ndunn/.qt/rc" ; 
   mPrefStream = NULL ; 
}

QtPower4Settings::~QtPower4Settings() 
{
}


QString QtPower4Settings::findKey(const QString & key) 
{
     if(mPrefStream==NULL){
         mPrefStream = new ifstream( mHomeFile,ios::in)   ; 
         if( ( mPrefStream->rdstate() && ifstream::failbit) != 0 ){
             mPrefStream->close() ; 
             delete mPrefStream ; 
             // touch the file
             ofstream touchStream(mHomeFile,ios::out) ; 
             touchStream << endl ; 
             touchStream.close() ; 
             // assuming it works this time ; 
             mPrefStream = new ifstream( mHomeFile,ios::in)   ; 
         }
     }
    char* buffer = new char[256] ; 
    while(! mPrefStream->eof() ){
        mPrefStream->getline(buffer,256) ; 
        if( getKey( QString( buffer ) ) == key){
            return getName( QString( buffer  ) ) ; 
        }
    }
    return "" ; 
}


QString QtPower4Settings::getKey(QString lineValue) 
{
    return   (QStringList::split("=",lineValue))[0] ; 
}


QString QtPower4Settings::getName(QString lineValue) 
{
    return   (QStringList::split("=",lineValue))[1] ; 
}



//QtPower4Settings::~QtPower4Settings() : ~QSettings() { }
QString QtPower4Settings::readEntry(const QString & key , const QString & def, bool * ok) 
{
    QString returnKey = findKey(key) ; 
    if(returnKey!=""){
        return returnKey ; 
    }
    else{
        return def ; 
    }
}

int QtPower4Settings::readNumEntry(const QString & key , int def,  bool * ok) 
{
    QString returnKey = findKey(key) ; 
    if(returnKey!=""){
        return atoi(returnKey); 
    }
    else{
        return def ; 
    }
}

double QtPower4Settings::readDoubleEntry(const QString & key , double def, bool * ok) 
{
    QString returnKey = findKey(key) ; 
    if(returnKey!=""){
        return atof(returnKey); 
    }
    else{
        return def ; 
    }
}

bool QtPower4Settings::readBoolEntry(const QString & key , bool def, bool * ok) 
{
    QString returnKey = findKey(key) ; 
    if(returnKey!=""){
        if(returnKey=="true") {
            return true ; 
        }
        else
        if(returnKey=="false") {
            return false ; 
        }
        else{
            return def ; 
        }
    }
    else{
        return def ; 
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

// (C) 2005 by Nathan Dunn, <ndunn@mac.com>


