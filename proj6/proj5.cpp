#include <iostream>
#include <string>
#include <utility>
#include <cstdlib>
#include "hashtable.h"
#include "passserver.h"

using namespace std;
using namespace cop4530;

void Menu();

int main()
{
  char userChoice;
  int userSize;
  string file, user, pass, newpass, fname;
  pair<string,string> product; 
  
  cout << "Enter preferred hash table capacity:";
  cin >> userSize;
  
  PassServer hTable(userSize);   
  Menu();
  cin >> userChoice;
  while (userChoice != 'x')
  {
    switch(userChoice)
    {
      case 'l': 
        cout << "Enter password file name to load from: ";
        cin >> file;
        hTable.load(file.c_str());
        break;
      
      case 'a':
        cout << "\nEnter username:";
        cin >> user;
        cout << "\nEnter password:";
        cin >> pass;
        product = make_pair(user, pass);
        hTable.addUser(product);
        break;
      
      case 'r':
        cout << "\nEnter username to remove:";
        cin >> user; 
        hTable.removeUser(user);
        break;
      
      case 'c': 
        cout << "\nEnter username:";
        cin >> user;
        cout << "\nEnter password:";
        cin >> pass;
        cout <<"\nEnter new password:";
        cin >> newpass;
        product = make_pair(user, pass);
        hTable.changePassword(product, newpass);
        break;
            
      case 'f': 
        cout << "\nEnter username:";
        cin >> user;
        hTable.find(user);
        break;
      
      case 'd': 
        hTable.dump();
        break;
            
      case 's': 
        cout << "\nHashtable size: " << hTable.size() << endl;
        break;
            
      case 'w': 
        cout << "\nEnter password file name to write to:";
        cin >> file;
        hTable.load(fname.c_str());
        hTable.write_to_file(file.c_str());
        break;
      
      case 'x':
        break;
      
      default: cout << "*****Error: Invalid entry.  Try again.\n";
        break;
    }

        Menu();
        cin >> userChoice;
  } 
  return(EXIT_SUCCESS);
}

void Menu()
{
  cout << "\n\n";
  cout << "l - Load From File" << endl;
  cout << "a - Add User" << endl;
  cout << "r - Remove User" << endl;
  cout << "c - Change User Password" << endl;
  cout << "f - Find User" << endl;
  cout << "d - Dump HashTable" << endl;
  cout << "s - HashTable Size" << endl;
  cout << "w - Write to Password File" << endl;
  cout << "x - Exit program" << endl;
  cout << "\nEnter choice : ";
}
