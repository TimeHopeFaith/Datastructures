/**************************************************************
* File: Word.h
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
#ifndef WORD_H
#define WORD_H

#include <iostream>
#include <string>
#include <queue>
//#include <list>

using namespace std;

class Word{

private:

	// This will hold the words
	string wordText;

	// This will hold the indicies of 
	// where the word appeared in the text
	queue<int> lineNumbers;

	// This will account for the number of times the word has appeared.
	int count;

	// This helps to determine if the word is filtered or not
	bool filterWord;

public:

	// Constructor that will make a string called "DEFAULT"
	Word();
	
	///////////////////////////////////////////////////////////////////////////
	// Constructor that will take in a string and records that as a filter word
	// Pre-Condition: A Word object that is passed in without the index. 
	// Post-Condition: A word is stored as a filter word.
	Word(string & inWord);

	///////////////////////////////////////////////////////////////////////////
	// Constructor that will take in a string and a line number of where a word 
	// appeared in a text
	// Pre-Condition: A Word object passed in with the index number
	// Post-Condition: A word is stored as an index word.
	Word(string & inWord, int & lineNumber);
	
	// Destructors
	~Word();
	
	//////////////// Accessors ///////////////////////////////
	
	///////////////////////////////////////////////////////////////////////////
	// GetWord will return the word that this class is holding
	// Pre-Condition: None.
	// Post-Condition: This returns the string of the Word.
	const string GetWord() const { return wordText;}
	
	///////////////////////////////////////////////////////////////////////////
	// Pre-Condition: None
	// Post-Condition: Returns the queue of lineNumbers
	queue<int> getList(){ return lineNumbers;}

	//////////////////////////////////////////////////////////////////////////
	// Accessor to get the count the word has appeared
	const int getCount() const{return count;}

	/////////////////////////////////////////////////////////////////////////
	// Returns if the current Word is a filter word or a regular word
	const bool isFilterWord() const{	return filterWord;}

	/////////////////////////////////////////////////////////////////////////
	// Increments the count and pushed the index number into the queue
	// Pre-Condition: Takes in the line number at which the word has appeared in.
	// Post-Condition: Pushes the number into the queue and increments count
	void CountWord(const int & lineNumber);

	//////////////////////////////////////////////////////////////////////////
	// Overrides the << operator to print output to the text file properly
	// Overrides the operator << to format the printing of the Word into a file.
	friend ostream &operator<< (ostream & out, const Word & inWord);
	
	// Overrides the < operator to make sure that when Words are compared,
	// the strings are actually getting compared.
	// The less than is on the left hand side
	friend bool operator <(const Word& lhs, const Word& rhs);

	// Overrides the == operator so that if the strings are the same,
	// it will return true.
	friend bool operator ==(const Word&lhs, const Word& rhs);
};

#endif
