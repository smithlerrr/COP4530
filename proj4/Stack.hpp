#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include "Stack.h"

using namespace cop4530;

//beginning of functions
template<typename T>
Stack<T>::Stack() :c(){}

template<typename T>
Stack<T>::~Stack(){}

template<typename T>
Stack<T>::Stack(const Stack<T>& s)
{
  c = s.c;
}

template<typename T>
Stack<T>::Stack(Stack<T> && s)
{
  c = std::move(s.c);
}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& s)
{
  c = s.c;
}

template<typename T>
Stack<T>& Stack<T>::operator=(Stack<T>&& s)
{
  c = std::move(s.c);

}

template<typename T>
bool Stack<T>::empty() const
{
  return c.empty();
}

template<typename T>
void Stack<T>::clear()
{
  c.clear();
}

template<typename T>
void Stack<T>::push(const T& x)
{
  c.push_back(x);
}

template<typename T>
void Stack<T>::push(T && x)
{
  c.push_back(x);
}

template<typename T>
void Stack<T>::pop()
{
  c.pop_back();
}

template<typename T>
T& Stack<T>::top()
{
  return c.back();
}

template<typename T>
const T& Stack<T>::top() const
{
  return c.back();
}

template<typename T>
int Stack<T>::size() const
{
  return c.size();
}

template<typename T>
void Stack<T>::print(std::ostream& os, char ofc) const
{
  for(auto i = c.begin(); i != c.end(); i++)
  {
    os << *i;
    os << ofc;
  }
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Stack<T>& a)
{
  a.print(os);
  return os;
}

template<typename T>
bool operator==(const Stack<T>& lhs, const Stack<T>& rhs)
{
  return lhs.c == rhs.c;
}

template <typename T>
bool operator!=(const Stack<T>& lhs, const Stack<T>& rhs)
{
  return !(lhs.c == rhs.c);
}

template<typename T>
bool operator< (const Stack<T>& a, const Stack<T>& b)
{
  return a.size()<b.size();
}; 
#endif