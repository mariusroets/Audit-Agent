BOOST_DIR=/data/boost_1_44_0
CC=g++
CFLAGS=-c -Wall -g
LDFLAGS=-static
LIBS=-lboost_program_options -lftp++
SOURCES=main.cpp daemon.cpp logfile.cpp infominer.cpp cpu.cpp util.cpp info.cpp os.cpp memory.cpp harddrive.cpp dmiparser.cpp system.cpp commandparser.cpp \
		software.cpp network.cpp
INCLUDE_DIRS=-I$(BOOST_DIR)
LIB_DIRS=-L$(BOOST_DIR)/stage/lib -L./ftplib
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=agent

all: $(SOURCES) $(EXECUTABLE)

clean:
	rm *.o $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(INCLUDE_DIRS) $(LIB_DIRS) $(OBJECTS) -o $@ $(LIBS)

.cpp.o:
	$(CC) $(INCLUDE_DIRS) $(CFLAGS) $< -o $@

