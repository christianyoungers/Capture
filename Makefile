CC = g++
FLAGS = -c
LIBS = -lSDLmain -lSDL -lGL -lglut
SOURCES = main.cpp block.cpp captureWorld.cpp players.cpp
HEADERS = block.h captureWorld.h players.h
GLOBALS = headers.h globals.h
OBJECTS = $(SOURCES:.cpp=.o)

all: Capture

Capture: $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBS) -o $@ 

main.o: main.cpp captureWorld.h $(GLOBALS)
	$(CC) $(FLAGS) main.cpp $(LIBS)

block.o: block.cpp block.h $(GLOBALS)
	$(CC) $(FLAGS) block.cpp $(LIBS)

captureWorld.o: captureWorld.cpp $(HEADERS) $(GLOBALS)
	$(CC) $(FLAGS) captureWorld.cpp $(LIBS)

players.o: players.cpp players.h $(GLOBALS)
	$(CC) $(FLAGS) players.cpp $(LIBS)

clean: 
	rm -rf *o *~ Capture