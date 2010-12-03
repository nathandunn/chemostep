// -*- C++ -*-

#include "QtFlatRenderer.h" 
#include "QtIntField.h" 
#include "QtTypeField.h" 
#include "QtFileLoadField.h" 
#include "QtFileSaveField.h" 
#include "QtFileLoadList.h" 
#include "QtCommandButton.h" 
#include "QtOptionField.h" 
#include "QtBoolField.h" 


#include "TransmitterApp.hpp"
#include "Option.hpp"
#include "Command.hpp"
#include "Type.hpp"
#include "Interface.hpp"
#include "InterfaceTypes.hpp"
#include "NameHandler.hpp"

#include <iostream>
using std::cout  ; 
using std::endl ; 

#include <vector>
using std::vector ; 

#include <qlayout.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qobjectlist.h>
#include <qframe.h>
#include <qvbox.h>
#include <qvgroupbox.h>
#include <qscrollview.h>
#include <qmessagebox.h>
#ifdef POWER64LINUX
#include <QtPower4Settings.hpp>
#endif
#include <qsettings.h>
#include <qstringlist.h>


QtFlatRenderer::QtFlatRenderer(TransmitterApp* newTransmitterApp,AppParser *newAppParser) : FlatRenderer(newTransmitterApp,newAppParser) 
, QScrollView(NULL,"APP")  
#ifdef POWER64LINUX
,mPrefs(new QtPower4Settings())
#else
,mPrefs(new QSettings())
#endif
{

}

/**
 *  It saves each option in the gui based on type.  In the final
 *  stage it writes out by deleting QSettings and the reinstatiates.
 *  Get the chilren (gui), and add options for each one.
 *  Get the groupBox which is defined for each type.  
 *  Since this is flat, we need to get the only type, 
 *  but we may as well iterate through them all in case there
 *  are additional types.
 */
bool QtFlatRenderer::savePreferences() 
{
    #ifndef POWER64LINUX
    mPrefs->setPath(mPrefURL.c_str(),mPreferenceRoot.c_str()) ; 
    #endif

    // cout << "optionList->size(): " << optionList->size() << endl ; 

    // need to get all of the option panels, somehow . . . . do we have this loaded?
    Option* theOption = NULL ; 
    string interfaceName  = "" ; 
    string  typeName ; 
    for(int i = 0 ; i < optionList->size() ; i++){
        theOption = (*optionList)[i] ; 
        // cout << "the full name: " << theOption->getName() << endl ; 
        saveOptionPref(theOption->getName(),getOptionFromGui(theOption)  , theOption->getType()) ; 
    }

    // this ensures that we write out
    #ifdef POWER64LINUX
    mPrefs->~QtPower4Settings() ; 
    mPrefs = NULL ; 
    mPrefs = new QtPower4Settings() ; 
    #else
    mPrefs->~QSettings() ; 
    mPrefs = NULL ; 
    mPrefs = new QSettings() ; 
    #endif
    return true ; 
}

bool QtFlatRenderer::loadPreferences() 
{
    #ifdef POWER64LINUX
    // this does absolutely nothing
    mPrefs->insertSearchPath(QSettings::Unix,QString( mPreferenceRoot.c_str()) ) ; 
    #else
    mPrefs->setPath(mPrefURL.c_str(),mPreferenceRoot.c_str()) ; 
    #endif

    Option* theOption = NULL ; 
    string interfaceName  = "" ; 
    string  typeName ; 
    // cout << "options to load: " << optionList->size() << endl ; 
    for(int i = 0 ; i < optionList->size() ; i++){
        theOption = (*optionList)[i] ; 
        // cout << "the full name: " << theOption->getName() << endl ; 
        loadOptionPref(theOption) ; 
    }

    return true ; 

}




int QtFlatRenderer::QtFlatRenderer::message(string caption,string text) 
{
    return QMessageBox::message(caption.c_str(),text.c_str()) ; 
}

/**
 *  It saves each option in the gui based on type using the QSettings class.  
 */
