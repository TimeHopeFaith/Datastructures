/*****************************************
** File:    ThreeDimension.h
** Homework: CMSC 341 Homework1, Fall 2014
** Author:  James Guan
** Date:    9/12/14
** Section: 02
** E-mail:  jguan3.umbc.edu 
**
** This file contains the class definitions for the ThreeDimension class for Homework1.
** This represents a 3D point that will have an x, y, and z value stored as integers
** This file will inherit from TwoDimension and will have an extra z value.
** This file inherits:
** int x, int y
** getX(), getY()
** setX(), setY()
**
** Adds:
** int z;
** static voidDisplayPoints(ThreeDimension points[], int &length);
** static ThreeDimension* sameXYZ(ThreeDimension points[], int length);
** getZ(), setZ()
**
** Overloads:
** operator << for cout
** 
***********************************************/

// Header guards
#ifndef THREEDIMENSION_H
#define THREEDIMENSION_H

// Includes
#include "TwoDimension.h"
#include <iostream>

using namespace std;

// class ThreeDimension extends public TwoDimension
class ThreeDimension : public TwoDimension {
	
	// Variables
	private:
		int z; // z coordinate

	// Functions
	public:

		//**********Static functions************//

		//-------------------------------------------------------
		// Name: displayPoints
		// PreCondition: an array of ThreeDimension objects and the length of the array
		// PostCondition: This will display the ThreeDimensional objects in an array that was passed in using the overloaded cout function
		//---------------------------------------------------------
		static void displayPoints(ThreeDimension points[], int &length);
		
		//-------------------------------------------------------
		// Name: sameXYZ
		// PreCondition:  a ThreeDimension with the x == y == z
		// PostCondition: returns a pointer that points to the object that has x == y == z.
		//---------------------------------------------------------
		static ThreeDimension* sameXYZ(ThreeDimension points[], int length);



		//**********Constructors**************//
		
		//-------------------------------------------------------
		// Name: ThreeDimension()
		// PreCondition:  none
		// PostCondition: sets z to 5
		//---------------------------------------------------------
		ThreeDimension() : TwoDimension() {z = 5;}
		
		//-------------------------------------------------------
		// Name: ThreeDimension
		// PreCondition:  takes in any 3 int values
		// PostCondition: calls parent constructor with parameters i, and j, and then sets z to k
		//---------------------------------------------------------
		ThreeDimension(int i, int j, int k) : TwoDimension(i, j) {z = k;} // this is an initializer list

		//********** Destructor *************//

		//-------------------------------------------------------
		// Name: ~ThreeDimension()
		// PreCondition:  This is a destructor
		// PostCondition: deletes and sets things to NULL
		//---------------------------------------------------------
		~ThreeDimension();

		//*************** Member Functions **************************//

		// inline implementation of member functions
		// setters for ThreeDimension that changes the z value
		void setZ(int NewZ);
		// getters for ThreeDimension that returns the z value
		int getZ() const;
		
		// overides the << cout operator to print out specific data for ThreeDimension objects
		friend ostream &operator<< (ostream &os, const ThreeDimension &two);

};// end class definition for ThreeDimension
#endif