# Leforditja a projektet
#	'allapot'	hozza tartozo main segitsegevel letrehoz egy tesztkornyezetet: teszt_allapot
#	'ui_vec'	hozza tartozo main segitsegevel letrehoz egy tesztkornyezetet: teszt_ui_vec
#	'elsoparse'	hozza tartozo main segitsegevel letrehoz egy tesztkornyezetet: teszt_elsoparse

INCLUDE = ../headers
INCLUDE_ELSOPARSE = ../elsoparse
OBJECTS = ../objects
BIN = ../bin

CC = x86_64-w64-mingw32-g++
#CC = g++
FLAGS = -I$(INCLUDE) -I$(INCLUDE_ELSOPARSE)

DEFINES		= -DUNICODE -DQT_DLL -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_THREAD_SUPPORT -DQT_NEEDS_QMAIN -DQT_SHARED
CXXFLAGS	= -pipe -O2 -frtti -fexceptions -mthreads $(DEFINES)
MINGWSTATIC	= -static-libgcc -static-libstdc++
QT_INCPATH	= -I'/usr/x86_64-w64-mingw32/sys-root/mingw/include/qt4/QtCore' -I'/usr/x86_64-w64-mingw32/sys-root/mingw/include/qt4/QtGui' -I'/usr/x86_64-w64-mingw32/sys-root/mingw/include/qt4' -I'/usr/x86_64-w64-mingw32/sys-root/mingw/include/qt4/ActiveQt' -I'release' -I'/usr/x86_64-w64-mingw32/sys-root/mingw/share/qt4/mkspecs/win32-g++'
QT_LIBS	= -L'/usr/x86_64-w64-mingw32/sys-root/mingw/lib' -lmingw32 -lqtmain -lQtGui -lQtCore

#	kiegeszitendo a tovabbi forrasfajlokkal
_OBJ = allapot.o utils.o ui.o elsoparseFlexer.o elsoparseParser.o
OBJ = $(patsubst %,$(OBJECTS)/%,$(_OBJ))
_MAINS_OBJ = allapot_main.o ui_vec_main.o elsoparse.o
MAINS_OBJ = $(patsubst %,$(OBJECTS)/%,$(_MAINS_OBJ))

_DEPS = allapot.h utils.h typedefs.h ui.h semantics.h FlexLexer.h
_DEPS_ELSOPARSE = elsoparseParser.h elsoparseParserbase.h
DEPS = $(patsubst %,$(INCLUDE)/%,$(_DEPS)) $(patsubst %,$(INCLUDE_ELSOPARSE)/%,$(_DEPS_ELSOPARSE))

_OUT = szimulacio
OUT = $(patsubst %,$(BIN)/%,$(_OUT))

#	reszmodulok forditasa
#	teszt_allapot:
_OBJ_ALLAPOT = allapot.o allapot_main.o utils.o
OBJ_ALLAPOT = $(patsubst %,$(OBJECTS)/%,$(_OBJ_ALLAPOT))
_DEPS_ALLAPOT = allapot.h utils.h typedefs.h
DEPS_ALLAPOT = $(patsubst %,$(INCLUDE)/%,$(_DEPS_ALLAPOT))
_OUT_ALLAPOT = teszt_allapot
OUT_ALLAPOT = $(patsubst %,$(BIN)/%,$(_OUT_ALLAPOT))

#	teszt_ui_vec:
_OBJ_UI_VEC = ui.o ui_vec_main.o
OBJ_UI_VEC = $(patsubst %,$(OBJECTS)/%,$(_OBJ_UI_VEC))
_DEPS_UI_VEC = ui.h typedefs.h
DEPS_UI_VEC = $(patsubst %,$(INCLUDE)/%,$(_DEPS_UI_VEC))
_OUT_UI_VEC = teszt_ui_vec
OUT_UI_VEC = $(patsubst %,$(BIN)/%,$(_OUT_UI_VEC))

#	teszt_elsoparse:
_OBJ_ELSOP = elsoparseFlexer.o elsoparseParser.o elsoparse.o utils.o
OBJ_ELSOP = $(patsubst %,$(OBJECTS)/%,$(_OBJ_ELSOP))
_DEPS_ELSOP = typedefs.h elsoparseParser.h elsoparseParserbase.h semantics.h FlexLexer.h utils.h
DEPS_ELSOP = $(patsubst %,$(INCLUDE)/%,$(_DEPS_ELSOP))
_OUT_ELSOP = teszt_elsoparse
OUT_ELSOP = $(patsubst %,$(BIN)/%,$(_OUT_ELSOP))


$(OBJECTS)/elsoparseFlexer.o: ../elsoparse/elsoparse.yy.cc
	$(CC) -c -o $@ $< $(FLAGS)

$(OBJECTS)/elsoparseParser.o: ../elsoparse/elsoparse.cc
	$(CC) -c -o $@ $< $(FLAGS)

$(OBJECTS)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(FLAGS) $(CXXFLAGS) $(QT_INCPATH)

all: $(OBJ)
	$(CC) -o $(OUT) $^ $(QT_INCPATH) $(QT_LIBS) $(MINGWSTATIC)

allapot: $(OBJ_ALLAPOT)
	$(CC) -o $(OUT_ALLAPOT) $^ $(MINGWSTATIC)
	
ui_vec: $(OBJ_UI_VEC)
	$(CC) -o $(OUT_UI_VEC) $^ $(QT_INCPATH) $(QT_LIBS)

elsoparse: $(OBJ_ELSOP)
	$(CC) -o $(OUT_ELSOP) $^

clean:
	rm -f $(OBJ) $(MAINS_OBJ)