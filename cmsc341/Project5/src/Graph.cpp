/***************************************************************
* File: Graph.cpp
* Author: James Guan
* Project: CMSC 341 Project5, Fall 2014
* Version Date: 12/8/2014
* Class Section: 02
* E-mail: jguan3@umbc.edu
* Description:
*
* This class reads the file and sets up for the Dijkstra's algorithm.
* It will return the max number of trips of the best route found to the driver.cpp
* 
// ******************PUBLIC OPERATIONS************************************
// void readFromFile() --> Reads the file and sets up the Dijkstras class
// int trips( source, destination, tourists) --> Calls the runDijkstras in
//												 the Dijkstras class and returns resulting data
*************************************************************************/
#ifndef GRAPH_CPP
#define GRAPH_CPP

#include "Graph.h"

/////////////////////
// Constructor: 
// Pre-Condition: Takes a file name
// Post-Condition: Checks if the file is valid
////////////////////
Graph::Graph(string filename)
{
	// Checks if the file can be opened
	try{
		Util::FileExists(filename.c_str());
	}
	catch (Exceptions &cException) {
    	cout << "EXCEPTION: " << cException.GetMessage() << endl;
    	exit(1);
  	}// end catch
	
	fileName = filename;
	
	// Calls read from file to read the data and set up all the data
	readFromFile();

}// end Graph constructor




/////////////////////////////////////////////////
// Reads the data file and sends in all the data
// to Dijkstras class for initialization
/////////////////////////////////////////////////
void Graph::readFromFile()
{

	// Opening the file
	ifstream inFile;
	inFile.open(fileName.c_str(),ios_base::in);
	
	// Exit if the file cannot be opened
	if(inFile.fail()){
	  cerr << "Error opening file" << endl;
	  exit(1);
	}// end if
	
	// Reads through the file
	//bool firstLineRead = false; 
	
	string line = "";
	
	inFile >> line;
	
	// Reads in N
	if(Util::IsAllDigits(line)){
		//numCities = (int)Util::GrabDigits(line);
		sscanf(line.c_str(), "%d", &numCities);
		cout << "Number of cities: " << numCities << endl;
		//makeCities();
		tourism = new Dijkstras( numCities );
		//tourism -> printKnownTable( 1 );
	}
	else{
		
		cerr << "Error: N not given as digit. Exiting..." << endl;
		exit(1);
	
	}
	
	// Reads in R
	inFile >> line;
	
	if(Util::IsAllDigits(line)){
		//numRoads = (int)Util::GrabDigits(line);
		sscanf(line.c_str(), "%d", &numRoads);
		cout << "Number of roads: " << numRoads << endl;
	}
		
	else{
		
		cerr << "Error: R not given as digit. Exiting..." << endl;
		exit(1);
	
	}
	
	// For the number of roads, record that data 
	// into Dijkstras class tourism
	for (int i = 0; i < numRoads; i++){
	
		int c1 = -1; // The first city
		int c2 = -1; // The second city
		int p = -1;  // Cost between the cities
		
		// Converts the string to characters
		inFile >> line;
		sscanf(line.c_str(), "%d", &c1);
		
		inFile >> line;
		sscanf(line.c_str(), "%d", &c2);
		
		inFile >> line;
		sscanf(line.c_str(), "%d", &p);
		
		//tourism -> insertEdge( c1 - 1 , c2 - 1, p );
		tourism -> insertEdge( c1 - 1 , c2 - 1, p - 1 );
		
	}
	
	//tourism -> printVertices( 1 );
	//tourism -> printNeighbors( 1 );
	//tourism -> priorityQueueTest( );
	inFile.close();
	
	//tourism -> printNeighbors();

}// end readFromFile




//////////////////////////////////////////////
// trips first scales the costs 
// then it runs the Dijkstras and returns the recorded
// highest road cost along the most efficient path
// and returns it
//////////////////////////////////////////////
int Graph::trips(int source, int destination, int tourists)
{
	// If the number is negative, leave the program
	if (tourists < 0)
	{
		cout << "You can't have a negative number of tourists!\nExiting..." << endl;
		exit(1);
	}
	cout << "S: " << source << " D: " << destination << " T: " << tourists << endl;
	tourism -> scaleCosts(tourists); // Example:  new costs for everyone = ceil( 99 / 29 )
	tourism -> runDijkstras( source - 1); // Runs the Dijkstras so all the data will be set
	
	return tourism -> getLowestHighestRouteCost( destination - 1);// Request the destination data
	
}// end trips

#endif