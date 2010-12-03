## -*- automake -*-
## FILE: "/Users/nathandunn/cvs/auto3/src/testclasses/Makefile.am"
## LAST MODIFICATION: "Fri, 24 Oct 2003 14:13:34 -0700 (nathandunn)"
## (C) 2003 by Nathan Dunn, <ndunn@mac.com>
## $Id: Makefile.am,v 1.3 2003/10/24 21:15:41 ndunn Exp $

lib_LIBRARIES = libtestclasses.a 

interface_headers= TestFeeder.hpp TestFileFeeder.hpp TestRandomFeeder.hpp TestNN.hpp TestAnnealer.hpp AnnealerObject.hpp 
interface_source=  TestFeeder.cpp TestFileFeeder.cpp TestRandomFeeder.cpp TestNN.cpp TestAnnealer.cpp 
interface = $(interface_headers) $(interface_source) 
#--------------------------
libtestclasses_aincludedir=../autogui
libtestclasses_ainclude_HEADERS=$(interface_headers)  
libtestclasses_a_SOURCES= $(interface) 
# libdir=../autogui

if MACOSX
  HOST_OPTION = 
endif


MISC_OPT = -Weffc++

INCLUDES =  -D@platform@ ${HOST_OPTION} -I../autogui
	
%.class: %.java
	`which jikes` $< -o $@

