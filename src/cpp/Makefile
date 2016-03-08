# Leforditja a projektet
#	'allapot'  hozza tartozo main segitsegevel letrehoz egy tesztkornyezetet: teszt_allapot

INCLUDE = ../headers
OBJECTS = ../objects
BIN = ../bin

CC = g++
FLAGS = -I$(INCLUDE)

#	kiegeszitendo a tovabbi forrasfajlokkal
_OBJ = allapot.o allapot_main.o utils.o
OBJ = $(patsubst %,$(OBJECTS)/%,$(_OBJ))

_DEPS = allapot.h utils.h typedefs.h
DEPS = $(patsubst %,$(INCLUDE)/%,$(_DEPS))

OUT = szimulacio

#	reszmodulok forditasa
_OBJ_ALLAPOT = allapot.o allapot_main.o utils.o
OBJ_ALLAPOT = $(patsubst %,$(OBJECTS)/%,$(_OBJ_ALLAPOT))
_DEPS_ALLAPOT = allapot.h utils.h tpyedefs.h
DEPS_ALLAPOT = $(patsubst %,$(OBJECTS)/%,$(_DEPS_ALLAPOT))
OUT_ALLAPOT = teszt_allapot


$(OBJECTS)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(FLAGS)

all: $(OBJ)
	$(CC) -o $(BIN)/$(OUT) $^

allapot: $(OBJ_ALLAPOT)
	$(CC) -o $(BIN)/$(OUT_ALLAPOT) $^

clean:
	rm -f $(OBJ)