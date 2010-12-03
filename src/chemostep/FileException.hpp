/*
 * $Id: FileException.hpp,v 1.1.1.1 2003/10/24 19:59:27 ndunn Exp $
 */
#ifndef FILEERROR_HPP_
#  define FILEERROR_HPP_

class FileException {

public:
    FileException(const char* errorString) ; 
    const char* getException() ; 

protected:
    const char* errorString ; 

} ;

#endif /* ifndef FILEERROR_H */
// -*- C++ -*-
// FILE: "/Users/nathandunn/cvs/auto2/chemostepAUTO/source/FileError.hpp"
// LAST MODIFICATION: "Wed, 15 Oct 2003 18:53:30 -0700 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: FileException.hpp,v 1.1.1.1 2003/10/24 19:59:27 ndunn Exp $

