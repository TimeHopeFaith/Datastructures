/**************************************************************
* File: Utility.h
* Author: James Guan
* Homework: CMSC 341 Project2, Fall 2014
* Version Date: 10/21/2014
* Class Section: 02
* E-mail: jguan3@umbc.edu
* Description:
*
* This is a class with static methods that will change all the character's 
* in a string from upcase to lowercase and vice versa.
*************************************************************/
#ifndef UTILITY_H
#define UTILITY_H
#include <string>

class Utility{

public:
	static std::string Upper(std::string word);
	static std::string Lower(std::string word);

	
};// end class definition


#endif