/**************************************************************
* File: HashedSplays.cpp
* Author: James Guan
* Homework: CMSC 341 Project3, Fall 2014
* Version Date: 11/4/2014
* Class Section: 02
* E-mail: jguan3@umbc.edu
* Description:
*
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
#ifndef HASHED_SPLAYS_CPP
#define HASHED_SPLAYS_CPP

#include "HashedSplays.h"
#include "SplayTree.h"
#include "Exceptions.h"
#include "Node.h"

#include <sstream>
#include <locale>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

// Default constructor here
// Default array size of 26
HashedSplays::HashedSplays()
{

	table = new SplayTree<Node>[ALPHABET_SIZE];
	m_trees = ALPHABET_SIZE;

}// end default constructor

// Constructor with the set size of the array
HashedSplays::HashedSplays(int size)
{
	
	table = new SplayTree<Node>[size];
	m_trees = size;
}// constructor with the set size of the array

// Destructor
HashedSplays::~HashedSplays()
{
	/*
	for (int i = 0; i < m_trees; i++){
		delete [] table[i];
		
	}
	*/
	
	delete[] table;
	table = NULL;

}// end Destructor

/**
 * Reads the file and puts the data into a splay tree.
 */
void HashedSplays::FileReader(string inFileName)
{

        if (Util::FileExists(inFileName.c_str())){
	  //cout << inFileName << " is valid. Continuing operation" << endl;
        }

	// Opens the file here
	ifstream inFile;
	inFile.open(inFileName.c_str(),ios_base::in);
	
	//if opening fails, it will exit the program
	if(inFile.fail()){
	  cerr << "Error opening file" << endl;
	  exit(1);
	}// end if
	
	string line; // Holds the next line of text from the file
	
	while (!inFile.eof()){

	    inFile >> line;
	    line = Util::Strip(line); // Removes punctuatiosn on the sides
	    line = Util::RemoveInsidePunct(line); // Removes punctuations inside the string except ' and -
	  
	    if (line.empty() == false){

	    // I was about to write a crap ton of if statements
	    // but then I figured that this would be 26x easier.
	        char letter = std::tolower(line[0]); // Gets the first character of the line
		int ascii = letter; //Converts that character into an ascii value.
		HandleInsertion(line, ascii - 97); // Calls handle insertion to... handle the insertion.
		
	    }// end if

	}// end while

	inFile.close(); // closes the file

}// end FileReader

/**
 * Handle Insertion will insert the line of text to the proper table Splay Tree
 */
void HashedSplays::HandleInsertion(string line, int tableIndex)
{
        Node temp = Node(line, 1);// Creates a brand new temporary Node for insertion

	// if table already has the same string, increment the frequency instead of insertion
	if (table[tableIndex].contains(temp)){
		
	  table[tableIndex].getRoot().IncrementFrequency();
		
	}// end if

	else{
		table[tableIndex].insert(temp);
	}// end else

}// end HandleInsertion

/**
 * Prints the hash of splay trees in alphabetical order.
 */
void HashedSplays::PrintHashCountResults()
{
  // This for loop will loop through the table and print out the first node in the Splay Tree
  // and then prints out the number of nodes it has.
    for (int i = 0; i < m_trees; i++){
    
      // Checks if it is empty or not
      if(table[i].isEmpty()){
	
	  cout << "This tree has no nodes." << endl;
      
      }// end if
    
      else{
	  int tableSize = table[i].size();
	  cout << "This tree starts with " << table[i].getRoot();
	  cout << " and has " << tableSize << " nodes." << endl;
      }// end else
  
  }// end for

}// end PrintHashResults

/**
 * Prints the tree at the index number in table
 */
void HashedSplays::PrintTree(int index)
{

  //if (table[index].isEmpty() == false){
      
      // checks if the index is the correct index 
      if (index >= m_trees || index < 0){
	throw Exceptions("Index number is out of bounds of the table.");
      }// end if
      
      else{
    
	table[index].printTree();
      
      }// end else
      
      PrintSplays(index);

      //}// end if
  
}// end PrintTree

/**
 * Serves the same purpose as previous method but matches the character or string to the certain array
 * by converting it to ascii and subtracting by 97 and uses the previous method to print
 */
void HashedSplays::PrintTree(string letter)
{
 
    char toChar = std::tolower(letter[0]);
    int index = toChar;
    index = index - 97;

    PrintTree(index);
}// end PrintTree

/**
 * Just a formatted print of of the number of splays that took place for each tree
 */
void HashedSplays::PrintSplays(int index)
{
    cout << "This tree had " << table[index].getSplayCount() << " splays." << endl;
}// end PrintSplays

/**
 * FindAll will find all the words that begin with the inputted word, and matches both upper and lower case of the same letters.
 */
void HashedSplays::FindAll(string inPart)
{
    cout << "Printing the results of the nodes that start with \'" << inPart << "\'" << endl;

    // Converts the first char in string to ascii
    char toChar = std::tolower(inPart[0]);
    int index = toChar;
    index = index - 97;
  
    // Lower cases the characters in the string for case insensitive comparison
    string word = Util::Lower(inPart);
  
    // Makes a temporary splay tree that will grab minimum values 
    // and remove them in order to print them in order
    SplayTree<Node> tempSplay = SplayTree<Node>(table[index]);
  
    // While there are still Nodes inside that temporary splay, keep going until it is empty.
    while (tempSplay.isEmpty() == false){
  
        Node tempNode = tempSplay.findMin();
	string tempString = Util::Lower(tempNode.GetWord());
	// Needs to be unsigned because you can't compare 
	// something unsigned with a signed number because 
	// unsigned has no negatives (which is good because size and length
	// are supposed to always be positive
	unsigned int matches = 0; 
	
	// Continues only if the word in the splay is as long as the word
	// we are checking with.
	if (tempString.length() >= word.length()){
      
	  for (std::string::size_type i = 0; i < word.length(); i++){
	      if (word[i] == tempString[i]){
	          matches++; // Increments matches when the matching characters are found
	      }// end if
	  }// end for
	  
	  // if the beginning characters of the splay string matches the check string,
	  // print it
	  if (matches == word.length()){
	      cout << tempNode << endl;
	  }//end if
	  
	}// if
	
	tempSplay.remove(tempNode); // Removes the minimum node to basically get the next node
    }// end while
}// end FindAll

/**
 * GetIndex returns the index as a form of a number in a string
 * (I honestly didn't see the use of this method at all)
 */
string HashedSplays::GetIndex(string inLetter)
{
    char toChar = std::tolower(inLetter[0]);
    int index = toChar;
    index = index - 97;
    string result;
    ostringstream convert;
    convert << index;
    result = convert.str();
    return result;
}// end GetIndex

#endif
