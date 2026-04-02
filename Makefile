app: main.o matrix.o vector.o gauss.o lu.o
	gcc -o app main.o matrix.o vector.o gauss.o lu.o -lm

test: test.o matrix.o vector.o gauss.o lu.o random.o
	gcc -o test test.o matrix.o vector.o gauss.o lu.o random.o -lm

main.o: main.c matrix.h vector.h gauss.h
	gcc -c main.c

matrix.o: matrix.c matrix.h
	gcc -c matrix.c

vector.o: vector.c vector.h
	gcc -c vector.c

gauss.o: gauss.c gauss.h
	gcc -c gauss.c

test.o: test.c matrix.h vector.h gauss.h lu.h generate_random.h
	gcc -c test.c

lu.o: lu.c lu.h
	gcc -c lu.c

random.o: generate_random.c generate_random.h
	gcc -c generate_random.c -o random.o

clear:
	rm -f *.o app test

run: app
	./app

testing: test
	./test