#include <iostream>
#include <algorithm>
#include "network.h"
/** OPERATOR OVERLOADS **/
bool operator< (const Network& __n1, const Network& __n2)
{
	if (__n1.GetNumNeighbors() < __n2.GetNumNeighbors()) {
		return true;
	}
	else if (__n1.GetNumNeighbors() == __n2.GetNumNeighbors()) {
		if (__n1.GetNetworkNum() > __n2.GetNetworkNum()) {
			return true;
		}
	}
	else {
		return false;
	}
}

bool operator> (const Network& __n1, const Network& __n2)
{
	return (__n2 < __n1);
}

bool operator<= (const Network& __n1, const Network& __n2)
{
	return !(__n1 > __n2);
}

bool operator>= (const Network& __n1, const Network& __n2)
{
	return !(__n1 < __n2);
}

bool operator== (const Network& __n1, const Network& __n2)
{
	return (!(__n1 < __n2) && !(__n1 > __n2));
}

bool operator!= (const Network& __n1, const Network& __n2)
{
	return (!(__n1 == __n2));
}
/** OPERATOR OVERLOADS **/
/****************************************************
 ** Function: Network(int __num)                   **
 ** Default, and regular constructor. If no        **
 ** parameters are passed, network number = 1      **
 ** Parameters: int = number of the network        **
 ** Return: none                                   **
 ****************************************************/
Network::Network(int __num)
{
	if (__num > 0) {
		networkNum = __num;
	}
	numNeighbors = 0;
	sorted = false;
}
/****************************************************
 ** Function: Network(const Network& __nIn)        **
 ** Copy constructor                               **
 ** Parameters: Network __nIn = network to copy    **
 ** Return: none                                   **
 ****************************************************/
Network::Network(const Network& __nIn)
{
	networkNum = __nIn.GetNetworkNum();
	numNeighbors = __nIn.GetNumNeighbors();
	sorted = __nIn.IsSorted();
	neighbors = __nIn.CopyNeighbors();
}
/****************************************************
 ** Function: GetNetworkNum() const                **
 ** Returns the number of the network              **
 ** Parameters: none                               **
 ** Return: int = number of the network            **
 ****************************************************/
// returns the network number
int Network::GetNetworkNum() const
{
	return networkNum;
}
/****************************************************
 ** Function: GetNumNeighbors() const              **
 ** Returns the number of neighbors to the network **
 ** Parameters: none                               **
 ** Return: int = number of neighbors              **
 ****************************************************/
int Network::GetNumNeighbors() const
{
	return numNeighbors;
}
/****************************************************
 ** Function: IsSorted() const                     **
 ** Returns the value of sorted                    **
 ** Parameters: none                               **
 ** Return: bool = whether neighbors are sorted    **
 ****************************************************/
bool Network::IsSorted() const
{
	return sorted;
}
/****************************************************
 ** Function: CopyNeighbors() const                **
 ** Returns a complete copy of the neighbors       **
 ** Parameters: none                               **
 ** Return: vector<int> neighbors                  **
 ****************************************************/
std::vector<int> Network::CopyNeighbors() const
{
	return neighbors;
}
/****************************************************
 ** Function: ChangeNetworkNumber(int __newNtwrk)  **
 ** Changes the number of the network to the one   **
 ** specified                                      **
 ** Parameters: int __newNtwrk = new network number**
 ** Return: bool: true = success; false = failure  **
 ****************************************************/
bool Network::ChangeNetworkNumber(int __newNtwrk)
{
	if (__newNtwrk == networkNum || __newNtwrk <= 0) {
		return false;
	}
	else {
		networkNum = __newNtwrk;
		return true;
	}
}
/****************************************************
 ** Function: InsertNeighbor(int __newNbr)         **
 ** Inserts a new neighbor to the network          **
 ** Parameters: int __newNbr = new neighbor        **
 ** Return: bool: true = success; false = failure  **
 ****************************************************/
bool Network::InsertNeighbor(int __newNbr)
{
	// must be positive and not the same as the network number
	if (__newNbr > 0 && __newNbr != networkNum) {
		for (int i = 0; i < neighbors.size(); ++i)	{
			if (__newNbr == neighbors[i]) {
				return false;
			} // if
			else {
				continue;
			} // else
		} // for
		// now that we checked all the neighbors
		neighbors.push_back(__newNbr);
		numNeighbors++;
		sorted = false;
		return true;
	} // if
	return false;
}
/****************************************************
 ** Function: Print()                              **
 ** Prints the network                             **
 ** Parameters: none                               **
 ** Return: none                                   **
 ****************************************************/
void Network::Print()
{
	if (!sorted) { SortNeighbors(); }
	std::cout << networkNum << ' ' << numNeighbors << ' ';
	// check if we are at the end of the std::vector
	for (int i = 0; i < neighbors.size(); ++i) {
		std::cout << neighbors[i];
		i != neighbors.size()-1 ? std::cout << '|' : std::cout << std::endl;
	}
}
/****************************************************
 ** Function: SortNeighbors()                      **
 ** Sorts the network neighbors                    **
 ** Parameters: none                               **
 ** Return: none                                   **
 ****************************************************/
void Network::SortNeighbors()
{
	if (!sorted) {
		std::sort(neighbors.begin(), neighbors.end());
		sorted = true;
	}
}