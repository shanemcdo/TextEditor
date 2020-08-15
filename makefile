CC = g++
CFLAGS = -c -Wall
INCLUDE = -Iinclude
LIBS = 

all: main TextEditor
	$(CC) bin/*.o -o bin/test.exe $(INCLUDE) $(LIBS)
	@echo

%: src/%.cpp
	$(CC) $< $(CFLAGS) -o bin/$@.o $(INCLUDE) $(LIBS)

clean:
	rm bin/*

new:
	mkdir bin

test: all
	bin/test.exe
