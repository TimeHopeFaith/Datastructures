/**************************************************************
 * File: WordBinarySearchTree.cpp
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
#ifndef WORD_BINARY_SEARCH_TREE_CPP
#define WORD_BINARY_SEARCH_TREE_CPP

#include "WordBinarySearchTree.h"
#include "Word.h"


WordBinarySearchTree::~WordBinarySearchTree(){
	makeEmpty();
}

/**
* Internal method to insert into a subtree.
* x is the item to insert.
* t is the node that roots the subtree.
* lineNumber is the line in which the Word has appeared.
* Set the new root of the subtree.
*/
void WordBinarySearchTree::insert( const Word & x, BinaryNode * & t , const int & lineNumber)
    {
        if( t == NULL )
            t = new BinaryNode( x, NULL, NULL );
        else if( x < t->element )
            insert( x, t->left , lineNumber);
        else if( t->element < x )
            insert( x, t->right, lineNumber);
        else{
			 // Duplicate so it will increment the count of the Word instead of adding a duplicate Word to the BST
	  t->element.CountWord(lineNumber); 
				
       	}// end else
    }// end insert

/***************************************************************************
 * Bootstrap for the overridden & overloaded insert function.
 */
void WordBinarySearchTree::insert( const Word & x, const int & lineNumber)
{
        insert( x, root , lineNumber);
}


#endif
