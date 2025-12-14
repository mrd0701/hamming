CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra

all: hamming

hamming: hamming.cpp
	$(CXX) $(CXXFLAGS) hamming.cpp -o hamming

clean:
	rm -f hamming
