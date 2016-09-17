/***************************************************************
* File: LinearProbing.cpp
* Author: James Guan
* Homework: CMSC 341 Project4, Fall 2014
* Version Date: 11/18/2014
* Class Section: 02
* E-mail: jguan3@umbc.edu
* Description:
*
* NOTES: I know the below functions are so repetitive but I did this for consistency,
*		so that I can use these different probing classes independently.
* 
* This is the linear probing class that will use the algorithm
* h( K, I ) = ( h( K ) + I ) mod M
* for the insert, remove, etc.
*
// LinearProbing class
//
// 
// 
// ******************None Member Functions ****************
// int linearHash(int key)	 	--> Returns a hash key of int
// int linearHash( const string & key)  --> Returns a hash key for strings
// ******************ERRORS********************************
// 
*************************************************************/
#ifndef LINEAR_PROBING_CPP
#define LINEAR_PROBING_CPP

#include "LinearProbing.h"

/**
 * Pre-Condition: A value of type int
 * Post-Condition: Return that value
 */
int linearHash( int key )
{
    	return key;
}// end linearHash




/**
 * Pre-Condition: A value of type string
 * Post-Condition: Converts that value into a hash key 
 * 		and returns that hash value
 */
int linearHash( const string & key )
{
    int hashVal = 0;

    for(unsigned int i = 0; i < key.length( ); i++ )
        hashVal = 37 * hashVal + key[ i ];

    return hashVal;
}// end linearHash

#endif