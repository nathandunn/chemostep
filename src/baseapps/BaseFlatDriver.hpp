/*
 * $Id$
 */
#ifndef BASEFLATDRIVER_HPP_
#  define BASEFLATDRIVER_HPP_

#include <TransmitterApp.hpp>

class AppInterfaceXmlEngine ; 
class Renderer ; 
class QWidget ; 
class AppInterface ; 
/** This is the base driver class to be used with TiFlatBaseApp.
 *
 */
class BaseFlatDriver : public TransmitterApp {

public:
    BaseFlatDriver(AppInterface* newApp=NULL) ; 
    virtual string transmitXml(string xmlMessage) ; 
    virtual void setRenderer(Renderer* newRenderer) ; 
    virtual QWidget* initGui() ; 
    virtual void setApp(AppInterface* newApp) ; 
    virtual void setXmlEngine(AppInterfaceXmlEngine* newXmlEngine) ; 
    virtual Renderer* getRenderer()  ; 

    string getBaseAppName() {
        return(mBaseAppName);
    }
    void setBaseAppName(string _mBaseAppName) {
        mBaseAppName = _mBaseAppName;
        return;
    }

    string getPrefName() {
        return(mPrefName);
    }
    void setPrefName(string _mPrefName) {
        mPrefName = _mPrefName;
        return;
    }

    string getPrefUrl() {
        return(mPrefUrl);
    }
    void setPrefUrl(string _mPrefUrl) {
        mPrefUrl = _mPrefUrl;
        return;
    }




protected:
    AppInterface* mApp ; 
    Renderer* mRenderer ; 
    AppInterfaceXmlEngine* mXmlRenderer ; 

	// protected apps
    string mBaseAppName ; 
    string mPrefName ; 
    string mPrefUrl; 

} ;

#endif /* ifndef BASEFLATDRIVER_H */
// -*- C++ -*-
// FILE: "/Users/nathandunn/tla/auto3--dev--1.3.2--patch-8/src/baseapps/BaseFlatDriver.hpp"
// LAST MODIFICATION: "Wed, 17 Mar 2004 18:04:34 -0800 (nathandunn)"
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

