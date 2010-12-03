## -*- automake -*-
## (C) 2003 by Nathan Dunn, <ndunn@mac.com>
## $Id: Makefile.am,v 1.3 2004/01/27 20:27:19 ndunn Exp $

# lib_LIBRARIES = libautogui.a # mapper # qtoption qttree #htmloption htmltree
# libautogui_a_SOURCES= libautogui.a # mapper # qtoption qttree #htmloption htmltree


bin_PROGRAMS=gaapp
# lib_LIBRARIES= libevoanneal.a


if DOMPI
  MPI_OPT = -I${MPICH}/include -DDOMPI
dnl   MPI_LIB     = -L${MPICH}/lib
dnl   MPI_ADD     = -lmpich 
	MPI_ADD = ${MPICH}/lib/libmpich.a
endif

# MOC = $(QTDIR)/bin/moc


# define options
if MACOSX
  HOST_OPTION = 
endif

X11_OPTION = -I/usr/X11R6/include
QTLIBFLAGS =  -L${QTDIR}/lib 



CHEMOSTEPLIBS=-L../chemostep -L../blitzchemostep -L../tinyblitzchemostep  
AUTOGUILIBS=-L../autogui -L../tinyautogui -L../qtautogui -L../baseapps -L../utils
TINYXMLLIBS=-L../tinyxml 
QT_OPT = -pipe -I${QTDIR}/include/qt
MISC_OPT = -Weffc++

#INCLUDES=-D@platform@ ${HOST_OPTION} ${QT_OPT} ${X11_OPT} -DTIXML_USE_STL  -I../tinyxml -I../wormsim -I../autogui -I../qtautogui -I../tinyautogui -I../chemostep -I../blitzchemostep -I../tinyblitzchemostep -I../baseapps -I../utils -I../gnuplot_i -I${BZDIR} ${MPI_OPT}




INCLUDES=-D@platform@ ${HOST_OPTION}  -DTIXML_USE_STL  -I../tinyxml -I../autogui -I../chemostep -I../blitzchemostep -I../tinyblitzchemostep -I../baseapps -I../utils -I../gnuplot_i -I${BZDIR} ${MPI_OPT}

gaapp_headers = GaApp.hpp 
gaapp_source= GaApp.cpp 
gaapp_SOURCES =  $(gaapp_source) 
gaapp_LDFLAGS = -L../gnuplot_i -L../utils $(TINYXMLLIBS) $(CHEMOSTEPLIBS) 
gaapp_LDADD =   -ltinyblitzchemostep -lblitzchemostep -lchemostep -ltinyxml -lutil -lgnuploti  -lautooption $(MPI_LIB) # -lMallocDebug # after target


# libdir= -L../wormsim -L../evoannealcheckapp $(QTLIBFLAGS) $(AUTOGUILIBS) $(TINYXMLLIBS) $(CHEMOSTEPLIBS) 


#BUILT_SOURCES = $(qtrender_MOC) 
#CLEANFILES = $(BUILT_SOURCES) $(DESTDIR)/evoannealapp.app/Contents/MacOS/* 

#%.moc.cpp: %.h
#	$(MOC) $< -o $@ 
	




