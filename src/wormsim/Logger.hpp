
#ifndef _Logger_h_
#define _Logger_h_

#include <fstream>
using std::ofstream ; 

#include <string>
using std::string ; 

/**
*
*  This is the log file that provides a universal access point for any 
*  thing that needs to be logged.  The log function is virtual and can
*  be over-written by future versions of the logger.  
*
*/


class Logger{

public:
	static Logger* getLogger() ; 	
	static Logger* getLogger(string newFileName) ; 	
	static void setFileName(string newFileName) ; 
	static string getFileName() ; 
 	virtual void log(string aString) ;  
	static ofstream outStream ; 
	
private:
	Logger() ; 	

	static Logger *aLogger ; 	
	static string fileName ; 	
	
} ;

#endif

