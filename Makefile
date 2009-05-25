CFLAGS=-Wall -std=c99

OBJECTS=structure.o
OBJECTS_PRODUCTION= $(OBJECTS) main.o 
OBJECTS_TEST=$(OBJECTS) test_structure.o

mosaico: tetris.o start.o
	gcc $(CFLAGS) tetris.o start.o -o go.o
	./go.o
	
test:  tetris.o
		gcc $(CFLAGS) tetris.o test.c cgreen/cgreen.a -o test.o
		./test.o


	
	
clean:
	rm -rf *.o
