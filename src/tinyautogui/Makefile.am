## -*- automake -*-

lib_LIBRARIES = libtinyauto.a # mapper # qtoption qttree #htmloption htmltree


interface_headers= TiAppInterface.hpp TiAppParser.hpp TiListParser.hpp TinyAppInterfaceXmlEngine.hpp TiFlatBaseApp.hpp
interface_source= TiAppInterface.cpp TiAppParser.cpp TiListParser.cpp TinyAppInterfaceXmlEngine.cpp TiFlatBaseApp.cpp
interface = $(interface_headers) $(interface_source) 
#--------------------------



#--------------------------
libtinyauto_aincludedir=../autogui
libdir=../autogui
libtinyauto_ainclude_HEADERS=$(interface_headers) 
libtinyauto_a_SOURCES= $(interface) 

if MACOSX
  HOST_OPTION = 
#  X11_OPTION = 
else
#  X11_OPTION = -I/usr/X11R6/include
#  QTLIBFLAGS =  -L${QTDIR}/lib 
endif


MISC_OPT = -Weffc++

INCLUDES=-D@platform@ ${HOST_OPTION} -DTIXML_USE_STL -I../tinyxml -I../autogui
# INCLUDES=-I${AUTOGUI}/source -I${TINYXML}/source -D@platform@ ${HOST_OPTION} -DTIXML_USE_STL 

%.moc.cpp: %.h
	$(MOC) $< -o $@ 
	
%.class: %.java
	`which jikes` $< -o $@

