## -*- automake -*-

# lib_LIBRARIES = libautogui.a # mapper # qtoption qttree #htmloption htmltree
# libautogui_a_SOURCES= libautogui.a # mapper # qtoption qttree #htmloption htmltree


bin_PROGRAMS = testset1  testset2 testset3 testset4 chemotest kineticanneal kineticannealtoy testnet netreader sigtest randtest # test3cache cachekineticannealtoy simpanneal blitztest autowtest  toy1 annealtest1 



if DOMPI
  MPI_OPT = -I${MPICH}/include -DDOMPI 
  MPI_LIB     = -L${MPICH}/lib
  MPI_ADD     = -lmpich 
endif



# define options
if MACOSX
  HOST_OPTION = 
endif


QT_OPT = -pipe -I${QTDIR}/include
MISC_OPT = -Weffc++

INCLUDES=-D@platform@ ${HOST_OPTION} ${QT_OPT} ${X11_OPT}  ${MPION} -I../tinyxml -I../blitzchemostep -I../chemostep -I../tinyblitzchemostep -I../utils -I${BZDIR} ${MPI_OPT}




testset1_SOURCES = test1.hpp test1.cpp 
testset1_LDFLAGS = -L../chemostep -L../blitzchemostep # -L$(BZDIR)/blitz/lib 
testset1_LDADD =   -lblitzchemostep  -lchemostep  -lstdc++ # -lMallocDebug # ${MPI_LIB} 

testset2_SOURCES = test2.hpp test2.cpp 
testset2_LDFLAGS = -L../chemostep -L../blitzchemostep -L../utils $(MPI_LIB) # -L$(BZDIR)/blitz/lib 
testset2_LDADD =   -lblitzchemostep  -lchemostep -lutil $(MPI_ADD) -lstdc++  # -lMallocDebug 

testset3_SOURCES = test3.hpp test3.cpp 
testset3_LDFLAGS = -L../chemostep -L../blitzchemostep $(MPI_LIB) # -L$(BZDIR)/blitz/lib 
testset3_LDADD =   -lblitzchemostep  -lchemostep -lstdc++ $(MPI_ADD)  # ${MPI_LIB} # -lMallocDebug 


testset4_SOURCES = test4.hpp test4.cpp 
testset4_LDFLAGS = -L../chemostep -L../blitzchemostep -L../utils $(MPI_LIB) # -L$(BZDIR)/blitz/lib 
testset4_LDADD =   -lblitzchemostep  -lchemostep -lutil -lstdc++  $(MPI_ADD) # ${MPI_LIB} # -lMallocDebug 

chemotest_SOURCES = chemotest.cpp 
chemotest_LDFLAGS = -L../chemostep -L../utils # $(QTLIBFLAGS) # -L$(BZDIR)/blitz/lib
chemotest_LDADD =   -lchemostep -lutil -lstdc++ # -lm

# test3cache_SOURCES = test3cache.hpp test3cache.cpp 
# test3cache_LDFLAGS = -L../chemostep -L../blitzchemostep # -L$(BZDIR)/blitz/lib 
# test3cache_LDADD =   -lblitzchemostep  -lchemostep -lstdc++  # ${MPI_LIB} # -lMallocDebug 



kineticannealtoy_SOURCES = kineticannealtoy.cpp 
kineticannealtoy_LDFLAGS = -L../chemostep -L../blitzchemostep -L../utils $(MPI_LIB) # $(QTLIBFLAGS) # -L$(BZDIR)/blitz/lib
kineticannealtoy_LDADD =   -lblitzchemostep  -lchemostep -lutil $(MPI_ADD) -lstdc++ # -lm


kineticanneal_SOURCES = kineticanneal.cpp 
kineticanneal_LDFLAGS = -L../chemostep -L../blitzchemostep -L../utils $(MPI_LIB) # $(QTLIBFLAGS) # -L$(BZDIR)/blitz/lib
kineticanneal_LDADD =   -lblitzchemostep  -lchemostep -lutil $(MPI_ADD) -lstdc++ # -lm


testnet_SOURCES = testnet.cpp 
testnet_LDFLAGS = -L../chemostep -L../blitzchemostep # $(QTLIBFLAGS) # -L$(BZDIR)/blitz/lib
testnet_LDADD =   -lblitzchemostep  -lchemostep -lstdc++ # -lm


netreader_SOURCES = netreader.cpp 
netreader_LDFLAGS = -L../tinyxml -L../chemostep -L../blitzchemostep -L../tinyblitzchemostep # $(QTLIBFLAGS) # -L$(BZDIR)/blitz/lib
netreader_LDADD =   -ltinyblitzchemostep -lblitzchemostep  -lchemostep -ltinyxml -lstdc++ # -l

sigtest_SOURCES = sigtest.cpp 
sigtest_LDFLAGS = -L../chemostep -L../blitzchemostep 
sigtest_LDADD =   -lblitzchemostep  -lchemostep -lstdc++ # -l


randtest_SOURCES = randtest.cpp 
randtest_LDFLAGS = -L../chemostep -L../blitzchemostep -L../utils
randtest_LDADD =   -lblitzchemostep  -lchemostep -lutil -lstdc++ # -l


############################
#
#  Below, not implemented
#
############################

# autowtest_SOURCES = autowtest.cpp 
# autowtest_LDFLAGS = -L../chemostep -L../blitzchemostep # $(QTLIBFLAGS) # -L$(BZDIR)/blitz/lib
# autowtest_LDADD =   -lblitzchemostep  -lchemostep # -lm
#
# cachekineticannealtoy_SOURCES = cachekineticannealtoy.cpp 
# cachekineticannealtoy_LDFLAGS = -L../chemostep -L../blitzchemostep -L../utils $(MPI_LIB) # $(QTLIBFLAGS) # -L$(BZDIR)/blitz/lib
# cachekineticannealtoy_LDADD =   -lblitzchemostep  -lchemostep -lutil -lmpich # -lm
#
# simpanneal_SOURCES = simpanneal.cpp 
# simpanneal_LDFLAGS = -L../chemostep -L../blitzchemostep # $(QTLIBFLAGS) # -L$(BZDIR)/blitz/lib
# simpanneal_LDADD =   -lblitzchemostep  -lchemostep # -lm


# blitztest_SOURCES = blitztest.cpp 
# blitztest_LDFLAGS = -L../chemostep -L../blitzchemostep # -L$(BZDIR)/blitz/lib 
# blitztest_LDADD =   -lblitzchemostep  -lchemostep  ${MPI_LIB} # -lMallocDebug 

# annealtest1_SOURCES = annealtest1.hpp annealtest1.cpp 
# annealtest1_LDFLAGS = -L../chemostep -L../blitzchemostep # -L$(BZDIR)/blitz/lib 
# annealtest1_LDADD =   -lblitzchemostep  -lchemostep  # ${MPI_LIB} # -lMallocDebug 
#
#
# toy1_SOURCES = toy1.hpp toy1.cpp 
# toy1_LDFLAGS = -L../chemostep -L../blitzchemostep # -L$(BZDIR)/blitz/lib 
# toy1_LDADD =   -lblitzchemostep  -lchemostep  # ${MPI_LIB} # -lMallocDebug 
#

# BUILT_SOURCES = $(qtrender_MOC) 
# CLEANFILES = $(BUILT_SOURCES) $(DESTDIR)/tree.app/Contents/MacOS/*

%.moc.cpp: %.h
	$(MOC) $< -o $@ 
	
%.class: %.java
	`which jikes` $< -o $@