bool QtFlatRenderer::saveOptionPref(string key,string value,string type) 
{
//    #ifndef MACOSX
        key = mPreferenceRoot + "/" + key ; 
//    #endif

    // cout << "saving pref key: " << key << " value: " << value << " type: " << type << endl ; 
    
    // need an app name
	if(type==OPT_BOOL){
        // cout << "the type is a bool" << endl ; 
        if(value==OPT_BOOL_TRUE){
            mPrefs->writeEntry(key.c_str(),true) ; 
            return true ; 
        }
        else
        if(value==OPT_BOOL_FALSE){
            mPrefs->writeEntry(key.c_str(),false) ; 
            return true ; 
        }
        else{
            // cout << "don't understand BOOL value: " << value<< endl ; 
            return false ; 
        }
    }
	if(type==OPT_STRING){
        mPrefs->writeEntry(key.c_str(),value.c_str()) ; 
		return true ; 
    }
    else
	if(type==OPT_DOUBLE){
        mPrefs->writeEntry(key.c_str(),atof(value.c_str())) ; 
		return true ; 
    }
    else
	if(type==OPT_INT){
        mPrefs->writeEntry(key.c_str(),atoi(value.c_str())) ; 
		return true ; 
    }
    else
	if(
        type==OPT_FILE_SAVE || 
        type==OPT_FILE_LOAD
        ){
        mPrefs->writeEntry(key.c_str(),value.c_str()) ; 
		return true ; 
    }
    else
	if(type==LIST_TYPE){
        mPrefs->writeEntry(key.c_str(),value.c_str()) ; 

		return true ; 
    }
    else
	if(type==LIST_FILE_LOAD){
        // for each key
        // in this case, the value should be xml so we need to parse into a vector

        vector<string>* valueList = TiListParser::parseList(value) ; 
        char buffer[256] ; 
        for(int i = 0 ; i < valueList->size() ; i++){
            sprintf(buffer,"%s/entry%i",key.c_str(),i) ; 
            // cout << "writing entry: " << buffer << " value: " << (*valueList)[i] << endl ; 
            mPrefs->writeEntry(buffer, ((*valueList)[i]).c_str() ) ; 
        }
		return true ; 
    }

    return false ; 
}


/** Puts options from preferences and sets them in the gui based on type.
 *  It does this from Qt's QSettings class.
**/   
bool QtFlatRenderer::loadOptionPref(Option *theOption) 
{

    string key = theOption->getName() ; 
    string type = theOption->getType() ; 
    
    key = mPreferenceRoot + "/" + key ; 

    // need an app name
	if(type==OPT_BOOL){
        bool keyValue = mPrefs->readBoolEntry(key.c_str(),false) ; 
        if(keyValue==true){
            theOption->setValue(OPT_BOOL_TRUE) ; 
        }
        else{
            theOption->setValue(OPT_BOOL_FALSE) ; 
        }

    }
    else
	if(type==OPT_STRING){
        QString keyValue = mPrefs->readEntry(key.c_str(),"fill in") ; 
        theOption->setValue(keyValue.ascii()) ; 
    }
    else
	if(type==OPT_DOUBLE){
        double keyValue = mPrefs->readDoubleEntry(key.c_str(),0.0) ; 
        char buffer[128] ; 
        sprintf(buffer,"%10.3f",keyValue) ; 
        theOption->setValue(buffer) ; 
    }
    else
	if(type==OPT_INT){
        int keyValue = mPrefs->readNumEntry(key.c_str(),0) ; 
        char buffer[128] ; 
        sprintf(buffer,"%i",keyValue) ; 
        theOption->setValue(buffer) ; 
    }
    else
	if(
        type==OPT_FILE_SAVE || 
        type==OPT_FILE_LOAD
        ){
        QString keyValue = mPrefs->readEntry(key.c_str(),"enter") ; 
        theOption->setValue(keyValue.ascii()) ; 
    }
    else
    // load from the original option, but then don't set anything
    if(type==LIST_TYPE){
        QString keyValue = mPrefs->readEntry(key.c_str(),"enter") ; 
        vector<string>* optionList = (new TiListParser())->parseList(theOption->getValue())  ;
        string xmlList = TiListParser::createList( optionList ,  keyValue.ascii())   ; 
        theOption->setValue(   xmlList ) ; 
    }
    else
	if(type==LIST_FILE_LOAD){
        // for each key
        // need to get keys as QStringList since the keys are TARGET_FILES, etc.
        // convert to xml, set to option and send over
        vector<string>* fileList = new vector<string>() ; 
        QStringList keyList = mPrefs->entryList(key.c_str()) ; 

        QString keyValue  ; 
        QString newKey ; 
        for(int i = 0 ; i < keyList.size() ; i++){
            #ifndef MACOSX
            newKey =  strcat( (char*) key.c_str(),"/")+  keyList[i] ; 
            keyValue = mPrefs->readEntry(newKey) ; 
            fileList->push_back(keyValue.ascii()) ; 
            #else
            newKey =  key + "/" +  keyList[i] ; 
            keyValue = mPrefs->readEntry(newKey) ; 
            fileList->push_back(keyValue) ; 
            #endif
        }

        string xmlList = TiListParser::createList(fileList) ; 
        theOption->setValue(xmlList) ; 
    }
    else{
        cout << "mPreferenceRoot: " << mPreferenceRoot << endl ; 
      cout << "could not find key ["<< key << "] or type[" << type<< "]" <<  endl ; 
    }
    // cout << "theValue:  "  << theOption->getValue() << endl ; 
    setGuiOption(theOption) ; 

    return true ; 
}




