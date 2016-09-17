/**************************************************************
* File: Word.cpp
* Author: James Guan
* Homework: CMSC 341 Project1, Fall 2014
* Version Date: 10/21/2014
* Class Section: 02
* E-mail: jguan3@umbc.edu
* Description:
*
* The Word class will contain the member variables “wordText”, “count”, and an STL Queue of Line numbers named “lineNumbers”. It will also contain a:
	a.	constructor
	b.	CountWord
	i.	increments the word’s occurrence
	ii.	add this unique value to the queue, and adds only once if in the same line 
	c.	member getters/setters
	d.	comparison operator == AND < for inserting into the BST
	e.	stream operator << 
	i.	<text>……………………… <count>: q1, q2, q3, q4 … qn
	ii.	the <count> portion is right justified, with “.” as the fill value
**************************************************************/

#ifndef WORD_CPP
#define WORD_CPP

#include "Word.h"
#include <iostream>
#include <queue>
//#include <list>

using namespace std;

// Default Constructor
Word::Word(){
	wordText = "DEFAULT";
	count = 0;
	lineNumbers = queue<int>();
	//lineNumbers= list <int> ();
	filterWord = true;
}// end constructor

// Constructor that takes a word only, making it a filterWord
Word::Word(string & inWord)
{
	wordText = inWord;
	count = 0;
	lineNumbers = queue<int>();
	filterWord = true;
}// end constructor

// Constructor that takes a word and a line number and pushes that line number into the queue
Word::Word(string & inWord, int & lineNumber)
{
	wordText = inWord;
	lineNumbers = queue<int>();
	lineNumbers.push(lineNumber);
	count = 1;
	filterWord = false;

}//end Word

// Word destructor
Word::~Word(){
	//delete wordText;
	//wordText = NULL;
}

// CountWord will increment count based on how many times it appeared and 
// will add the line the word appeared into lineNumbers queue.
void Word::CountWord(const int & lineNumber){
	count++;
	if (lineNumbers.back() != lineNumber){
		lineNumbers.push(lineNumber);
	}// end if

}// end CountWord

// Overloaded

/**********************************************************************/
//				Operator Overrides				//

// Overriding the << operator to format the output to the text file for Word
ostream &operator<<(ostream & out, const Word & inWord)
{
	out << inWord.wordText;

	// If the word is not a filterWord, print more.
	if (inWord.filterWord == false){

		// This makes sure the dots and words stay within 24 characters long.
		int dots = 23;
		if (inWord.count > 9){
			dots = 22;
			if (inWord.count > 99){
				dots = 21;
				if (inWord.count > 999){
					dots = 20;
					if (inWord.count > 9999){
						dots = 19;
					}// end dots
				}// end dots
			}// end dots
		}// end if dots

		// Prints out the dots 
		for (int i = inWord.GetWord().length(); i < dots; i++){
			out << ".";
		}// end if

		// Prints the count and a colon
		out << inWord.count << ":";
		
		// Prints the queue of line numbers by first copying the queue over,
		// then popping it off
		queue<int> temp = inWord.lineNumbers;
		while (temp.empty() == false){
			out << " " << temp.front();
			temp.pop();
		}// end while
		
		
	}// end if

	out << "\n";
	return out;
}// end << operator




// Overridden < operator to be able to compare if the lhs Word 
// is less in value to the right hand Word based on their strings
bool operator <(const Word& lhs, const Word& rhs)
{
	if(lhs.GetWord() < rhs.GetWord())
	{
		return true;
	}
	return false;
}


// Overridden == operator to be able to check for Word equality based on the equality of their strings.
bool operator ==(const Word&lhs, const Word& rhs)
{
	if(lhs.GetWord() == rhs.GetWord())
	{
		return true;
	}
	return false;
}// end operator == 


#endif
