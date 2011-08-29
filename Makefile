UNAME=$(shell uname)
BOOST_DIR=/data/boost_1_44_0
CC=g++
ifeq ($(UNAME), Darwin)
CFLAGS=-c -Wall -g -DNOLFS
endif
ifeq ($(UNAME), Linux)
CFLAGS=-c -Wall -g
endif
LIBS=-lftp++
SOURCES=main.cpp daemon.cpp logfile.cpp infominer.cpp \
		cpu.cpp util.cpp info.cpp os.cpp memory.cpp harddrive.cpp \
		dmiparser.cpp system.cpp commandparser.cpp \
		software.cpp network.cpp commandlineparser.cpp
INCLUDE_DIRS=-I$(BOOST_DIR)
LIB_DIRS=-L./ftplib
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=agent

all: $(SOURCES) $(EXECUTABLE)

clean:
	rm *.o $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(INCLUDE_DIRS) $(LIB_DIRS) $(OBJECTS) -o $@ $(LIBS)

.cpp.o:
	$(CC) $(INCLUDE_DIRS) $(CFLAGS) $< -o $@