string QtFlatRenderer::getOptionFromGui(Option* optionValue) 
{
	QWidget* lineWidget = NULL ; 
    // cout << "the path: " << optionValue->getPath() << endl ; 
    lineWidget = (QtOptionField*) this->child( (optionValue->getPath()+NameHandler::NAME_DELIMITER+optionValue->getName()).c_str()  ) ; 
    if( lineWidget != NULL  ) { 
//         cout << "lineWidget->getName(): " << lineWidget->className() << endl ; 
        if(  strcmp(  lineWidget->className(),"QtOptionField") == 0 ){
            return ((QLineEdit*) lineWidget)->text().ascii() ; 
        }
        else
        if( strcmp(lineWidget->className(),"QtBoolField") == 0 ){
            if(  ((QCheckBox*) lineWidget)->isChecked()){
                return "TRUE" ; 
            }
            else{
                return "FALSE" ; 
            }
        }
        else
//        if(lineWidget->className()=="QtIntField"){
        if( strcmp(lineWidget->className(),"QtIntField")==0){
            return ((QSpinBox*) lineWidget)->text().latin1() ; 
        }
        else
        if( 
//            lineWidget->className()=="QtFileLoadField"
            strcmp(lineWidget->className(),"QtFileLoadField")==0
            ||
//            lineWidget->className()=="QtFileSaveField"){
            strcmp(lineWidget->className(),"QtFileSaveField")==0 ){
            return ((QtFileLoadField*) lineWidget)->getFileName() ; 
        }
        else
        if(strcmp(lineWidget->className(),"QtFileLoadList")==0){
        // return as xml loads
            return  ( (QtFileLoadList*)lineWidget)->getListXml() ; 
        }
        else
        if(  strcmp(  lineWidget->className(),"QtTypeField") == 0 ){
//            cout << "getting QtTypeField: " << ( (QtTypeField*) lineWidget)->currentText().ascii()  << endl ; 
            return ((QtTypeField*) lineWidget)->currentText().ascii() ; 
        }
        else
        {
            return "WIDGET NOT FOUND" ; 
        }
    }
    else{
        return "NULL OPTION" ; 
    }
}

string QtFlatRenderer::updateOptionsFromGui() 
{
    return "" ; 
}

