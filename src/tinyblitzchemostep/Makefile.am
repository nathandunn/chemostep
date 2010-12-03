## -*- automake -*-
## FILE: "/mnt/sanfs/home/users/ndunn/svn/chemotrunk/src/tinyblitzchemostep/Makefile.am"
## LAST MODIFICATION: "Thu, 27 Jan 2005 15:23:51 -0800 (ndunn)"
## (C) 2003 by Nathan Dunn, <ndunn@mac.com>
## $Id: Makefile.am,v 1.2 2004/01/13 20:43:36 ndunn Exp $

lib_LIBRARIES = libtinyblitzchemostep.a # mapper # qtoption qttree #htmloption htmltree


interface_headers= TinyBzNetParser.hpp 
interface_source= TinyBzNetParser.cpp 
interface = $(interface_headers) $(interface_source) 
#--------------------------


#--------------------------
# libtinyblitzchemostep_ainclude_HEADERS=$(interface_headers) 
libtinyblitzchemostep_a_SOURCES= $(interface) 

if MACOSX
  HOST_OPTION = 
#  X11_OPTION = 
else
#  X11_OPTION = -I/usr/X11R6/include
#  QTLIBFLAGS =  -L${QTDIR}/lib 
endif


MISC_OPT = -Weffc++

INCLUDES=-D@platform@ ${HOST_OPTION} -DTIXML_USE_STL -I../tinyxml -I../chemostep -I../blitzchemostep -I../autogui -I../utils -I${BZDIR}  ${MPI_OPTION} 
# INCLUDES=-I${AUTOGUI}/source -I${TINYXML}/source -D@platform@ ${HOST_OPTION} -DTIXML_USE_STL 

%.moc.cpp: %.h
	$(MOC) $< -o $@ 
	
%.class: %.java
	`which jikes` $< -o $@


