#ifndef XMLFILETOKENIZER_HPP_
#  define XMLFILETOKENIZER_HPP_

#include <vector>
using std::vector ; 

#include <string>
using std::string ; 

/**  This class generates file-names as vector<string> from an input file, a number of files to generate, and any additional token.  If the token is not found, it will simply append to the pre-append phase. 
 *
 */
class XmlFileTokenizer {

public:
    static vector<string>* createFileNames( string initFile, int numFiles, char token='%') ; 

protected:
    static vector<string>* createUsingToken(string initFile,int numFiles,char token) ; 
    static vector<string>* createUsingFile(string initFile,int numFiles) ; 

} ;

#endif /* ifndef XMLFILETOKENIZER_H */
// -*- C++ -*-
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

