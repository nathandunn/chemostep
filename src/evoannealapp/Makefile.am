## -*- automake -*-
## (C) 2003 by Nathan Dunn, <ndunn@mac.com>
## $Id: Makefile.am,v 1.3 2004/01/27 20:27:19 ndunn Exp $

# lib_LIBRARIES = libautogui.a # mapper # qtoption qttree #htmloption htmltree
# libautogui_a_SOURCES= libautogui.a # mapper # qtoption qttree #htmloption htmltree


bin_PROGRAMS=evoannealapp tennisapp inputtrace distributionapp
# lib_LIBRARIES= libevoanneal.a


if DOMPI
  MPI_OPT = -I${MPICH}/include -DDOMPI
dnl   MPI_LIB     = -L${MPICH}/lib
dnl   MPI_ADD     = -lmpich 
	MPI_ADD = ${MPICH}/lib/libmpich.a
endif

MOC = $(QTDIR)/bin/moc


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

INCLUDES=-D@platform@ ${HOST_OPTION} ${QT_OPT} ${X11_OPT} -DTIXML_USE_STL  -I../tinyxml -I../wormsim -I../autogui -I../qtautogui -I../tinyautogui -I../chemostep -I../blitzchemostep -I../tinyblitzchemostep -I../baseapps -I../utils -I../gnuplot_i -I${BZDIR} ${MPI_OPT}


evoannealapp_headers = PerturbFrame.h evoannealapp.hpp EvoAnnealDriver.hpp AnnealerThread.hpp  
evoannealapp_source= PerturbFrame.cpp evoannealapp.cpp EvoAnnealDriver.cpp AnnealerThread.cpp 
evoannealapp_MOC = PerturbFrame.moc.cpp
dnl evoannealapp_include_HEADERS=$(evoannealapp_headers) 
evoannealapp_SOURCES =  $(evoannealapp_source) $(evoannealapp_MOC)
evoannealapp_LDFLAGS = -L../gnuplot_i -L../wormsim $(QTLIBFLAGS) $(AUTOGUILIBS) $(TINYXMLLIBS) $(CHEMOSTEPLIBS) $(MPI_LIB)
evoannealapp_LDADD =   -lwormsim -lbaseflatdriver -lqtrender -ltinyauto -lautogui -ltinyblitzchemostep -lblitzchemostep -lchemostep -ltinyxml -lqt-mt -lutil -lgnuploti $(MPI_ADD) # -lMallocDebug # after target


tennisapp_headers = tennisapp.hpp TennisDriver.hpp 
tennisapp_source= tennisapp.cpp TennisDriver.cpp 
tennisapp_SOURCES =  $(tennisapp_source) 
tennisapp_LDFLAGS = -L../gnuplot_i -L../wormsim $(QTLIBFLAGS) $(AUTOGUILIBS) $(TINYXMLLIBS) $(CHEMOSTEPLIBS) $(MPI_LIB)
tennisapp_LDADD =   -lonewormsim -lbaseflatdriver -lqtrender -ltinyauto -lautogui -ltinyblitzchemostep -lblitzchemostep -lchemostep -ltinyxml -lqt-mt -lutil -lgnuploti $(MPI_ADD) # -lMallocDebug # after target


# inputtrace_headers = InputTracer.hpp 
# inputtrace_source= mainInputTrace.cpp InputTracer.cpp 
inputtrace_headers = InputTracerAuto.hpp 
inputtrace_source= InputTracerAuto.cpp 
inputtrace_SOURCES =  $(inputtrace_source) 
inputtrace_LDFLAGS = -L../gnuplot_i -L../wormsim  -L../utils $(TINYXMLLIBS) $(CHEMOSTEPLIBS) 
inputtrace_LDADD =   -lonewormsim -ltinyblitzchemostep -lblitzchemostep -lchemostep -ltinyxml -lutil -lgnuploti -lautooption # -lMallocDebug # after target


distributionapp_headers = DistributionApp.hpp 
distributionapp_source= DistributionApp.cpp 
distributionapp_SOURCES =  $(distributionapp_source) 
distributionapp_LDFLAGS = -L../gnuplot_i -L../wormsim  -L../utils $(TINYXMLLIBS) $(CHEMOSTEPLIBS) 
distributionapp_LDADD =   -lonewormsim -ltinyblitzchemostep -lblitzchemostep -lchemostep -ltinyxml -lutil -lgnuploti  -lautooption # -lMallocDebug # after target


libdir= -L../wormsim -L../evoannealcheckapp $(QTLIBFLAGS) $(AUTOGUILIBS) $(TINYXMLLIBS) $(CHEMOSTEPLIBS) $(MPI_LIB)


BUILT_SOURCES = $(qtrender_MOC) 
CLEANFILES = $(BUILT_SOURCES) $(DESTDIR)/evoannealapp.app/Contents/MacOS/* 

%.moc.cpp: %.h
	$(MOC) $< -o $@ 
	




