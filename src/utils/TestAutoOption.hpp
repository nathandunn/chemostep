#ifndef TESTAUTOOPTION_HPP_
#  define TESTAUTOOPTION_HPP_

#include <AutoOptionList.hpp>

/**  This class tests that the option creation portions work, and works with maintestautooption.cpp.
 *
 */
class TestAutoOption : public AutoOptionList{

public:
  TestAutoOption(int argc, char *argv[]);
	virtual void run() ; 

protected:
	virtual void initOptions() ; 
	int mInt1, mInt2 ; 
	double mDouble1, mDouble2 ; 
	char mChar1, mChar2 ; 
	string mOption1, mOption2 ; 
	bool mFlag1, mFlag2 ; 

} ;

#endif /* ifndef TESTAUTOOPTION_H */
// -*- C++ -*-

// (C) 2006 by Nathan Dunn, <ndunn@mac.com>


