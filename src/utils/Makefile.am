## -*- automake -*-
## FILE: "/Users/nathandunn/svn/chemotrunk/src/utils/Makefile.am"
## LAST MODIFICATION: "Fri, 19 May 2006 14:28:38 -0700 (nathandunn)"
## (C) 2003 by Nathan Dunn, <ndunn@mac.com>
## $Id: Makefile.am,v 1.2 2003/10/24 21:10:28 ndunn Exp $

lib_LIBRARIES = libutil.a 
# bin_PROGRAMS = testautooption autooptionrenderer
bin_PROGRAMS = testautooption # autooptionrenderer

if DOX11
QT_OPT = -pipe -I${QTDIR}/include/qt
else
QT_OPT = -pipe -I${QTDIR}/include
endif
MISC_OPT = -Weffc++


# autooption_headers = AutoOptionList.hpp GuiStub.hpp GeneralType.hpp IntType.hpp DoubleType.hpp FlagType.hpp OptionType.hpp CharType.hpp
# autooption_source = AutoOptionList.cpp GuiStub.cpp GeneralType.cpp IntType.cpp DoubleType.cpp FlagType.cpp OptionType.cpp CharType.cpp

# util_headers=StringTokenizer.hpp OptionList.hpp RNG.hpp XmlFileTokenizer.hpp $(autooption_headers)
# util_source=StringTokenizer.cpp OptionList.cpp RNG.cpp  XmlFileTokenizer.cpp $(autooption_source)
util_headers=StringTokenizer.hpp OptionList.hpp RNG.hpp XmlFileTokenizer.hpp 
util_source=StringTokenizer.cpp OptionList.cpp RNG.cpp  XmlFileTokenizer.cpp 
util=$(util_headers) $(util_source) 

#--------------------------
# if HASAUTOGUI
#     AUTOGUI=/usr/local/autogui
# endif
libutil_aincludedir=${prefix}/include/chemostep
libutil_ainclude_HEADERS=$(util_headers) 
libutil_a_SOURCES=$(util) 


testautooption_headers = TestAutoOption.hpp
testautooption_source= maintestautooption.cpp TestAutoOption.cpp
testautooption_SOURCES =  $(testautooption_source) 
testautooption_LDFLAGS = -L../utils -L../tinyxml
testautooption_LDADD =   -ltinyxml -lutil -lautooption # -lMallocDebug # after target

# autooptionrenderer_headers = AutoOptionRenderer.hpp
# autooptionrenderer_source= AutoOptionRenderer.cpp
# autooptionrenderer_SOURCES =  $(autooptionrenderer_source) 
# autooptionrenderer_LDFLAGS = -L../utils -L../tinyxml -L${QTDIR}/lib 
# autooptionrenderer_LDADD =   -ltinyxml -lutil  -lqt-mt # -lMallocDebug # after target


if MACOSX
  HOST_OPTION = 
endif

# DESTDIR = ../../libs
# bindir = .



INCLUDES = -I.. -D@platform@ ${MPIOPT} ${HOST_OPTION} 

	
%.class: %.java
	`which jikes` $< -o $@

