# hello:	hello.cpp
# 	g++ -g -o hello hello.cpp

# clean:
# 	-rm hello

appname := CalculatorServer

CXX := g++
CXXFLAGS := -Wall -g

srcfiles := $(shell find . -maxdepth 3 -name "*.cpp")
objects  := $(patsubst %.cpp, %.o, $(srcfiles))

all: $(appname)

$(appname): $(objects)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(appname) $(objects) $(LDLIBS)


clean:
	rm -f $(objects)