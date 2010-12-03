#ifndef XMLRENDERER_HPP_
#  define XMLRENDERER_HPP_

#include <stdlib.h>
#include <string>
using namespace std;
using std::string ;

#include <iostream>

#include <fstream>
using std::ofstream ;

/**
XmlRenderer is the base class for any XML
output from an application. Its implementation
is definitely not complete. It should include
any method that will be common to any more
specific renderer. 
*/

class XmlRenderer {
  
public:
  XmlRenderer() ; 
  // ~XmlRenderer() ; 

  virtual void openFile(char fileName[]);
  virtual void closeFile();

private:
  ofstream toXMLFile ;
};

#endif /* ifndef XMLRENDERER_H */
// -*- C++ -*-

