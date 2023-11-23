object = AES.o main.o

main: $(object)
	g++ -o main $(object)

main.o: main.cpp AES.h
	g++ -c main.cpp

AES.o: AES.cpp AES.h
	g++ -c AES.cpp

.PHONY: clean

clean:
	rm -f main $(object) 