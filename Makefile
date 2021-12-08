test: main.o

	g++ main.o -luuid -lgdi32 -lole32 -o test.exe

main.o: main.cpp main.h

	g++ -c main.cpp
	

clean:

	del test.exe main.o
