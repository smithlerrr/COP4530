#include <iostream>
#include <sstream>
#include <ctime>
#include "networksList.h"
// debugging flags
const bool DEBUG = false;
const bool DEBUG_TIME = false;

/* FUNCTION PROTOTYPES */
void FindIndex(std::string, int&, int&);
std::vector<int> GetNetworks(std::string);
/* END FUNCTION PROTOTYPES */

int main()
{
	// variables initialization
	int firstIndex, secondIndex, // used to get substrings
		prevNet, currentNet, nextNet; // used to get neighbors
	std::string input, // stores each line of the text file
		subStr; // the sub string containing numbers
	// initialize a vector to store the temp network numbers
	// for each line
	std::vector<int> tmpNetworks;
	NetworksList networksList; // create a network list object

	clock_t t1;
	t1 = clock();

	// read each line until no more input is detected
	while(getline(std::cin, input) && input != "-1" && input != "") {
		// find the indexes to use to get a substring
		FindIndex(input, firstIndex, secondIndex);
		// get the substring
		subStr = input.substr(firstIndex, secondIndex);
		if (DEBUG) {
			std::cout << "The substring is: " << subStr << std::endl;
		}
		// save the numbers
		tmpNetworks = GetNetworks(subStr);
		prevNet = 0; // initialize every time
		currentNet = 0; // initialize every time
		nextNet = 0; // initialize every time
		for (int i = 0; i < tmpNetworks.size(); ++i) {
			currentNet = tmpNetworks[i];
			// if is not the last number in the temp vector
			if (i != tmpNetworks.size() - 1) {
				nextNet = tmpNetworks[i+1];
			} // if
			else {
				nextNet = 0;
			} // else
			// make sure the networks don't repeat
			if (currentNet != prevNet) {
				// creaete a new network object
				Network *newNet = new Network(tmpNetworks[i]);
				// input the network number into the networksList
				networksList.InsertNetwork(*newNet);

				if (DEBUG) {
					std::cout << "last net num:" << tmpNetworks[i] 
						<< std::endl;
				}
				// since the neighbor to be entered will be to the last network
				// of the vector, we use that to our advantage
				// insert neighbors into the network
				if (prevNet != 0) {
					networksList.InsertNeighbor(tmpNetworks[i], prevNet);
				}
				if (nextNet != 0) {
					networksList.InsertNeighbor(tmpNetworks[i], nextNet);
				}
				// dealocate memory
				delete newNet;
			}
			// in case that the networks repeat
			else if (currentNet != nextNet) {
				if (nextNet != 0) {
					networksList.InsertNeighbor(tmpNetworks[i], nextNet);
				}
			}
			if (DEBUG) {
				std::cout << "Network " << i+1 << ": " << tmpNetworks[i] 
					<< std::endl;
				std::cout << "PrevNet:" << prevNet << "\nCurrNet:" 
					<< currentNet << "\nNextNEt:" << nextNet << std::endl;
			}
			// maintain sanity
			prevNet = currentNet;
		} // for
	} // while

	networksList.SortNetworks();
	for (int ntwrk = 0; ntwrk < networksList.GetNumNetworks(); ++ntwrk) {
		networksList.PrintNetwork(ntwrk);
	}

	clock_t t2 = clock();
	double clockDiff = ((double)t2 - (double)t1) / CLOCKS_PER_SEC;

	if (DEBUG_TIME) {
		std::cout << "Execution time: " << clockDiff << " seconds" 
			<< std::endl;
	}
	return 0;
}
/**********************************************************
 ** Function: FindIndex(String __in, int __fi, int __si) **
 ** Finds the index of the sixth and seventh bar         **
 ** as __fi, __si, respectively. The string is not       **
 ** changed, but both integer parameters are             **
 ** returned with the respective indexes.                **
 **********************************************************/
void FindIndex(std::string __in, int& __fi, int& __si)
{
	int barCounter = 0;
	bool foundFirstIndex = false,
		foundSecondIndex = false;
	for (int i = 0; i < __in.length(); ++i) {

		if (__in[i] == '|') { barCounter++; }
		if (DEBUG) {
			std::cout << "barCounter: " << barCounter << std::endl;
		}
		if (barCounter == 6 && !foundFirstIndex) {
			__fi = i+1;
			foundFirstIndex = true;
		}
		if (barCounter == 7 && !foundSecondIndex) {
			__si = i;
			foundSecondIndex = true;
		}
	}
	// need to get the amount of chars to second index
	__si -= __fi;
	return;
}
/*****************************************************
 ** Function: GetNetworks(String __in)              **
 ** Accepts a string as parameter, and returns the  **
 ** Network numbers within it. It will ignore '[]'  **
 ** by default, since a char cannot be entered __in **
 ** an int variable                                 **
 *****************************************************/
std::vector<int> GetNetworks(std::string __in)
{
	// create a string stream with the input
	std::istringstream iss(__in);
	// create a vector
	std::vector<int> returnVector;
	int num;
	// read each number
	// and store in the vector
	while(iss >> num) {
		returnVector.push_back(num);
	}
	return returnVector;
}