CC=g++

IDIR =../include
CFLAGS=-std=gnu++11
ODIR=obj

LIBS=-lsfml-graphics -lsfml-window -lsfml-system

_DEPS = hellomake.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

OBJ = main.o board.o sprite_manager.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $<  $(CFLAGS)

../bomBot: $(OBJ)
	$(CC) -o $@ $^ $(LIBS)  $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o 
