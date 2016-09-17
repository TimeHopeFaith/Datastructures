/**************************************************************
* File: Exceptions.h
* Author: James Guan
* Homework: CMSC 341 Project2, Fall 2014
* Version Date: 10/21/2014
* Class Section: 02
* E-mail: jguan3@umbc.edu
* Description:
*
* The Exceptions class is a user-made exception that prints out a
* user specified message.
* 
*************************************************************/

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <string>

using namespace std;

class Exceptions{

private:
	string message;
public:
	Exceptions(string m = "Horrible error. Something really broke.\nMeaning that you probably entered an invalid file name for either the filter or the data.") : message(m) {}
	string GetMessage() const throw() { return message;	}
};

#endif
