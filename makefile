main: main.o data.o files.o vagas.o
	gcc -o main main.o data.o files.o vagas.o
main.o: main.c data.h files.h vagas.h
	gcc -c main.c
data.o: data.c
	gcc -c data.c
files.o: files.c
	gcc -c files.c
vagas.o: vagas.c
	gcc -c vagas.c