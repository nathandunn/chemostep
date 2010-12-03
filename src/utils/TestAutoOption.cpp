#include <iostream>
using std::cout ; 
using std::endl ; 

#include "AutoOptionList.hpp"


#include "TestAutoOption.hpp"

TestAutoOption::TestAutoOption(int argc, char *argv[]): AutoOptionList(argc,argv)
{
	initOptions() ; 
	parseOption() ; // for every input map to variables
	standardOptions() ; 
}

void TestAutoOption::run() 
{
	 cout << "running app with " ; 
	 cout << "mInt1[" << mInt1 << "] " ; 
	 cout << "mInt2[" << mInt2 << "] " ; 
	 cout << "mDouble1[" << mDouble1 << "] " ; 
	 cout << "mDouble2[" << mDouble2<< "] " ; 
	 cout << "mOption1[" << mOption1 << "] " ; 
	 cout << "mOption2[" << mOption2<< "] " ; 
	 cout << "mFlag1[" << mFlag1 << "] " ; 
	 cout << "mFlag2[" << mFlag2<< "] " ; 
	 cout << "mChar1[" << mChar1 << "] " ; 
	 cout << "mChar2[" << mChar2<< "] " ; 
	 cout << endl ; 
}


void TestAutoOption::initOptions() 
{
	setBinary("testautooption") ; 
	addFlag(&mFlag1,"flag1","Test flag variable 1",false,"A longer description of the flag variable 1","flag options") ; 
	addFlag(&mFlag2,"flag2","Test flag variable 2",false,"A longer description of the flag variable 2","flag options") ; 
	addInt(&mInt1,"int1","Test integer variable 1") ; 
	addInt(&mInt2,"int2","Test integer variable 2") ; 
	addDouble(&mDouble1,"double1","Test double variable 1",-1.0, " ", "int options") ; 
	addDouble(&mDouble2,"double2","Test double variable 2",-1.0, " " , "int options") ; 
	addOption(&mOption1,"option1","Test option variable 1") ; 
	addOption(&mOption2,"option2","Test option variable 2") ; 
	addChar(&mChar1,"char1","Test char variable 1") ; 
	addChar(&mChar2,"char2","Test char variable 2") ; 

 
}



// -*- C++ -*-

// (C) 2006 by Nathan Dunn, <ndunn@mac.com>


