/**************************************************************
* File: Indexer.cpp
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

#ifndef INDEXER_CPP
#define INDEXER_CPP

#include "Indexer.h"
#include "BinarySearchTree.h"
#include "WordBinarySearchTree.h"
#include "dsexceptions.h"
#include "Utility.h"
#include "Word.h"
#include "Exceptions.h"

#include <sstream>
#include <locale>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

// Constructor for Indexer that takes in two parameters:
// - the file name of the file that has the words that will be filtered out
// - the file name of the file where we must index the text from
// 
Indexer::Indexer (string & filterFile, string & dataFile){
		filteredBST = BinarySearchTree<Word>();
		indexedBST = WordBinarySearchTree();

		// Check if the files are valid and openable.
		if (FileExists(filterFile.c_str()) && FileExists(dataFile.c_str())){
		     filterfile = filterFile;
		     datafile = dataFile;
		}// end if
		else{
			throw Exceptions();
			exit(1);
		}// end else
		
		filterfile = filterFile;
		datafile = dataFile;

}// end Indexer constructor

// Indexer destructor
Indexer::~Indexer(){

}// end Indexer destructor

// FileExists takes in the file name and checks to see if the file exists.
bool Indexer::FileExists (const char* filename) const{
		
		
		ifstream inFile;
		inFile.open(filename);

		//if opening fails, it will exit the program
		if(inFile.fail()){
			throw Exceptions();
			
			exit(1);
		}// end if
		
	return true;
}// end FileExists

// FileFilterReader reads in the text to filter out into a BST
BinarySearchTree<Word> Indexer::FileFilterReader(string & filename){

		ifstream inFile;
		inFile.open(filename.c_str(),ios_base::in);

		//if opening fails, it will exit the program
		if(inFile.fail()){
			cerr << "Error opening file" << endl;
			exit(1);
		}// end if

		// variables/pointers to store the strings/ words
		// from the text file.
		string item;
		Word * temp = NULL;

		// While it is not the end of the text, keep reading in text
		// and store it into the filteredBST.
		while(!inFile.eof()){
			inFile >> item;
			item = Utility::Lower(item);
			temp = new Word(item);
			filteredBST.insert(* temp);
		}// end while

		// set the pointer to NULL temp;
		delete temp; // comment out if program fails
		temp = NULL;

		// close the file
		inFile.close();

		return filteredBST;

}// end FileFilterReader

// This does both the reading from the text file, and removing the 
// words that match the ones in the filteredBST. 
BinarySearchTree<Word> Indexer::FileWordReader(string & filename){

		// This is the specialized child BST that will
		// use the special insert function to add in the 
		// words.
		WordBinarySearchTree wordTree = WordBinarySearchTree();

		ifstream inFile;
		inFile.open(filename.c_str(),ios_base::in);
		
		//if opening fails, it will exit the program
		if(inFile.fail()){
			cerr << "Error opening file" << endl;
			exit(1);
		}// end if
		
		// Variables/pointers used to store and traverse
		// the file stream. 
		//inFile >> noskipws;
		//string line = NULL;
		Word * tempWord1 = NULL;
		Word * tempWord2 = NULL;
		int index = 1;
	
		// These are 
		while (!inFile.eof())
		{
		       string line;
			
			// This will store where the 
			// file was last at.
			// This is mainly for finding empty lines 
			// inside the input files.
			int len = inFile.tellg();
			
			// This gets the current line to check if the line
			// is empty or not.
			getline (inFile, line);
			
			// This is really required because 
			// of the way >> will only find a string delimited by spaces.
			// Checks to see if the string is empty.
			if(line == "" || line == " " || line == "\n")
			{
				// Checks if the next strings would be empty.
			 	while ((line == "" || line == " " || line == "\n") && !inFile.eof()){
			      		index++;
					// Advances the placement of where to return
					// to after incrementing the index.
			      		len = inFile.tellg();
			      		getline (inFile, line);
			    	}// while
			}// end if
		       
			// Returns the file back to a placement that 
			// will allow it to read the next line.
			inFile.seekg(len ,std::ios_base::beg);
			
			// If the line is going to end, increment index number 
			// before moving to the next line.
			if (inFile.peek() == '\n' || inFile.peek() == 13){
			  index++;
			
			}// end if

			inFile >> line;
			
			// Removes punctuations at the front of the string
			while (ispunct(line[0]) || line[0] == ' '){
					line = line.substr (1, line.length() - 1);
			}// end while

			// Makes sure the line is not empty to advance.
			if (line.empty() == false){

				// Removes punctuations at the back of the string
				while (ispunct(line[line.length()-1])){
					line = line.substr (0, line.length() - 1);
						
				}// end while
				
				
				// variables to handle removing the punctuations from the middle of the string
				string temp1 = "";
				string temp2 = "";
				string tester = "";
				bool punctuation = false; // if there was punctuation in between, split into two words
				bool apostrophe = false; // if apostrophe has already been found
	      

				// removes the punctuations from the string and removes any extra apostrophies
				for(std::string::size_type i = 0; i < line.length(); i++){
						
					// checks if the current character in the string can be put back into the new string
					if(isdigit(line[i]) == false && (ispunct(line[i]) == false || line[i] == '\'' || line[i] == '-')){
						if (apostrophe == false){
							if (punctuation == false){
								temp1 = temp1 + line[i];
							
							}
							else if (punctuation == true){
								temp2 = temp2 + line[i];
							}
							
						}// end if apostrophe 

						// this tries to prevent adding any new apostrophes 
						if (apostrophe == true){
							if (line[i] != '\''){
								if (punctuation == false){
									temp1 = temp1 + line[i];
						
								}// end if
								else if (punctuation == true){
									temp2 = temp2 + line[i];
								}// end if
							}// end if
						}// end if

						// if the first apostrophe has been found, make apostrophe true
						if (line[i] == '\''){
							apostrophe = true;
						}// end if
						
					}// end if

					// if punctuation has been found, make punctuation true
					if(ispunct(line[i]) && line[i] != '\'' && line[i] != '-')
						punctuation = true;

					
				}// end for
				
				// Cleans out the second word, eliminating any apostrophes or dashes
				while (ispunct(temp2[0])){
					temp2 = temp2.substr (1, temp2.length() - 1);
				}// end while

				// sets all characters lowercase and inserts the words into the BST
				temp1 = Utility::Lower(temp1);
				if (temp1.empty() == false && filteredBST.contains(temp1) == false){
					tempWord1 = new Word(temp1, index);
					wordTree.insert(* tempWord1, index);
				}// end if
				
				// Inserts the second word if there was a second word.
				temp2 = Utility::Lower(temp2);
				if (temp2.empty() == false && filteredBST.contains(temp2) == false){
					tempWord2 = new Word(temp2, index);
					wordTree.insert(* tempWord2, index);
				}// end if
			}// end if 
		}// end while
		delete tempWord1;
		delete tempWord2;
		tempWord1 = NULL;
		tempWord2 = NULL;
		inFile.close();

		indexedBST = wordTree;
		return indexedBST;
	}// end FileWordReader

// DoIndex is what will call all the associated functions
// to Do the indexes
void Indexer::DoIndex(){
	FileFilterReader(filterfile);
	FileWordReader(datafile);

	OutputResults();
	indexedBST.makeEmpty();
	filteredBST.makeEmpty();
}// end DoIndex()

// OutputResults will output the results of both the filterBST and the indexBST 
// into a text document
void Indexer::OutputResults(){

	// Output for the filterBST
	ofstream outputFile1;
	outputFile1.open("filterResults.txt");
	while (filteredBST.isEmpty() == false){
		
		Word pointer = filteredBST.findMin();
		outputFile1 << pointer;
		//cout << pointer;
		filteredBST.remove(pointer);
	}// end while

	// Output for the indexBST
	outputFile1.close();

	ofstream outputFile2;
	outputFile2.open("indexResults.txt");
	while (indexedBST.isEmpty() == false){
		Word pointer = indexedBST.findMin();
		outputFile2 << pointer;
		//cout << pointer;
		indexedBST.remove(pointer);
	}// end while

	outputFile2.close();
	
}// end OutputResults

#endif
