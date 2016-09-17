/**************************************************************
* File: Hash.cpp
* Author: James Guan
* Homework: CMSC 341 Project4, Fall 2014
* Version Date: 11/18/2014
* Class Section: 02
* E-mail: jguan3@umbc.edu
* Description:
* 
* NOTES: I am trying to make the TA's jobs easier by printing to the console some debugging data,
* 	and the tables after all the hashing into a file called table.txt. Hope this helps.
*	Also, I was going to make a Hash parent class with a child class that just overrides the 
*	insert function but I ran out of time. Sorry for all the repetitive code. Just know that 
*	the only thing different in all the probing classes is the findPos function and that the
* 	double probing part has an extra function called secondHash.
*
*	Comment out the PrintTable() calls if you do not wish for the tables to print.
*
*
* This is the Hash.cpp file that will call the linear, quadratic,
* and double probing classes/ functions to do those types of probes
* and then it will print their data in intervals based on what the user 
* has entered for the interval.This has all the function definitions.
* 
// Hash class
// 
// CONSTRUCTION: 
// 1.	the name of a file which contains unique random integers separated by whitespace.
// 2.	N -- the total number of random integers to attempt to insert (e.g. 1000)
// 3.	INTERVAL -- the interval (number of attempted insertions) for reporting data (e.g. 200)
// 4.	M - the size of the hash table
// 5.	R - the largest prime less than M
// 
// ******************    ENUMS    ************************
//  enum Entry
// 	 FROM_FILE represents that the slot in the vector is valid and from a file
//	 EMPTY represents that the slot in the vector is EMPTY
//
// ******************PUBLIC OPERATIONS*********************
// void PrintValues( )	  --> Debug function that prints the data collected from file
// void LinearHash( ) 	  --> Function that uses linear probing and prints out the data
// void QuadraticHash( )  --> Function that uses quadratic probing and prints out the data
// void DoubleHash( )	  --> Function that uses double probing and prints out the data
// void ResetOutputFile( )--> Resets the output files results.txt and table.txt
*************************************************************/

#ifndef HASH_CPP
#define HASH_CPP

#include "Hash.h"


using namespace std;

///////////////////////////
////// Constructor ////////
///////////////////////////
// 
// Checks if the file exists, then
// Converts the char * variables
// to integers and puts them into their 
// proper member variables.
// 
//
///////////////////////////
Hash::Hash(char *filename, char *num, char *numIntervals, char *size, char *prime)
{
	Util::FileExists(filename);

	fileName = filename;
	sscanf(num, "%d", &numInts);
	sscanf(numIntervals, "%d", &interval);
	sscanf(size, "%d", &tableSize);
	sscanf(prime, "%d", &largestPrime);

	//storedNumbers.reserve(numInts); // Reserves a certain amount of memory for the vector
	storedNumbers = vector<FileValues>(numInts);

	/*
	for (unsigned int i = 0; i < storedNumbers.capacity(); i++){
		storedNumbers[i].info = EMPTY;
	}	
	*/

	//PrintValues();

	ReadFromFile();

	/*
	linearHashTable.reserve(tableSize);
	quadraticHashTable.reserve(tableSize);
	doubleHashTable.reserve(tableSize);
	 */ 
	
	
}// end constructor

