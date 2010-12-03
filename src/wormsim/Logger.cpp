
#include <iostream>
using std::cout ; 
using std::endl ; 
using std::ios ; 

#include <string>
using std::string ; 

#include <fstream>
using std::ofstream ; 

#include "Logger.hpp" 

/*  ***********************************************************************************
    Default Constructor() */
   
//! No body.
/*  *********************************************************************************** */
Logger::Logger(){
}

/*  ***********************************************************************************
    setFilename() */
   
//! Closes any pre-existing output stream, then opens a new one..
/*  *********************************************************************************** */
void Logger::setFileName(string newFileName){
    if(outStream != 0){
	outStream.close() ; 
    }
    
    if(newFileName != fileName) {
	fileName = newFileName ; 
	outStream.open(fileName.c_str(),ios::out) ;  
    }
}


/*  ***********************************************************************************
    getFileName() */
/*  *********************************************************************************** */
string Logger::getFileName(){
    return fileName ; 
}


/*  ***********************************************************************************
    getLogger() */
   
//! Creates and returns the log file if necessary..
/*  *********************************************************************************** */
Logger *Logger::getLogger(string newFileName){
    // if the names are the same, do nothing

    if(outStream == NULL){
	cout << "the output stream is NULL" << endl ; 
	outStream.open(newFileName.c_str(),ios::out) ; 
    }

    // cout << "new: '" << newFileName << "' old: '" << fileName << "'" <<  endl ;
    
    if(newFileName == fileName) {
        // cout << "names are the same " << endl ; 
        if(outStream.is_open()){           
            // cout << "was open, doing nothing" << endl ;
	    
        }else{
            // cout << "was closed, opening up that biatch" << endl ; 
            outStream.open(newFileName.c_str(),ios::out) ; 
        }
	
    }else{
        // cout << "names are different " << endl ;
	
        if(outStream.is_open()){
            // cout << "was open, closing;" << endl ; 
            outStream.close() ;
	    
        }else{
            // cout << "was closed, anyway" << endl ; 
        }
	
        outStream.open(newFileName.c_str(),ios::out) ; 
    }
    
    fileName = newFileName ; 
    
    return getLogger() ; 
}


/*  ***********************************************************************************
    getLogger() */
   
//! Creates the "instance" of the logger (if it hasn't alreadyy been created) and returns it.
/*  *********************************************************************************** */
Logger *Logger::getLogger()  {    
    if(aLogger == NULL){
        // cout << "logger is Null, making new one" << endl ; 
	aLogger = new Logger() ; 
    }
    
    return aLogger ; 
}

 

/*  ***********************************************************************************
    log() */
   
//! Adds the passed string to the log file.
/*  *********************************************************************************** */
void Logger::log(string logString){
    if(outStream==NULL){
	outStream.open(fileName.c_str(),ios::out) ; 
    }

    outStream <<  logString << endl ; 
}

Logger *Logger::aLogger  = 0 ; 
string Logger::fileName = "templog.txt" ; 
ofstream Logger::outStream      ; 




