CXX=g++
CXXFLAGS=-std=c++2a -Wall -c
LXXFLAGS=-std=c++2a

OBJECTS=main.o VerilogtoCPP.o Gate.o Wire.o
TARGET=main

$(TARGET):$(OBJECTS)
	$(CXX) $(LXXFLAGS) $(OBJECTS) -o $(TARGET)
main.o: main.cpp VerilogtoCPP.h Gate.h Wire.h
	$(CXX) $(CXXFLAGS) main.cpp
VerilogtoCPP.o: VerilogtoCPP.cpp Gate.h Wire.h
	$(CXX) $(CXXFLAGS) VerilogtoCPP.cpp
Gate.o: Gate.cpp
	$(CXX) $(CXXFLAGS) Gate.cpp
Wire.o: Wire.cpp
	$(CXX) $(CXXFLAGS) Wire.cpp
clean:
	rm -f $(TARGET) $(OBJECTS)
