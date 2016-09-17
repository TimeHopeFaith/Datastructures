all: Driver.o Exceptions.o Utility.o dsexceptions.o BinarySearchTree.o Word.o WordBinarySearchTree.o Indexer.o

	g++ -Wall Driver.o Exceptions.o Utility.o dsexceptions.o BinarySearchTree.o Word.o WordBinarySearchTree.o Indexer.o -o Driver.out

Exceptions.o: Exceptions.cpp
	g++ -Wall -c Exceptions.cpp

Utility.o: Utility.cpp
	g++ -Wall -c Utility.cpp

dsexceptions.o: dsexceptions.cpp
	g++ -Wall -c dsexceptions.cpp

BinarySearchTree.o: BinarySearchTree.cpp
	g++ -Wall -c BinarySearchTree.cpp

Word.o: Word.cpp
	g++ -Wall -c Word.cpp

WordBinarySearchTree.o: WordBinarySearchTree.cpp
	g++ -Wall -c WordBinarySearchTree.cpp

Indexer.o: Indexer.cpp
	g++ -Wall -c Indexer.cpp

run:
	./Driver.out
# -f removes any errors if the file is not present
clean:
	rm -rf *.o
	rm -f Driver.out
	rm -f *~ *.h.gch *#