// -*- C++ -*-
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: QtTypeField.cpp,v 1.2 2004/01/13 20:43:36 ndunn Exp $

#include "QtTypeField.h"

#include "CommandButton.hpp" 
#include "Renderer.hpp" 
#include "TiListParser.hpp" 

#include <qcombobox.h>
#include <stdlib.h>

#include <vector>
using std::vector ; 

QtTypeField::QtTypeField(vector<string>* valueMap, QWidget *parent, const char* name,Renderer *referenceObject, string newType) :   QComboBox (  parent, name ) , CommandButton( NameHandler::getNameFromPath(name) ,NameHandler::getAllButNameFromPath(name) ,newType , referenceObject)
{
    mSelectedOption = 0 ; 
    mOptionVector = new vector<string>(*valueMap) ; 
    mNumOptions = mOptionVector->size() ; 
//    vector<string>::iterator valueIter = valueMap->begin() ;  
   
	for(int i = 0 ; i < mNumOptions ; i++){
        insertItem( QString( ((*valueMap)[i]).c_str() ) ) ; 
    }

    
    setCurrentItem(0) ; 
    connect(this,SIGNAL(activated(const QString & string)),this,SLOT(updateOption(const QString & string))) ; 
    connect(this,SIGNAL(activated(int)),this,SLOT(updateOption(int))) ; 
}

void QtTypeField::updateOption(const QString & string) 
{
	updateOption() ; 
}


void QtTypeField::updateOption(int newOption) 
{
    mSelectedOption = currentItem() ; 
    ((Renderer*) thisParent)->setOptionFromGui( this, (new TiListParser())->createList(mOptionVector,currentText().ascii() )  ) ; 
}




void QtTypeField::setList(string xmlList) 
{
    vector<string>* newList = TiListParser::parseList(xmlList, &mSelectedOption ) ; 
    setList(newList) ; 
}

void QtTypeField::setList(vector<string>* newList) 
{
    clear() ; 
    for(int i = 0 ; i < newList->size() ; i++){
        insertItem( ((*newList)[i]).c_str() ) ; 
    }

    setCurrentItem(mSelectedOption) ; 
}







