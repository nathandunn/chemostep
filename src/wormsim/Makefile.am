## -*- automake -*-
## (C) 2003 by Nathan Dunn, <ndunn@mac.com>
## $Id: Makefile.am,v 1.3 2004/01/27 20:27:19 ndunn Exp $



# bin_PROGRAMS = mainapp # petriapp
lib_LIBRARIES = libwormsim.a libonewormsim.a 




# define options
if MACOSX
  HOST_OPTION = 
endif

X11_OPTION = -I/usr/X11R6/include
QTLIBFLAGS =  -L${QTDIR}/lib 

if DOMPI
  MPI_OPTION = -I${MPICH}/include -DDOMPI
  MPI_ADD     = ${MPICH}/lib/libmpich.a
dnl   MPI_LIB     = -L${MPICH}/lib
dnl   MPI_ADD     = -lmpich 
endif


AUTOGUILIBS=-L../autogui -L../tinyautogui -L../qtautogui -L../baseapps -L../utils
TINYXMLLIBS=-L../tinyxml 
CHEMOSTEP=-L../chemostep -L../blitzchemostep -L../tinyblitzchemostep
QT_OPT = -pipe -I${QTDIR}/include
MISC_OPT = -Weffc++

# INCLUDES=-D@platform@ ${HOST_OPTION} ${QT_OPT} ${X11_OPT}  -DTIXML_USE_STL  -I../tinyxml -I../autogui -I../qtautogui -I../tinyautogui -I../chemostep -I../blitzchemostep -I../tinyblitzchemostep -I../gnuplotchemostep -I../gnuplot_i -I${BZDIR} ${MPI_OPT}
INCLUDES=-D@platform@ ${HOST_OPTION} ${QT_OPT} ${X11_OPT} -I${BZDIR} ${MPI_OPTION} -I../autogui -I../qtautogui -I../tinyautogui -I../baseapps -I../blitzchemostep -I../tinyblitzchemostep -I../chemostep -I../utils 


MOVEMENT_MODEL_HEADER=SharpTurnMovementModel.hpp UniformFwdMovement.hpp ForwardMovementModel.hpp PirouetteMovementModel.hpp TurnAroundMovementModel.hpp DieMovementModel.hpp ShuffleMovementModel.hpp ShufflePreserveMovementModel.hpp
MOVEMENT_MODEL_SOURCE=SharpTurnMovementModel.cpp UniformFwdMovement.cpp ForwardMovementModel.cpp PirouetteMovementModel.cpp TurnAroundMovementModel.cpp DieMovementModel.cpp ShuffleMovementModel.cpp ShufflePreserveMovementModel.cpp

BEHAVIOR_MODEL_HEADER=RandomBehaviorModel.hpp ShortMemoryBehaviorModel.hpp  ForwardBehaviorModel.hpp  NetworkBehaviorModel.hpp Mode3NetworkBehaviorModel.hpp UniformNetBehaviorModel.hpp WormSimEval.hpp WormSimMeanDistEval.hpp WormSimSqrtMeanDistEval.hpp WormSimSqrtRadDistEval.hpp WormSimRadDistEval.hpp WormSimAllTrackEval.hpp WormSimProbTracks.hpp ProbDistribution.hpp 
BEHAVIOR_MODEL_SOURCE=RandomBehaviorModel.cpp ShortMemoryBehaviorModel.cpp  ForwardBehaviorModel.cpp  NetworkBehaviorModel.cpp Mode3NetworkBehaviorModel.cpp UniformNetBehaviorModel.cpp WormSimEval.cpp WormSimMeanDistEval.cpp WormSimSqrtMeanDistEval.cpp WormSimSqrtRadDistEval.cpp WormSimRadDistEval.cpp WormSimAllTrackEval.cpp WormSimProbTracks.cpp ProbDistribution.cpp
MAP_MODEL_HEADER=Map.hpp BehaviorModel.hpp MapData.hpp OneWormMapSpace.hpp Position.hpp WormTrack.hpp MapSpace.hpp DogbowlLinRadialMap.hpp LinRadialMap.hpp GaussRadialMap.hpp PowerRadialMap.hpp QuadMap.hpp Dimension.hpp BaseWorm.hpp Worm.hpp WormMapStats.hpp WormShuffler.hpp UniformRadWormShuffler.hpp Set2RadWormShuffler.hpp SetRadWormShuffler.hpp WindowFunction.hpp PowerWindowFunction.hpp InflectionWindowFunction.hpp UniformRadSpaceWormShuffler.hpp UniformAlternateRadSpaceWormShuffler.hpp EvenRadWormShuffler.hpp 
MAP_MODEL_SOURCE=BehaviorModel.cpp MapData.cpp OneWormMapSpace.cpp Position.cpp WormTrack.cpp MapSpace.cpp DogbowlLinRadialMap.cpp LinRadialMap.cpp GaussRadialMap.cpp PowerRadialMap.cpp QuadMap.cpp Dimension.cpp              Worm.cpp WormMapStats.cpp UniformRadWormShuffler.cpp  Set2RadWormShuffler.cpp SetRadWormShuffler.cpp  WindowFunction.cpp PowerWindowFunction.cpp InflectionWindowFunction.cpp UniformRadSpaceWormShuffler.cpp UniformAlternateRadSpaceWormShuffler.cpp EvenRadWormShuffler.cpp
ONE_MAP_MODEL_HEADER=Map.hpp RectMap.hpp OneWormMapSpace.hpp WormLogger.hpp Position.hpp WormTrack.hpp BaseWorm.hpp SimpleWorm.hpp WormShuffler.hpp OneWormSimEval.hpp WorstPairOneWormSimEval.hpp UniformOneNetBehaviorModel.hpp DogbowlLinRadialMap.hpp LinRadialMap.hpp EvenRadWormShuffler.hpp Dimension.hpp
ONE_MAP_MODEL_SOURCE=        RectMap.cpp OneWormMapSpace.cpp WormLogger.cpp Position.cpp WormTrack.cpp              SimpleWorm.cpp 				   OneWormSimEval.cpp WorstPairOneWormSimEval.cpp UniformOneNetBehaviorModel.cpp  DogbowlLinRadialMap.cpp LinRadialMap.cpp EvenRadWormShuffler.cpp Dimension.cpp 
WINDOW_HEADER=WindowFunction.hpp PowerWindowFunction.hpp InflectionWindowFunction.hpp  
WINDOW_SOURCE=WindowFunction.cpp PowerWindowFunction.cpp InflectionWindowFunction.cpp  
TENNIS_HEADER=TennisCourtMap.hpp TennisCourtAwayShuffler.hpp TennisCourtSetPositionShuffler.hpp
TENNIS_SOURCE=TennisCourtMap.cpp TennisCourtAwayShuffler.cpp TennisCourtSetPositionShuffler.cpp

