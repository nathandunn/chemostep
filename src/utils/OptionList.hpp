
/*--------------------------------------------------------------*/
/*  Copyright (c) 2000 by the University of Oregon.		*/
/*  See the COPYRIGHT file in this directory for permission	*/
/*  to use and distribute this software.			*/
/*--------------------------------------------------------------*/

// $Id: OptionList.hpp,v 1.1.1.1 2003/01/03 23:11:59 ndunn Exp $

// OptionList -- organize and access command line options		

// John Conery								
// University of Oregon							
// May 2000								
									
// An OptionList object is initialized with an argument count and array	
// of strings -- typically the values of argc and argv passed to main().
// Call one of the "get" methods to scan the argument strings and return
// the value of an argument -- the argument name and it value string(s)	
// will be removed from the list.  Call the contents() method to return	
// a list of strings currently in the list.				
//									
// Notes/restrictions:							
// * this version does not support Posix or GNU style argument lines;	
//   option names must start with a single dash				
// * all options are specified separately -- the old Unix style of	
//   specifying arguments in a single "word" is not supported		
// * no value can start with a dash, e.g. in "cmnd -foo -start" the	
//   string "-start" is not returned as the value of the option "-foo".	
// * this version does no error checking on numbers -- whatever is	
//   returned by "atoi" or "atod" is used as the argument value.	
//									
// To do: 								
// * check numeric strings for illegal chars				
// * "parseArgs" interface?						
// * Posix/GNU style options (passed as optional params to constructor)	
// * error handler?  optional argument, invoked on range/format error?	
// * list of options (i.e. all values up to next argument name)		
// * "no" on flags, e.g. -nofoo returns false for "-foo"		

#ifndef _OptionList_h_
#define _OptionList_h_

#include <vector>
using std::vector ;

#include <string>
using std::string ; 

#include <list>
using std::list ; 
#include <float.h>




class OptionList {
public:
  OptionList(int argc, char *argv[]);
  ~OptionList();
   vector<string> getTokenizedStringList(const string &name, char token);
   vector<string> createList(const string input, const vector<int> numList,char token);
   vector<int> getIntList(const string &name, const string iDefault);
  int getInt(const string &name, int idefault = 0, int min = -INT_MAX, int max = INT_MAX);
  double getDouble(const string &name, double ddefault = 0.0, double min = -DBL_MAX, double max = DBL_MAX);
  bool getFlag(const string &name, bool bdefault = false);
  string getOption(const string &name, const string &sdefault = "");
  char getChar(const string &name, const char &sdefault = '0');
  void print() const;
  list<string> &contents();
  string next();
  bool empty() const;
private:
  list<string> theList;
};


#endif
