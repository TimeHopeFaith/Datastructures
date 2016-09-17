/***************************************************************
* File: QuadraticProbing.cpp
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
* This is the quadratic probing class that will use the algorithm
* h( K, I ) = ( h( K ) + I^2) mod M
* for the insert, remove, etc.
*
// QuadraticProbing class
//
// 
// 
// ******************None Member Functions ****************
// int quadraticHash(int key)	 	--> Returns a hash key of int
// int quadraticHash( const string & key)  --> Returns a hash key for strings
// ******************ERRORS********************************
// 
*************************************************************/
#ifndef QUADRATIC_PROBING_CPP
#define QUADRATIC_PROBING_CPP

#include "QuadraticProbing.h"

/**
 * Pre-Condition: A value of type int
 * Post-Condition: Return that value
 */
int quadraticHash( int key )
{
    	return key;
}




/**
 * Pre-Condition: A value of type int
 * Post-Condition: Return that value
 */
int quadraticHash( const string & key )
{
    int hashVal = 0;

    for(unsigned int i = 0; i < key.length( ); i++ )
        hashVal = 37 * hashVal + key[ i ];

    return hashVal;
}

#endif