ANNEALER_HEADER=SeqOneWormBlitzNetAnnealer.hpp
ANNEALER_SOURCE=SeqOneWormBlitzNetAnnealer.cpp

UTIL_HEADER=StatReporter.hpp Logger.hpp 
UTIL_SOURCE=StatReporter.cpp Logger.cpp 



libwormsim_aincludedir=${prefix}/include/chemostep
libwormsim_ainclude_HEADERS = $(MOVEMENT_MODEL_HEADER) $(BEHAVIOR_MODEL_HEADER) $(MAP_MODEL_HEADER) $(UTIL_HEADER)
libwormsim_a_SOURCES = $(MOVEMENT_MODEL_SOURCE) $(BEHAVIOR_MODEL_SOURCE) $(MAP_MODEL_SOURCE) $(UTIL_SOURCE) $(TINYXMLLIBS) $(CHEMOSTEP) $(MPI_LIB)
# libwormsim_a_LIBADD =   -ltinyblitzchemostep -lblitzchemostep -ltinyauto -lblitzchemostep -lautogui -lchemostep -ltinyxml -lutil $(MPI_ADD) # after target
libwormsim_a_LIBADD =   ../tinyblitzchemostep/libtinyblitzchemostep.a ../blitzchemostep/libblitzchemostep.a  ../tinyautogui/libtinyauto.a ../autogui/libautogui.a ../chemostep/libchemostep.a ../tinyxml/libtinyxml.a ../utils/libutil.a $(MPI_ADD) # after target


libonewormsim_aincludedir=${prefix}/include/chemostep
libonewormsim_ainclude_HEADERS =  $(MOVEMENT_MODEL_HEADER) $(BEHAVIOR_MODEL_HEADER) $(ONE_MAP_MODEL_HEADER) $(TENNIS_HEADER) $(ANNEALER_HEADER)
libonewormsim_a_SOURCES = $(TENNIS_SOURCE) $(MOVEMENT_MODEL_SOURCE)  $(BEHAVIOR_MODEL_SOURCE) $(ONE_MAP_MODEL_SOURCE) $(ANNEALER_SOURCE) $(TINYXMLLIBS) $(CHEMOSTEP) $(MPI_LIB) 
# libonewormsim_a_LIBADD =   -ltinyblitzchemostep -lblitzchemostep -ltinyauto -lblitzchemostep -lautogui -lchemostep -ltinyxml -lutil $(MPI_ADD) # after target
libonewormsim_a_LIBADD =   ../tinyblitzchemostep/libtinyblitzchemostep.a ../blitzchemostep/libblitzchemostep.a  ../tinyautogui/libtinyauto.a ../autogui/libautogui.a ../chemostep/libchemostep.a ../tinyxml/libtinyxml.a ../utils/libutil.a $(MPI_ADD) # after target






