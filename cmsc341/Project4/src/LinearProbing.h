/***************************************************************
* File: LinearProbing.h
* Author: James Guan
* Homework: CMSC 341 Project4, Fall 2014
* Version Date: 11/18/2014
* Class Section: 02
* E-mail: jguan3@umbc.edu
* Description:
*
* IMPORTANT: Must call CalculateClusters() before attempting to access clusters 
* 	to ensure the clusters are up to date.
*
* This is the linear probing class that will use the algorithm
* h( K, I ) = ( h( K ) + I ) mod M
* for the insert, remove, etc.
*
* Uses an enum EntryType to mark the different areas of the vector
* DELETED means that there is an item that was there but it was deleted
* ACTIVE means that there is currently an item at that location in the hash table
* EMPTY means no values have ever been in that spot
// LinearProbing class
//
// CONSTRUCTION: 
// 1.	M - the size of the hash table
// 
// 
// ******************PUBLIC OPERATIONS*********************
// bool contains ( x )   	 --> Returns true if it contains the item
// void makeEmpty( )    	 --> Sets every spot to EMPTY
// bool insert( x )      	 --> Insert x and return true if successful
// bool isActive( currentPos )   --> Returns true if the current spot is already filled
// bool remove( x )       	 --> Remove x and return true if successful
// int findPos( x )	  	 --> Returns an empty position (same position if it can't find one)
// int getKey( x )	  	 --> This returns the hash key h( K ) = K mod M
// void PrintTable( ) 	  	 --> Prints the table (for debugging purposes in this project)
// void CalculateClusters( )	 --> Calculates the cluster data
/. ******************** ACCESSORS *************************
// int GetTotalProbes( )  	 --> Accessor for totalProbes
// int GetMaxProbes( ) 	  	 --> Accessor for maxProbes
// int GetNumClusters( )  	 --> Accessor for numClusters
// int GetMaxClusters( )  	 --> Accesor for maxClusters
// double GetAverageClusters( )  --> Accessor for averageClusters
// ***************** Private Operations *******************
// void incrementProbes()	 --> Increments the number of probes that occur
// void changeMaxProbes(int num) --> Changes the max probe number
// ******************None Member Functions ****************
// int linearHash(int key)	 	--> Returns a hash key of int
// int linearHash( const string & key)  --> Returns a hash key for strings
// ******************ERRORS********************************
// 
*************************************************************/
#ifndef LINEAR_PROBING_H
#define LINEAR_PROBING_H

#include <vector>
#include <string>
#include <cstdlib>
#include <iostream>
#include <stdio.h>

#include "Exceptions.h" 

using namespace std;

template <typename HashedObj>
class LinearProbing
{

public:
	
	/////////////////// ENUM /////////////////
	enum EntryType{ ACTIVE, EMPTY, DELETED};
	
	////////////////// CONSTRUCTOR /////////////////////
	// Just takes in the size and sets the array to that size
	// Initializes the current size 
	explicit LinearProbing(unsigned int size ) : array(size) , currentSize(size)
	{ 
		numClusters = 0;

		maxClusters = 0;
		
		averageClusters = 0;
		
		totalProbes = 0;
		
		maxProbes = 0;
		
		makeEmpty(); 
		
		
	}//LinearProbing constructor




	/**
	 * Pre-Condition: None
	 * Post-Condition: Returns true if the item is in the hash table
	 *
	 */
	bool contains (const HashedObj & x ) const
	{	
		int currentPos = findPos( x );
		if ( isActive( currentPos ) )
			if ( array[ currentPos ].element == x )
				return true;
		return false;
	}// end contains


	
	/**
 	 * 
	 *
	 */
	void makeEmpty()
	{
		currentSize = 0;
		for (unsigned int i = 0; i < array.size( ); i++)
			{array[i].info = EMPTY;}
	}// end makeEmpty
	


	/**
	 * Pre-Condition: The object to be hashed
	 * Post-Condition: True if the object was put into the table
	 * 		successfully
	 */
	bool insert(const HashedObj & x)
	{
		
		int currentPos = findPos(x);

		if ( isActive(currentPos) )
			return false;	
		
		array[ currentPos ] = HashEntry( x , ACTIVE);
		

		/*
		 * No rehashing so disregard this bit.
        	if( ++currentSize > array.size( ) / 2 )
            		rehash( );
		 */

		return true;

	}// end insert



	/**
	 * Pre-Condition: None
	 * Post-Condition: True if the place is occuppied
	 * 
	 */
	bool isActive( int currentPos ) const
      	{ 
		return array[ currentPos ].info == ACTIVE; 
		
	}// end isActive



	
	/**
	 * Pre-Condition: Object to be hashed
	 * Post-Condition: removal of that object if it is in the table
	 * 		and returns true if it was in the table
	 */
	bool remove (const HashedObj & x)
	{
		
		int currentPos = findPos(x);
		if ( isActive(currentPos) && array[currentPos].element == x)
		{
       			array[ currentPos ].info = DELETED;
			return true;
		}

       		return false;

	}// end remove

	
	

	/**
	 * Pre-Condition: Passed in hash object 
	 * Post-Condition: Finds an empty spot in the hash table to insert
	 * 		Flips a boolean to false if it can't find an empty spot
	 */
	int findPos( const HashedObj & x )
	{
		// Variables
		int offset = 1;
		int currentPos = getKey( x );
		int originalPos = currentPos;
		bool failure = false;
		int probeCounter = 1;

		incrementProbes();
		
		// Loop through the whole table to try and find an empty spot
		while (array[currentPos].info != EMPTY && array[currentPos].element != x && failure == false)
		{	
			incrementProbes();
			probeCounter++;
			
			currentPos = currentPos + offset;

			if (currentPos >= (int)array.capacity()){
				currentPos = currentPos - (int)array.capacity();
			}// end if
				
			// If the algorithm brings it back to the same spot after a while
			// Note the failure.
			if (currentPos == originalPos)
			{
				failure = true;
			}// end if
			
		}// end while
		
		changeMaxProbes(probeCounter);
		
		return currentPos;
	
	}// end findPos



