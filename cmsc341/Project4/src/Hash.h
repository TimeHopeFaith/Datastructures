/***************************************************************
* File: Hash.h
* Author: James Guan
* Homework: CMSC 341 Project4, Fall 2014
* Version Date: 11/18/2014
* Class Section: 02
* E-mail: jguan3@umbc.edu
* Description:
*
* NOTES: I am trying to make the TA's jobs easier by printing to the console some debugging data,
* 	and the tables after all the hashing into a file called table.txt. Hope this helps.
*	Also, I was going to make a Hash parent class with a child class that just overrides the 
*	insert function but I ran out of time. Sorry for all the repetitive code. Just know that 
*	the only thing different in all the probing classes is the findPos function and that the
* 	double probing part has an extra function called secondHash.
* 
* This is the Hash.h file that will call the linear, quadratic,
* and double probing classes/ functions to do those types of probes
* and then it will print their data in intervals based on what the user 
* has entered for the interval.
* 
// Hash class
// 
// CONSTRUCTION: 
// 1.	the name of a file which contains unique random integers separated by whitespace.
// 2.	N -- the total number of random integers to attempt to insert (e.g. 1000)
// 3.	INTERVAL -- the interval (number of attempted insertions) for reporting data (e.g. 200)
// 4.	M - the size of the hash table
// 5.	R - the largest prime less than M
// 
// ******************    ENUMS    ************************
//  enum Entry
// 	 FROM_FILE represents that the slot in the vector is valid and from a file
//	 EMPTY represents that the slot in the vector is EMPTY
//
// ******************PUBLIC OPERATIONS*********************
// void PrintValues( )	  --> Debug function that prints the data collected from file
// void LinearHash( ) 	  --> Function that uses linear probing and prints out the data
// void QuadraticHash( )  --> Function that uses quadratic probing and prints out the data
// void DoubleHash( )	  --> Function that uses double probing and prints out the data
// void ResetOutputFile( )--> Resets the output files results.txt and table.txt
*************************************************************/
#ifndef HASH_H
#define HASH_H

#include "Exceptions.h"
#include "Util.h"
#include "QuadraticProbing.h"
#include "LinearProbing.h"
#include "DoubleProbing.h"

#include <iostream>
#include <sstream>
#include <locale>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iomanip>

using namespace std;

class Hash
{

 public:
	

	enum Entry{ EMPTY , FROM_FILE };
	Hash(char *filename, char *num, char *numIntervals, char *size, char *prime);
	


	/**
	 * Pre-Condition: None
	 * Post-Condition: Prints the file input values, storedNumbers data,
	 * storedNumbers capacity, and other debugging data
	 */
	void PrintValues();
	


	/**
	 * Pre-Condition: A vector storedNumbers of valid data
	 * Post-Condition: Printed hash data into 
	 * 		results.txt
	 * 		and also a printing of the table in 
	 * 		table.txt
	 *		The 3 functions below have nearly identical code
	 */
	void LinearHash();
	void QuadraticHash();
	void DoubleHash();


	
	/**
	 * Pre-Condition: None
	 * Post-Condition: Clears the files to input new data into.
	 *		clears table.txt and results.txt 
	 * 		This is because I am appending to the files
	 *		so I can output to the file from different functions
	 *		without overwriting the previous write. 
	 *		
	 */
	void ResetOutputFile();
  
 private:
	// Struct for the vector of numbers from the input file
	// this is to help make sure junk data resulting from c++
	// vectors are not read.
	struct FileValues
	{
		int element;
		Entry info;
		
		FileValues( ) : element ( 0 ) , info ( EMPTY ) { }
		FileValues( int e, Entry i )
			: element( e ), info (i ) { }
	};
	
	// Member variables
	string fileName;
	int numInts;
	int interval;
	int tableSize;
	int largestPrime;
	vector <FileValues> storedNumbers;
	
	// Unused
	//vector <int> linearHashTable;
	//vector <int> quadraticHashTable;
	//vector <int> doubleHashTable;

	void ReadFromFile();
	void PrintHeading(const char *type);

};

#endif