string QtFlatRenderer::setGuiOption(Option* optionValue) 
{

    // get the appropriately named field from the mainFrame and set
    // value from the optionValue

    // cout << "setGuiOption: " << optionValue << endl ; 
    // cout << "setGuiOption path: '" << optionValue->getPath() << "'" << endl ; 

    QWidget* fieldWidget = NULL ; 
    fieldWidget = (QWidget*) this->child( (optionValue->getPath()+NameHandler::NAME_DELIMITER+optionValue->getName()).c_str()  ) ; 
    string type = optionValue->getType() ; 
	if(type==OPT_BOOL){
        if(   optionValue->getValue()==OPT_BOOL_TRUE){
            ((QtBoolField*) fieldWidget)->setChecked( true ) ; 
            ((QtBoolField*) fieldWidget)->updateOption( true ) ; 
            
        }
        else
        if(   optionValue->getValue()==OPT_BOOL_FALSE){
            ((QtBoolField*) fieldWidget)->setChecked( false ) ; 
            ((QtBoolField*) fieldWidget)->updateOption( false ) ; 
        }
        else
        {
            // cout << "problem with option field value: " << optionValue->getValue() << endl ; 
        }
    }
    else
	if( type==OPT_STRING
        ||
        type==OPT_DOUBLE
        ){
        if( fieldWidget != NULL  ) { 
//            cout << "setting option-field text to: " << optionValue->getValue() << endl ; 
            ((QtOptionField*) fieldWidget)->setText( (optionValue->getValue()).c_str() ) ; 
            ((QtOptionField*) fieldWidget)->updateOption() ; 
        }
    }
    else
	if( type==OPT_INT ){
//            cout << "setting option-int num to: " << optionValue->getValue() << endl ; 
        ((QtIntField*) fieldWidget)->setValue( atoi((optionValue->getValue()).c_str()) ) ; 
        ((QtIntField*) fieldWidget)->updateOption(atoi((optionValue->getValue()).c_str())) ; 
    }
    else
    if( type==OPT_FILE_LOAD ||
        type==OPT_FILE_SAVE){
//            cout << "setting option-file to: " << optionValue->getValue() << endl ; 
        ((QtFileLoadField*) fieldWidget)->setFileName( (optionValue->getValue()).c_str() ) ; 
        ((QtFileLoadField*) fieldWidget)->updateOption() ; 
    }
    else
    if( type==LIST_FILE_LOAD){
        // cout << "the value: " << optionValue->getValue() << endl ; 
        ((QtFileLoadList*) fieldWidget)->setList( optionValue->getValue() ) ; 
        ((QtFileLoadList*) fieldWidget)->updateOption() ; 
    }
    else
    if( type==LIST_TYPE){
        ((QtTypeField*) fieldWidget)->setList( (optionValue->getValue()).c_str() ) ; 
        ((QtTypeField*) fieldWidget)->updateOption(0) ; 
    }

    return "TRUE" ; 
}


// layout in 2 columns, the first being the type name and description, and the second being the actual description of everything in the interface. 
string QtFlatRenderer::addGuiDescription(string pathToType,Type* theType,QVBoxLayout *theParentLayout,QWidget *theParentWidget) {
    string descriptionName = pathToType +NameHandler::NAME_DELIMITER+ "description"  ; 


    if(theParentWidget == NULL || theParentLayout == NULL ){
        // cout << "addGuiOption: parent is NULL" << endl ; 
        theParentWidget = this ; 
        theParentLayout = (QVBoxLayout*) this->layout() ; 
//        theParentLayout = (QVBoxLayout*) mainFrame->layout() ; 
//        theParentWidget = mainFrame ; 
//        theParentLayout = mainFrameLayout ; 
    }


    QHBoxLayout *descriptionRow = new QHBoxLayout(theParentWidget,5) ;
    descriptionRow->setMargin(5) ; 
    QLabel* typeLabel = new QLabel("description:",theParentWidget) ; 
    descriptionRow->addWidget(typeLabel) ; 
    QLabel* descriptionField = new QLabel( (theType->getDescription()).c_str() ,theParentWidget ) ; 
    descriptionRow->addWidget(descriptionField) ; 

    theParentLayout->addItem(descriptionRow) ; 

    return "" ; 

}

