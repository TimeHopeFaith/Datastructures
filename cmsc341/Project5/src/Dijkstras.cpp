/***************************************************************
* File: Dijkstras.cpp
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
#ifndef DIJKSTRAS_CPP
#define DIJKSTRAS_CPP

#include "Dijkstras.h"



/////////////////////////////////////////////////////////////////////////////
// Destructor that cleans up the vectors of Struct Roads and 
// the vectors of Struct Vertex
/////////////////////////////////////////////////////////////////////////////
Dijkstras::~ Dijkstras ( ) 
{
	// Clears the vector vertices
	unsigned int tempSizeVertex = vertices.size();
	for (unsigned int i = 0; i < tempSizeVertex; i++)
	{
		// Clears the vector neighbors within each vertices
		unsigned int tempSize = vertices[i] -> neighbors.size();
		for (unsigned int j = 0; j < tempSize; j++)
		{
			delete vertices[i] -> neighbors[j];
			vertices[i] -> neighbors[j] = NULL;
		}
		delete vertices[i];
		vertices[i] = NULL;
	}
		

}// end destructor



//////////////////////////////////////////////////////////////////////
// This pushes false into the added and the known vectors,
// and it pushes a new Vertex into the vertices vector ( 1 for each city )
//////////////////////////////////////////////////////////////////////
void Dijkstras::setUpDijkstras( int numCities )
{
	// Adds new items corresponding to the number of cities
	for (int i = 0; i < numCities; i++)
	{
		vertices.push_back( new Vertex( i ) );
		known.push_back( false );
		added.push_back( false );
	}// end for
		
}// end setUpDijkstra's




//////////////////////////////////////////////////////
// Prints the known bool values for debugging purposes
//////////////////////////////////////////////////////
void Dijkstras::printKnownTable( unsigned int offset ) const
{

	for (unsigned int i = 0; i < known.size(); i++)
	{
		
		cout << i + offset << ": " << known[i]  << endl;
	
	}
	
}// end printKnown

//////////////////////////////////////////////
// Prints the vector of booleans that 
// is supposed to be used to prevent duplicates
// from being entered into the queue while running Dijkstra's
//////////////////////////////////////////////
void Dijkstras::printAdded( unsigned int offset ) const
{

	// Goes through the vector and prints the boolean value 
	// in terms of 1 or 0. 1 means that the item has already been
	// added into the array.
	for (unsigned int i = 0; i < added.size(); i++)
	{
		
		cout << i + offset << ": " << added[i]  << endl;
	
	}
	
}// end printKnown




//////////////////////////////////////////////////////
// Prints the values in each Vertex. The offset is so that
// if the person starts from 1, you just add 1 to the index
// to get what they are representing it in ( starting 0 or 1)
//////////////////////////////////////////////////////
void Dijkstras::printVertices( unsigned int offset ) const
{

	cout << "Vertices information: " << endl;
	for (unsigned int i = 0; i < vertices.size(); i++)
	{
	
		cout << "Vertex: " << i + offset  << " Cost: " << vertices[i] -> cost;
		cout << " Path: " <<  vertices[i] -> path + offset;
		cout << " Known: " << known[i];
		cout << " MaxCostAlongRoute: " << vertices[i] -> lowestHighestRouteCost << " Number of Neighbors: " << vertices[i] -> neighbors.size() << endl;
		
	}// end for
	
}// end printVertices

	
	
	
////////////////////////////////////////////////////////////////////////////
// Inserts the new Road information into both vertices, adjacent and source
////////////////////////////////////////////////////////////////////////////
void Dijkstras::insertEdge( int source, int adjacent, int weight )
{
	//cout << "Index: " << index << endl;
	//cout << "Passengers: " << weight << endl;
	
	vertices[source] -> neighbors.push_back( new Roads ( weight, adjacent ) );
	vertices[adjacent] -> neighbors.push_back( new Roads (weight, source) );

}// insertEdge




//////////////////////////////////////////////////
// Debug statement to print the neighbor's vector 
// in each Vertex to see who their neighbors are
//////////////////////////////////////////////////
void Dijkstras::printNeighbors( unsigned int offset ) const
{
	// Loops through the vertices
	for (unsigned int i = 0; i < vertices.size(); i++)
	{
	
		// Loops through the neighbors within those vertices
		for (unsigned int j = 0; j < vertices[i] -> neighbors.size(); j++)
		{
			
			cout << i + offset << ": " << vertices[i] -> neighbors[j] -> location + (int)offset;
			cout << " Cost: " << vertices[i] -> neighbors[j] -> cost << endl;
		
		}// end for
	
	}// end for

}// end printNeighbors





//////////////////////////////////////
// scaleCosts 
//////////////////////////////////////
void Dijkstras::scaleCosts( int scale )
{
	
	for (unsigned int i = 0; i < vertices.size(); i++)
	{
	
		for (unsigned int j = 0; j < vertices[i] -> neighbors.size(); j++)
		{
		
			vertices[i] -> neighbors[j] -> cost = (ceil ( ((float)scale) / (float)vertices[i] -> neighbors [j] -> cost));
		
		}// end for
		
	
	}// end for
	
	//printNeighbors( 1 );
	
}// end scaleCosts





/////////////////////////////////////////////////
// This runs the actual Dijkstra's algorithm, 
// taking into account that it needs to find the 
// highest cost along the route, it will check
// for that as well
/////////////////////////////////////////////////
void Dijkstras::runDijkstras( int start )
{
	
	// These check if the location requested is valid (won't throw a segmentation fault)
	if ( start < 0 )
	{
		cout << "You requested a city number less than 1 as your starting position\nwhich is invalid." << endl;
		cout << "Try entering a number between 1 and " << vertices.size() << " next time. Exiting..." << endl;
		exit(1);
	}
	if ( (unsigned int)start >= vertices.size() ){
		cout << "You requested an invalid city greater than the number of cities\nas your starting position." << endl;
		cout << "Try entering a number between 1 and " << vertices.size() << " next time. Exiting..." << endl;
		exit(1);
	}
	
	
	// This is the queue that will help sort the costs from least to greatest
	// automatically as required by Dijkstra's algorithm
	priority_queue < Vertex, vector<Vertex> , std::greater<Vertex> > items;
	//priority_queue < Vertex, vector<Vertex> , std::greater<Vertex> > tester;
	
	// Start the queue with the start location
	vertices[start] -> cost = 0;
	items.push( *(vertices[start]) );
	//tester = items;
	// Will cause segmentation fault if accessing part of array not allowed (try catch here)
	//string shit = "";
	
	// Loops through the priority queue (New items will be pushed if there are
	// connections to the start node
	while ( items.empty() == false )
	{
	
		//cout << items.top().cost << " " << items.top().location + 1 << endl;
		
		// Sets the current location as known so that it won't be added to the queue again
		known[items.top().location] = true;
		
		// Looks at all the neighbors and checks their costs 
		for (unsigned int i = 0; i < vertices[items.top().location] -> neighbors.size(); i++)
		{
			
			//cout << " Left Cost: " << vertices[items.top().location] -> cost + items.top().neighbors[i] -> cost << " Neighbor's Cost: " << vertices[items.top().neighbors [i] -> location] -> cost;
			
			// Checks for the highest cost along the route and updates to get the highest route cost  (not total)
			unsigned int tempHighestRouteCost = 0;
			// Checks if the current route has a higher route cost
			if (tempHighestRouteCost < vertices[items.top().location] -> lowestHighestRouteCost)
			{
				tempHighestRouteCost = vertices[items.top().location] -> lowestHighestRouteCost;
			}// end if
			// Checks if the neighbor has a higher route cost
			if (tempHighestRouteCost < items.top().neighbors[i] -> cost)
			{
				tempHighestRouteCost = items.top().neighbors[i] -> cost;
			}// end if
			
			// Checks if the cost to get to the neighboring node would be less with the current path
			if ( ((vertices[items.top().location] -> cost) + (items.top().neighbors[i] -> cost)) < (vertices[items.top().neighbors [i] -> location] -> cost))
			{
				//cout << " Update: Old: " << vertices[items.top().neighbors [i] -> location] -> cost << " New: " <<  vertices[items.top().location] -> cost + items.top().neighbors[i] -> cost;
				vertices[items.top().neighbors [i] -> location] -> cost = (vertices[items.top().location] -> cost) + (items.top().neighbors[i] -> cost);
				vertices[items.top().neighbors [i] -> location] -> path = items.top().location;
				vertices[items.top().neighbors [i] -> location] -> lowestHighestRouteCost = tempHighestRouteCost;			
			}// end if
			// If the costs end up being equal, find which route has the lowest high route cost and pick that one
			if ( ((vertices[items.top().location] -> cost) + (items.top().neighbors[i] -> cost)) == (vertices[items.top().neighbors [i] -> location] -> cost))
			{
				if ( vertices[items.top().location] -> lowestHighestRouteCost < vertices[items.top().neighbors[i] -> location] -> lowestHighestRouteCost)
				{
					vertices[items.top().neighbors [i] -> location] -> lowestHighestRouteCost = tempHighestRouteCost;
					vertices[items.top().neighbors [i] -> location] -> cost = (vertices[items.top().location] -> cost) + (items.top().neighbors[i] -> cost);
					vertices[items.top().neighbors [i] -> location] -> path = items.top().location;
				}// end if
			}// end if
			
			//cout << " Location: " << items.top().neighbors[i] -> location + 1 << " Known: " << known[items.top().neighbors[i] -> location];
			
			// Makes sure to mark which vertices were added to the queue so that no repeats would happen
			if ( known[items.top().neighbors[i] -> location] == false && added[items.top().neighbors[i] -> location] == false) {
			
				items.push( *(vertices[items.top().neighbors[i] -> location]) );
				//tester = items;
				added[items.top().neighbors[i] -> location] = true;
				//cout << " Push: " << vertices[items.top().neighbors[i] -> location] -> location + 1 << endl; 
				//printAdded( 1 );
				
			}// end if
			//cin >> shit;
		}// end for
		
		// Pops the item so that the next item in the queue will be visible
		items.pop();
		
		
		//cout << " Items top: " << items.top().location + 1;
		
		/*
		while (tester.empty() == false)
		{
			cout << tester.top().cost << " " << tester.top().location + 1  << endl;
			tester.pop();
		}
		
		//cout << " Popped " << endl;
		//cout << " Items top after pop: " << items.top().location + 1 << endl;
		*/
	}// end while
	
	printVertices( 1 );

}// end runDijkstra's




