## -*- automake -*-

# lib_LIBRARIES = libautogui.a # mapper # qtoption qttree #htmloption htmltree
# libautogui_a_SOURCES= libautogui.a # mapper # qtoption qttree #htmloption htmltree


bin_PROGRAMS =  alopextest1 



if DOMPI
  MPI_OPT = -I${MPICH}/include -DDOMPI 
  MPI_LIB     = -L${MPICH}/lib
  MPI_ADD     = -lmpich 
endif



# define options
if MACOSX
  HOST_OPTION = 
  X11_OPTION = 
else
  X11_OPTION = -I/usr/X11R6/include
  QTLIBFLAGS =  -L${QTDIR}/lib 
endif

if QTMAC
    QTLIBFLAGS = -prebind -L${QTDIR}/lib 
    DESTDIR =../apps/rendertest.app/Contents/MacOS
    bindir =
else
	DESTDIR = ../
	bindir = bin 
endif 

QT_OPT = -pipe -I${QTDIR}/include
MISC_OPT = -Weffc++

INCLUDES=-D@platform@ ${HOST_OPTION} ${QT_OPT} ${X11_OPT}  ${MPI_OPT} -I../tinyxml -I../blitzchemostep -I../chemostep -I../tinyblitzchemostep -I../utils -I${BZDIR} ${MPI_OPT}




 alopextest1_SOURCES = alopextest1.hpp alopextest1.cpp 
 alopextest1_LDFLAGS = -L../chemostep -L../blitzchemostep -L../utils ${MPI_LIB} # -L$(BZDIR)/blitz/lib 
 alopextest1_LDADD =   -lblitzchemostep  -lchemostep  -lutil -lstdc++ ${MPI_ADD} # ${MPI_LIB} # -lMallocDebug 

%.moc.cpp: %.h
	$(MOC) $< -o $@ 
	
%.class: %.java
	`which jikes` $< -o $@