string QtFlatRenderer::addGuiOption(string pathToType,Option* theOption,QVBoxLayout *theParentLayout,QWidget *theParentWidget) 
{


    optionList->push_back(theOption) ; 

    string optionName = pathToType +NameHandler::NAME_DELIMITER+ (theOption->getName()) ; 
    // cout << "adding option via name: " << optionName << endl ; 

    if(theParentWidget == NULL || theParentLayout == NULL ){
        // cout << "addGuiOption: parent is NULL" << endl ; 
        theParentWidget = this ; 
        theParentLayout = (QVBoxLayout*) this->layout() ; 
//        theParentWidget = mainFrame ; 
//        theParentLayout = (QVBoxLayout*) mainFrame->layout() ; 
//        theParentLayout = mainFrameLayout ; 
    }

    QHBoxLayout *optionRow = new QHBoxLayout(theParentWidget,5) ;
    optionRow->setMargin(5) ; 
//    QLabel* optionLabel = new QLabel( (theOption->getName()).c_str(),theParentWidget) ; 
    QLabel* optionLabel = new QLabel( (theOption->getLabel()).c_str(),theParentWidget) ; 
    optionRow->addWidget(optionLabel) ; 

//    // cout << "the optionType: " << theOption->getType() << endl ; 
//    // cout << "the optionValue: " << theOption->getValue() << endl ; 
//    // cout << "the optionName: " << theOption->getName() << endl ; 
    
    if(theOption->getType()==InterfaceTypes::OPT_DOUBLE || theOption->getType()==InterfaceTypes::OPT_STRING ){
        QtOptionField *optionField = new QtOptionField( (theOption->getValue()).c_str() ,theParentWidget,optionName.c_str(),this, theOption->getType() ) ; 
        optionRow->addWidget(optionField) ; 
    }else
    if(theOption->getType()==InterfaceTypes::OPT_INT ){
        QtIntField *optionField = new QtIntField( (theOption->getValue()).c_str() ,theParentWidget,optionName.c_str(),this, theOption->getType() ) ; 
        optionRow->addWidget(optionField) ; 

    }
    else
    if(theOption->getType()==InterfaceTypes::OPT_BOOL){
        QtBoolField *optionField = new QtBoolField( (theOption->getValue()).c_str() ,theParentWidget,optionName.c_str(),this, theOption->getType() ) ; 
        optionRow->addWidget(optionField) ; 
    }
    else
    if(theOption->getType()==InterfaceTypes::OPT_FILE_LOAD){
        QtFileLoadField *optionField = new QtFileLoadField( (theOption->getName()).c_str() ,theParentWidget,optionName.c_str(),this, theOption->getType() ) ; 
        optionRow->addWidget(optionField) ; 
    }
    else
    if(theOption->getType()==InterfaceTypes::OPT_FILE_SAVE){
        QtFileLoadField *optionField = new QtFileSaveField( (theOption->getName()).c_str() ,theParentWidget,optionName.c_str(),this, theOption->getType() ) ; 
        optionRow->addWidget(optionField) ; 
    }
    else
    if(theOption->getType()==InterfaceTypes::LIST_FILE_LOAD){
        QtFileLoadList *optionField = new QtFileLoadList( (theOption->getName()).c_str() ,theParentWidget,optionName.c_str(),this, theOption->getType() ) ; 
        optionRow->addWidget(optionField) ; 
    }
    else
    if(theOption->getType()==InterfaceTypes::LIST_TYPE){
        QtTypeField *optionField = new QtTypeField(  TiListParser::parseList( theOption->getValue()) ,theParentWidget,optionName.c_str(),this, theOption->getType() ) ; 
        optionRow->addWidget(optionField) ; 
    }
    else{
        // cout << "option unaccounted for: " << theOption->getType()  << endl; 
    }


    theParentLayout->addItem(optionRow) ; 
    return "" ; 
}




string QtFlatRenderer::setGuiCommand(string pathToType,Command* optionValue) 
{
    return "" ; // /I don't think that this will do much
}


