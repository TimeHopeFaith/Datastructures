all: driver.o Exceptions.o Util.o Dijkstras.o Graph.o

	g++ -Wall driver.o Exceptions.o Util.o Dijkstras.o Graph.o -o Driver.out

Exceptions.o: Exceptions.cpp
	g++ -Wall -c Exceptions.cpp

Util.o: Util.cpp
	g++ -Wall -c Util.cpp

Dijkstras.o: Dijkstras.cpp

	g++ -Wall -c Dijkstras.cpp

Graph.o: Graph.cpp
	g++ -Wall -c Graph.cpp

run:
	./Driver.out $(FILE)
# -f removes any errors if the file is not present
clean:
	rm -rf *.o
	rm -f Driver.out
	rm -f *~ *.h.gch *#