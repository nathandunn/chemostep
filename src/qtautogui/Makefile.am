## -*- automake -*-

lib_LIBRARIES = libqtrender.a # mapper # qtoption qttree #htmloption htmltree

qtrender_headers= QtCommandButton.h QtOptionField.h  QtFlatRenderer.h QtIntField.h QtBoolField.h QtFileLoadField.h QtFileSaveField.h QtFileLoadList.h QtTypeField.h # QtRenderWidget.h # DO NOT INCLUDE THESE
qtrender_source = QtCommandButton.cpp QtOptionField.cpp QtFlatRenderer.cpp  QtIntField.cpp QtBoolField.cpp QtFileLoadField.cpp QtFileSaveField.cpp QtFileLoadList.cpp QtTypeField.cpp # QtRenderWidget.cpp # QtTreeRenderer.cpp
qtrender_MOC =  QtCommandButton.moc.cpp QtOptionField.moc.cpp QtFlatRenderer.moc.cpp QtIntField.moc.cpp QtBoolField.moc.cpp QtFileLoadField.moc.cpp QtFileSaveField.moc.cpp QtFileLoadList.moc.cpp QtTypeField.moc.cpp # QtRenderWidget.moc.cpp  

qtrender =  $(qtrender_source)  # $(qtrender_headers)

if POWER64LINUX
power4_headers= QtPower4Settings.hpp 
power4_source= QtPower4Settings.cpp 
else
power4_headers = 
power4_source = 
endif 

power4 =  $(power4_source)  $(power4_headers)
    
#--------------------------

if MACOSX
  HOST_OPTION = 
endif

X11_OPTION = -I/usr/X11R6/include
QTLIBFLAGS =  -L${QTDIR}/lib 

#--------------------------
libqtrender_aincludedir=../autogui ../tinyautogui
libqtrender_ainclude_HEADERS=$(qtrender_headers) $(power4_headers) 
libqtrender_a_SOURCES=  $(qtrender) $(power4) $(qtrender_MOC)
# libdir=../autogui


MOC = $(QTDIR)/bin/moc


MISC_OPT = -Weffc++

if DOX11
INCLUDES=-D@platform@ ${HOST_OPTION} -I../autogui -I../tinyautogui -I${QTDIR}/include/qt
else
INCLUDES=-D@platform@ ${HOST_OPTION} -I../autogui -I../tinyautogui -I${QTDIR}/include
endif

BUILT_SOURCES = $(qtrender_MOC) 
CLEANFILES = $(BUILT_SOURCES) 

%.moc.cpp: %.h
	$(MOC) $< -o $@ 
	
%.class: %.java
	`which jikes` $< -o $@

