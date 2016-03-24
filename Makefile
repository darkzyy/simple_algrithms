CXX = g++
CXXFLAGS = -O2 -Wall

CFILES = $(shell find -name "*.cpp")
BINARY = $(CFILES:.cpp=.bin)


.PHONY: build clean

build: $(BINARY)

%.bin: %.cpp
	$(CXX) $< $(CXXFLAGS) -o $@

clean:
	rm $(BINARY) 2> /dev/null
