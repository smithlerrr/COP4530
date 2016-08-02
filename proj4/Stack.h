#ifndef STACK_H
#define STACK_H
#include <iostream>
#include <list>

namespace cop4530
{
  template<typename T>
  class Stack
  {
    std::list<T> c;
   
    public:
      Stack<T>();   //zero-argument constructor.  
      ~Stack<T>();  //destructor.
      Stack<T>(const Stack<T>&);  //copy constructor
      Stack<T>(Stack<T>&&);   //move constructor.
      Stack<T>& operator=(const Stack<T>&);  //copy assignment operator=.
      Stack<T>& operator=(Stack<T>&&);   //move assignment operator=
      bool empty() const;   //returns true if the Stack contains no elements 
      void clear();   //delete all elements from the stack
      void push(const T& x);  //adds x to the Stack. copy version.
      void push(T && x);   //adds x to the Stack. move version.
      void pop();   //removes and discards the most recently added element
      T& top();   //mutator that returns the most recently added element
      const T& top() const;   //accessor that returns recently added element
      int size() const;   //returns the number of elements stored in the Stack.
      void print(std::ostream& os, char ofc= ' ') const;    //prints Stack
  };
  //invokes print method
  template<typename T> 
  std::ostream& operator<<(std::ostream& os, const Stack<T>& a);
  
  template<typename T>
  bool operator==(const Stack<T>&, const Stack<T>&);    //true if equal
  
  template<typename T>
  bool operator!=(const Stack<T>&, const Stack<T>&);    //true if not equal
  
  template<typename T>
  bool operator< (const Stack<T>& a, const Stack<T>& b);  //true if a<b

  #include "Stack.hpp"
}
#endif