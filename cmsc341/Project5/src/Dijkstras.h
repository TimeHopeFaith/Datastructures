/***************************************************************
* File: Dijkstras.h
* Author: James Guan
* Project: CMSC 341 Project5, Fall 2014
* Version Date: 12/8/2014
* Class Section: 02
* E-mail: jguan3@umbc.edu
* Description:
*
* This is the class that will handle the Dijkstra's algorithm
* for calculating two different costs for a location:
* 	- The total cost to get to the current location
* 	- The highest road cost along the path to get to the current location requested
* 
// ******************PUBLIC OPERATIONS*********************
// void setUpDijkstras( numCities ) 		 --> Prepares by setting up all the vectors to run Dijkstra's
// void printKnownTable( offset )			 --> Prints the vector of bool, known 
// void printVertices( offset ) 			 --> Prints the information of each Vector
// void insertEdge( source, adjacent, cost ) --> Prepares the Roads between the vertices specified
// void printNeighbors( offset ) 			 --> Prints the neighbor information of each Vertex
// void scaleCosts( scale )	  				 --> New cost = ceil( scale / road cost)
// void runDijkstras( start )			 	 --> Runs the actual Dijkstra's algorithm
// unsigned int getLowestHighestRouteCost( location ) --> Returns the highest road cost along the path to location
// *********************** Structs *************************
// struct Roads  --> Represents the adjacent paths the Vertex is connected to
// struct Vertex --> Represents the vertex that will hold the path, neighbors, max cost along route, total cost
*************************************************************/

#ifndef DIJKSTRAS_H
#define DIJKSTRAS_H

#include <iostream>
#include <vector>
#include <queue> // This is for the priority_queue
#include <limits> // This is for the infinite value
#include <functional> // This is to make the priority_queue go from least to greatest
#include <math.h> // This is for the CIEL used to calculate the costs
#include <stdlib.h> // This is to allow exiting the program when an error occurs
#include <map> // This is not used

using namespace std;

class Dijkstras
{

public:
	//////////////////////////////////////////////////////////////////////////////
	//	Default Constructor - Not used
	//	Calls setUpDijkstras with a standard and puts in 100
	// 	to set up 100 cities (vector of Vertex Structs of size 100)
	//////////////////////////////////////////////////////////////////////////////
	Dijkstras () { setUpDijkstras (100); }
	
	//////////////////////////////////////////////////////////////////////////////
	//	Constructor that takes the number of cities to construct (Starts at 0)
	//	It will then set up a vector of Vertex structs of size numCities
	//////////////////////////////////////////////////////////////////////////////
	Dijkstras ( int numCities ) { setUpDijkstras( numCities); }
	
	/////////////////////////////////////////////////////////////////////////////
	// Destructor that cleans up the vectors of Struct Roads and 
	// the vectors of Struct Vertex
	/////////////////////////////////////////////////////////////////////////////
	~ Dijkstras ( );
	
	/////////////////////////////////////////////////////////////////////////////
	// Pre-Condition: The number of cities that Dijkstra's algorithm will be run on
	// Post-Condition: The initialization of vertices vector and known vector (All false)
	/////////////////////////////////////////////////////////////////////////////
	void setUpDijkstras( int numCities );
	
	/////////////////////////////////////////////////////////////////////////////
	// Pre-Condition: Offset for how the person is representing the cities (Starting from 0 or 1)
	// Post-Condition: A printing of the table of known (Prints 0 or 1)
	/////////////////////////////////////////////////////////////////////////////
	void printKnownTable( unsigned int offset ) const;
	
	/////////////////////////////////////////////////////////////////////////////
	// Pre-Condition: Offset for how the person is representing the cities (Starting from 0 or 1)
	// Post-Condition: A printing of Vertex information where it prints if it is known,
	//				the path to the next Vertex, the cost to get to the current Vertex,
	//				and the highest number of trips along that route to take the passengers.
	/////////////////////////////////////////////////////////////////////////////
	void printVertices( unsigned int offset ) const;
	
	////////////////////////////////////////////////////////////////////////////
	// Pre-Condition: Takes in a Vertex, and the adjacent Vertex, and the cost to
	//				travel between the two vertices
	// Post-Condition: Makes a new Struct Roads and puts in these values into that
	//				struct and then puts it into the vertices'	neighbors vector.
	/////////////////////////////////////////////////////////////////////////////
	void insertEdge( int source, int adjacent, int cost );
	
	////////////////////////////////////////////////////////////////////////////
	// Pre-Condition: Offset for if the user starts from 0 or 1
	// Post-Condition: Debugging print to print the paths of each Vertex
	/////////////////////////////////////////////////////////////////////////////
	void printNeighbors( unsigned int offset ) const;
	
	
	////////////////////////////////////////////////////////////////////////////
	// Pre-Condition: Takes in the number of things traveling across the roads
	// Post-Condition: Takes scale, divide it by the cost of each route, ceiling that,
	//				and make that the new cost for the routes between the vertices.
	//				This is so that the representation will be in number of passengers 
	//				per trip rather than just the number of passengers
	/////////////////////////////////////////////////////////////////////////////
	void scaleCosts( int scale );
	
	////////////////////////////////////////////////////////////////////////////
	// Pre-Condition: Takes in the start location to run Dijkstra's algorithm
	// Post-Condition: Takes scale, divide it by the cost of each route, ceiling that,
	//				and make that the new cost.
	/////////////////////////////////////////////////////////////////////////////
	void runDijkstras( int start );
	
	// Unused here because a faster implementation has been made
	// but this navigates all the paths to find the highest cost
	// along the route
	//int highestRouteCost( int location );
	
	////////////////////////////////////////////////////////////////////////////
	// Pre-Condition: Takes in the location of what you want to check
	// Post-Condition: Returns the highest cost experienced along the route to
	//				get to the location specified.
	/////////////////////////////////////////////////////////////////////////////
	unsigned int getLowestHighestRouteCost ( int location );
	
	// Debugging print to check the added vector of bool
	void printAdded( unsigned int offset ) const;

private:

	//////////////////////////////////////////////////
	// This struct 
	//////////////////////////////////////////////////
	struct Roads
	{
		unsigned int cost;
		int location;
		
		Roads ( ) : cost ( numeric_limits<unsigned int>::max() ), location ( -1) {}
		Roads ( int a, int b) : cost ( a ) , location ( b ) {}
		
		// Overridden operators to compare the costs (originally used for a priority queue)
		bool operator<(const Roads& RHS) const
		{
			return (this-> cost < RHS.cost);
		}
		bool operator>(const Roads& RHS) const
		{
			return (this-> cost > RHS.cost);
		}
	};// end struct Roads

	struct Vertex
	{
		unsigned int location;
		unsigned int cost;
		int path;
		unsigned int lowestHighestRouteCost;
		vector < Roads * > neighbors;
		
		Vertex ( unsigned int city ) : location (city),  cost ( numeric_limits<unsigned int>::max() ) , path ( -1 ), lowestHighestRouteCost ( 0 ){}
		
		// Overridden operators for the priority queue to sort by cost
		bool operator<(const Vertex& RHS) const
		{
			return (this-> cost < RHS.cost);
		}
		bool operator>(const Vertex& RHS) const
		{
			return (this-> cost > RHS.cost);
		}
	};// end struct Vertex
	
	vector <bool> known; // Holds true or false if the Vertex has been visited or not
	vector <bool> added; // Holds true or false if the Vertex has been added to the queue already
	vector <Vertex * > vertices; // Holds number of vertices equivalent to numCities
	
};// end class definition

#endif