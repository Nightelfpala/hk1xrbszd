# Leforditja a projektet
#	'utils'		hozza tartozo main segitsegevel letrehoz egy tesztkornyezetet: teszt_utils
#	'allapot'	hozza tartozo main segitsegevel letrehoz egy tesztkornyezetet: teszt_allapot
#	'ui_parts'	hozza tartozo main segitsegevel letrehoz egy tesztkornyezetet: teszt_ui_vec
#	'elsoparse'	hozza tartozo main segitsegevel letrehoz egy tesztkornyezetet: teszt_elsoparse
#	'interpret'	hozza tartozo main segitsegevel letrehoz egy tesztkornyezetet: teszt_interpret

INCLUDE = ../headers
INCLUDE_ELSOPARSE = ../elsoparse
INCLUDE_INTERPRET = ../interpret
OBJECTS = ../objects
BIN = ../bin

#CC = x86_64-w64-mingw32-g++ -g -DwxDEBUG_LEVEL=0
#CC = x86_64-w64-mingw32-g++ -g -DwxDEBUG_LEVEL=0 -Wall -Wextra
CC = x86_64-w64-mingw32-g++
#MOC = moc.exe
FLAGS = -I$(INCLUDE) -I$(INCLUDE_ELSOPARSE) -I$(INCLUDE_INTERPRET)

#DEFINES		= -DUNICODE -DQT_DLL -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_THREAD_SUPPORT -DQT_NEEDS_QMAIN -DQT_SHARED
#DEFINES		= -DUNICODE -DQT_DLL -DQT_GUI_LIB -DQT_CORE_LIB -DQT_THREAD_SUPPORT -DQT_NEEDS_QMAIN -DQT_SHARED
#DEFINES		= -DUNICODE -DQT_DLL -DQT_GUI_LIB -DQT_CORE_LIB -DQT_NEEDS_QMAIN -DQT_SHARED
#DEFINES		= -DQT_DLL -DQT_GUI_LIB -DQT_CORE_LIB -DQT_NEEDS_QMAIN -DQT_SHARED
#DEFINES		= -DQT_GUI_LIB -DQT_CORE_LIB -DQT_NEEDS_QMAIN -DQT_SHARED
CXXFLAGS	= -pipe -O2 -frtti -fexceptions -mthreads $(DEFINES)
#CXXFLAGS	= -pipe -O2 -frtti -fexceptions $(DEFINES)
#CXXFLAGS	= -pipe -frtti -fexceptions $(DEFINES) -fno-stack-protector -DWXUSINGDLL
#MINGWSTATIC	= -static-libgcc -static-libstdc++
#QT_INCPATH	= -I'/usr/x86_64-w64-mingw32/sys-root/mingw/include/qt4/QtCore' -I'/usr/x86_64-w64-mingw32/sys-root/mingw/include/qt4/QtGui' -I'/usr/x86_64-w64-mingw32/sys-root/mingw/include/qt4' -I'/usr/x86_64-w64-mingw32/sys-root/mingw/include/qt4/ActiveQt' -I'release' -I'/usr/x86_64-w64-mingw32/sys-root/mingw/share/qt4/mkspecs/win32-g++'
#QT_LIBS	= -L'/usr/x86_64-w64-mingw32/sys-root/mingw/lib' -lmingw32 -lqtmain -lQtGui -lQtCore

WX_INC = -I/usr/x86_64-w64-mingw32/sys-root/mingw/include/wx-3.0 \
	-I/usr/x86_64-w64-mingw32/sys-root/mingw/lib/wx/include/x86_64-w64-mingw32-msw-unicode-3.0/

WX_LIB = -L/usr/x86_64-w64-mingw32/sys-root/mingw/lib \
	-lwx_baseu-3.0-x86_64-w64-mingw32 \
	-lwx_mswu_core-3.0-x86_64-w64-mingw32

