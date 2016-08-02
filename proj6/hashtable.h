#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <functional>
#include <algorithm>
#include <unistd.h>
#include <vector>
#include <list>
#include <string>
#include <utility>
#include <stdlib.h>
#include <cstring>

using namespace std;
namespace cop4530
{

	static const unsigned int max_prime = 1301081; //max_prime is used by the helpful functions provided to you 
	static const unsigned int default_capacity = 11; //the default_capacity is used if the initial capacity of the underlying vector of the hash table is zero.

	using hashEntry = pair<string, string>;

	template<typename K, typename V>
	class HashTable
	{
		public: 
			HashTable();
			HashTable(size_t);	//constructor. Create a hash table, where the size of the vector is set to prime_below(size) (where size is default  to 101), where prime_below() is a private member function of the HashTable and provided to you.
			~HashTable();	// destructor. Delete all elements in hash table.
			bool contains(const K &k); 		//check if key k is in the hash table.
			bool match(const std::pair<K,V> &kv) const; 	//check if key-value pair is in the hash table.
			bool insert(const std::pair<K,V> &kv); 	//add the key-value pair kv into the hash table. Don't add if kv is already in the hash table. If the key is the hash table but with a different value, the value should be updated to the new one with kv. Return true if kv is inserted or the value is updated; return false otherwise (i.e., if kv is in the hash table).
			bool insert (std::pair<K,V> &&kv); 	//move version of insert.
			bool remove(const K &k); 	//delete the key k and the corresponding value if it is in the hash table. Return true if k is deleted, return false otherwise (i.e., if key k is not in the hash table).
			void clear(); 	//delete all elements in the hash table
			bool load(const char *filename); 	//load the content of the file with name filename into the hash table. In the file, each line contains a single pair of key and value, separated by a white space.
			void dump(); 	//display all entries in the hash table. If an entry contains multiple key-value pairs, separate them by a semicolon character (:) (see the provided executable for the exact output format).
			bool write_to_file(const char *filename); 	//write all elements in the hash table into a file with name filename. Similar to the file format in the load function, each line contains a pair of key-value pair, separated by a white space.
	
		protected:
			void makeEmpty(); //delete all elements in the hash table. The public interface clear() will call this function.
			void rehash(); //Rehash function. Called when the number of elements in the hash table is greater than the size of the vector.
			size_t myhash(const K &k); //return the index of the vector entry where k should be stored.
			unsigned long prime_below (unsigned long);  
			void setPrimes(vector<unsigned long>&);
			int currentSize, totalSize;	
			vector< list < pair <K, V> > >theList;
	};

	#include "hashtable.hpp"
}
#endif