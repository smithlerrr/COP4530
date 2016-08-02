#ifndef NETWORKSLIST_H
#define NETWORKSLIST_H

#include "network.h"

class NetworksList {
	private:
		int numNetworks;
		bool sorted;
		// this vector of networks is the main purpose of this class
		std::vector<Network> networks;
	/****************************************************
	 ** Function: Swap(int __fi, int __si)             **
	 ** Swaps two networks in the networks vector      **
	 ** Parameters: int __si = first network position  **
	 **             int __fi = second network position **
	 ** Return: none                                   **
	 ****************************************************/
		void Swap(int, int);
	/****************************************************
	 ** Function: QuickSort(int __fi, int __si)        **
	 ** QuickSort algorith adapted to the networks     **
	 ** vector of this class                           **
	 ** Parameters: int __si = first index             **
	 **             int __fi = second index            **
	 ** Return: none                                   **
	 ****************************************************/
		void QuickSort(int, int);
	/****************************************************
	 ** Function: Partition(int __fi, int __si)        **
	 ** Returns a pivot for the quicksort to use       **
	 ** Parameters: int __si = first index             **
	 **             int __fi = second index            **
	 ** Return: int = the pivot                        **
	 ****************************************************/
		int Partition(int, int);
	public:
	/****************************************************
	 ** Function: NetworksList()                       **
	 ** Default constructor for the NetworksList class **
	 ****************************************************/
		NetworksList();
	/******************************************************
	 ** Function: NetworksList(NetworksList __inNetList) **
	 ** Copy constructor for NetworksList class          **
	 ******************************************************/
		NetworksList(const NetworksList&);
	/****************************************************
	 ** Function: GetNumNetworks() const               **
	 ** Returns the number of networks entered into    **
	 ** the networks vector                            **
	 ** Return value is int                            **
	 ****************************************************/
		int GetNumNetworks() const;
	/****************************************************
	 ** Function: GetNumNeighbors(int __netNum)        **
	 ** Returns the number of neighbors of a specific  **
	 ** network in the list                            **
	 ** Parameters: int = location of network on vector**
	 ** Return: int = number of neighbors              **
	 ****************************************************/
		int GetNumNeighbors(int) const;
	/****************************************************
	 ** Function: GetNumNeighbors()                    **
	 ** Sorts the networks vector using a quicksort    **
	 ** algorithm                                      **
	 ** Parameters: none                               **
	 ** Return: none                                   **
	 ****************************************************/
		void SortNetworks();
	/******************************************************
	 ** Function: InsertNetwork(const Network& __newNet) **
	 ** Inserts a new network into the networks vector   **
	 ** Parameters: Network = network to be entered      **
	 ** Return: bool: true = success; false = failure    **
	 ******************************************************/
		bool InsertNetwork(const Network&);
	/***************************************************************
	 ** Function: InsertNeighbor(int __netNum, int __newNeighbor) **
	 ** Inserts a new neighbor to the specified network           **
	 ** Parameters: int __netNum = number of the network          **
	 **             int __newNeighbor = new neighbor to enter     **
	 ** Return: bool: true = success; false = failure             **
	 ***************************************************************/
		bool InsertNeighbor(int, int);
	/****************************************************
	 ** Function: CopyNetworks() const                 **
	 ** Returns a full copy of the networks vector     **
	 ** Parameters: none                               **
	 ** Return: vector<Network> = copy of networks     **
	 ****************************************************/
		std::vector<Network> CopyNetworks() const;
	/****************************************************
	 ** Function: PrintNetwork(int __ntwrk)            **
	 ** Prints the specified network                   **
	 ** Parameter: int = position of the network       **
	 ** Return: none                                   **
	 ****************************************************/
		void PrintNetwork(int);
};

#endif