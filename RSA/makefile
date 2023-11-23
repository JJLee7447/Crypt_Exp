objects = main.o RSA.o

main : $(objects)
	g++ -o main $(objects)

main.o : main.cpp RSA.h
	g++ -c main.cpp
RSA.o : RSA.cpp RSA.h
	g++ -c RSA.cpp