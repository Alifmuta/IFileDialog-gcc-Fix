all: main.o
	g++ main.o -luuid -lgdi32 -lole32 -o test.exe
	del main.o

main.o: main.cpp ifiledialog.h
	g++ -c main.cpp
