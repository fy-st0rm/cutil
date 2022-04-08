
all:
	gcc -c cutil.c main.c
	gcc -o main cutil.o main.o
	rm *.o
	./main
