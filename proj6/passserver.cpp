#ifndef PASSSERVER_CPP
#define PASSSERVER_CPP

#include <iostream>
#include "hashtable.h"
#include "passserver.h"

using namespace std;

PassServer::PassServer(size_t size)
{
  HashTable<string,string> hTable(size);
  theList.resize(default_capacity);
}

PassServer::~PassServer()
{}

bool PassServer::load(const char *filename)
{
  if (HashTable::load(filename))
    return true;

  else
    return false;
}

bool PassServer::addUser(std::pair<string,string> &kv)
{
  if(match(kv) == true)
  {
    cout << "\n*****Error: User already exists. Could not add user." << endl;
    return false;
  }
  
  else
  {
    encrypt(kv.second);
    insert(kv);
    cout << "\nUser " << kv.first << " added!" << endl;
    return true;
  }
}

bool PassServer::addUser(std::pair<string,string> &&kv)
{
  if(match(kv) == true)
  {
    cout << "\n*****Error: User already exists. Could not add user." << endl;
    return false;
  }
  else
  {
    encrypt(kv.second);
    insert(kv);
    cout << "\nUser " << kv.first << " added!" << endl;
    return true;
  }
}

bool PassServer::removeUser(const string &k)
{
  list < pair <string, string> > &thisList = theList[myhash(k)];
  list < pair <string, string> >::iterator it;
  for(it = thisList.begin(); it != thisList.end(); it++)
  {
     if(k == it->first)
      {
        thisList.erase(it);
        cout << "\nUser " << k << " deleted." << endl;
        return true;
      }
  }
  
  cout << "\n*****Error: User not found.  Could not delete user" << endl;
  return false;
}

bool PassServer::changePassword(const pair<string, string> &p, const string &newpassword)
{
    bool user_found = false;
    bool pw_correct = false;

    list < pair <string, string> > &thisList = theList[myhash(p.first)];
    list < pair <string, string> >::iterator it;

    if(match(p) == false)
    {
      cout << "\n*****Error: User not found.  Could not change user password" << endl;
      return false;
    }

    for(it = thisList.begin(); it != thisList.end(); it++)
    {
      if(p.first == it->first)
      {
        if(p.second != it->second)
        {
          cout << "\n*****Error: Passwords do not match.";
          return false;
        }

        else if(p.second == it->second)
        {
          if(p.second == newpassword)
          {
            cout << "\n*****Error: New password cannot match old password.";
            return false;
          }
        }    
      }
    }

    it->second = newpassword;
    cout << "\nPassword changed for user " << p.first << endl;
    return true;
}

bool PassServer::find(const string &user)
{
	if(!contains(user))
  {
    cout << "*****Error: User could not be found." << endl;
    return false;
  }

  else
  {
    cout << "User " << user << "found!" << endl;
    return true;
  }
}

void PassServer::dump()
{
  for(int i = 0; i < theList.size(); ++i)
  {
    list <pair<string,string>> &thisList = theList[i];
    list < pair < string, string> >::iterator itr = thisList.begin();
    for(itr; itr != thisList.end(); ++itr)
    {
      cout << "\nV[" << i << "]" << "\t";
      cout << itr->first << ":" << itr->second;
    }
  }
}

size_t PassServer::size()
{
  vector < list < pair <string, string> > >::const_iterator it = theList.begin();
  list < pair <string, string> >::const_iterator it2;
  int x = 0;
  for(; it != theList.end(); it++)
  {
     if(!(*it).empty())
     for(it2 = (*it).begin(); it2 != (*it).end(); it2++)
      {
          x++;
      }
  }
  return x;
}

bool PassServer::write_to_file(const char *filename)
{
    HashTable::write_to_file(filename);
    return true;
}

string PassServer::encrypt(const string &str)
{
	char *password = new char [100];
  char salt[] = "$1$########";

  strcpy(password, crypt(str.c_str(), salt));
  string encryptPass = password;
  return encryptPass.substr(12,34);
}
#endif