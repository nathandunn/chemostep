## -*- automake -*-
## (C) 2003 by Nathan Dunn, <ndunn@mac.com>
## $Id: Makefile.am,v 1.7 2004/04/02 02:23:01 ndunn Exp $

bin_PROGRAMS = autonetminer # networkminer # netsearch
networkminer_MOC = SearchGui.moc.cpp SearchForm2.moc.cpp
GUI_LIBS=SearchGui.hpp SearchForm2.hpp 
GUI_LIBS+=SearchGui.cpp SearchForm2.cpp
SUPPORT_LIBS=ConnectionTypes.hpp SearchDriver.hpp LookupTable.hpp Neuron.hpp ConnectionReader.hpp ConnectionWriter.hpp Connection.hpp ConnectionPath.hpp DepthFirstSearch.hpp LookupField.hpp NeuronList.hpp Threshold.hpp ThresholdList.hpp 
REPORT_LIBS=Stat.hpp EdgeStatLine.hpp EdgeStat.hpp CountRule.hpp CountWeightRule.hpp CountEachRule.hpp CountWeightOnlyRule.hpp EdgeWriter.hpp TextEdgeWriter.hpp DotWriter.hpp
SUPPORT_LIBS+=SearchDriver.cpp LookupTable.cpp Neuron.cpp ConnectionReader.cpp ConnectionWriter.cpp Connection.cpp ConnectionPath.cpp DepthFirstSearch.cpp LookupField.cpp NeuronList.cpp Threshold.cpp ThresholdList.cpp 
REPORT_LIBS+=Stat.cpp EdgeStatLine.cpp EdgeStat.cpp CountRule.cpp CountWeightRule.cpp CountEachRule.cpp CountWeightOnlyRule.cpp EdgeWriter.cpp TextEdgeWriter.cpp DotWriter.cpp
COMMANDLINE_LIBS=CommandLineSearch.hpp CommandLineSearch.cpp



MOC = $(QTDIR)/bin/moc
UIC      = $(QTDIR)/bin/uic -L$(QTDIR)/plugins
QMAKE    = $(QTDIR)/bin/qmake
QTLIBFLAGS=-L${QTDIR}/lib 
# BUILDDIR     = ../BUILDSTUFF

if DOX11
QT_OPT = -DQT_NO_DEBUG -I${QTDIR}/include/qt
X11_OPTION = -I/usr/X11R6/include
else
QT_OPT = -DQT_NO_DEBUG -I${QTDIR}/include
HOST_OPTION = 
endif


TINYXMLLIBS=-L../tinyxml 
AUTOGUILIBS=-L../autogui -L../tinyautogui -L../qtautogui -L../baseapps -L../utils

# QT options
#QT_OPT = -pipe -Wall -W -DQT_NO_DEBUG -I${QTDIR}/include

# INCLUDES= -D@platform@ -I../autogui ${HOST_OPTION} ${QT_OPT} ${X11_OPT}
INCLUDES=-D@platform@ ${HOST_OPTION} ${QT_OPT} ${X11_OPT}  -I../autogui -I../qtautogui -I../tinyautogui -I../baseapps -I../utils
# networkminer_LDFLAGS=$(QTLIBFLAGS) $(AUTOGUILIBS) $(TINYXMLLIBS)
# networkminer_LDADD = -lbaseflatdriver -lqtrender -ltinyauto -lautogui -ltinyxml -lqt-mt   # after target


# networkminer_SOURCES =     $(SUPPORT_LIBS) $(REPORT_LIBS) $(GUI_LIBS) $(networkminer_MOC)
autonetminer_SOURCES=SearchAutoGui.hpp SearchAutoGui.cpp $(SUPPORT_LIBS) $(REPORT_LIBS)  
autonetminer_LDFLAGS=$(QTLIBFLAGS) $(AUTOGUILIBS) $(TINYXMLLIBS)
autonetminer_LDADD= -lbaseflatdriver -lqtrender -ltinyauto -lautogui -ltinyxml -lqt-mt -lutil  # after target
# netsearch_SOURCES =     $(SUPPORT_LIBS) $(REPORT_LIBS) $(COMMANDLINE_LIBS) 


# CLEANFILES = $(networkminer_MOC) $(DESTDIR)/mapper
# BUILT_SOURCES = $(networkminer_MOC)

	

