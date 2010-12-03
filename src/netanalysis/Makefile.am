## -*- automake -*-
## (C) 2003 by Nathan Dunn, <ndunn@mac.com>



lib_LIBRARIES = libnetanalysis.a libpruneanalysis.a libdotwriter.a



# define options
if MACOSX
  HOST_OPTION = 
  X11_OPTION = 
else
  X11_OPTION = -I/usr/X11R6/include
  QTLIBFLAGS =  -L${QTDIR}/lib 
endif

if DOMPI
  MPI_OPTION = -I${MPICH}/include -DDOMPI
  MPI_LIB     = -L${MPICH}/lib
  MPI_ADD     = -lmpich 
endif

AUTOGUILIBS=-L../autogui -L../tinyautogui -L../qtautogui -L../baseapps -L../utils
TINYXMLLIBS=-L../tinyxml 
CHEMOSTEPLIBS=-L../chemostep -L../blitzchemostep -L../tinyblitzchemostep
#QT_OPT = -pipe -I${QTDIR}/include
QT_OPT = # -pipe -I${QTDIR}/include
MISC_OPT = -Weffc++

# INCLUDES=-D@platform@ ${HOST_OPTION} ${QT_OPT} ${X11_OPT} -I${BZDIR} ${MPI_OPTION} -I../autogui -I../qtautogui -I../tinyautogui -I../baseapps -I../blitzchemostep -I../tinyblitzchemostep -I../chemostep -I../utils 
INCLUDES=-D@platform@ ${HOST_OPTION} ${QT_OPT} ${X11_OPT} -I${BZDIR}  -I../blitzchemostep -I../tinyblitzchemostep -I../chemostep -I../utils -I../wormsim 


general_headers=DataFilter.hpp Label.hpp LabelSet.hpp  LabelFactory.hpp GenericLabelIdentifierSet.hpp # LabelIdentifier.hpp 
general_source=DataFilter.cpp Label.cpp LabelIdentifier.cpp LabelSet.cpp GenericLabelIdentifierSet.cpp LabelFactory.cpp 
general=$(general_headers) $(general_source)
zeroorder_headers=ZeroOrderFilter.hpp ZeroOrderImpulseFilter.hpp ZeroOrderLabel.hpp ZeroOrderLabelIdentifier.hpp ZeroOrderImpulseLabelIdentifier.hpp  
zeroorder_source=ZeroOrderFilter.cpp ZeroOrderImpulseFilter.cpp ZeroOrderLabel.cpp ZeroOrderLabelIdentifier.cpp ZeroOrderImpulseLabelIdentifier.cpp   
firstorder_headers=FirstOrderFilter.hpp FirstOrderImpulseFilter.hpp FirstOrderLabel.hpp FirstOrderLabelIdentifier.hpp FirstOrderImpulseLabelIdentifier.hpp  
zeroorder=$(zeroorder_headers) $(zeroorder_source)
firstorder_source=FirstOrderFilter.cpp FirstOrderImpulseFilter.cpp FirstOrderLabel.cpp FirstOrderLabelIdentifier.cpp FirstOrderImpulseLabelIdentifier.cpp   
firstorder=$(firstorder_headers) $(firstorder_source)
secondorder_headers=SecondOrderFilter.hpp  SecondOrderImpulseFilter.hpp SecondOrderLabel.hpp SecondOrderLabelIdentifier.hpp SecondOrderImpulseLabelIdentifier.hpp  
secondorder_source=SecondOrderFilter.cpp  SecondOrderImpulseFilter.cpp SecondOrderLabel.cpp SecondOrderLabelIdentifier.cpp SecondOrderImpulseLabelIdentifier.cpp 
secondorder=$(secondorder_headers) $(secondorder_source)

signal_headers=RawSignal.hpp ImpulseSignal.hpp Peak.hpp # StepSignal.hpp
signal_sources=RawSignal.cpp ImpulseSignal.cpp Peak.cpp # StepSignal.cpp
signal=$(signal_headers) $(signal_sources)


# libnetanalysis dependencies
libnetanalysis_aincludedir=${prefix}/include/chemostep
libnetanalysis_ainclude_HEADERS =$(signal_headers)  $(general_headers) $(zeroorder_headers) $(firstorder_headers) $(secondorder_headers)
libnetanalysis_a_SOURCES = $(signal) $(general) $(zeroorder) $(firstorder) $(secondorder)

# libpruneanalysis dependencies
libpruneanalysis_aincludedir=${prefix}/include/chemostep
libpruneanalysis_ainclude_HEADERS = PulseAnalyzer.hpp BlitzNetPruner.hpp
libpruneanalysis_a_SOURCES = PulseAnalyzer.cpp BlitzNetPruner.cpp 

libdotwriter_aincludedir=${prefix}/include/chemostep
libdotwriter_ainclude_HEADERS = DotNetConverter.hpp
libdotwriter_a_SOURCES = DotNetConverter.cpp


%.moc.cpp: %.h
	$(MOC) $< -o $@ 
	
%.class: %.java
	`which jikes` $< -o $@