	/**
	 * Pre-Condition: Passed in hash object 
	 * Post-Condition: Does the modulus to get the key 
 	 * 		Formula is h( K ) = K mod M
	 */
	int getKey(const HashedObj & x ) const
	{	
		
		int hashVal = linearHash (x);

		//cout << "hasval: " << hashVal << " % " << (int)array.capacity();

		// Does the modulus here with formula h( K ) = K mod M
		hashVal = hashVal % (int)array.capacity();

		//cout << " = " << hashVal << endl;

		if (hashVal < 0)
			hashVal = hashVal + (int)array.capacity();

		return hashVal;

	}// end getKey
	


	/**
	 * Pre-Condition: Data
	 * Post-Condtion: Printing the hash table
	 * 		and the elements inside and the status of each index
	 * 		of the hash table
	 */
	void PrintTable()
	{
		cout << "Linear Probing actual table" << endl;
		for (unsigned int i = 0; i < array.capacity(); i++){
			
			cout << i << ": " << array[i].element << " ";

			if (array[i].info ==  EMPTY)
				cout << "EMPTY";	
			else if (array[i].info ==  ACTIVE)
				cout << "ACTIVE";
			else if (array[i].info ==  DELETED)
				cout << "DELETED";

				
			cout << endl;
		}//end for
	}// end PrintTable




	/**
	 * IMPORTANT: This must be called to update the values 
	 * 		for numClusters, maxClusters, and averageClusters!!
         * Pre-Condition: None
	 * Post-Condition: update cluster values of numClusters, maxClusters, and averageClusters
 	 */
	void CalculateClusters()
	{
		// Variables
		int items = 0;
		int clusters = 0;
		int totalItems = 0;

		// Goes through the Hash table to calculate the clusters
		for(unsigned int i = 0; i < array.capacity(); i++){
			if (array[i].info == ACTIVE)
			{
				items++;
			}
			else
			{
				if (items > maxClusters)
					maxClusters = items;
				if (items > 0)
					clusters++;
				totalItems = totalItems + items;
				items = 0;
			}// end else

		}//end for
		
		// Does this one last time if there was a cluster that went to the end
		if (items > maxClusters)
			maxClusters = items;

		if (items > 0){
			clusters++;
			totalItems = totalItems + items;
		}
		
		// Updates the cluster numbers here
		numClusters = clusters;
		averageClusters = (double)totalItems / (double)clusters;

		/*
		cout << "average clusters: " << averageClusters << endl;
		cout << "totalItems: " << totalItems;
		cout << "clusters: " << clusters;
		*/
	
	} // end CalculateClusters


	//////////////////////////////////////////////
	///////////// Accessors //////////////////////
	//////////////////////////////////////////////

	/**
	 * Accessor for totalProbes
	 */
	int GetTotalProbes() const { return totalProbes; }
	

	/**
	 * Accessor for maxProbes
	 */
	int GetMaxProbes() const { return maxProbes; }
		

	/**
	 * IMPORTANT: CalculateClusters must be called first to update this value!
	 * Accessor for numClusters
	 */
	int GetNumClusters() const { return numClusters; }


	/**
	 * IMPORTANT: CalculateClusters must be called first to update this value!
	 * Accessor for maxClusters
	 */
	int GetMaxClusters() const { return maxClusters; }


	/**
	 * IMPORTANT: CalculateClusters must be called first to update this value!
	 * Accessor for averageClusters
	 */
	double GetAverageClusters() const { return averageClusters; }//end GetAverageClusters
	

private:
	
	/**
         * A struct that will hold an integer/ string 
         * and the status of the current area in the vector
         */
	struct HashEntry
	{
		HashedObj element;
		EntryType info;
		
		HashEntry( ) : element ( NULL ) , info ( EMPTY ) { }
		HashEntry( const HashedObj & e, EntryType i )
			: element( e ), info (i ) { }
	};// end struct

	// Member variables
	vector<HashEntry> array; // This will be the hash table
	unsigned int currentSize; // This stores the size of the hash table

	int totalProbes; // Holds total probes that have occurred
	int maxProbes; // Holds the maximum probes that have occured for a single insert
	int numClusters; // Holds the number of clusters there currently are
	int maxClusters; // Holds the maximum amount of clusters that have ever occurred
	double averageClusters; // This holds the average number of clusters currently

	/**
	 * Pre-Condition: None
	 * Post-Condition: This will increment the total amount of probes
	 */
	void incrementProbes()
	{

		totalProbes = totalProbes + 1;

	}// end increment probes


	/**
	 * Pre-Condition: A new max probe number higher than the current one
	 * Post-Condition: A change to the new max probe number
	 */
	void changeMaxProbes(int num)
	{
		if (maxProbes < num)
			maxProbes = num; 
	}// end change max probes
	
};// end LinearProbing class definition

/**
 * Pre-Condition: An integer
 * Post-Condition: Just returns that same integer as the key
 */ 
int linearHash(int key);

/**
 * Code provided by Nicholas
 * Pre-Condition: A string
 * Post-Condition: It will get a key based on that String
 */
int linearHash( const string & key);

#endif