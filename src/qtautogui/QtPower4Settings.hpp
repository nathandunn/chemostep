
#ifndef QTPOWER4SETTINGS_HPP_
#  define QTPOWER4SETTINGS_HPP_

#include <fstream>
using std::ifstream ; 
using std::ios ; 

#include <qsettings.h>

class QtPower4Settings : public QSettings {

public:
    QtPower4Settings() ; 
    ~QtPower4Settings() ; 
    virtual QString readEntry(const QString & key , const QString & def = QString::null , bool * ok = 0 ) ; 
    virtual int readNumEntry(const QString & key , int def =0, bool * ok = 0 ) ; 
    virtual double readDoubleEntry(const QString & key , double def =0, bool * ok = 0 ) ; 
    virtual bool readBoolEntry(const QString & key , bool def =0, bool * ok = 0 ) ; 

protected:
    virtual QString findKey(const QString & key) ; 
    virtual QString getKey(QString lineValue) ; 
    virtual QString getName(QString lineValue) ; 
    QString mHomeFile ; 
    ifstream *mPrefStream ; 

} ;

#endif /* ifndef QTPOWER4SETTINGS_H */
// -*- C++ -*-

// (C) 2005 by Nathan Dunn, <ndunn@mac.com>


