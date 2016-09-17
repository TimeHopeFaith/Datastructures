all: driver.o Exceptions.o Util.o LinearProbing.o QuadraticProbing.o DoubleProbing.o Hash.o

	g++ -Wall driver.o Exceptions.o Util.o LinearProbing.o QuadraticProbing.o DoubleProbing.o Hash.o -o Driver.out

Exceptions.o: Exceptions.cpp
	g++ -Wall -c Exceptions.cpp

LinearProbing.o: LinearProbing.cpp
	g++ -Wall -c LinearProbing.cpp

QuadraticProbing.o: QuadraticProbing.cpp
	g++ -Wall -c QuadraticProbing.cpp 

DoubleProbing.o: DoubleProbing.cpp
	g++ -Wall -c DoubleProbing.cpp

Hash.o: Hash.cpp
	g++ -Wall -c Hash.cpp

Util.o: Util.cpp
	g++ -Wall -c Util.cpp

run:
	./Driver.out $(FILE) $(N) $(INTERVAL) $(M) $(R)
# -f removes any errors if the file is not present
clean:
	rm -rf *.o
	rm -f Driver.out
	rm -f *~ *.h.gch *#