///////////////////////////////////
// 
// ReadFromFile opens the file.
// reads from it, calls the Util
// function to grab the digits,
// and then puts it into the 
// vector storedNumbers
//
//////////////////////////////////
void Hash::ReadFromFile()
{

        // Opening the file 
 	ifstream inFile;
	inFile.open(fileName.c_str(),ios_base::in);
	
	//if opening fails, it will exit the program
	if(inFile.fail()){
	  cerr << "Error opening file" << endl;
	  exit(1);
	}// end if
	
	unsigned int counter = 0;// This is to resize the vector if there are too many items.	

	while (!inFile.eof())
	{

	    string line = ""; // Holds the next line of text from the file
	    inFile >> line;
	    //cout << line << endl;

	    if (line.empty() == false && Util::IsAllDigits(line))
	    {
		
		line = Util::GrabDigits(line); // Grabs the digits from the string
		//cout << "Entered here " << line << endl;
		int temp = 0;
		sscanf(line.c_str(), "%d", &temp);

		if (counter == storedNumbers.capacity())
  		{
			// resize the vector if it starts getting full
			// by putting the data in a temporary vector,
			// replacing the vector at storedNumbers with 1 bigger
			// This will only happen when N does not exactly match the
			// actual number of data to be hashed!
			vector<FileValues> temporary = vector<FileValues>(storedNumbers.capacity()+1); 
			//temporary.reserve(storedNumbers.capacity() + 1);
			
			for (unsigned int i = 0; i < temporary.capacity(); i++)
			{
				temporary[i].element = storedNumbers[i].element;
				temporary[i].info = storedNumbers[i].info;

			}

			storedNumbers = vector<FileValues>(storedNumbers.capacity() + 1);

			for (unsigned int i = 0; i < temporary.capacity(); i++)
			{
				storedNumbers[i].element = temporary[i].element;
				storedNumbers[i].info = temporary[i].info;
			}			

			// This causes loss of data for some reason
			//storedNumbers.resize(storedNumbers.capacity() + 1);
		}// end if
		
		// Stores the data and turns the info to FROM_FILE 
		// to note that the data is valid
		storedNumbers[counter].element = temp;
		storedNumbers[counter].info = FROM_FILE;
		counter++;
		
		
	    }// end if
	    
	    //PrintValues();

	}// end while

	inFile.close(); // closes the file
	
	//PrintValues();


}// end ReadFromFile()




/**
 * Resets the output file to make it empty.
 */
void Hash::ResetOutputFile()
{

	FILE *outfile;
	
	if((outfile=freopen("results.txt", "w" ,stdout))==NULL) {
    		printf("Cannot open file.\n");
    		exit(1);
  	}// end if
	
	cout << " " << endl;
	fclose(stdout);

	FILE *tablefile;
	
	if((tablefile=freopen("table.txt", "w" ,stdout))==NULL) {
    		printf("Cannot open file.\n");
    		exit(1);
  	}// end if
	
	cout << " " << endl;
	fclose(stdout);

}// end ResetoutputFile





/////////////////////////////////
// 
// This is will use linear probing
// and output the results
// at the intervals described
//
////////////////////////////////
void Hash::LinearHash()
{
       int counter = 0; // counter used to compare with interval to print the data
	int successes = 0; // counter for the number of successful insertions
	int failures = 0; // counter for the number of failures
	
	// Opening the file and redirects the cout and prinf
	// to print into a file
	FILE *outfile;
	
	if((outfile=freopen("results.txt", "a" ,stdout))==NULL) {
    		printf("Cannot open file.\n");
    		exit(1);
  	}// end if
	
	// Ensures the printing of doubles prints 
	// to the accuracy of 2 decimal places
	cout << fixed;
	cout.precision(2);
	
	// This prints the heading for the data
	string type = "Linear"; 
	PrintHeading(type.c_str());

	LinearProbing<int> linear = LinearProbing<int>(static_cast<unsigned int>(tableSize));
	
	// loops through the numbers insert them into the linear probing class
	for (unsigned int i = 0; i < storedNumbers.capacity(); i ++){

		if (storedNumbers[i].info == FROM_FILE){

		          // Track the successes and failures
			if(linear.insert(storedNumbers[i].element)){
				successes++;
			}// end if
			else
				failures++;

			counter++;
			
			// print if it was available
			if (counter % interval == 0){
			        // Print the insertion data
				printf("%*d", 5, counter);
				cout << "     ";
				cout << (double)successes / (double)tableSize;
				printf("%*d", 9, successes);
				printf("%*d", 8, failures);
				cout << "\t";
				
				// Print Probe data
				printf("%*d", 9, linear.GetTotalProbes());
				cout << "    " << (double)linear.GetTotalProbes() / (double)counter;
				printf("%*d", 6, linear.GetMaxProbes());
	
				// Print cluster data
				linear.CalculateClusters();		
				printf("%*d", 11, linear.GetNumClusters());	
				cout << "   " << linear.GetAverageClusters();
				printf("%*d", 7, linear.GetMaxClusters());

				cout << endl;
				
			}// end if

			
		}// end if

		/*	
		else{
			cout << "BREAK" << i << endl;
			break;
		}// end else
		*/

	}// end for
	
	// Debugging data
	//cout << "Reached end of Linear Hash" << endl;
	
	fclose(stdout);
	
	FILE *tablefile;
	
	if((tablefile=freopen("table.txt", "a" ,stdout))==NULL) {
    		printf("Cannot open file.\n");
    		exit(1);
  	}// end if
	cout << "\n";
	linear.PrintTable();
	fclose(stdout);

	
	
	

}// end LinearHash




