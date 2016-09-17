/***************************************************************
* File: Graph.h
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

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <math.h>

#include "Exceptions.h"
#include "Util.h"
#include "Dijkstras.h"

// Divide the number of people by the number the buses can take, and ceiling that to find the cost. 
using namespace std;

//int trips(int source, int destination, int tourists)
class Graph
{

private:

	string fileName; // Stores the file name
	int numCities; // Stores the number of cities 
	int numRoads; // Stores the number of roads as stated
	Dijkstras *tourism; // This is the Dijkstras algorithm thing

public: 
	
	////////////////////
	// Takes in the file name of the file to be read
	// and calls readFromFile to set that all up
	////////////////////
	Graph(string filename);
	
	// Destructor deletes the data of the only pointer
	~Graph() { 	delete tourism; tourism = NULL;}
	
	////////////////////
	// Pre-Condition: A valid string fileName already entered
	// Post-Condition: All the data read from the file that will
	// 			store the first two numbers into numCities and numRoads
	// 			and then stores the rest of the roads in tourism
	////////////////////
	void readFromFile();

	////////////////////
	// Pre-Condition: Takes in the start location, the destination, 
	//				and the number of tourists.
	// Post-Condtion: Returns the best route's highest road cost
	////////////////////
	int trips(int source, int destination, int tourists);


};// end class Graph

#endif