main: main.o data.o files.o
	gcc -o main main.o data.o files.o
main.o: main.c data.h files.h
	gcc -c main.c
data.o: data.c
	gcc -c data.c
files.o: files.c
	gcc -c files.c