/////////////////////////////////
// 
// This is will use quadratic probing
// and output the results
// at the intervals described
//
////////////////////////////////
void Hash::QuadraticHash()
{
       int counter = 0; // counter used to compare with interval to print the data
	int successes = 0; // counter for the number of successful insertions
	int failures = 0; // counter for the number of failures
	
	// Opening the file and redirects the cout and prinf
	// to print into a file
	FILE *outfile;
	
	if((outfile=freopen("results.txt", "a" ,stdout))==NULL) {
    		printf("Cannot open file.\n");
    		exit(1);
  	}// end if
	
	// Ensures the printing of doubles prints 
	// to the accuracy of 2 decimal places
	cout << fixed;
	cout.precision(2);
	
	// This prints the heading for the data
	string type = "Quadratic"; 
	PrintHeading(type.c_str());

	QuadraticProbing<int> quadratic = QuadraticProbing<int>(static_cast<unsigned int>(tableSize));
	
	// loops through the numbers insert them into the quadratic probing class
	for (unsigned int i = 0; i < storedNumbers.capacity(); i ++){

		if (storedNumbers[i].info == FROM_FILE){

		          // Track the successes and failures
			if(quadratic.insert(storedNumbers[i].element)){
				successes++;
			}// end if
			else
				failures++;

			counter++;
			
			// print if it was available
			if (counter % interval == 0){
			        // Print the insertion data
				printf("%*d", 5, counter);
				cout << "     ";
				cout << (double)successes / (double)tableSize;
				printf("%*d", 9, successes);
				printf("%*d", 8, failures);
				cout << "\t";
				
				// Print Probe data
				printf("%*d", 9, quadratic.GetTotalProbes());
				cout << "    " << (double)quadratic.GetTotalProbes() / (double)counter;
				printf("%*d", 6, quadratic.GetMaxProbes());
	
				// Print cluster data
				quadratic.CalculateClusters();		
				printf("%*d", 11, quadratic.GetNumClusters());	
				cout << "   " << quadratic.GetAverageClusters();
				printf("%*d", 7, quadratic.GetMaxClusters());

				cout << endl;
				
			}// end if

			
		}// end if	
		else{
			cout << "BREAK" << i << endl;
			break;
		}// end else
	}// end for
	
	// Debugging data
	//cout << "Reached end of Quadratic Hash" << endl;
	
	fclose(stdout);
	
	FILE *tablefile;
	
	if((tablefile=freopen("table.txt", "a" ,stdout))==NULL) {
    		printf("Cannot open file.\n");
    		exit(1);
  	}// end if
	cout << "\n";
	quadratic.PrintTable();
	fclose(stdout);

}// end QuadraticHash




