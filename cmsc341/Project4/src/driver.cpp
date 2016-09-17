/***************************************************************
 * File:    driver.cpp
 * Project: CMSC 341 - Project 4 - Comparing Hashing Techniques
 * Author : James Guan
 * Date   : 12-November-2014
 * Section: Lecture-02
 * E-mail:  jguan3@umbc.edu
 *
 * The part of the project that contains main to
 * run the Hashing using linear, quadratic, and double probing.
 *
 * NOTES: I am trying to make the TA's jobs easier by printing to the console some debugging data,
 * 	and the tables after all the hashing into a file called table.txt. Hope this helps.
 *	Also, I was going to make a Hash parent class with a child class that just overrides the 
 *	insert function but I ran out of time. Sorry for all the repetitive code. Just know that 
 *	the only thing different in all the probing classes is the findPos function and that the
 * 	double probing part has an extra function called secondHash.
 *
 *************************************************************/

#include "Hash.h"

using namespace std;

int main(int argc, char *argv[]) {
	

  // Checks for correct number of command line arguments.
  if (argc != 6) {

        cout << "Not enough command line arguments" << endl;
	cout << "It should look like this: " << endl;
	cout << "./Driver.out input1.txt 10 1 9 7" << endl;
	cout << "Exiting..." << endl;

  }// end if

  // Run if the correct number of command line arguments are found.
  else{
  	try {
		// This will first pass in all the command line arguments
		// Then it will call the different hashing functions 
		// to perform the probes.
    		Hash hashes(argv[1], argv[2], argv[3], argv[4], argv[5]);

    		hashes.PrintValues(); // Comment this out if you don't want console debug data

		hashes.ResetOutputFile();
    		hashes.LinearHash();
    		hashes.QuadraticHash();
		hashes.DoubleHash();
  		cout << endl;
  	}// end try
  	// Error catching
  	catch (Exceptions &cException) {
    		cout << "EXCEPTION: " << cException.GetMessage() << endl;
    	return 1;
  	}// end catch
  }// end else

  //Uncomment for number of seconds running.
  cout << clock() / (float)(CLOCKS_PER_SEC) << endl;
  return 0;

}// end main