#	---------------------------------------
#	
ELSOPARSE_HEADERS = elsoparseParser.h elsoparseParserbase.h
INTERPRET_HEADERS = interpretParser.h interpretParserbase.h
#	
ELSOPARSE_OBJECTS = elsoparseFlexer.o elsoparseParser.o
INTERPRET_OBJECTS = interpretFlexer.o interpretParser.o
#	kiegeszitendo a tovabbi objectfajlokkal
#_OBJ = allapot.o utils.o $(ELSOPARSE_OBJECTS) $(INTERPRET_OBJECTS) szimulacio.o szimulacio_main.o
_OBJ = $(INTERPRET_OBJECTS) $(ELSOPARSE_OBJECTS) allapot.o utils.o ui_main.o appmain.o ui_parts.o
OBJ = $(patsubst %,$(OBJECTS)/%,$(_OBJ))
#	teszteleshez hasznalt mainekbol keletkezo object fajlok
_MAINS_OBJ = allapot_main.o elsoparse.o utils_main.o ui_parts_main.o ui_parts_appmain.o interpret.o
MAINS_OBJ = $(patsubst %,$(OBJECTS)/%,$(_MAINS_OBJ))

_DEPS = allapot.h utils.h typedefs.h semantics.h FlexLexer.h ui_parts.h ui_main.h appmain.h
_DEPS_ELSOPARSE = elsoparseParser.h elsoparseParserbase.h
_DEPS_INTERPRET = interpretParser.h interpretParserbase.h
DEPS = $(patsubst %,$(INCLUDE)/%,$(_DEPS)) $(patsubst %,$(INCLUDE_ELSOPARSE)/%,$(_DEPS_ELSOPARSE)) $(patsubst %,$(INCLUDE_INTERPRET)/%,$(_DEPS_INTERPRET))

_OUT = szimulacio
OUT = $(patsubst %,$(BIN)/%,$(_OUT))

#	reszmodulok forditasa
#	teszt_utils:
_OBJ_UTILS = utils.o utils_main.o
OBJ_UTILS = $(patsubst %,$(OBJECTS)/%,$(_OBJ_UTILS))
_DEPS_UTILS = utils.h
DEPS_UTILS = $(patsubst %,$(INCLUDE)/%,$(_DEPS_UTILS))
_OUT_UTILS = teszt_utils
OUT_UTILS = $(patsubst %,$(BIN)/%,$(_OUT_UTILS))

#	teszt_allapot:
_OBJ_ALLAPOT = allapot.o allapot_main.o utils.o
OBJ_ALLAPOT = $(patsubst %,$(OBJECTS)/%,$(_OBJ_ALLAPOT))
_DEPS_ALLAPOT = allapot.h utils.h typedefs.h
DEPS_ALLAPOT = $(patsubst %,$(INCLUDE)/%,$(_DEPS_ALLAPOT))
_OUT_ALLAPOT = teszt_allapot
OUT_ALLAPOT = $(patsubst %,$(BIN)/%,$(_OUT_ALLAPOT))

#	teszt_elsoparse:
_OBJ_ELSOP = $(ELSOPARSE_OBJECTS) elsoparse.o utils.o
OBJ_ELSOP = $(patsubst %,$(OBJECTS)/%,$(_OBJ_ELSOP))
_DEPS_ELSOP = typedefs.h $(ELSOPARSE_HEADERS) semantics.h FlexLexer.h utils.h
DEPS_ELSOP = $(patsubst %,$(INCLUDE)/%,$(_DEPS_ELSOP))
_OUT_ELSOP = teszt_elsoparse
OUT_ELSOP = $(patsubst %,$(BIN)/%,$(_OUT_ELSOP))

