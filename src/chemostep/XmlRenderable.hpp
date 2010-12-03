#ifndef XMLRENDERABLE_HPP_
#  define XMLRENDERABLE_HPP_

#include <iostream>
using std::ostream ; 

#include <string>
using std::string ; 

/** Description:  Class XmlRenderable is the interface/abstract class that most other classes get the "toXML" method from.
 *
 */
class XmlRenderable {

public:
    virtual void toXML(ostream *s) = 0 ; 
    static void setNumTabs(int newNumTabs) ; 
    static int getNumTabs() ; 
    static void decrementTabCount() ; 
    ostream& operator<<(ostream &s) ; 
    virtual void addSpacer(ostream *s,int postCounterAdjust=0) ; 

protected:
    static int mNumTabs ; 
    static string mSpacerValue  ; 

} ;

#endif /* ifndef XMLRENDERABLE_H */

