#ifndef LIST_HPP
#define LIST_HPP

#include "List.h"

using namespace cop4530;

template <typename T>
List<T>::const_iterator::const_iterator() 	// default zero parameter constructor
{
	this->current = nullptr;
}

template <typename T>
const T& List<T>::const_iterator::operator*() const 	//operator*() to return element
{
	return retrieve();
}

// increment/decrement operators
template <typename T>
typename List<T>::const_iterator &List<T>::const_iterator::operator++()
{
	current = current->next;
	return *this;
}

template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator++(int)
{
	const_iterator temp = *this;
	++(*this);
	return temp;
}

template <typename T>
typename List<T>::const_iterator & List<T>::const_iterator::operator--()
{
	current = current->prev;
	return *this;
}

template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator--(int)
{
	const_iterator temp = *this;
	--(*this);
	return temp;
}

// comparison operators
template <typename T>
bool List<T>::const_iterator::operator==(const const_iterator &rhs) const
{
	return current == rhs.current;
}

template <typename T>
bool List<T>::const_iterator::operator!=(const const_iterator &rhs) const
{
	return !(*this == rhs);
}

template <typename T>
T& List<T>::const_iterator::retrieve() const 	//retrieve the element refers to
{
	return current->data;
}

template <typename T>
List<T>::const_iterator::const_iterator(Node *p) 	//protected constructor
{
	current = p;
}					

template <typename T>
List<T>::iterator::iterator()
{

}

template <typename T>
T& List<T>::iterator::operator*()
{
	return const_iterator::retrieve();
}

template <typename T>
const T& List<T>::iterator::operator*() const
{
	return const_iterator::operator*();
}

// increment/decrement operators
template <typename T>
typename List<T>::iterator &List<T>::iterator::operator++()
{
	this->current = this->current->next;
	return *this;
}

template <typename T>
typename List<T>::iterator List<T>::iterator::operator++(int)
{
	iterator temp = *this;
	++(*this);
	return temp;
}

template <typename T>
typename List<T>::iterator &List<T>::iterator::operator--()
{
	this->current = this->current->prev;
	return *this;
}

template <typename T>
typename List<T>::iterator List<T>::iterator::operator--(int)
{
	iterator temp = *this;
	--(*this);
	return temp;
}

template <typename T>
List<T>::iterator::iterator(Node *p) : const_iterator{p}{}

template <typename T>
List<T>::List() // default zero parameter constructor
{
	init();
}

template <typename T>
List<T>::List(const List &rhs) // copy constructor
{
	init();
	for(auto &x : rhs)
		push_back(x);
}

template <typename T>
List<T>::List(List && rhs) // move constructor
{
	theSize = rhs.theSize;
	head = rhs.head;
	tail = rhs.tail;

	rhs.theSize = 0;
	rhs.head = 0;
	rhs.tail = 0;
}

// num elements with value of val
template <typename T>
List<T>::List(int num, const T& val)
{
	init();
	for(int i = 0; i < num; i++)
	{
		this->push_back(val);
	}
}

template <typename T>
List<T>::List(const_iterator start, const_iterator end)
{
	init();
	while(start != end)
	{
		this->push_back(*start);
		start++;
	}	
}

template <typename T>
List<T>::~List() // destructor
{
	clear(); // clear the list
	delete head; // delete sentinels
	delete tail;
}

// copy assignment operator
template <typename T>
const List<T> &List<T>::operator=(const List &rhs)
{
	List copy = rhs;
	std::swap(*this, copy);
	return *this;
}

// move assignment operator
template <typename T>
List<T> &List<T>::operator=(List && rhs)
{
	std::swap(theSize, rhs.theSize);
	std::swap(head, rhs.head);
	std::swap(tail, rhs.tail);
	return *this;
}

template <typename T>
int List<T>::size() const // number of elements
{
	return theSize;
}

template <typename T>
bool List<T>::empty() const // check if list is empty
{
	return size() == 0;
}

template <typename T>
void List<T>::clear() // delete all elements
{
	while (!empty()) // only need to delete if nodes are present
	{ 
		pop_front(); // pop nodes off one by one until empty
	}
}