//////////////////////////////////////////////////////
// Returns the highest cost encountered along route
//////////////////////////////////////////////////////
unsigned int Dijkstras::getLowestHighestRouteCost ( int location )
{

	if ( location < 0 )
	{
		cout << "You requested a city number less than 1 as your destination\nwhich is invalid." << endl;
		cout << "Try entering a number between 1 and " << vertices.size() << " next time. Exiting..." << endl;
		exit(1);
	}// end if
	if ( (unsigned int)location >= vertices.size() ){
		cout << "You requested an invalid city greater than the number of cities\nas your destination." << endl;
		cout << "Try entering a number between 1 and " << vertices.size() << " next time. Exiting..." << endl;
		exit(1);
	}// end if
	if ( vertices[location] -> path == -1 && vertices[location] -> cost ==  numeric_limits<unsigned int>::max())
	{
		cout << "The city " << location << " was unreachable by bus from the start location specified." << endl;
		return numeric_limits<int>::max();
	}// end if
	return vertices[location] -> lowestHighestRouteCost;

}// end getLowestHighestRouteCost

//////////////////////////////////////////////////////////////////////////////
// Unused function that was innefficient in that it would find the highest cost
//	along the path after running the whole Dijkstra's
//////////////////////////////////////////////////////////////////////////////
/*
int Dijkstras::highestRouteCost( int location )
{
	
	unsigned int highestCost = 0;

	if (vertices[location] -> path == -1)
	{
		if ( vertices[location] -> cost == 0 )
		{
			cout << "Location is the same as start location" << endl;
		}
		else {
		
			cout << "Location cannot be accessed by bus.\n(No path found for this end location)\nTry taking a helicopter?" << endl; 
		
		}
		return vertices[location] -> cost;
	}
	
	while (vertices[location] -> path != -1)
	{
	
		for (unsigned int i = 0; i < vertices[location] -> neighbors.size(); i++)
		{
		
			if ( vertices[location] -> neighbors [i] -> location == vertices[location] -> path)
			{
				//cout << "Location: " << location << "Path: " << vertices[location] -> path << "Location of opposite" << vertices[location] -> neighbors [i] -> location << endl;
				//cout << "Runner up Cost: " << vertices[location] -> neighbors [i] -> cost << "Highest cost: " << highestCost << endl; 
				if ( vertices[location] -> neighbors[i] -> cost > highestCost)
				{
					
					highestCost = vertices[location] -> neighbors[i] -> cost;
					//cout << "Location: " << location << "Highest value: " << highestCost << endl;
				}
				else{
					i = vertices[location] -> neighbors.size();
				}
					
			}
				
		}
		
		location = vertices[location] -> path;
	}
	return highestCost;

}
*/

#endif
