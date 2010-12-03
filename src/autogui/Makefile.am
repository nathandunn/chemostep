## -*- automake -*-
## (C) 2003 by Nathan Dunn, <ndunn@mac.com>
## $Id: Makefile.am,v 1.2 2003/10/24 21:10:28 ndunn Exp $

lib_LIBRARIES = libautogui.a 

interface_headers= Interface.hpp Type.hpp Command.hpp Option.hpp InterfaceTypes.hpp InterfaceXmlString.hpp CommandArgumentField.hpp NameHandler.hpp AppInterface.hpp  
interface_source= Interface.cpp Type.cpp Command.cpp Option.cpp InterfaceTypes.cpp InterfaceXmlString.cpp CommandArgumentField.cpp NameHandler.cpp AppInterface.cpp   
xml_engine_headers = AppInterfaceXmlEngine.hpp AppParser.hpp 
xml_engine_source =  
renderer_headers = Renderer.hpp TreeRenderer.hpp FlatRenderer.hpp OptionField.hpp TransmitterApp.hpp ClickableObject.hpp CommandButton.hpp CommandActor.hpp 
renderer_source = Renderer.cpp TreeRenderer.cpp FlatRenderer.cpp  
text_headers = StringTokenizer.hpp 
text_source = StringTokenizer.cpp 
interface = $(interface_headers) $(interface_source) $(xml_engine_headers) $(xml_engine_source)  $(renderer_headers) $(renderer_source) # $(text_headers) $(text_source) 
#--------------------------
# if HASAUTOGUI
#     AUTOGUI=/usr/local/autogui
# endif
libautogui_aincludedir=../autogui ../utils
libautogui_ainclude_HEADERS=$(interface_headers) $(xml_engine_headers) $(renderer_headers) # $(text_headers)
libautogui_a_SOURCES= $(interface) 
# libautogui_a_LIBADD =  -lutils # after target
libautogui_a_LIBADD =  ../utils/libutil.a

if MACOSX
  HOST_OPTION = 
endif

# DESTDIR = ../../libs
# bindir = .

MISC_OPT = -Weffc++


QT_OPT = -pipe -I${QTDIR}/include

INCLUDES = -I.. -D@platform@ ${MPIOPT} ${HOST_OPTION} ${QT_OPT} 

	
%.class: %.java
	`which jikes` $< -o $@

