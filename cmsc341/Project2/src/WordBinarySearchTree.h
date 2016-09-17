/**************************************************************
 * File: WordBinarySearchTree.h
 * Author: James Guan
 * Homework: CMSC 341 Project2, Fall 2014
 * Version Date: 10/21/2014
 * Class Section: 02
 * E-mail: jguan3@umbc.edu
 * Description:
 *
 * This is a child of Binary Search Tree class that will specialize in helping inserting the Words quicker.
 * It will override and overload the parent insert function to also take in the lineNumbers so that it 
 * may insert the line number into the already existing element if there were duplicates.
 *************************************************************/

#ifndef WORD_BINARY_SEARCH_TREE_H
#define WORD_BINARY_SEARCH_TREE_H

#include "BinarySearchTree.h"
#include "Word.h"

class WordBinarySearchTree : public BinarySearchTree<Word>{

private:
	/**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
	 * lineNumber is the index number that will be added into the Word queue
     */
    void insert( const Word & x, BinaryNode * & t , const int & lineNumber);

public:

    // This is a regular constructor just calling the parent constructor
    WordBinarySearchTree() : BinarySearchTree<Word>(){

    }

    ~WordBinarySearchTree();

    ///////////////////////////////////////////////////////////////////////////////
    // This is the overloaded/overriden isnert function to accept the line number.
    // Pre-Condition: The Word and the line number where it appeared
    // Post-Condition: Stores the Word if there are no duplicates, but if there is,
    // 		store the line number in the Word's queue.
    void insert( const Word & x, const int & lineNumber);
	
    ////////////////////////////////////////////////////////////////////////////////////////
	//If the regular insert function is called, send it to the parent BST for processing.
	// Pre-Condition: A word that has no index.
	// Post-Condition: Stores the Word (most likely a filter BST)
    void insert( const Word & x){ BinarySearchTree<Word>::insert(x, root);}

};

#endif
