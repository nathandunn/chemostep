## -*- automake -*-

# lib_LIBRARIES = libautogui.a # mapper # qtoption qttree #htmloption htmltree
# libautogui_a_SOURCES= libautogui.a # mapper # qtoption qttree #htmloption htmltree


bin_PROGRAMS = rendertest  appinterface xmltest 



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

AUTOGUILIBS=-L../autogui -L../tinyautogui -L../qtautogui -L../testclasses
TINYXMLLIBS=-L../tinyxml 
QT_OPT = -pipe -I${QTDIR}/include
MISC_OPT = -Weffc++

INCLUDES=-D@platform@ ${HOST_OPTION} ${QT_OPT} ${X11_OPT}  -DTIXML_USE_STL  -I../tinyxml -I../autogui -I../testclasses -I../qtautogui -I../tinyautogui

# if DOMPI
#   MPIOPT = -DMPION
# endif

rendertest_SOURCES = rendertest.hpp rendertest.cpp 
rendertest_LDFLAGS = $(QTLIBFLAGS) $(AUTOGUILIBS) $(TINYXMLLIBS) 
rendertest_LDADD =   -lqtrender -ltestclasses -ltinyauto -lautogui -ltinyxml -lqt-mt   # after target
# rendertest_DEPENDENCIES = ../renderer/librender.a  ../renderer/libautogui.a ../renderer/libtestclass.a    # after target

xmltest_SOURCES = xmltest.cpp 
xmltest_LDFLAGS = $(TINYXMLLIBS)
xmltest_LDADD = -ltinyxml  # after target
#xmltest_DEPENDENCIES = /libtinyxml.a # after target

appinterface_SOURCES = newappinterfacetest.cpp 
appinterface_LDFLAGS =  $(AUTOGUILIBS) $(TINYXMLLIBS) 
appinterface_LDADD =  -ltestclasses -ltinyauto -lautogui -ltinyxml  # after target
#appinterface_DEPENDENCIES = ../appinterface/libautogui.a ../testclasses/libtestclass.a ../tinyxml/libtinyxml.a # after target





BUILT_SOURCES = $(qtrender_MOC) 
CLEANFILES = $(BUILT_SOURCES) $(DESTDIR)/tree.app/Contents/MacOS/*

%.moc.cpp: %.h
	$(MOC) $< -o $@ 
	
%.class: %.java
	`which jikes` $< -o $@

