CC=g++
CFLAGS=-c -Wall -g
LDFLAGS=
SOURCES=main.cpp daemon.cpp logfile.cpp infominer.cpp cpu.cpp util.cpp info.cpp os.cpp memory.cpp
INCLUDE_DIRS=-I=/data/boost_1_44_0
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=agent

all: $(SOURCES) $(EXECUTABLE)

clean:
	rm *.o $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(INCLUDE_DIRS) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(INCLUDE_DIRS) $(CFLAGS) $< -o $@

