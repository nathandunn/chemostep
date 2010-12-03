// -*- C++ -*-
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: QtFileLoadList.cpp,v 1.2 2004/01/13 20:43:36 ndunn Exp $

#include "QtFileLoadList.h"

#include "NameHandler.hpp" 
#include "CommandButton.hpp" 
#include "Renderer.hpp" 

#include <qfiledialog.h>
#include <qpushbutton.h>
#include <qframe.h>
#include <qlayout.h>
#include <qlistbox.h>
#include <qstring.h>


QtFileLoadList::QtFileLoadList(const QString & text, QWidget *parent, const char* name,Renderer *referenceObject, string newType) :   QFrame(   parent,name ) , CommandButton( NameHandler::getNameFromPath(name) ,NameHandler::getAllButNameFromPath(name) ,newType , referenceObject)
{
    // add a QLineEdit and a QPushButton
    localLayout = new QVBoxLayout(this,5) ; 



    // column 2
//    QFrame* frame2 = new QFrame(this,"frame2") ; 
//    QVBoxLayout* column2 = new QVBoxLayout(frame2,5) ; 

//    column2->addWidget(addFileButton) ; 
//    column2->addWidget(removeFileButton) ; 


    QFrame* row1Frame2 = new QFrame(this,"row1Frame2") ; 
    QFrame* row2Frame2 = new QFrame(this,"row2Frame2") ; 
    QFrame* row3Frame2 = new QFrame(this,"row3Frame2") ; 
    

    // row  1
    fileBox = new QListBox(row1Frame2,"listBox") ; 
    fileBox->setSelectionMode(QListBox::Single) ; 

    // row 2 
    addFileButton = new QPushButton("add",row2Frame2) ; 
    removeFileButton = new QPushButton("remove",row2Frame2) ; 
    editFileButton = new QPushButton("edit",row2Frame2) ; 

    // row 3 
    clearFileButton = new QPushButton("clear",row3Frame2) ; 
    moveDownButton = new QPushButton("move down",row3Frame2) ; 
    moveUpButton = new QPushButton("move up",row3Frame2) ; 

    QHBoxLayout* row1 = new QHBoxLayout(row1Frame2,5) ; 
    QHBoxLayout* row2 = new QHBoxLayout(row2Frame2,5) ; 
    QHBoxLayout* row3 = new QHBoxLayout(row3Frame2,5) ; 

    // row 1 
    row1->addWidget(fileBox) ; 

    // row 2 
    row2->addWidget(addFileButton) ; 
    row2->addWidget(removeFileButton) ; 
    row2->addWidget(editFileButton) ; 

    // row 3
    row3->addWidget(clearFileButton) ; 
    row3->addWidget(moveDownButton) ; 
    row3->addWidget(moveUpButton) ; 

    // add the buttons to each row
    localLayout->addWidget(row1Frame2) ; 
    localLayout->addWidget(row2Frame2) ; 
    localLayout->addWidget(row3Frame2) ; 


    // connect QPushButton to the QFileDialog
    connect(addFileButton,SIGNAL(clicked()),this,SLOT(addFile())) ; 
    connect(removeFileButton,SIGNAL(clicked()),this,SLOT(removeFile())) ; 
    connect(editFileButton,SIGNAL(clicked()),this,SLOT(editFile())) ; 
    connect(clearFileButton,SIGNAL(clicked()),this,SLOT(clearFiles())) ; 
    connect(moveDownButton,SIGNAL(clicked()),this,SLOT(moveSelectionDown())) ; 
    connect(moveUpButton,SIGNAL(clicked()),this,SLOT(moveSelectionUp())) ; 

    connect(fileBox,SIGNAL(doubleClicked(QListBoxItem*)),this,SLOT(editFile())) ; 
    connect(fileBox,SIGNAL(returnPressed(QListBoxItem*)),this,SLOT(editFile())) ; 

}

/**
 *  This will be rendered as xml by the TiListParser class.  
 */
