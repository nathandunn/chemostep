## -*- automake -*-

lib_LIBRARIES = libchemostep.a 

alopexer_headers=Alopexer.hpp NetAlopexer.hpp
alopexer_source=NetAlopexer.cpp

ga_headers=GAAlgorithm.hpp NetworkParameter.hpp 
annealer_headers=Annealer.hpp NetAnnealer.hpp AnnealingTarget.hpp AcceptModel.hpp TtestAcceptModel.hpp SzuAcceptModel.hpp MetropolisAcceptModel.hpp
annealer_source =Annealer.cpp NetAnnealer.cpp AcceptModel.cpp TtestAcceptModel.cpp SzuAcceptModel.cpp MetropolisAcceptModel.cpp
graddescent_headers=GradDescent.hpp TrainingTarget.hpp
graddescent_source =GradDescent.cpp
temp_headers=TempSchedule.hpp PowerTempSchedule.hpp MomentumTempSchedule.hpp MomentumPowerTempSchedule.hpp Momentum2PowerTempSchedule.hpp SzuTempSchedule.hpp GeometricTempSchedule.hpp
temp_source =TempSchedule.cpp PowerTempSchedule.cpp MomentumTempSchedule.cpp MomentumPowerTempSchedule.cpp Momentum2PowerTempSchedule.cpp  SzuTempSchedule.cpp GeometricTempSchedule.cpp
network_headers=NeuralNetwork.hpp NetPerturber.hpp BinNetEvaluator.hpp NetEvaluator.hpp XmlNetInterface.hpp SigLookup.hpp Note.hpp
network_source= NeuralNetwork.cpp NetPerturber.cpp BinNetEvaluator.cpp NetEvaluator.cpp XmlNetInterface.cpp SigLookup.cpp Note.cpp
feeder_headers=FeederSet.hpp Feeder.hpp SetFeeder.hpp StepFeeder.hpp FileFeeder.hpp PulseFeeder.hpp ScaledFileFeeder.hpp
feeder_source=  FeederSet.cpp Feeder.cpp SetFeeder.cpp StepFeeder.cpp FileFeeder.cpp PulseFeeder.cpp ScaledFileFeeder.cpp
evaltrace_headers=  EvalTrace.hpp  TextEvalTrace.hpp  XmlRenderable.hpp
evaltrace_source=   EvalTrace.cpp TextEvalTrace.cpp  XmlRenderable.cpp
evaltrace = $(evaltrace_headers) $(evaltrace_source) 
alopex = $(alopexer_headers) $(alopexer_source) 
network = $(network_headers) $(network_source) 
annealer = $(annealer_headers) $(annealer_source) 
ga = $(ga_headers) 
graddescent = $(graddescent_headers) $(graddescent_source) 
temp = $(temp_headers) $(temp_source) 
feeder = $(feeder_headers) $(feeder_source) 
#--------------------------

# libdir=../chemostep
# libchemostep_aincludedir=../chemostep
libchemostep_aincludedir=${prefix}/include/chemostep
libchemostep_ainclude_HEADERS=$(alopexer_headers) $(network_headers) $(graddescent_headers) $(annealer_headers) $(temp_headers) $(feeder_headers) $(evaltrace_headers) $(ga_headers)
libchemostep_a_SOURCES= $(feeder) $(network) $(graddescent) $(annealer) $(alopex) $(temp)  $(evaltrace) $(ga)
libchemostep_a_LIBADD=../utils/libutil.a ${MPI_LIB} # shortcut
dnl libchemostep_a_LIBADD=-lutil ${MPI_LIB}
dnl libchemostep_a_LDFLAGS=-L../utils

if MACOSX
  HOST_OPTION = 
endif

if DOMPI
  MPI_OPTION = -I${MPICH}/include -DDOMPI
  MPI_LIB     = ${MPICH}/lib/libmpich.a
endif


MISC_OPT = -Weffc++

INCLUDES =  -D@platform@ ${HOST_OPTION} -I../utils ${MPI_OPTION}
	
%.class: %.java
	`which jikes` $< -o $@

