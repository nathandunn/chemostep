## -*- automake -*-
## FILE: "/Users/nathandunn/svn/chemostep-nathan/src/gnuplot_i/Makefile.am"
## LAST MODIFICATION: "Wed, 17 Aug 2005 14:55:42 -0700 (nathandunn)"
## (C) 2003 by Nathan Dunn, <ndunn@mac.com>
## $Id: Makefile.am,v 1.2 2004/01/13 20:43:36 ndunn Exp $

lib_LIBRARIES = libgnuploti.a # mapper # qtoption qttree #htmloption htmltree
bin_PROGRAMS =   example # anim 

if MACOSX
  HOST_OPTION = 
endif


INCLUDES=-D@platform@ ${HOST_OPTION} 



#--------------------------
interface_headers= gnuplot_i.hpp 
interface_source=  gnuplot_i.cpp 
interface = $(interface_headers) $(interface_source) 
# libdir=../../lib
libgnuploti_aincludedir=${prefix}/include/gnuplot
libgnuploti_ainclude_HEADERS= $(interface_headers) 
libgnuploti_a_SOURCES= $(interface) 
#--------------------------

myexample_headers= $(interface_headers) 
myexample_source=  $(interface_source) example.cpp
myexample = $(myexample_headers) $(myexample_source) 
example_SOURCES= $(myexample) 
example_LDFLAGS =   -L.
example_LDADD =   -lgnuploti -lstdc++

#sinepng_headers= ${interface_headers) 
#sinepng_source=  ${interface_source) sinepng.cpp
#sinepng = $(sinepng_headers) $(sinepng_source) 
#sinepng_LDFLAGS =   -L.
#sinepng_LDADD =   -lgnuploti
#
#anim_headers= ${interface_headers) 
#anim_source=  ${interface_source) anim.c
#anim = $(anim_headers) $(anim_source) 
#anim_LDFLAGS =   -L.
#anim_LDADD =   -lgnuploti

	
