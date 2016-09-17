/*****************************************
** File:    ThreeDimension.cpp
** Homework: CMSC 341 Homework1, Fall 2014
** Author:  James Guan
** Date:    9/12/14
** Section: 02
** E-mail:  jguan3.umbc.edu 
**
** This file contains the code to make ThreeDimension work.
** This class will use the parent class for x and y.
** This class will hold the z value with an integers.
** This class will give the ability to modify the z.
**
** There is a static method that will be called to cout an array of ThreeDimension objects
** There is a static method that will return a pointer pointing to the ThreeDimension that has x == y == z, within an array.
** 
** Overloads:
** operator << for cout
** 
***********************************************/

// head guards
#ifndef THREEDIMENSION_CPP
#define THREEDIMENSION_CPP

// includes
#include "ThreeDimension.h"
#include <iostream>

// namespace
using namespace std;



// displayPoints
// Takes in an array of ThreeDimensions and its length
// Then it will call cout on each function to display the data
void ThreeDimension::displayPoints(ThreeDimension dimensions[], int &length){
	for (int i = 0; i < length; i++){
		cout << dimensions[i] << endl;
	}// end for
}// end displayPoints



// sameXYZ
// Takes in an array of ThreeDimensions and its length
// Does a linear search of the array to find the object with x == y == z
// Points the pointer to that object and return that pointer
ThreeDimension* ThreeDimension::sameXYZ(ThreeDimension points[], int length){
	// temporary pointer
	ThreeDimension* pointer = NULL;

	// for loop to linearly search the array for that object with x == y == z
	for (int i = 0; i < length; i++){

		// if it is found, point the pointer to it and return it
		if (points[i].getX() == points[i].getY() && points[i].getX() == points[i].getZ()){
			pointer = &points[i];
			
			cout << *pointer << endl;

			return pointer;
		}// end if
	}// end for
	return pointer; // returns a pointer that points to NULL if one is not found
}// end sameXYZ

// destructor
ThreeDimension::~ThreeDimension(){
	
}// end destructor

// setZ
// this is a setter for z
void ThreeDimension::setZ(int NewZ){
	z = NewZ;
}// end setZ

// getZ
// this is a getter for z
int ThreeDimension::getZ() const{
	return z;
}// end getZ

// operator<<
// This overloads the cout to print the x, y, and z values
ostream &operator<<(ostream &os, const ThreeDimension &three)
{
		os << "This 3D point has the values of: " << endl
		<< "x: " << three.getX() << endl
		<< "y: " << three.getY() << endl
		<< "z: " << three.getZ() << endl
		<< "___" << endl;
		return os;
}// end operator<<

#endif