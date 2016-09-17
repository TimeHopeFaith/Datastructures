/*****************************************
** File:    TwoDimension.cpp
** Homework: CMSC 341 Homework1, Fall 2014
** Author:  James Guan
** Date:    9/12/14
** Section: 02
** E-mail:  jguan3.umbc.edu 
**
** This file contains the code to make TwoDimension work.
** This class will hold an x, y value with integers
** This class will give the ability to modify the x, y.
**
** Overloads:
** operator << for cout
** 
***********************************************/

// header guards
#ifndef TWODIMENSION_CPP
#define TWODIMENSION_CPP

// includes
#include "TwoDimension.h"
#include <iostream>

// using standard library
using namespace std;

// destructor with nothing to destroy
TwoDimension::~TwoDimension()
{	
}// end destructor



// setX
// Given a new x, replaces the current x with new x
void TwoDimension::setX(int NewX){
	x = NewX;
}// end setX



// setY
// Given a new Y, replaces the current x with new Y
void TwoDimension::setY(int NewY){
	y = NewY;
}// end setY



// getX
// returns the x value
int TwoDimension::getX() const{
	return x;
}// end getX



// getY
// returns the y value
int TwoDimension::getY() const{
	return y;
}// end getY

// operator<< 
// overloads the cout operator to print something specific for this class
ostream &operator<<(ostream &os, const TwoDimension &two)
{
		// Whenever cout is called in this function, it will print the stuff below
		os << "This 2D point has the values of: " << endl
		<< "x: " << two.getX() << endl
		<< "y: " << two.getY() << endl
		<< "___" << endl;
		return os;
}// end operator<<

#endif