string QtFlatRenderer::addGuiCommand(string pathToType,Command* theCommand,QBoxLayout* theParentLayout,QWidget* theParentWidget) 
{
    string commandName = pathToType +NameHandler::NAME_DELIMITER+ (theCommand->getName()) ; 
    if(theParentWidget == NULL || theParentLayout == NULL ){
        theParentWidget = this ; 
        theParentLayout = (QVBoxLayout*) this->layout() ; 
//        theParentWidget = mainFrame ; 
//        theParentLayout = (QVBoxLayout*) mainFrame->layout() ; 
//        theParentLayout = mainFrameLayout ; 
    }

    QHBoxLayout* rowLayout = new QHBoxLayout(theParentWidget,5) ; 
    QtCommandButton* commandButton = new QtCommandButton( (theCommand->getName()).c_str() ,theParentWidget,commandName.c_str(),this,theCommand->getType()) ; 
    rowLayout->addWidget(commandButton) ; 
    theParentLayout->addItem(rowLayout) ; 

    return "" ; 
}


string QtFlatRenderer::setGuiType(string pathToType,Type* type)
{
	return "" ;
}


string QtFlatRenderer::addGuiType(string pathToType,Type* type)
{
    // add a group-box
    string typeName = pathToType ; 
//    // cout << "QtFlatRenderer: thetypeName: " << typeName << endl ; 
//    QVGroupBox* groupBox =  new QVGroupBox(typeName.c_str(),mainFrame,typeName.c_str()) ; 
//    QVGroupBox* groupBox =  new QVGroupBox(typeName.c_str(),mainFrame->viewport(),typeName.c_str()) ; 
//    mainFrame->addChild(groupBox) ; 
    QVGroupBox* groupBox =  new QVGroupBox(typeName.c_str(),this->viewport(),typeName.c_str()) ; 
    this->addChild(groupBox) ; 

    groupBox->setColumnLayout(2,Qt::Horizontal) ; 
    groupBox->layout()->setSpacing(6) ; 
    groupBox->layout()->setMargin(11) ; 
    
    QVBoxLayout* rowLayout = new QVBoxLayout(groupBox,5) ; 

    // add all options
    map<string,Option*> *theOptionMap = type->getOptionMap() ; 
    map<string,Option*>::iterator theOptionIterator  ; 
    // add all commands
    map<string,Command*> *theCommandMap = type->getCommandMap() ; 
    map<string,Command*>::iterator theCommandIterator  ; 

	
    addGuiDescription(pathToType,type,rowLayout,groupBox) ;

    
   // for each option . . . . add
   if(theOptionMap!=NULL && theOptionMap->size()>0){
        for( theOptionIterator=theOptionMap->begin()  ;  theOptionIterator!=theOptionMap->end()    ; theOptionIterator++){
            // cout << &theOptionIterator << endl ; 
            // cout << theOptionIterator->second << endl ; 
           addGuiOption(pathToType,theOptionIterator->second , rowLayout  ,  groupBox  ) ; 
       }
   }
  
   if(theCommandMap!=NULL && theCommandMap->size()>0 && theOptionMap!=NULL && theOptionMap->size()>0){
       // add some type of spacer, here
//       QSpacerItem *spacer = new QSpacerItem(400,60) ; 
//       rowLayout->addItem(spacer) ; 
   }
    
   // for each command . . . . add
   if(theCommandMap!=NULL && theCommandMap->size()>0){
       for( theCommandIterator=theCommandMap->begin()  ;  theCommandIterator!=theCommandMap->end()    ; theCommandIterator++){
           addGuiCommand(pathToType,theCommandIterator->second , rowLayout  ,  groupBox  ) ; 
       }
   }


	return "" ;
}

string QtFlatRenderer::setGuiInterface(string pathToType,Interface* type)
{
	return "" ;
}

string QtFlatRenderer::addGuiInterface(string pathToType,Interface* type)
{
	return "" ;
}


string QtFlatRenderer::clearGui()  
{
    QObjectList* childList = (QObjectList*) this->children() ; 
    if(childList!=NULL){
        childList->setAutoDelete(true) ; 
        childList->clear() ; 
    }
    return "" ; 
}

