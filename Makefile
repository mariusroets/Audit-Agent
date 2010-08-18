CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.cpp daemon.cpp logfile.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=agent

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

