#ifndef NETWORK_H
#define NETWORK_H

#include <vector>

class Network
{
	/** OPERATOR OVERLOADS **/
    friend bool operator< (const Network& n1, const Network& n2);
    friend bool operator> (const Network& n1, const Network& n2);
    friend bool operator<= (const Network& n1, const Network& n2);
    friend bool operator>= (const Network& n1, const Network& n2);
    friend bool operator== (const Network& n1, const Network& n2);
    friend bool operator!= (const Network& n1, const Network& n2);
    /** OPERATOR OVERLOADS **/
	private:
    	int networkNum;
    	int numNeighbors;
    	bool sorted;
    	std::vector<int> neighbors;
	public:
/****************************************************
 ** Function: Network(int __num)                   **
 ** Default, and regular constructor. If no        **
 ** parameters are passed, network number = 1      **
 ** Parameters: int = number of the network        **
 ** Return: none                                   **
 ****************************************************/		
		Network(int = 1);
/****************************************************
 ** Function: Network(const Network& __nIn)        **
 ** Copy constructor                               **
 ** Parameters: Network __nIn = network to copy    **
 ** Return: none                                   **
 ****************************************************/
        Network(const Network&);
/****************************************************
 ** Function: GetNetworkNum() const                **
 ** Returns the number of the network              **
 ** Parameters: none                               **
 ** Return: int = number of the network            **
 ****************************************************/
		int GetNetworkNum() const;
/****************************************************
 ** Function: GetNumNeighbors() const              **
 ** Returns the number of neighbors to the network **
 ** Parameters: none                               **
 ** Return: int = number of neighbors              **
 ****************************************************/
		int GetNumNeighbors() const;
/****************************************************
 ** Function: IsSorted() const                     **
 ** Returns the value of sorted                    **
 ** Parameters: none                               **
 ** Return: bool = whether neighbors are sorted    **
 ****************************************************/
        bool IsSorted() const;
/****************************************************
 ** Function: CopyNeighbors() const                **
 ** Returns a complete copy of the neighbors       **
 ** Parameters: none                               **
 ** Return: vector<int> neighbors                  **
 ****************************************************/
		std::vector<int> CopyNeighbors() const;
/****************************************************
 ** Function: ChangeNetworkNumber(int __newNtwrk)  **
 ** Changes the number of the network to the one   **
 ** specified                                      **
 ** Parameters: int __newNtwrk = new network number**
 ** Return: bool: true = success; false = failure  **
 ****************************************************/
		bool ChangeNetworkNumber(int);
/****************************************************
 ** Function: InsertNeighbor(int __newNbr)         **
 ** Inserts a new neighbor to the network          **
 ** Parameters: int __newNbr = new neighbor        **
 ** Return: bool: true = success; false = failure  **
 ****************************************************/
		bool InsertNeighbor(int);
/****************************************************
 ** Function: Print()                              **
 ** Prints the network                             **
 ** Parameters: none                               **
 ** Return: none                                   **
 ****************************************************/
		void Print();
/****************************************************
 ** Function: SortNeighbors()                      **
 ** Sorts the network neighbors                    **
 ** Parameters: none                               **
 ** Return: none                                   **
 ****************************************************/
		void SortNeighbors();
};

#endif