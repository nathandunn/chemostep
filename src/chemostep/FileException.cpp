/*
 * $Id: FileException.cpp,v 1.1.1.1 2003/10/24 19:59:27 ndunn Exp $
 */

#include <iostream>
using std::cout ; 
using std::endl ; 

#include "FileException.hpp"

FileException::FileException(const char* newErrorString) 
{
    errorString = newErrorString ;
}

const char* FileException::getException() 
{
    return errorString ; 
}



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
// FILE: "/Users/nathandunn/cvs/auto2/chemostepAUTO/source/FileError.cpp"
// LAST MODIFICATION: "Wed, 15 Oct 2003 18:53:49 -0700 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: FileException.cpp,v 1.1.1.1 2003/10/24 19:59:27 ndunn Exp $

