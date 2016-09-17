all: Driver.o TwoDimension.o ThreeDimension.o

	g++ -Wall Driver.o TwoDimension.o ThreeDimension.o -o Driver.out

TwoDimension.o: TwoDimension.cpp
	g++ -Wall -c TwoDimension.cpp

ThreeDimension.o: ThreeDimension.cpp
	g++ -Wall -c  ThreeDimension.cpp

run:
	./Driver.out
# -f removes any errors if the file is not present
clean:
	rm -rf *.o
	rm -f Driver.out
	rm -f *~ *.h.gch *#