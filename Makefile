app: main.o matrix.o vector.o gauss.o
	gcc -o app main.o matrix.o vector.o gauss.o -lm

main.o: main.c matrix.h vector.h gauss.h
	gcc -c main.c

matrix.o: matrix.c matrix.h
	gcc -c matrix.c

vector.o: vector.c vector.h
	gcc -c vector.c

gauss.o: gauss.c gauss.h
	gcc -c gauss.c

clear:
	rm -f *.o app

run: app
	./app