template <typename T>
void List<T>::reverse() // reverse the order of the elements
{
	List<T> temp;
	int tempS = theSize;
	for(int i = 0; i < tempS; i++)
	{
		temp.push_front(this->back());
		this->pop_back();
	}

	for(int j = 0; j < tempS; j++)
	{
		this->push_front(temp.front());
		temp.pop_front();
	}
}

template <typename T>
T& List<T>::front() // reference to the first element
{
	return *begin();
}

template <typename T>
const T& List<T>::front() const
{
 return *begin();
}

template <typename T>
T& List<T>::back() // reference to the last element
{
	return *--end();
}

template <typename T>
const T& List<T>::back() const
{
	return *--end();
} 

template <typename T>
void List<T>::push_front(const T & val) // insert to the beginning
{
	insert(begin(), val);
}

template <typename T>
void List<T>::push_front(T && val) // move version of insert
{
	insert(begin(), std::move(val));
}

template <typename T>
void List<T>::push_back(const T & val) // insert to the end
{
	insert(this->end(), val);
}

template <typename T>
void List<T>::push_back(T && val) // move version of insert
{
	insert(this->end(), std::move(val));
}

template <typename T>
void List<T>::pop_front() // delete first element
{
	erase(begin());
}

template <typename T>
void List<T>::pop_back() // delete last element
{
	erase(--end());
}

template <typename T>
void List<T>::remove(const T &val) // remove all elements with value = val
{
	iterator I = this->begin();
	for(I; I != this->end(); ++I)
	{
		if(*I == val)
		{
			this->erase(I);
			I = this->begin();
		}
	}

}

// print out all elements. ofc is deliminitor
template <typename T>
void List<T>::print(std::ostream& os, char ofc) const
{
	const_iterator I = this->begin();
	for(I; I != this->end(); ++I)
	{
		os << *I << ofc;
	}
} 

template <typename T>
typename List<T>::iterator List<T>::begin() // iterator to first element
{
	return this->head->next;
}

template <typename T>
typename List<T>::const_iterator List<T>::begin() const
{
	return this->head->next;
}

template <typename T>
typename List<T>::iterator List<T>::end() // end marker iterator
{
	return this->tail;
}

template <typename T>
typename List<T>::const_iterator List<T>::end() const
{
	return this->tail;
} 

template <typename T>
typename List<T>::iterator List<T>::insert(iterator itr, const T& val) // insert val ahead of itr
{
	Node *p = itr.current;
	theSize++;
	return { p->prev = p->prev->next = new Node{ val, p->prev, p } };
}

template <typename T>
typename List<T>::iterator List<T>::insert(iterator itr, T && val) // move version of insert
{
	Node *p = itr.current; // make new node
	theSize++;
	return { p->prev = p->prev->next = new Node(std::move(val), p->prev, p) };
}

template <typename T>
typename List<T>::iterator List<T>::erase(iterator itr) // erase one element
{
	Node *p = itr.current;
	iterator retVal{p->next};
	p->prev->next = p->next;
	p->next->prev = p->prev;
	delete p;
	theSize--;

	return retVal;
}

template <typename T>
typename List<T>::iterator List<T>::erase(iterator start, iterator end) // erase [start, end)
{
	for(iterator itr = start; itr != end;)
		itr = erase(itr);

	return end;
}

template <typename T>
void List<T>::init() // initialization
{
	theSize = 0;
	head = new Node;
	tail = new Node;
	head->next = tail;
	tail->prev = head;
}

// overloading comparison operators
template <typename T>
bool operator==(const List<T> &lhs, const List<T> &rhs)
{
	return (lhs.size()==rhs.size());
};

template <typename T>
bool operator!=(const List<T> & lhs, const List<T> &rhs)
{
	return (lhs.size()!=rhs.size());
};

// overloading output operator
template <typename T>
std::ostream & operator<<(std::ostream &os, const List<T> &l)
{
	l.print(os);
	return os;
};
#endif
