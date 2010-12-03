// -*- C++ -*-


#ifndef QTFLATRENDERER_H_
#define QTFLATRENDERER_H_


#include <qmainwindow.h>
#include <qscrollview.h>


#include "FlatRenderer.hpp"  
#include "InterfaceTypes.hpp"  

class TransmitterApp ; 
class QVBoxLayout ; 
class QFrame ; 
class QVBox ; 
class QScrollView ; 
#ifdef POWER64LINUX
class QtPower4Settings ; 
#else
class QSettings; 
#endif


/**
 *  An application renderer which supports set Commands and Options 
 *  only.  The application will not allow interfaces to be swicthed
 *  once the application has been started. 
 *
 */

class QtFlatRenderer :  public FlatRenderer , public QScrollView, public InterfaceTypes {


public:
    QtFlatRenderer(TransmitterApp* newTransmitterApp=NULL,AppParser *appParser=NULL) ; 

    /*
     *  Methods to implement from FlatRenderer
     */

    /*
     *  Methods to implement from Renderer
     */

    // pull GUI to MAP
    virtual string getOptionFromGui(Option* optionValue) ; 
    virtual string updateOptionsFromGui() ; 

    // push GUI to file
    virtual bool saveOptionPref(string key,string value,string type) ;  
    virtual bool loadOptionPref(Option* theOption) ;  
    virtual bool savePreferences() ;  
    virtual bool loadPreferences() ;  



    // push to GUI
    virtual string setGuiOption(Option* optionValue) ; 
    virtual string addGuiOption(string pathToType,Option* optionValue,QVBoxLayout* theParentLayout=NULL ,QWidget *theParentWidget=NULL) ; 
    virtual string addGuiDescription(string pathToType,Type* theType,QVBoxLayout* theParentLayout=NULL ,QWidget *theParentWidget=NULL) ; 
    virtual string setGuiCommand(string pathToType,Command* optionValue) ; 
    virtual string addGuiCommand(string pathToType,Command* optionValue,QBoxLayout* theParentLayout=NULL,QWidget *theParentWidget=NULL) ; 
    virtual string setGuiType(string pathToType,Type* type) ; 
    virtual string addGuiType(string pathToType,Type* type) ; 
    virtual string setGuiInterface(string pathToType,Interface* type) ; 
    virtual string addGuiInterface(string pathToType,Interface* type) ; 
    virtual int message(string caption,string text) ; 

	// update GUI
    virtual string clearGui()  ; 


protected:
    QScrollView *mainFrame ; 
    QVBox *mainLayout  ; 
    #ifdef POWER64LINUX
    QtPower4Settings* mPrefs ; 
    #else
    QSettings* mPrefs ; 
    #endif

} ; 



#endif


