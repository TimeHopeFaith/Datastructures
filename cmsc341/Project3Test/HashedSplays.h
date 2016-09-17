/**************************************************************
* File: HashedSplays.h
* Author: James Guan
* Homework: CMSC 341 Project3, Fall 2014
* Version Date: 11/4/2014
* Class Section: 02
* E-mail: jguan3@umbc.edu
* Description:
*
// ******************PUBLIC OPERATIONS*********************
//	HashedSplays();		--> Default constructor that sets the
//					array of SplayTrees to ALPHABET_SIZE of 26
//
//	HashedSplays(int size);	--> Sets the array size to the parameter
//
//	~HashedSplays();		--> Destructor to clean up my messy pointers
//
//	void FileReader(string inFileName); --> Takes in a file and fills the splay tree
//						with the words from the file after trimming them
//						of their punctuations.
//
//	void HandleInsertion(string line, int tableIndex); --> This right here is called in FileReader
//						and this will insert the words into the proper Splay Tree in table
//
//	void PrintHashCountResults(); --> Prints the first Node of each splay tree 
//					in table and prints the number of Nodes in the splay tree
//					NOTE: Lupoli named this differently in 
// 					the UML diagram (PrintHashCounts) and the driver.cpp... I am so confused. What do I follow?
//					do I follow the driver.cpp or the UML? I decided to follow the driver.cpp
//					Lupoli a great teacher though. I just got confused, that's all.
//
//	void PrintTree(int index); --> Prints the splay tree that is at the table index described.
//	
//	void PrintTree(string letter); --> Same method as above, just converts the letter to ascii 
//					and subtracts it by 97 to get the index for the table.
//	
//	void PrintSplays(int index); --> Prints the number splays that have occurred for that splay tree.
//
//	void FindAll(string inPart); --> Find all takes in a word and compares it to other words (not case
//					sensitive so "The" will have results like "then" etc.
//
//	string GetIndex(string inLetter); --> I honestly didn't ever call this but it seems like I was suppsosed 
//					to get the index with this method. I just happened to find a better 
//					way of doing it. I still implemented it though so it can be used.
*************************************************************/
#ifndef HASHED_SPLAYS_H
#define HASHED_SPLAYS_H

#include "SplayTree.h"
#include "Node.h"
#include "Exceptions.h"

#include <sstream>
#include <locale>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>


using namespace std;

// Global Constants
const int ALPHABET_SIZE = 26; // The size of the alphabet


class HashedSplays{

public:

	/**
	 * Creates an array of empty Splay Trees
	 * Pre-Condition: None
	 * Post-Condition: A brand new Hash of Splay Trees. YAY.
	 */
	HashedSplays();

	/**
	 * Creates an array of empty SplayTrees
	 * 
	 * Pre-Condition: Number of splay trees that will be grown.
	 * Post-Condition: A brand new array of splay trees of whatever number inserted.
	 */
	HashedSplays(int size);

	/**
	 * Destructor! Wonderful, wonderful destruction! I mean destructing!
	 */
	~HashedSplays();

	/**
	 * Pre-Condition: A file name
	 * Post-Condition: Reads the file and parses the strings and puts it all into 
	 * a splay tree. There will be trimming and removal of numbers.
	 */
	void FileReader(string inFileName);

	/**
	 * Pre-Condition: The line of text and the index of the Splay Tree where the line will be inserted.
	 * Post-Condition: The line of text inserted into a splay tree
	 */
	void HandleInsertion(string line, int tableIndex);

	/**
	 * Pre-Condition: A valid hash of valid splay trees
	 * Post-Condition: Prints the first node in the splay tree at the certain hash
	 * 		and the number of nodes inside the tree.
	 */ 
	void PrintHashCountResults();

	/**
	 * Pre-Condition: The index at which the splay tree you want to print is located
	 * Post-Condition: Printing of the splay tree.
	 */
	void PrintTree(int index);
	
	/**
	 * Pre-Condition: The letter which the items inside the splay tree start with.
	 * Post-Condition: Printing of the splay tree by calling PrintTree(int index)
	 */
	void PrintTree(string letter);

	/** 
	 * Pre-Condition: The index of the splay tree you want to get the number of splays of.
	 * Post-Condition: Prints the number of splays that tree had done.
	 */
	void PrintSplays(int index);

	/**
	 * Pre-Condtion: The word that you want to find that other words start with.
	 * Post-Condition: A printing of the words that start with that word you entered.
	 */
	void FindAll(string inPart);

	/**
	 * Pre-Condition: The word you want to get the index of.
	 * Post-Condition: The index of that word (Although, I don't know why you want it in a string)
	 */
	string GetIndex(string inLetter);

private: 

	SplayTree<Node> *table; //The pointer that will point to an array of splay trees.
	int m_trees; // The size of the array.
};// end class definition.

#endif