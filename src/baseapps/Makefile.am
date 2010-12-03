## -*- automake -*-
## (C) 2003 by Nathan Dunn, <ndunn@mac.com>
## $Id: Makefile.am,v 1.3 2004/01/27 20:27:19 ndunn Exp $

# we give it as both a standalone as proof of concept 
# and a linkable library to expand other apps
bin_PROGRAMS = baseflatdriver
lib_LIBRARIES = libbaseflatdriver.a


CHEMOSTEPLIBS=-L../chemostep -L../blitzchemostep -L../tinyblitzchemostep # -L../gnuplotchemostep # -L../gnuplot_i
AUTOGUILIBS=-L../autogui -L../tinyautogui -L../qtautogui -L${QTDIR}/lib
TINYXMLLIBS=-L../tinyxml 
if DOX11
QT_OPT = -pipe -I${QTDIR}/include/qt
else
QT_OPT = -pipe -I${QTDIR}/include
endif
MISC_OPT = -Weffc++

INCLUDES=-D@platform@ ${HOST_OPTION} ${QT_OPT} ${X11_OPT}  -DTIXML_USE_STL  -I../tinyxml -I../autogui -I../qtautogui -I../tinyautogui -I../chemostep -I../blitzchemostep -I../tinyblitzchemostep -I${BZDIR} ${MPI_OPT}

baseflatdriver_headers = BaseFlatDriver.hpp 
baseflatdriver_source= baseflatmain.cpp BaseFlatDriver.cpp 
baseflatdriver_SOURCES = $(baseflatdriver_headers) $(baseflatdriver_source)
baseflatdriver_LDFLAGS = $(QTLIBFLAGS) $(AUTOGUILIBS) $(TINYXMLLIBS) $(CHEMOSTEPLIBS)
baseflatdriver_LDADD =   -lqtrender -ltinyauto -lautogui -ltinyblitzchemostep -lblitzchemostep -lchemostep -ltinyxml -lqt-mt   # after target

libbaseflatdriver_headers = BaseFlatDriver.hpp 
libbaseflatdriver_source= BaseFlatDriver.cpp 
libbaseflatdriver_a_SOURCES = $(baseflatdriver_headers) $(baseflatdriver_source)
#libbaseflatdriver_a_LBFLAGS = $(QTLIBFLAGS) $(AUTOGUILIBS) $(TINYXMLLIBS) $(CHEMOSTEPLIBS)
# libbaseflatdriver_a_LIBADD =   -lqtrender -ltinyauto -lautogui -ltinyblitzchemostep -lblitzchemostep -lchemostep -ltinyxml -lqt-mt   # after target

BUILT_SOURCES = $(qtrender_MOC) 
CLEANFILES = $(BUILT_SOURCES) $(DESTDIR)/baseflatdriver.app/Contents/MacOS/*

																		

