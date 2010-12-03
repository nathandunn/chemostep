## -*- automake -*-
## FILE: "/Users/nathandunn/tla/auto3--dev--1.4.5--base-0/src/tinyxml/Makefile.am"
## LAST MODIFICATION: "Fri, 30 Jul 2004 13:41:24 -0700 (nathandunn)"
## (C) 2003 by Nathan Dunn, <ndunn@mac.com>
## $Id: Makefile.am,v 1.2 2003/10/24 20:46:57 ndunn Exp $

lib_LIBRARIES = libtinyxml.a # mapper # qtoption qttree #htmloption htmltree


# bin_PROGRAMS = treeapp  # mapper # qtoption qttree #htmloption htmltree
interface_headers= tinystr.h tinyxml.h 
interface_source=  tinystr.cpp tinyxml.cpp tinyxmlerror.cpp tinyxmlparser.cpp
interface = $(interface_headers) $(interface_source) 
#--------------------------
libtinyxml_aincludedir=../../include
libdir=../..//lib
libtinyxml_ainclude_HEADERS=$(interface_headers) 
libtinyxml_a_SOURCES= $(interface) 


INCLUDES=-D@platform@ ${HOST_OPTION} -DTIXML_USE_STL 


