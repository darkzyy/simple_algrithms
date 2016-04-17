CXX = g++
CXXFLAGS = -O2 -Wall -std=gnu++11 -Werror -I./inc -g

CFILES = $(shell find -name "*.cpp")
BINARY = $(CFILES:.cpp=.bin)


.PHONY: build clean

build: $(BINARY)

%.bin: %.cpp
	$(CXX) $< $(CXXFLAGS) -o $@

clean:
	rm $(BINARY) 2> /dev/null
