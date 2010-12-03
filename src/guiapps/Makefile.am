## -*- automake -*-
## (C) 2003 by Nathan Dunn, <ndunn@mac.com>
## $Id: Makefile.am,v 1.3 2004/01/27 20:27:19 ndunn Exp $

# lib_LIBRARIES = libautogui.a # mapper # qtoption qttree #htmloption htmltree
# libautogui_a_SOURCES= libautogui.a # mapper # qtoption qttree #htmloption htmltree


bin_PROGRAMS = guianneal

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
    DESTDIR=guianneal.app/Contents/MacOS
    bindir=/../MacOS
else
	DESTDIR=../
	bindir=bin 
endif 

CHEMOSTEPLIBS=-L../chemostep -L../blitzchemostep -L../tinyblitzchemostep # -L../gnuplotchemostep # -L../gnuplot_i
AUTOGUILIBS=-L../autogui -L../tinyautogui -L../qtautogui -L../baseapps  -L../utils
TINYXMLLIBS=-L../tinyxml 
QT_OPT = -pipe -I${QTDIR}/include
MISC_OPT = -Weffc++

INCLUDES=-D@platform@ ${HOST_OPTION} ${QT_OPT} ${X11_OPT}  -DTIXML_USE_STL  -I../tinyxml -I../autogui -I../qtautogui -I../tinyautogui -I../chemostep -I../blitzchemostep -I../tinyblitzchemostep -I../baseapps -I../utils -I${BZDIR} ${MPI_OPT}


guianneal_headers = guianneal.hpp AnnealerDriver.hpp 
guianneal_source= guianneal.cpp AnnealerDriver.cpp 
guianneal_SOURCES = $(guianneal_headers) $(guianneal_source)
guianneal_LDFLAGS = $(QTLIBFLAGS) $(AUTOGUILIBS) $(TINYXMLLIBS) $(CHEMOSTEPLIBS) $(MPI_LIB)
# guianneal_LDADD =   -lqtrender -ltinyauto -lautogui -ltinyblitzchemostep -lblitzchemostep -lgnuplotchemostep -lgnuploti -lchemostep -ltinyxml -lqt-mt   # after target
guianneal_LDADD =   -lbaseflatdriver -lqtrender -ltinyauto -lautogui -ltinyblitzchemostep -lblitzchemostep -lchemostep -ltinyxml -lqt-mt -lutil $(MPI_ADD)   # after target
# rendertest_DEPENDENCIES = ../renderer/librender.a  ../renderer/libautogui.a ../renderer/libtestclass.a    # after target


BUILT_SOURCES = $(qtrender_MOC) 
CLEANFILES = $(BUILT_SOURCES) $(DESTDIR)/tree.app/Contents/MacOS/*

%.moc.cpp: %.h
	$(MOC) $< -o $@ 
	
%.class: %.java
	`which jikes` $< -o $@

