CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11
LDFLAGS =

objects = main.o RC4.o

main: $(objects)
	$(CXX) $(LDFLAGS) -o main $(objects)

main.o: main.cpp RC4.h
	$(CXX) $(CXXFLAGS) -c main.cpp

rc4.o: RC4.cpp RC4.h
	$(CXX) $(CXXFLAGS) -c RC4.cpp

clean:
	rm -f main $(objects)
