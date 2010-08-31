CC=g++
CFLAGS=-c -Wall -g
LDFLAGS=
SOURCES=main.cpp daemon.cpp logfile.cpp infominer.cpp cpu.cpp util.cpp info.cpp os.cpp memory.cpp harddrive.cpp dmiparser.cpp system.cpp commandparser.cpp \
		software.cpp network.cpp
INCLUDE_DIRS=-I=/data/boost_1_44_0
LIB_DIRS=-L=/data/boost_1_44_0/stage/lib
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=agent

all: $(SOURCES) $(EXECUTABLE)

clean:
	rm *.o $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(INCLUDE_DIRS) $(LDFLAGS) $(LIB_DIRS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(INCLUDE_DIRS) $(CFLAGS) $< -o $@

