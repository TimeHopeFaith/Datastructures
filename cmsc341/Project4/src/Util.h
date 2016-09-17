/***************************************************************
* File: Util.h
* Author: James Guan
* Homework: CMSC 341 Project3, Fall 2014
* Version Date: 10/31/2014
* Class Section: 02
* E-mail: jguan3@umbc.edu
* Description:
*
* This is a class with static methods that will change all the character's 
* in a string from upcase to lowercase, removes punctuations, and check if the file exists.
*
// ******************PUBLIC OPERATIONS*********************
// static string Lower(string inString) --> Turns all char in string to lower case
// static string Strip(string inString) --> Removes all punctuations from the outer edges
// static string RemoveInsidePunct(string inString) --> Removes all punctuations from inside the string
// 								Except for '\'' and '-'
// static string FileExists(char *fileName) --> Attempts to open the file to see if it exists
//						      Throws error message if fails
// static string GrabDigits(string inString) --> Returns only digits from the string
// bool IsAllDigits(string inString) --> Returns true if the string only contains digits
*************************************************************/
#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <ostream>
#include <fstream>


class Util{

public:
       /**
        * I hate commenting. I have to literally repeat myself. Someone needs to e-mail me
	 * and tell me if I'm overdoing the comments or not. Please. SAVE ME. It's Halloween
        * and my comments are literally a lot more scary than the people outside.
        * Pre-Condition: Just takes in a string
        * Post-Condition: Returns a string of lowercase letters
        */
	static std::string Lower(std::string inString);
	
	 /**
        * Pre-Condition: Just takes in a string
        * Post-Condition: Returns a string with the punctuations at the end trimmed off
        */
	static std::string Strip(std::string inString);

        /**
        * Pre-Condition: Just takes in a string
        * Post-Condition: Returns a string with the punctuations inside the string cut off
        * 			and also removes the numbers.
        */
	static std::string RemoveInsidePunct(std::string inString);

    	/** 
	 * Pre-Condition: A file name
        * Post-Condition: Returns true if it exists, otherwise exit the program and complain.
	 */
	static bool FileExists(const char* fileName);

	/**
	 * Pre-Condition: A string
	 * Post-Condition: Returns a string of all digits
	 */
	static std::string GrabDigits(std::string inString);
	
	/**
 	 * Pre-Condition: A string 
	 * Post-Condition: Returns true if the string contains only digits
	 */
	static bool IsAllDigits(std::string inString);

};// end class definition

#endif