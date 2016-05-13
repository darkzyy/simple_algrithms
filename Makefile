CXX = g++
CC = gcc
CXXFLAGS = -O2 -Wall -std=gnu++11 -Werror -I./inc
CFLAGS = -O2 -Wall -std=gnu11 -Werror -I./inc -m32

CXXFILES = $(shell find -name "*.cpp")
CFILES = $(shell find -name "*.c")
BINARY = $(CXXFILES:.cpp=.cppbin) $(CFILES:.c=.cbin) 


.PHONY: build clean

build: $(BINARY)

%.cppbin: %.cpp
	$(CXX) $< $(CXXFLAGS) -o $@

%.cbin: %.c
	$(CC) $< $(CFLAGS) -o $@

clean:
	rm $(BINARY) 2> /dev/null
