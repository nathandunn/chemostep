

#ifndef NOTE_HPP_
#  define NOTE_HPP_

#include <string>
using std::string ; 

#include <map>
using std::map ; 

#include <sstream>
using std::ostringstream ; 

#include <XmlRenderable.hpp>


class Note : public map<string,string> , public XmlRenderable{

public:
    Note() ; 
    Note(Note* newNote) ; 
    virtual string* getText() ; 
    virtual string toXML(int numTabs = 0 ) ; 
    virtual void clearNotes() ; 
    virtual void addNote(string name,string value) ; 
    virtual void setNote(string name,string value) ;  /// Overwrites the note if it exists
    virtual void setNote(string name,double value) ;  /// Overwrites the note if it exists
    virtual string* getNote(string name) ; 
    Note& operator=(Note &rhsNote); 
    virtual void toXML(ostream *s) ; 

protected:
    map<string,string>::iterator mHashIter ; 
    ostringstream *mStringStream ; 
    int mSpaceCounter ; 


} ;

#endif /* ifndef NOTE_H */
// -*- C++ -*-
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

