## -*- automake -*-
## (C) 2003 by Nathan Dunn, <ndunn@mac.com>
## $Id: Makefile.am,v 1.3 2004/01/27 20:27:19 ndunn Exp $

# lib_LIBRARIES = libautogui.a # mapper # qtoption qttree #htmloption htmltree
# libautogui_a_SOURCES= libautogui.a # mapper # qtoption qttree #htmloption htmltree


# bin_PROGRAMS = alopexapp newalopexapp
bin_PROGRAMS = newalopexapp


if DOMPI
  MPI_OPT = -I${MPICH}/include -DDOMPI
  MPI_LIB     = -L${MPICH}/lib
  MPI_ADD     = -lmpich
endif



# define options
if MACOSX
  HOST_OPTION = 
  X11_OPTION = 
else
  X11_OPTION = -I/usr/X11R6/include
  QTLIBFLAGS =  -L${QTDIR}/lib 
endif



if QTMAC
    QTLIBFLAGS=-prebind -L${QTDIR}/lib 
    DESTDIR=alopexapp.app/Contents/MacOS
    bindir=/../MacOS
else
	DESTDIR=../
	bindir=bin 
endif 


CHEMOSTEPLIBS=-L../chemostep -L../blitzchemostep -L../tinyblitzchemostep -L../wormsim 
AUTOGUILIBS=-L../autogui -L../tinyautogui -L../qtautogui -L../baseapps -L../utils
TINYXMLLIBS=-L../tinyxml 
QT_OPT = -pipe -I${QTDIR}/include
MISC_OPT = -Weffc++

INCLUDES=-D@platform@ ${HOST_OPTION} ${QT_OPT} ${X11_OPT}  -DTIXML_USE_STL  -I../tinyxml -I../autogui -I../qtautogui -I../tinyautogui -I../chemostep -I../blitzchemostep -I../tinyblitzchemostep -I../baseapps -I../utils -I../wormsim -I../gnuplot_i -I${BZDIR} ${MPI_OPT}


# alopexapp_headers = guialopexer.hpp AlopexDriver.hpp AlopexThread.hpp 
# alopexapp_source= guialopexer.cpp AlopexDriver.cpp AlopexThread.cpp
# alopexapp_SOURCES = $(alopexapp_headers) $(alopexapp_source)
# alopexapp_LDFLAGS = $(QTLIBFLAGS) $(AUTOGUILIBS) $(TINYXMLLIBS) $(CHEMOSTEPLIBS) $(MPI_LIB)
# alopexapp_LDADD =  -lbaseflatdriver -lqtrender -ltinyauto -lautogui -lwormsim -ltinyblitzchemostep -lblitzchemostep -lchemostep -ltinyxml -lqt-mt -lutil $(MPI_ADD) # after target

newalopexapp_headers = alopex2app.hpp Alopex2Driver.hpp 
newalopexapp_source= alopex2app.cpp Alopex2Driver.cpp 
newalopexapp_SOURCES = $(newalopexapp_headers) $(newalopexapp_source)
newalopexapp_LDFLAGS = -L../gnuplot_i -L../wormsim $(QTLIBFLAGS) $(AUTOGUILIBS) $(TINYXMLLIBS) $(CHEMOSTEPLIBS) $(MPI_LIB)
newalopexapp_LDADD =  -lbaseflatdriver -lqtrender -ltinyauto -lautogui -lwormsim -ltinyblitzchemostep -lblitzchemostep -lchemostep -ltinyxml -lqt-mt -lutil -lgnuploti  $(MPI_ADD) # after target




BUILT_SOURCES = $(qtrender_MOC) 
CLEANFILES = $(BUILT_SOURCES) $(DESTDIR)/tree.app/Contents/MacOS/*

