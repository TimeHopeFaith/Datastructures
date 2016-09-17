/**************************************************************
* File: Indexer.h
* Author: James Guan
* Homework: CMSC 341 Project2, Fall 2014
* Version Date: 10/21/2014
* Class Section: 02
* E-mail: jguan3@umbc.edu
* Description:
*
* The Indexer class is where most of the actual work is done in the project. 
* These are the design goals should be met:
	1) Has a constructor that: 
		a)	allow passing in the file names that it will be working with and doing the validation needed.
		b)	Does all other initialization for the object.
	2) A method DoIndex() that will build the BSTs and show the proper output.  
	   This method does not directly do the work but it does so using other methods defined.
		a)	Build the filteredBST.
		b)	Build the indexedBST.
		c)	Output the results.

*
*************************************************************/

#ifndef INDEXER_H
#define INDEXER_H

#include "BinarySearchTree.h"
#include "WordBinarySearchTree.h"
#include "dsexceptions.h"
#include "Utility.h"
#include "Word.h"
#include "Exceptions.h"

#include <locale>
#include <fstream>
#include <string>

using namespace std;

class Indexer{

private:
  BinarySearchTree<Word> filteredBST; 
  BinarySearchTree<Word> indexedBST;
  string datafile;
  string filterfile;

public:
        // Constructor that takes in a file that carries a list of filter words
        // and it will take a dataFile
        Indexer (string & filterFile, string & dataFile);
	
	// Destructor
	~Indexer();
	
	///////////////////////////////////////////////////////////////////////////
	// FileExists
	// Pre-Condition: The name of the file
	// Post-Condition: Returns true if the file is found, else throw an error,
	//              and exit.
	// Method that will return true if the file exists
	bool FileExists (const char * filename) const;

	///////////////////////////////////////////////////////////////////////////
	// DoIndex that will call the associated methods
	// Pre-Condition: None
	// Post-Condition: Calls FileFilterReader and FileWordReader to store data into the BST
	//              and then call OutputResults to output the results
	void DoIndex();

	///////////////////////////////////////////////////////////////////////////
	// This will take in the file name that it will open to store the filter words
	// Pre-Condition: Takes in the file name of the filter file. 
	// Post-Condition: Returns an ordered BST of Filtered Words.
	BinarySearchTree<Word> FileFilterReader(string & filename);
	
	///////////////////////////////////////////////////////////////////////////
	// This will take in the file name of data and it will store it in a BST,
	// Pre-Condition: The file name of the data that needs to be indexed
	// Post-Condition: Returns an ordered BST of indexed words with the filter words removed.
	// It does so by 
	// first checking if it is filtered or not before it will put itself in a BST.
	BinarySearchTree<Word> FileWordReader(string & filename);
	
	// This method outputs the results
	// Pre-Condition: A filled out BST.
	// Post-Condition: A nicely outputted to a file index of stuff.
	void OutputResults();

};

#endif
