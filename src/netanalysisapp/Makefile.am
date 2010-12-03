## -*- automake -*-
## (C) 2003 by Nathan Dunn, <ndunn@mac.com>
## $Id: Makefile.am,v 1.3 2004/01/27 20:27:19 ndunn Exp $

# lib_LIBRARIES = libautogui.a # mapper # qtoption qttree #htmloption htmltree
# libautogui_a_SOURCES= libautogui.a # mapper # qtoption qttree #htmloption htmltree


bin_PROGRAMS=plotapp simpleplot dottynet # wienerapp pruner netanalysis  sannapp 


if DOMPI
  MPI_OPT = -I${MPICH}/include -DDOMPI
  MPI_LIB     = -L${MPICH}/lib
  MPI_ADD     = -lmpich 
endif



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

INCLUDES=-D@platform@ ${HOST_OPTION} ${QT_OPT} ${X11_OPT} -DTIXML_USE_STL  -I../tinyxml -I../wormsim -I../autogui -I../qtautogui -I../tinyautogui -I../chemostep -I../blitzchemostep -I../tinyblitzchemostep -I../baseapps -I../utils -I../netanalysis -I../gnuplot_i -I${GSL}/include -I${BZDIR} -I/sw/include ${MPI_OPT}


# netanalysis_headers = analysisapp.hpp AnalysisDriver.hpp 
# netanalysis_source= analysisapp.cpp AnalysisDriver.cpp 
# netanalysis_SOURCES = $(netanalysis_headers) $(netanalysis_source)
# netanalysis_LDFLAGS = -L../netanalysis -L../wormsim -L../gnuplot_i $(QTLIBFLAGS) $(AUTOGUILIBS) $(TINYXMLLIBS) $(CHEMOSTEPLIBS) $(MPI_LIB)
# netanalysis_LDADD =   -lgnuploti -lnetanalysis -lwormsim -lbaseflatdriver -lqtrender -ltinyauto -lautogui -ltinyblitzchemostep -lblitzchemostep -lchemostep -ltinyxml -lqt-mt -lutil $(MPI_ADD) # -lMallocDebug # after target


# sannapp_headers = sannapp.hpp SannDriver.hpp 
# sannapp_source= sannapp.cpp SannDriver.cpp 
# sannapp_SOURCES = $(sannapp_headers) $(sannapp_source)
# sannapp_LDFLAGS = -L../netanalysis -L../wormsim -L../gnuplot_i $(QTLIBFLAGS) $(AUTOGUILIBS) $(TINYXMLLIBS) $(CHEMOSTEPLIBS) $(MPI_LIB)
# sannapp_LDADD =   -lgnuploti -lnetanalysis -lwormsim -lbaseflatdriver -lqtrender -ltinyauto -lautogui -ltinyblitzchemostep -lblitzchemostep -lchemostep -ltinyxml -lqt-mt -lutil # $(MPI_ADD) # -lMallocDebug # after target

# wienerapp_headers = wienerapp.hpp WienerDriver.hpp 
# wienerapp_source= wienerapp.cpp WienerDriver.cpp 
# wienerapp_SOURCES = $(wienerapp_headers) $(wienerapp_source)
# wienerapp_LDFLAGS = -L../netanalysis -L../wormsim -L../gnuplot_i $(QTLIBFLAGS) $(AUTOGUILIBS) $(TINYXMLLIBS) $(CHEMOSTEPLIBS) $(MPI_LIB)
# wienerapp_LDADD =   -lgnuploti -lnetanalysis -lwormsim -lbaseflatdriver -lqtrender -ltinyauto -lautogui -ltinyblitzchemostep -lblitzchemostep -lchemostep -ltinyxml -lqt-mt -lutil $(MPI_ADD) # -lMallocDebug # after target

plotapp_headers = plotapp.hpp PlotDriver.hpp 
plotapp_source= plotapp.cpp PlotDriver.cpp 
plotapp_SOURCES = $(plotapp_headers) $(plotapp_source)
plotapp_LDFLAGS = -L../wormsim -L../gnuplot_i $(QTLIBFLAGS) $(AUTOGUILIBS) $(TINYXMLLIBS) $(CHEMOSTEPLIBS) $(MPI_LIB)
plotapp_LDADD =   -lgnuploti -lwormsim -lbaseflatdriver -lqtrender -ltinyauto -lautogui -ltinyblitzchemostep -lblitzchemostep -lchemostep -ltinyxml -lqt-mt -lutil $(MPI_ADD) # -lMallocDebug # after target

# pruner_headers = pruneapp.hpp PruneDriver.hpp 
# pruner_source= pruneapp.cpp PruneDriver.cpp 
# pruner_SOURCES = $(pruner_headers) $(pruner_source)
# pruner_LDFLAGS = -L../wormsim -L../gnuplot_i $(QTLIBFLAGS) $(AUTOGUILIBS) $(TINYXMLLIBS) $(CHEMOSTEPLIBS) $(MPI_LIB)
# pruner_LDADD =   -lgnuploti -lpruneanalysis -lwormsim -lbaseflatdriver -lqtrender -ltinyauto -lautogui -ltinyblitzchemostep -lblitzchemostep -lchemostep -ltinyxml -lqt-mt -lutil $(MPI_ADD) # -lMallocDebug # after target

simpleplot_headers = simpleplotapp.hpp SimplePlotDriver.hpp 
simpleplot_source= simpleplotapp.cpp SimplePlotDriver.cpp 
simpleplot_SOURCES = $(simpleplot_headers) $(simpleplot_source)
simpleplot_LDFLAGS =  -L../wormsim -L../gnuplot_i $(QTLIBFLAGS) $(AUTOGUILIBS) $(TINYXMLLIBS) $(CHEMOSTEPLIBS) $(MPI_LIB)
simpleplot_LDADD =   -lgnuploti -lwormsim -lbaseflatdriver -lqtrender -ltinyauto -lautogui -ltinyblitzchemostep -lblitzchemostep -lchemostep -ltinyxml -lqt-mt -lutil $(MPI_ADD) # -lMallocDebug # after target


dottynet_headers = dottynetapp.hpp DottyNetDriver.hpp
dottynet_source = dottynetapp.cpp DottyNetDriver.cpp
dottynet_SOURCES = $(dottynet_headers) $(dottynet_source) 
dottynet_LDFLAGS = -L../netanalysis $(QTLIBFLAGS) $(AUTOGUILIBS) $(TINYXMLLIBS) $(CHEMOSTEPLIBS) 
dottynet_LDADD =   -ldotwriter -lbaseflatdriver -lqtrender -ltinyauto -lautogui -ltinyblitzchemostep -lblitzchemostep -lchemostep -ltinyxml -lqt-mt -lutil  

BUILT_SOURCES = $(qtrender_MOC) 

