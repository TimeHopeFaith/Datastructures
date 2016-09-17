/*****************************************
** File:    TwoDimension.h
** Homework: CMSC 341 Homework1, Fall 2014
** Author:  James Guan
** Date:    9/12/14
** Section: 02
** E-mail:  jguan3.umbc.edu 
**
** This file contains the class definitions for the TwoDimension class for Homework1.
** This class will hold an x, y value with integers
** This class will give the ability to modify the x, y.
**
** Overloads:
** operator << for cout
** 
***********************************************/

// header guards
#ifndef TWODIMENSION_H
#define TWODIMENSION_H

// includes
#include <iostream>

// using standard library
using namespace std;

// class
class TwoDimension
{
	// variables
	private:
   		int x, y; // x and y  coordinates

	public: 
		//********** Constructor *************//

		//inline implementations of a constructor
		TwoDimension(){x = 3, y = 4;}
		TwoDimension(int i, int j):x(i), y(j){} // this is an initializer list
		~TwoDimension();// this is a destructor

		// getters and setters, do I have to say more? (Legit question)
		void setX(int NewX);
		void setY(int NewY);
		int getX() const;
		int getY() const;

		// overides the << cout operator to print out specific data for TwoDimension objects
		friend ostream &operator<< (ostream &os, const TwoDimension &two);
};// end class definition for TwoDimension
#endif