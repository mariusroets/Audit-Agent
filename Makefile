CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.cpp daemon.cpp logfile.cpp infominer.cpp cpu.cpp util.cpp info.cpp
INCLUDE_DIRS=-I=/data/boost_1_44_0
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=agent

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(INCLUDE_DIRS) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

