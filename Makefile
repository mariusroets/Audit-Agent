UNAME=$(shell uname)

#Defaults
CFLAGS=-c -Wall -g
BOOST_DIR=/data/boost_1_44_0
CC=g++
LIBS=-lftp++ -lgeneral

ifeq ($(UNAME), Darwin)
#Mac specific stuff
CFLAGS=-c -Wall -g -DNOLFS -arch i386 -arch ppc -arch ppc64 -arch x86_64
LDFLAGS=-arch i386 -arch ppc -arch ppc64 -arch x86_64
BOOST_DIR=../boost_1_44_0
endif
ifeq ($(UNAME), Linux)
#Linux specific stuff
endif
SOURCES=main.cpp daemon.cpp logfile.cpp infominer.cpp \
		cpu.cpp util.cpp info.cpp os.cpp memory.cpp harddrive.cpp \
		dmiparser.cpp system.cpp commandparser.cpp \
		software.cpp network.cpp commandlineparser.cpp \
		outputfile.cpp asset.cpp architecture.cpp \
		sysprofileparser.cpp linuxnetwork.cpp macnetwork.cpp \
		linuxos.cpp macos.cpp linuxmemory.cpp macmemory.cpp \
		linuxharddrive.cpp macharddrive.cpp linuxsystem.cpp \
		macsystem.cpp linuxsoftware.cpp macsoftware.cpp \
		linuxasset.cpp macasset.cpp linuxcpu.cpp maccpu.cpp \
		tinystr.cpp tinyxml.cpp tinyxmlerror.cpp tinyxmlparser.cpp

INCLUDE_DIRS=-I$(BOOST_DIR) -I./libgeneral
LIB_DIRS=-L./ftplib -L./libgeneral
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=agent

all: $(SOURCES) $(EXECUTABLE)

clean:
	rm *.o $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(INCLUDE_DIRS) $(LIB_DIRS) $(OBJECTS) -o $@ $(LIBS)

.cpp.o:
	$(CC) $(INCLUDE_DIRS) $(CFLAGS) $< -o $@