string QtFileLoadList::getListXml() 
{
    string returnString = "" ; 
    returnString += "<"+TiListParser::LIST+">\n" ;
    if(fileBox!=NULL){
//        cout <<" fileBox size is: " << fileBox->count() << endl ; 
        for(int i = 0 ; i < fileBox->count() ; i++){
            returnString += "\t<"+TiListParser::ITEM+">" ;
            returnString += fileBox->text(i).ascii() ; 
            returnString += "</"+TiListParser::ITEM+">" ;
            returnString += "\n" ; 
        }
    }
//    else{
//        cout << "fileBox is NULL" << endl ; 
//    }
    returnString += "</"+TiListParser::LIST+">\n" ;


    return returnString ;  ; 
}

void QtFileLoadList::setList(string xmlList) 
{
//    cout << "xmlList" << endl ; 
    vector<string>* newList = TiListParser::parseList(xmlList) ; 
    setList(newList) ; 
}


void QtFileLoadList::setList(vector<string>* newList) 
{
//    cout << "vector<list>" << endl ; 
    clearFiles() ; 
    for(int i = 0 ; i < newList->size() ; i++){
//        fileBox->insertItem( (*newList)[i] ) ; 
        fileBox->insertItem( ((*newList)[i]).c_str() ) ; 
    }
}




vector<string>* QtFileLoadList::getListVector() 
{
    vector<string>* returnVector = new vector<string>() ; 
    if(fileBox==NULL){
        return returnVector ; 
    }

    for(int i = 0 ; i < fileBox->count() ; i++){
//        returnVector->push_back(fileBox->text(i)) ; 
        returnVector->push_back( (fileBox->text(i)).latin1() ) ; 
    }

    return returnVector ; 
}



void QtFileLoadList::addFile() 
{
    QString fileName  = (QFileDialog::getOpenFileName()) ; 
    if(fileName!=""){
        fileBox->insertItem(fileName) ; 
        updateOption() ;   
    }
}

void QtFileLoadList::clearFiles() 
{
    fileBox->clear() ; 
    updateOption() ; 
}


void QtFileLoadList::editFile() 
{
    int currentItem = fileBox->currentItem() ; 
    QString fileName = fileBox->text(currentItem)   ; 

    fileName  = QFileDialog::getOpenFileName( fileName ) ; 
    if(fileName!=""){
        fileBox->changeItem(fileName,currentItem) ; 
        updateOption() ;   
    }
}

void QtFileLoadList::removeFile() 
{
    fileBox->removeItem(  fileBox->currentItem() ) ; 
    updateOption() ;   
}



void QtFileLoadList::moveSelectionDown() 
{
    int currentItem = fileBox->currentItem() ; 
    int nextItem = currentItem + 1 ; 

    if(nextItem < fileBox->count()){
        QString thisFileName = fileBox->text(currentItem)   ; 
        QString nextFileName = fileBox->text(nextItem)   ; 

        fileBox->changeItem(thisFileName,nextItem) ; 
        fileBox->changeItem(nextFileName,currentItem) ; 
        fileBox->setSelected(nextItem,true) ; 
        updateOption() ;   
    }
}

void QtFileLoadList::moveSelectionUp() 
{
    int currentItem = fileBox->currentItem() ; 
    int nextItem = currentItem - 1 ; 

    if(currentItem>0){
        QString thisFileName = fileBox->text(currentItem)   ; 
        QString nextFileName = fileBox->text(nextItem)   ; 

        fileBox->changeItem(thisFileName,nextItem) ; 
        fileBox->changeItem(nextFileName,currentItem) ; 
        fileBox->setSelected(nextItem,true) ; 
        updateOption() ;   
    }
}




void QtFileLoadList::updateOption()
{
        string fileText = "" ; 


        fileText += "<"+TiListParser::LIST+">\n" ;
        for(int i = 0 ; i < fileBox->count() ; i++){
            fileText += "\t<"+TiListParser::ITEM+">" ;
            fileText += fileBox->text(i).ascii() ; 
            fileText += "</"+TiListParser::ITEM+">" ;
            fileText += "\n" ; 
        }
        fileText += "</"+TiListParser::LIST+">\n" ;

//        cout << "fileText: " << fileText << endl ; 

        fileText = fileText.substr(0,fileText.length()-1) ; 

        // add everything 
        ((Renderer*) thisParent)->setOptionFromGui( this,fileText) ; 
}