#	teszt_interpret:
_OBJ_INTERP = $(INTERPRET_OBJECTS) $(ELSOPARSE_OBJECTS) allapot.o interpret.o utils.o
OBJ_INTERP = $(patsubst %,$(OBJECTS)/%,$(_OBJ_INTERP))
_DEPS_INTERP = typedefs.h $(INTERP_HEADERS) $(ELSOPARSE_HEADERS) allapot.h semantics.h typedefs.h FlexLexer.h utils.h
DEPS_INTERP = $(patsubst %,$(INCLUDE)/%,$(_DEPS_INTERP))
_OUT_INTERP = teszt_interpret
OUT_INTERP = $(patsubst %,$(BIN)/%,$(_OUT_INTERP))

#	teszt_ui_parts:
_OBJ_UI_VEC = ui_parts.o ui_parts_main.o ui_parts_appmain.o utils.o
OBJ_UI_VEC = $(patsubst %,$(OBJECTS)/%,$(_OBJ_UI_VEC))
_DEPS_UI_VEC = ui_parts.h ui_parts_main.h ui_parts_appmain.h typedefs.h
DEPS_UI_VEC = $(patsubst %,$(INCLUDE)/%,$(_DEPS_UI_VEC))
_OUT_UI_VEC = teszt_ui_parts
OUT_UI_VEC = $(patsubst %,$(BIN)/%,$(_OUT_UI_VEC))

#	#	teszt_ui_main:
#	_OBJ_UI_MAIN = allapot.o utils.o $(ELSOPARSE_OBJECTS) $(INTERPRET_OBJECTS) appmain.o ui_main.o appmain.o ui_parts.o
#	OBJ_UI_MAIN = $(patsubst %,$(OBJECTS)/%,$(_OBJ_UI_MAIN))
#	_DEPS_UI_MAIN = ui_parts.h ui_main.h appmain.h typedefs.h utils.h allapot.h $(ELSOPARSE_HEADERS) $(INTERPRET_HEADERS)
#	DEPS_UI_MAIN = $(patsubst %,$(INCLUDE)/%,$(_DEPS_UI_MAIN))
#	_OUT_UI_MAIN = teszt_ui_main
#	OUT_UI_MAIN = $(patsubst %,$(BIN)/%,$(_OUT_UI_MAIN))


all: $(OBJ)
	$(CC) -o $(OUT) $^ $(MINGWSTATIC) $(WX_LIB)

everything: all utils allapot elsoparse interpret ui_parts

$(OBJECTS)/interpretFlexer.o: ../interpret/interpret.yy.cc
	$(CC) -c -o $@ $< $(FLAGS)

$(OBJECTS)/interpretParser.o: ../interpret/interpret.cc
	$(CC) -c -o $@ $< $(FLAGS)

$(OBJECTS)/elsoparseFlexer.o: ../elsoparse/elsoparse.yy.cc
	$(CC) -c -o $@ $< $(FLAGS)

$(OBJECTS)/elsoparseParser.o: ../elsoparse/elsoparse.cc
	$(CC) -c -o $@ $< $(FLAGS)

$(OBJECTS)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(FLAGS) $(CXXFLAGS) $(WX_INC)
	
utils: $(OBJ_UTILS)
	$(CC) -o $(OUT_UTILS) $^ $(MINGWSTATIC)

allapot: $(OBJ_ALLAPOT)
	$(CC) -o $(OUT_ALLAPOT) $^ $(MINGWSTATIC)
	
ui_parts: $(OBJ_UI_VEC)
	$(CC) -o $(OUT_UI_VEC) $^ $(WX_LIB) $(MINGWSTATIC)

#ui_main: $(OBJ_UI_MAIN)
#	$(CC) -o $(OUT_UI_MAIN) $^ $(MINGWSTATIC) $(WX_LIB)

elsoparse: $(OBJ_ELSOP)
	$(CC) -o $(OUT_ELSOP) $^ $(MINGWSTATIC)

interpret: $(OBJ_INTERP)
	$(CC) -o $(OUT_INTERP) $^ $(FLAGS) $(MINGWSTATIC)

clean:
	rm -f $(OBJ) $(MAINS_OBJ)
	