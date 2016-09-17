all: driver.o Exceptions.o Util.o dsexceptions.o Node.o SplayTree.o HashedSplays.o

	g++ -Wall driver.o Exceptions.o Util.o dsexceptions.o Node.o SplayTree.o HashedSplays.o -o driver.out

Exceptions.o: Exceptions.cpp
	g++ -Wall -c Exceptions.cpp

Util.o: Util.cpp
	g++ -Wall -c Util.cpp

dsexceptions.o: dsexceptions.cpp
	g++ -Wall -c dsexceptions.cpp

Node.o: Node.cpp
	g++ -Wall -c Node.cpp

SplayTree.o: SplayTree.cpp
	g++ -Wall -c SplayTree.cpp

HashedSplays.o: HashedSplays.cpp
	g++ -Wall -c HashedSplays.cpp

run:
	./driver.out $(DATA)
# -f removes any errors if the file is not present
clean:
	rm -rf *.o
	rm -f driver.out
	rm -f *~ *.h.gch *#