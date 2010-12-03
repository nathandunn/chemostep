/**
 */
#include <vector>
using std::vector ; 

#include <iostream>
using std::cout ; 
using std::endl ; 

#include <fstream>
using std::ifstream;
using std::ofstream;

#include <iostream>
using std::ios ;

#include <math.h>



#include "FileFeeder.hpp"

FileFeeder::FileFeeder() : Feeder() , INPUT_BUFF(30)  ,mMinValue(-DBL_MAX),mMaxValue(DBL_MAX),mFailValue(-DBL_MAX)
{
}

FileFeeder::FileFeeder(string newFile,double newMinValue,double newMaxValue,double newFailValue) : Feeder() , INPUT_BUFF(30),mMinValue(newMinValue),mMaxValue(newMaxValue),mFailValue(newFailValue)
{
    setFile(newFile) ; 
}


double FileFeeder::getNextPoint(int pointAt) {

    if(fileData->size()<pointCounter){
        throw "data counter exceeds data size" ; 
    }
    vector<double>* timePoint = (*fileData)[pointCounter] ; 
    if(timePoint->size()<pointAt){
        throw "point does not exist" ; 
    }

    pointCounter++ ; 
    timeCounter = timeCounter + deltaT  ; 

    double returnValue = ((   ( ( *timePoint )[pointAt])  *scale) + offset)  ; 
//    cout << "returnValue[" << returnValue << "] mMinValue[" << mMinValue << "] mMaxValue[" << mMaxValue << "] mFailValue[" << mFailValue << "]" << endl;  
    if(returnValue >= mMinValue && returnValue <= mMaxValue){
        return returnValue ; 
    }
    else{
        cout << "returning FAIL VALUE" << endl ; 
        return mFailValue ; 
    }
}


int FileFeeder::getNumPoints() 
{
    if(fileData!=NULL){
        return fileData->size() ; 
    }
    else 
        throw "fileData==NULL" ; 
}

bool FileFeeder::isTimePointValid() 
{
     float div = timeCounter/deltaT ; // for some stupid reason, this HAS to be a float, otherwise it performs floor wrong
     double floordiv = floor(div) ; 
     double ceildiv = ceil(div) ; 
     return (floordiv==ceildiv) ;
}



bool FileFeeder::hasMorePoints() 
{
    if(fileData==NULL) throw "fileData is NULL" ; 
    return (pointCounter< (fileData->size())) ; 
}

string FileFeeder::getFileName() 
{
    return mFileName ; 
}

bool FileFeeder::loadSigFile(string sigFileName) 
{
    const char* cStimFile = sigFileName.c_str() ; 
    ifstream inFile  ; 
    try{
        inFile.open(cStimFile, ios::in) ; 
    }
    catch(const char * error){
        throw "failed to open sig file" + sigFileName + "  error " + error ; 
    }
    catch(...){
        throw "failed to open sig: " + sigFileName ; 
    }

    if(!inFile)
    {
       throw "failed to read file: " + sigFileName ;
    }
  int charCount = 0 ; 
  char *buffer = new char[INPUT_BUFF] ; 
  const char linedelimeter = '\n' ;  

  if(fileData==NULL){
      throw "fileData is NULL, could not set sigData" ; 
  }
  if(sigData==NULL){
      sigData = new vector<double>(fileData->size()) ; 
  }

  try{

      sigData->clear() ; 
      while( inFile.getline(buffer,INPUT_BUFF,linedelimeter) ){
          // just read a single line for now
//          cout << "adding to file: " << atof(buffer) << endl ; 
          sigData->push_back(atof(buffer)) ; 
      }
  }
  catch(const char *error){
      cout << "error reading sigdata file: " << error << endl ; 
  }
  catch(...){
      cout << "unspecified reading sigdata file: " << sigFileName << endl ; 
  }

    try{
        inFile.close() ; 
    }
    catch(const char * error){
        throw "failed to close file" + sigFileName + "  error " + error ; 
    }
    catch(...){
        throw "failed to close: " + sigFileName ; 
    }

    return true ; 
}


bool FileFeeder::setFile(string newFileName) 
{
    mFileName = newFileName ; 
    const char* cStimFile = mFileName.c_str() ; 
    ifstream inFile  ; 
    try{
        inFile.open(cStimFile, ios::in) ; 
    }
    catch(const char * error){
        throw "failed to open file" + mFileName + "  error " + error ; 
    }
    catch(...){
        throw "failed to open: " + mFileName ; 
    }

    if(!inFile)
    {
       throw "failed to read file: " + mFileName ;
    }
  int charCount = 0 ; 
  char *buffer = new char[INPUT_BUFF] ; 
  const char linedelimeter = '\n' ;  

  if(fileData==NULL){
      fileData = new vector<vector<double>*>() ; 
  }

  fileData->clear() ; 



  try{

      while( inFile.getline(buffer,INPUT_BUFF,linedelimeter) ){
          // just read a single line for now
          vector<double>* lineVector = new vector<double>() ; 
          lineVector->push_back(atof(buffer)) ; 
          fileData->push_back(lineVector) ; 
      }
      sigData = new vector<double>(fileData->size()) ; 
      calculateSigPoints() ;
  }
  catch(const char *error){
      cout << "error reading file: " << error << endl ; 
  }
  catch(...){
      cout << "unspecified reading file: " << mFileName << endl ; 
  }

    try{
        inFile.close() ; 
    }
    catch(const char * error){
        throw "failed to close file" + mFileName + "  error " + error ; 
    }
    catch(...){
        throw "failed to close: " + mFileName ; 
    }


    return true ; 
}


//vector<double>* FileFeeder::getNextTimeSteps(double newTimeStep) 
//{
//    // return current timeStep (assuming that it has been advanced)
//    if(fileData->size()<pointCounter){
//        throw "data counter exceeds data size" ; 
//    }
//    vector<double>* timePoint = (*fileData)[pointCounter] ; 
//
//    timeCounter = timeCounter + newTimeStep ; 
//    pointCounter =  ((int) (timeCounter/deltaT)) ; 
//
//    return timePoint ; 
//}


// returns the previous value, it looks like
double FileFeeder::getNextTimeStep(double newTimeStep, int pointAt) 
{
    // return current timeStep (assuming that it has been advanced)
    if(fileData->size()<pointCounter){
        throw "data counter exceeds data size" ; 
    }
    vector<double>* timePoint = (*fileData)[pointCounter] ; 
    if(timePoint->size()<pointAt){
        throw "point does not exist" ; 
    }

    timeCounter = timeCounter + newTimeStep ; 
    pointCounter =  ((int) (timeCounter/deltaT)) ; 

//    return (*timePoint)[pointAt] ; 
//    return ((   ( ( *timePoint )[pointAt])  *scale) + offset)  ; 
    double returnValue = ((   ( ( *timePoint )[pointAt])  *scale) + offset)  ; 
//    cout << "returnValue[" << returnValue << "] mMinValue[" << mMinValue << "] mMaxValue[" << mMaxValue << "] mFailValue[" << mFailValue << "]" << endl;  
    if(returnValue >= mMinValue && returnValue <= mMaxValue){
        return returnValue ; 
    }
    else{
        return mFailValue  ; 
    }
}

const string FileFeeder::FEEDER_NAME = "FILE_FEEDER" ; 



/* Function int main(int argc, char **argv) {{{ */
//int main(int argc, char **argv)
//{


//    return 0;
//} /* }}} */


/* Modeline for ViM {{{
 * vim:set ts=4:
 * vim600:fdm=marker fdl=0 fdc=3:
 * }}} */

// -*- C++ -*-

