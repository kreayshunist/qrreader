CC=g++
RM=rm

INCLUDE_FLAGS=-I/usr/local/include -I/usr/include/opencv -I/usr/include
CFLAGS=-c -Wall $(INCLUDE_FLAGS)
LDFLAGS=`pkg-config opencv --cflags --libs` `pkg-config zbar --cflags --libs`

SOURCES=main.cpp
OBJECTS=$(SOURCES:.cpp=.o)

EXECUTABLE=main

all : $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS) Makefile
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o :
	$(CC) $(CFLAGS) $< -o $@

clean : 
	$(RM) $(OBJECTS) $(EXECUTABLE)