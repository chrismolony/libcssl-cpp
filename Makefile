all: test.o cssl.o
		g++ -o test test.o cssl.o

test.o: test.cpp cssl.h
		g++ -c test.cpp

cssl.o: cssl.cpp cssl.h
		g++ -c cssl.cpp

clean:
		rm -rf *.o test
