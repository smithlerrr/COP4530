#include <iostream>
#include "networksList.h"
/****************************************************
 ** Function: NetworksList()                       **
 ** Default constructor for the NetworksList class **
 ****************************************************/
NetworksList::NetworksList()
{
	numNetworks = 0;
	sorted = false;
}
/******************************************************
 ** Function: NetworksList(NetworksList __inNetList) **
 ** Copy constructor for NetworksList class          **
 ******************************************************/
NetworksList::NetworksList(const NetworksList& __inNetList)
{
	numNetworks = __inNetList.GetNumNetworks();
	networks = __inNetList.CopyNetworks();
	sorted = false;
}
/****************************************************
 ** Function: GetNumNetworks() const               **
 ** Returns the number of networks entered into    **
 ** the networks vector                            **
 ** Return value is int                            **
 ****************************************************/
int NetworksList::GetNumNetworks() const
{
	return numNetworks;
}
/****************************************************
 ** Function: GetNumNeighbors(int __netNum)        **
 ** Returns the number of neighbors of a specific  **
 ** network in the list                            **
 ** Parameters: int = location of network on vector**
 ** Return: int = number of neighbors              **
 ****************************************************/
int NetworksList::GetNumNeighbors(int __netNum) const
{
	int numNeighbors = 0;
	for (int i = 0; i < networks.size(); ++i) {
		// once the network is found
		if (networks[i].GetNetworkNum() == __netNum) {
			// get the num of neighbors
			numNeighbors = networks[i].GetNumNeighbors();
			// return it
			return numNeighbors;
		}
	}
	// if it gets here, the network wasn't found
	return numNeighbors;
}
/****************************************************
 ** Function: GetNumNeighbors()                    **
 ** Sorts the networks vector using a quicksort    **
 ** algorithm                                      **
 ** Parameters: none                               **
 ** Return: none                                   **
 ****************************************************/
void NetworksList::SortNetworks()
{
	// if not sorted, sort
	if (!sorted) {
		int init = 0;
		int lastNet = GetNumNetworks();
		QuickSort(init, lastNet);
		sorted = true;
	}
} // sort neighbors
/******************************************************
 ** Function: InsertNetwork(const Network& __newNet) **
 ** Inserts a new network into the networks vector   **
 ** Parameters: Network = network to be entered      **
 ** Return: bool: true = success; false = failure    **
 ******************************************************/
bool NetworksList::InsertNetwork(const Network& __newNet)
{
	// check if the network has been entered in the system
	for (int i = 0; i < networks.size(); ++i) {
		if (networks[i].GetNetworkNum() == __newNet.GetNetworkNum()) {
			return false;
		}
		else { continue; }
	}
	// if the network has not been entered in the vector yet
	networks.push_back(__newNet); // add to the end of the vector
	numNetworks++;
	sorted = false;
	return true;
}
/***************************************************************
 ** Function: InsertNeighbor(int __netNum, int __newNeighbor) **
 ** Inserts a new neighbor to the specified network           **
 ** Parameters: int __netNum = number of the network          **
 **             int __newNeighbor = new neighbor to enter     **
 ** Return: bool: true = success; false = failure             **
 ***************************************************************/
bool NetworksList::InsertNeighbor(int __netNum, int __newNeighbor)
{
	// start looking for a network with __netNum
	for (int i = 0; i < networks.size(); ++i) {
		// if its found try to insert it into the object
		if (__netNum == networks[i].GetNetworkNum()) {
			if (networks[i].InsertNeighbor(__newNeighbor)) {
			 	return true;
			} // if
			// else, the neighbor has been entered previously
			else {
				return false;
			} // else
		} // if
		// if that is not the network, keep looking
		continue;
	}
	// either the network wasnt found, or another error occurred
	return false;
}
/****************************************************
 ** Function: CopyNetworks() const                 **
 ** Returns a full copy of the networks vector     **
 ** Parameters: none                               **
 ** Return: vector<Network> = copy of networks     **
 ****************************************************/
std::vector<Network> NetworksList::CopyNetworks() const
{
	return networks;
}
/****************************************************
 ** Function: PrintNetwork(int __ntwrk)            **
 ** Prints the specified network                   **
 ** Parameter: int = position of the network       **
 ** Return: none                                   **
 ****************************************************/
void NetworksList::PrintNetwork(int __ntwrk)
{
	networks[__ntwrk].Print();
}
			/*********************/
			/** PRIVATE METHODS **/
			/*********************/
/****************************************************
 ** Function: Swap(int __fi, int __si)             **
 ** Swaps two networks in the networks vector      **
 ** Parameters: int __si = first network position  **
 **             int __fi = second network position **
 ** Return: none                                   **
 ****************************************************/
void NetworksList::Swap(int __fi, int __si)
{
	Network tmpNet = networks[__fi];
	networks[__fi] = networks[__si];
	networks[__si] = tmpNet;
}
/****************************************************
 ** Function: QuickSort(int __fi, int __si)        **
 ** QuickSort algorith adapted to the networks     **
 ** vector of this class                           **
 ** Parameters: int __si = first index             **
 **             int __fi = second index            **
 ** Return: none                                   **
 ****************************************************/
void NetworksList::QuickSort(int __fi,int __si)
{
	int r;
	if(__fi<__si) {
	    r=Partition(__fi,__si);
	    QuickSort(__fi,r);
	    QuickSort(r+1,__si);
	} // if
} // QuickSort
/****************************************************
 ** Function: Partition(int __fi, int __si)        **
 ** Returns a pivot for the quicksort to use       **
 ** Parameters: int __si = first index             **
 **             int __fi = second index            **
 ** Return: int = the pivot                        **
 ****************************************************/
int NetworksList::Partition(int __fi,int __si)
{
	Network x = networks[__fi];
	int i=__fi;
	int j;

	for(j=__fi+1; j<__si; j++) {
		if(networks[j]>=x) {
	    	i=i+1;
		    // swap the networks
	    	Swap(i,j);
		} // if
	} // for
	// swap the networks
	Swap(i,__fi);
	return i;
} // Partition