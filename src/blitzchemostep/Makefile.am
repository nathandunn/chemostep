## -*- automake -*-

lib_LIBRARIES = libblitzchemostep.a 


network_headers= blitzdefs.hpp BlitzNet.hpp BlitzLiveNet.hpp  BlitzNetEvaluator.hpp BlitzNetPerturber.hpp   BlitzEulerNetEvaluator.hpp BlitzEulerLiveNetEvaluator.hpp BlitzEulerSigLiveNetEvaluator.hpp BlitzEulerLiveNetEvaluator.hpp BlitzEulerSigNetEvaluator.hpp BlitzEulerNoiseLiveNetEvaluator.hpp BlitzEulerNoiseSigNetEvaluator.hpp KineticBlitzEulerEval.hpp BlitzEulerPerturber.hpp BlitzEulerWrapPerturber.hpp BlitzNetAnnealer.hpp   BlitzGAAlgorithm.hpp BzNetParser.hpp FastSigLookup.hpp SigLookupInterface.hpp SigLookupBz.hpp SeqBlitzNetAnnealer.hpp SeqResetBlitzNetAnnealer.hpp BlitzNetAlopexPerturber.hpp BlitzNetAlopexWrapPerturber.hpp BlitzNetAlopexer.hpp  BlitzMidPointNetEvaluator.hpp BlitzMidPointLiveNetEvaluator.hpp # SeqCheckBlitzNetAnnealer.hpp SeqAdjustBlitzNetAnnealer.hpp  BlitzNetGradientDescent.hpp  AutoWKineticBlitzEulerEval.hpp CachedKineticBlitzEulerEval.hpp 
network_source= blitzdefs.cpp BlitzNet.cpp BlitzLiveNet.cpp  BlitzNetEvaluator.cpp BlitzEulerPerturber.cpp  BlitzEulerWrapPerturber.cpp BlitzNetPerturber.cpp BlitzEulerNetEvaluator.cpp BlitzEulerLiveNetEvaluator.cpp BlitzEulerSigLiveNetEvaluator.cpp BlitzEulerSigNetEvaluator.cpp BlitzEulerNoiseLiveNetEvaluator.cpp BlitzEulerNoiseSigNetEvaluator.cpp KineticBlitzEulerEval.cpp BlitzNetAnnealer.cpp BlitzGAAlgorithm.cpp FastSigLookup.cpp SigLookupBz.cpp SigLookupInterface.cpp SeqBlitzNetAnnealer.cpp SeqResetBlitzNetAnnealer.cpp  BlitzNetAlopexPerturber.cpp BlitzNetAlopexWrapPerturber.cpp BlitzNetAlopexer.cpp BlitzMidPointNetEvaluator.cpp BlitzMidPointLiveNetEvaluator.cpp # SeqCheckBlitzNetAnnealer.cpp SeqAdjustBlitzNetAnnealer.cpp BlitzNetGradientDescent.cpp  AutoWKineticBlitzEulerEval.cpp  CachedKineticBlitzEulerEval.cpp 
renderer_headers= BlitzNetRenderer.hpp   BlitzReportNetRenderer.hpp BlitzXmlNetRenderer.hpp # BlitzCSVNetRenderer.hpp BlitzFlatCSVNetRenderer.hpp
renderer_source=                        BlitzReportNetRenderer.cpp BlitzXmlNetRenderer.cpp  # BlitzCSVNetRenderer.cpp BlitzFlatCSVNetRenderer.cpp
network = $(network_headers) $(network_source) 
renderer = $(renderer_headers) $(renderer_source) 
#--------------------------
#--------------------------


if MACOSX
  HOST_OPTION = 
endif

if DOMPI
  MPI_OPTION = -I${MPICH}/include -DDOMPI
  MPI_LIB     = ${MPICH}/lib/libmpich.a
endif


MISC_OPT = -Weffc++

INCLUDES =  -D@platform@ ${HOST_OPTION} -I../chemostep -I../utils -I${BZDIR} ${MPI_OPTION}
    
#--------------------------
#--------------------------

libblitzchemostep_aincludedir=${prefix}/include/chemostep
libblitzchemostep_ainclude_HEADERS=$(network_headers) $(renderer_headers)
libblitzchemostep_a_SOURCES= $(network) $(renderer) 

# libblitzchemostep_a_LDFLAGS=-L../chemostep -L../utils
# libblitzchemostep_a_LIBADD= -L../chemostep -L../utils -lchemostep -lblitz -lutil -lm -L$(BZDIR)/lib ${MPI_LIB} 
libblitzchemostep_a_LIBADD=  ${MPI_LIB} ../chemostep/libchemostep.a ../utils/libutil.a 

	
%.class: %.java
	`which jikes` $< -o $@

