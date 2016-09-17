/*****************************************
** File:    Driver.cpp
** Homework: CMSC 341 Homework1, Fall 2014
** Author:  James Guan
** Date:    9/12/14
** Section: 02
** E-mail:  jguan3.umbc.edu 
**
**   This file contains the main driver for Homework1.
** This program will:
**
** 1. Create a ThreeDimensional point called firstPt with x = 3, y = 4, z = 5.
**
** 2. Call the overloaded cout function in ThreeDimension.
**
** 3. Make an int of value 10 to make an array of ThreeDimension called points of size 10.
**
** 4. Calls the static method displayPoints to display the x, y, z data.
**
** 5. Calls sameXYZ to get the pointer of the object that has the same x, y, z values
**
** 6. Create an if and else statement to display the object with the same x, y, z, 
**		or print that there was no point found with those specs.
**
** 7. Deletes the array and then sets the pointers to NULL for proper garbage collection.
**
***********************************************/
// Header guards
#ifndef DRIVER_CPP
#define DRIVER_CPP

// Includes
#include "TwoDimension.h"
#include "ThreeDimension.h"
#include <iostream>
#include <stdlib.h> // for rand

using namespace std;

// main
int main()
{

	// Arbitrary variable for me to use to make my command prompt window to not close so fast on Windows.
	//int forWindows;
	
	// Instructions up to step 4 in the assignments
	ThreeDimension firstPt(3,4,5);
	std::cout << "firstPt:\n" << firstPt << endl;

	// variables
	int size = 10;
	ThreeDimension *points = new ThreeDimension[size];
	
	// for loop to change all the x, y, z variables to new random values in the array
	cout << "Creating array of ThreeDimensional points" << endl;
	for (int i = 0; i < size; i++){

		points[i].setX((rand() % 19) - 9);
		points[i].setY((rand() % 19) - 9);
		points[i].setZ((rand() % 19) - 9);

	}// end for

	// Used this to test the static sameXYZ function in the scenario that it finds a dimension with the same X, Y, Z
	//points[3].setX(8);
	//points[3].setY(8);
	//points[3].setZ(8);

	// Calling the functions 
	ThreeDimension::displayPoints(points,size);
	ThreeDimension *pointer = ThreeDimension::sameXYZ(points, size);

	// The if statement that prints the ThreeDimension with the same x, y, z that was found
	if (pointer != NULL)
		{cout << "Point with the same X, Y, & Z:\n" << *pointer << endl;	}
	
	// else statement to print the 404 point not found error
	else
		{cout << "point was not found with the same x, y, and z values" << endl;	}
	
	// Garbage collecting here: delete data and set pointers to NULL;
	pointer = NULL;
	delete [] points;
	points = NULL;

	// Had to use this to make my command prompt not close too quickly
	//cout << "Enter something to exit" << endl;
	//std::cin >> forWindows; 

	return 0;

}// end main
#endif