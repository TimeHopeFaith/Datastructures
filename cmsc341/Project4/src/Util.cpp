/***************************************************************
* File: Util.cpp
* Author: James Guan
* Homework: CMSC 341 Project4, Fall 2014
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
#ifndef UTIL_CPP
#define UTIL_CPP

#include "Util.h"
#include "Exceptions.h"

#include <fstream>
#include <locale>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

/**
 * This will turn the characters in the string to lower case
 * and returns that new lowercase string
 */ 
std::string Util::Lower(std::string inString){
	std::string temp = "";
	std::locale loc;
	for(std::string::size_type i = 0; i < inString.length(); i++){
		temp = temp + std::tolower(inString[i],loc);
	}
	return temp;
}// end Lower

/**
 * This will remove the punctuations at the edges.
 * Yep... That's pretty much it.
 */
std::string Util::Strip(std::string inString){
	
       // Removes the punctuations on the left side
	while (ispunct(inString[0]) || inString[0] == ' '){
		inString = inString.substr (1, inString.length() - 1);
	}// end while

       
	if (inString.empty() == false){
  		// Removes the punctuations on the right side
		while (ispunct(inString[inString.length()-1]) || inString[inString.length()-1] == ' '){
			inString = inString.substr (0, inString.length() - 1);
						
		}// end while


	}// end if

	return inString;


}// end Strip

/**
 * RemoveInsidePunct will remove the punctuations inside the string.
 * Removes all of them except for - and '
 * Also removes numbers! 
 */
std::string Util::RemoveInsidePunct(std::string inString){

	std::string temp1 = "";

	bool secondPunct = false; // if dash or apostrophe has already been found

	// This will only allow one punctuation to be in the word so it would either be ' or -
	// allowed in the string
	for(std::string::size_type i = 0; i < inString.length(); i++){
		
		if((isdigit(inString[i]) == false && ispunct(inString[i]) == false && inString[i] != ' ') || inString[i] == '\'' || inString[i] == '-'){
		    if(secondPunct == false){
		      
		        temp1 = temp1 + inString[i];
			
			if (inString[i] == '-' || inString[i] == '\''){
			    secondPunct = true;
			}// end if
		    
		    }// end if
		    
		    else{

		        if(inString[i] != '-' && inString[i] != '\''){
			    temp1 = temp1 + inString[i];
		        }// endif

		    }// end else
		    
		}// end if
	}// end for

	return temp1;

}// end RemoveInsidePunct

/**
 * This checks if the file exists and if it does not, complains, and exits the program.
 */
bool Util::FileExists(const char* fileName){
	ifstream inFile;
	inFile.open(fileName);

	//if opening fails, it will exit the program
	if(inFile.fail()){
		throw Exceptions("Invalid file name.\nThe program will now close.");	
		exit(1);
	}// end if

	inFile.close();

	return true;

}// end FileExists

/**
 * Grabs only digits from the strings
 */
std::string Util::GrabDigits(std::string inString)
{
	
	std::string temp = "";

	for(std::string::size_type i = 0; i < inString.length(); i++){

		if (isdigit(inString[i]) == true){
			temp = temp + inString[i];
		}

	}
	
	return temp;

}// end GrabDigits

/**
 * Checks if the string contains only Digits
 */
bool Util::IsAllDigits(std::string inString)
{

	for(std::string::size_type i = 0; i < inString.length(); i++){

		if (isdigit(inString[i]) == false){
			cout << "This value is not a digit" << endl;
			return false;
		}// end if

	}// end for
	
	return true;
}// end IsAllDigits

#endif
