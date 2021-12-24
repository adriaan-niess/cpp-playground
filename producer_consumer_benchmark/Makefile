CC=g++
CFLAGS=-c -std=c++17 -Wall -I./src -DBOOST_LOG_DYN_LINK
LDFLAGS=-lboost_log -lpthread -lcrypto -lssl
SOURCES=$(shell find src -name "*.cpp")
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=benchmark

DEBUG ?= 0
ifeq (DEBUG, 1)
	CFLAGS += -g3 -gdwarf2 -DDEBUG
else
	CFLAGS += -DNDEBUG
endif

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -rf $(EXECUTABLE) $(OBJECTS)
