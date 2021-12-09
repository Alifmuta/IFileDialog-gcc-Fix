all: main.o

	g++ main.o -luuid -lgdi32 -lole32 -o test.exe

main.o: main.cpp ifiledialog.h

	g++ -c main.cpp
	

clean:

	del test.exe main.o
