/***************************************************************
* File: DoubleProbing.cpp
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
* This is the double probing class that will use the algorithm
* h ( K, I ) = ( h( K ) + I * h2( K ) ) mod M 
* where h2 ( K ) = R - ( K mod R ) 
* for the insert, remove, etc.
*
// DoubleProbing class
//
// 
// 
// ******************None Member Functions ****************
// int doubleHash(int key)	 	--> Returns a hash key of int
// int doubleHash( const string & key)  --> Returns a hash key for strings
// ******************ERRORS********************************
// 
*************************************************************/
#ifndef DOUBLE_PROBING_CPP
#define DOUBLE_PROBING_CPP

#include "DoubleProbing.h"

/**
 * Pre-Condition: A value of type int
 * Post-Condition: Return that value
 */
int doubleHash( int key )
{
    	return key;
}




/**
 * Pre-Condition: A value of type int
 * Post-Condition: Return that value
 */
int doubleHash( const string & key )
{
    int hashVal = 0;

    for(unsigned int i = 0; i < key.length( ); i++ )
        hashVal = 37 * hashVal + key[ i ];

    return hashVal;
}

#endif