/////////////////////////////////
// 
// This is will use double probing
// and output the results
// at the intervals described
//
////////////////////////////////
void Hash::DoubleHash()
{
        int counter = 0; // counter used to compare with interval to print the data
	int successes = 0; // counter for the number of successful insertions
	int failures = 0; // counter for the number of failures
	
	// Opening the file and redirects the cout and prinf
	// to print into a file
	FILE *outfile;
	
	if((outfile=freopen("results.txt", "a" ,stdout))==NULL) {
    		printf("Cannot open file.\n");
    		exit(1);
  	}// end if
	
	// Ensures the printing of doubles prints 
	// to the accuracy of 2 decimal places
	cout << fixed;
	cout.precision(2);
	
	// This prints the heading for the data
	string type = "Double"; 
	PrintHeading(type.c_str());

	DoubleProbing<int> doubleHash = DoubleProbing<int>(static_cast<unsigned int>(tableSize), largestPrime);
	
	// loops through the numbers insert them into the double probing class
	for (unsigned int i = 0; i < storedNumbers.capacity(); i ++){

		if (storedNumbers[i].info == FROM_FILE){

		          // Track the successes and failures
			if(doubleHash.insert(storedNumbers[i].element)){
				successes++;
			}// end if
			else
				failures++;

			counter++;
			
			// print if it was available
			if (counter % interval == 0){
			        // Print the insertion data
				printf("%*d", 5, counter);
				cout << "     ";
				cout << (double)successes / (double)tableSize;
				printf("%*d", 9, successes);
				printf("%*d", 8, failures);
				cout << "\t";
				
				// Print Probe data
				printf("%*d", 9, doubleHash.GetTotalProbes());
				cout << "    " << (double)doubleHash.GetTotalProbes() / (double)counter;
				printf("%*d", 6, doubleHash.GetMaxProbes());
	
				// Print cluster data
				doubleHash.CalculateClusters();		
				printf("%*d", 11, doubleHash.GetNumClusters());	
				cout << "   " << doubleHash.GetAverageClusters();
				printf("%*d", 7, doubleHash.GetMaxClusters());

				cout << endl;
				
			}// end if

			
		}// end if	
		else{
			cout << "BREAK" << i << endl;
			break;
		}// end else
	}// end for
	
	// Debugging data
	
	//cout << "Reached end of Double Hash" << endl;
	
	fclose(stdout);
	
	FILE *tablefile;
	
	if((tablefile=freopen("table.txt", "a" ,stdout))==NULL) {
    		printf("Cannot open file.\n");
    		exit(1);
  	}// end if
	cout << "\n";
	doubleHash.PrintTable();
	fclose(stdout);


}// end DoubleHash


void Hash::PrintValues()
{
	cout << "\nTable of Numbers from File (Not yet Hashed)" << endl;
	for (unsigned int i = 0; i < storedNumbers.capacity(); i++)
	{
		cout << storedNumbers[i].element << " ";
		if (storedNumbers[i].info ==  EMPTY)
				cout << "EMPTY";	
			else if (storedNumbers[i].info ==  FROM_FILE)
				cout << "FROM_FILE";
		cout << endl;
		
	}
	cout << "Capacity: " <<  storedNumbers.capacity() << endl;
	cout << "///// USER ENTERED VALUES FROM COMMANDLINE /////" << endl;
	cout << "Filename: " << fileName << endl;
	cout << "Number of random integers: " << numInts << endl;
	cout << "Interval: " << interval << endl;
	cout << "Size of table: " << tableSize << endl;
	cout << "Largest prime less than M: " << largestPrime << endl;

}

void Hash::PrintHeading(const char *type)
{
	cout << "\n                          " << type;
	cout << " Probing Analysis (Table size = " << tableSize << ")" << endl;
	cout << "                --- Inserts ---   ------- Probes -------    ----- Clusters ------" << endl;
	cout << "    N   lambda  success  failed     total    avg    max     number   avg     max" << endl;

}

#endif
