#include <iostream>
using std::cout ; 
using std::endl ; 


#include "TestAutoOption.hpp"

int main(int argc,char** argv){
	TestAutoOption test(argc,argv) ; 
	test.run() ; 
	cout << test.getOptionXML() << endl ; 
}



// -*- C++ -*-

// (C) 2006 by Nathan Dunn, <ndunn@mac.com>


