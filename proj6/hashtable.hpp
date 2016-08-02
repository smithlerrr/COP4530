#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include "hashtable.h"

using namespace cop4530;

template <typename K, typename V>
HashTable<K,V>::HashTable()
{
  currentSize = 0;
  totalSize = default_capacity;
  theList.resize(default_capacity);
}

template <typename K, typename V>
HashTable<K,V>::HashTable(size_t hashSize)
{
  totalSize = prime_below(hashSize);
  currentSize = 0;
  theList.resize(prime_below(hashSize));
}

template <typename K, typename V>
HashTable<K,V>::~HashTable()
{
  for(size_t i = 0; i < theList.size(); ++i)
    theList[i].clear();
}

template <typename K, typename V>
bool HashTable<K,V>::contains(const K &k)
{
  auto &thisList = theList[myhash(k)];
  auto it = thisList.begin();

  for (; it != thisList.end(); it++)
  {
    if (k == it->first)
    {
      cout << "\n*****User '" << k << "' found.";
      return true;
    }
  }
  cout << "\n*****User '" << k << "' was not found.";  
  return false;
}

template <typename K, typename V>
bool HashTable<K,V>::match(const std::pair<K,V> &kv) const
{
  auto thisList = theList[myhash(kv.first)];
  auto it = thisList.begin();

  for (; it != thisList.end(); it++)
  {
    if (kv.first == it->first)
    {
       if (kv.second == it->second)
      {
        cout << "\n*****User '" << kv.first << "' found.";
        return true;
      }
    }
  }
  return false;
}

template <typename K, typename V>
bool HashTable<K,V>::insert(const std::pair<K,V> & kv)
{
  if(++currentSize >= theList.size())
    rehash();

  theList[myhash(kv.first)].push_back(kv);
  cout << "\nEntry added" << endl;
  currentSize++;
  return true;
}

template <typename K, typename V>
bool HashTable<K,V>::insert(std::pair<K,V> && kv)
{
  if(++currentSize >= theList.size())
    rehash();

  theList[myhash(kv.first)].push_back(kv);
  cout << "\nEntry added" << endl;
  currentSize++;
  return true;
}

template <typename K, typename V>
bool HashTable<K,V>::remove(const K &k) 
{
  auto &whichList = theList[myhash(k)];
  auto itr = find(begin(whichList), end(whichList), k);
  if(itr == end(whichList))
    return false;

  whichList.erase(itr);
  --currentSize;
  return true;

}

template <typename K, typename V>
void HashTable<K,V>::clear()
{
  for(auto &thisList : theList)
    thisList.clear();
}

template <typename K, typename V>
bool HashTable<K,V>::load(const char *filename)
{
  string line, pass;
  ifstream file;
  file.open(filename);
  if(!file)
  {
    cout << "*****Error: Could not open file to read" << endl;
    return false;
  }

  while(getline(file,line,':'))
  {
    pair <string, string> loadUser;
    loadUser.first = line;
    getline(file, pass);
    loadUser.second = pass;
    
    auto itr = theList[myhash(loadUser.first)].begin();
    for(;itr != theList[myhash(loadUser.first)].end(); ++itr)
    {
      if(itr->first == loadUser.first)
      {
        cout << "\n*****Error: User already exists. Could not add user. \n";
        return false;;
      }
    }

    theList[myhash(loadUser.first)].push_back(loadUser);
    line = "";
    pass = "";  
  }
  
  file.close();
}

template <typename K, typename V>
void HashTable<K,V>::dump()
{
  for(size_t i = 0; i < theList.size(); ++i)
  {
    list < pair < string, string > > &thisList = theList[i];
    list < pair < string, string> >::iterator it = thisList.begin();
    
    for(it; it != thisList.end(); ++it)
    {
      cout << "\nV[" << i << "]" << "\t";
      cout << it->first << ":" << it->second;
    }
  }
}

template <typename K, typename V>
bool HashTable<K,V>::write_to_file(const char *filename)
{
  ofstream file;
  file.open(filename);
  for(unsigned int i = 0; i < theList.capacity(); ++i)
  {
    if(!theList[i].empty())
    {
      list<pair <string, string> >::iterator itr;
      for( itr = theList[i].begin(); itr != theList[i].end(); itr++ )
        file << itr->first << ":" << itr->second << "\n";

      return true;
    }
    else
    {
      cout <<"****Error: Could not write to file";
      return false;
    }
  }

  file.close();
}

template <typename K, typename V>
void HashTable<K,V>::makeEmpty()
{
  currentSize = 0;
  for(auto &thisList : theList)
    thisList.clear();
}

template <typename K, typename V>
void HashTable<K,V>::rehash()
{
  vector<list<hashEntry> > oldLists = theList;
  theList.resize(prime_below(2 * theList.size()));
  for (unsigned int j = 0; j < theList.size(); j++)
    theList[j].clear();

  currentSize = 0;
  for (auto & theList : oldLists)
  {
    for (auto &thisList : theList)
      insert(move(thisList));
  }
}

template <typename K, typename V>
size_t HashTable<K,V>::myhash(const K &k)
{
  unsigned int hashVal = 0;

  for(char ch : k)
    hashVal = 37 * hashVal + ch;

  return hashVal % theList.size();
}

template <typename K, typename V>
unsigned long HashTable<K,V>::prime_below(unsigned long n)
{
  if (n > max_prime)
  {
    std::cerr << "** input too large for prime_below()\n";
    return 0;
  }

  if (n == max_prime)
  {
    return max_prime;
  }

  if (n <= 1)
  {
    std::cerr << "** input too small \n";
    return 0;
  }

  // now: 2 <= n < max_prime
  std::vector <unsigned long> v (n+1);
  setPrimes(v);
  while (n > 2)
  {
    if (v[n] == 1)
      return n;
    
    --n;
  }

  return 2;
}

//Sets all prime number indexes to 1. Called by method prime_below(n) 
template <typename K, typename V>
void HashTable<K, V>::setPrimes(std::vector<unsigned long>& vprimes)
{
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.capacity();

  for (i = 2; i < n; ++i)
    vprimes[i] = 1;

  for( i = 2; i*i < n; ++i)
    {
      if (vprimes[i] == 1)
        for(j = i + i ; j < n; j += i)
          vprimes[j] = 0;
    }
}
#endif