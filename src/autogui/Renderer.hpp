// -*- C++ -*-

#ifndef RENDERER_hpp_
#define RENDERER_hpp_

#include <string>
using std::string ; 


#include <vector>
using std::vector ; 

class CommandActor ; 
class Option; 
class Command; 
class Interface; 
class Type; 
class TransmitterApp ; 
class ClickableObject ; 
class Option ; 




///  This is the base-class that handles all of the maps that are rendered, similar
///  to AppInterface, so instead of tree, will need to have access to Option,
///  Type, Interface, and Command.  
///
///
///  - We look at this as being three interfaces:  "GUI (client)", "client map", "server (ether)". 
///  - This class has most of the client map methods.
///  - Qt..... classes have the GUI(client)  methods.  
///  - server(ether) methods can be overloaded, or handled explicitly by another class, though it will
///    be passing strings to a method explicitly now.
///
///   \todo Implement file save and open.
/// 

class Option ; 

class Renderer{

public:
    Renderer(TransmitterApp *transmitterApp=NULL) ; 
    // APP push to MAP
    virtual string loadAppToMap(string xmlString) ; 

    // MAP push to GUI
    virtual string renderAppToGui(string xmlString="") = 0 ;  // may also render the previously loaded app


    // GUI push to MAP (and to APP)
    virtual string doCommandButton(CommandActor *commandActor) ; 
    virtual string optionSetInGui(Option* optionSet,string pathToType) ; 

    // pull GUI to MAP
    virtual string getOptionFromGui(Option* optionName)=0 ; 
    virtual string updateOptionsFromGui()=0 ; 

    // push GUI to file
    virtual void setPreferenceRoot(string newRoot) ; 
    virtual string getPreferenceRoot() ; 
    virtual void setPreferenceURL(string newURL) ; 
    virtual string getPreferenceURL() ; 
    virtual bool savePreferences() ; 
    virtual bool loadPreferences() ; 
    virtual bool saveOptionPref(string key,string value,string type)=0 ;  
    virtual bool loadOptionPref(Option* theOption)=0 ;  
//    virtual bool saveTypePref(string key,string value,string type)=0 ;  
//    virtual bool loadTypePref(string key,string value,string type)=0 ;  

    // push to GUI
    virtual string setGuiOption(Option* optionValue)=0 ; 
//    virtual string addGuiOption(string pathToType,Option* optionValue)=0 ; 
    virtual string setGuiCommand(string pathToType,Command* optionValue)=0 ; 
//    virtual string addGuiCommand(string pathToType,Command* optionValue)=0 ; 
    virtual string setGuiType(string pathToType,Type* type)=0 ; 
    virtual string addGuiType(string pathToType,Type* type)=0 ; 
    virtual string setGuiInterface(string pathToType,Interface* type)=0 ; 
    virtual string addGuiInterface(string pathToType,Interface* type)=0 ; 
    virtual int message(string caption,string text)=0 ; 
    
    // push to MAP
    virtual string setMapOption(string pathToType,Option* optionValue) ; 
    virtual string addMapOption(string pathToType,Option* optionValue) ; 
    virtual string setMapCommand(string pathToType,Command* optionValue) ; 
    virtual string addMapCommand(string pathToType,Command* optionValue) ; 


    // pull from MAP
    virtual Option* getMapOption(string pathToType,string optionName) ; 

	// update GUI
    virtual string clearGui() = 0 ; 

    // push to APP
    virtual string transmitXmlCommand(string xmlCommands) ; 

    // pull MAP push to APP 
    virtual string transmitXmlOptions(string xmlCommands) ; 

    // push to APP 
    virtual string transmitXml(string xmlCommands,TransmitterApp* transmitterApp= NULL ) ; 
    virtual string setOptionFromGui(CommandActor* theActor,string theValue) ;


    void setTransmitterApp(TransmitterApp* newTransmitterApp){
        transmitterApp = newTransmitterApp ; 
    }

    TransmitterApp* getTransmitterApp(){
        return transmitterApp ; 
    }

    unsigned int getCommandId() ;

protected:
    TransmitterApp *transmitterApp ; 
    unsigned int theCommandId ; 
    string xmlMap  ; 
    string mPreferenceRoot ; 
    string mPrefURL ; 
    vector<Option*>* optionList ; 

} ;



#endif


