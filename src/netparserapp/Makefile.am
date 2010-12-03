## -*- automake -*-
## (C) 2003 by Nathan Dunn, <ndunn@mac.com>
## $Id: Makefile.am,v 1.3 2004/01/27 20:27:19 ndunn Exp $



bin_PROGRAMS = netparser



# define options
  X11_OPTION = -I/usr/X11R6/include
  QTLIBFLAGS =  -L${QTDIR}/lib 



AUTOGUILIBS=-L../autogui -L../tinyautogui -L../qtautogui -L../baseapps -L../utils
TINYXMLLIBS=-L../tinyxml 
QT_OPT = -pipe -I${QTDIR}/include/qt
MISC_OPT = -Weffc++

# INCLUDES=-D@platform@ ${HOST_OPTION} ${QT_OPT} ${X11_OPT}  -DTIXML_USE_STL  -I../tinyxml -I../autogui -I../qtautogui -I../tinyautogui -I../chemostep -I../blitzchemostep -I../tinyblitzchemostep -I../gnuplotchemostep -I../gnuplot_i -I${BZDIR} ${MPI_OPT}
INCLUDES=-D@platform@ ${HOST_OPTION} ${QT_OPT} ${X11_OPT}  -I../autogui -I../qtautogui -I../tinyautogui -I../baseapps -I../utils

netparser_headers =  netparser.hpp  NetDataParser.hpp  ConnectionData.hpp ASymmParser.hpp SymmParser.hpp NeuronNamer.hpp
netparser_source= netparser.cpp NetDataParser.cpp ConnectionData.cpp ASymmParser.cpp SymmParser.cpp NeuronNamer.cpp
netparser_SOURCES = $(netparser_headers) $(netparser_source)
netparser_LDFLAGS = $(QTLIBFLAGS) $(AUTOGUILIBS) $(TINYXMLLIBS) 
netparser_LDADD =   -lbaseflatdriver -lqtrender -ltinyauto -lautogui -ltinyxml -lqt-mt -lutil  # after target


BUILT_SOURCES = $(qtrender_MOC) 

%.moc.cpp: %.h
	$(MOC) $< -o $@ 
	
%.class: %.java
	`which jikes` $< -o $@

