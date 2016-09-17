/***************************************************************
* File: Exceptions.h
* Author: James Guan
* Homework: CMSC 341 Project4, Fall 2014
* Version Date: 10/21/2014
* Class Section: 02
* E-mail: jguan3@umbc.edu
* Description:
*
* The Exceptions class is a user-made exception that prints out a
* user specified message. This is carried over from Project 2. 
* 
*************************************************************/

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <string>

using namespace std;

class Exceptions{

private:
	string message; // error message variable
public:
	// default error message
	Exceptions() : message("Horrible error. Something really broke.\nMeaning that you probably entered an invalid file name for either the filter or the data.") {}
	
	// custom error message
 	Exceptions(string m) : message(m) {}

	// I think this throws the message when an error is thrown?
	string GetMessage() const throw() { return message;	}
};

#endif
