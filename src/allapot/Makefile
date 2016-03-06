# Leforditja az 'allapot' modult es a hozza tartozo main segitsegevel letrehoz egy tesztkornyezetet: teszt_allapot

CC = g++
OBJ = allapot.o main.o
OUT = teszt_allapot

%.o: %.c
	$(CC) -c -o $@

all: $(OBJ)
	$(CC) -o $(OUT) $^

clean:
	rm -f $(OBJ)