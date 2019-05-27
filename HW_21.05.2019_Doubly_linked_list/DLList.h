#pragma once
#include<iostream>
#include<exception>
#include<string>
using namespace std;

//Реализуйте двусвязной список
//B функции main протестируйте все реализованные методы

out_of_range lower("out of lower bound");
out_of_range upper("out of upper bound");

template<typename T>
class List {
private:
	class Node {
		T el;
		Node* nextPtr;
		Node* prevPtr;
		
	public:
		Node(T el, Node*nextPtr, Node*prevPtr) {
			this->el = el;
			this->nextPtr = nextPtr;
			this->prevPtr = prevPtr;
			
		}
		T& getEl() { return el; }
		Node*& getNextPtr() { return nextPtr; }
		Node*& getPrevPtr() { return prevPtr; }
		void setEl(T el) { this->el = el; }
		void setNextPtr(T* ptr) { this->nextPtr = ptr; }
		void setPrevPtr(T* ptr) { this->prevPtr = ptr; }
		
	};
	Node* firstPtr, *lastPtr;
	int size;

public:
	List();
	List(const List&obj);
	~List();
	int getSize();
	T& operator[](int index);
	void push_back(T el);
	void push_front(T el);
	void insert_by_pos(T el, int pos);
	void pop_front();
	void pop_back();
	void del_by_pos(int pos);
	void dump();
};

template<typename T>
inline List<T>::List()
{
	firstPtr = lastPtr = NULL;
	size = 0;
}

template<typename T>
inline List<T>::List(const List & obj)
{
	Node*cur_ptr = obj.firstPtr;

	while (cur_ptr != obj.lastPtr->getNextPtr()) {
		push_back(cur_ptr->getEl());
		cur_ptr = cur_ptr->getNextPtr();
	}
}

template<typename T>
inline List<T>::~List()
{
	int general_size = size;//tmp size because size is changing every time
	for (int i = 0; i < general_size; i++)
		pop_front();
	firstPtr = lastPtr = 0;
}

template<typename T>
inline int List<T>::getSize()
{
	return size;
}

template<typename T>
inline T & List<T>::operator[](int index)throw()
{
	int counter1 = 0;
	int counter2 = size - 1;
	Node*begin_ptr = firstPtr;
	Node*end_ptr = lastPtr;

	if (index >= size) {
		throw upper;
	}
	else if (index < 0)
		throw lower;
	else {
		while (begin_ptr != lastPtr->getNextPtr()) {

			if (counter1 == index)
				return begin_ptr->getEl();
			if (counter2 == index)
				return end_ptr->getEl();
			begin_ptr = begin_ptr->getNextPtr();
			end_ptr = end_ptr->getPrevPtr();
			counter1++;
			counter2--;
		}
	}
}

template<typename T>
inline void List<T>::push_back(T el)
{
	if (size == 0) {
		Node* ptr = new Node(el, NULL, NULL);
		firstPtr = lastPtr = ptr;
	}
	else {
		Node *cur_ptr = new Node(el, NULL, lastPtr);
		lastPtr->getNextPtr() = cur_ptr;
		lastPtr = cur_ptr;
	}
	size++;
}

template<typename T>
inline void List<T>::push_front(T el)
{
	Node *cur_ptr = new Node(el, firstPtr, NULL);
	firstPtr = cur_ptr;
	size++;
	if (size == 1)
		lastPtr = firstPtr;
}

template<typename T>
inline void List<T>::insert_by_pos(T el, int pos)throw()
{
	Node*begin_ptr = firstPtr;
	Node*end_ptr = lastPtr;
	Node*tmp_b = begin_ptr;
	int counter1 = 0;
	int counter2 = getSize() - 1;


	if (pos == 0)
		push_front(el);
	else if (pos == size)
		push_back(el);
	else if (pos<0 || pos>size)
		throw out_of_range("out of range\n");

	else if (pos > 0 && pos < size) {
 		while (counter1 != pos && counter2 != pos) {
			tmp_b = begin_ptr;//must do to save previous pointer
			begin_ptr = begin_ptr->getNextPtr();
			end_ptr = end_ptr->getPrevPtr();
			counter1++;
			counter2--;
		}
		if (counter1 == pos) {//test till middle of the list
			
			Node *newPtr = new Node(el, begin_ptr, tmp_b /*begin_ptr->getPrevPtr()*/);// works, but if using  as prevPtr (begin_ptr->getPrevPtr()) it is always NULL? чтение невозможно
			begin_ptr->getPrevPtr() = newPtr;
			newPtr->getPrevPtr()->getNextPtr() = newPtr;
			
		}
		else if (counter2 == pos) {
			Node *newPtr = new Node(el, end_ptr, end_ptr->getPrevPtr());
			end_ptr->getPrevPtr() = newPtr;
			newPtr->getPrevPtr()->getNextPtr() = newPtr;
		}
		size++;
	}
}

template<typename T>
inline void List<T>::pop_front()
{
	if (size != 0)
	{
		Node* cur_ptr = firstPtr;
		firstPtr = firstPtr->getNextPtr();
		delete cur_ptr;
		size--;
	}
	else
		cout << "Trying to delete from empty list" << endl;
}

template<typename T>
inline void List<T>::pop_back()
{
	if (size != 0)
	{
		Node* cur_ptr = lastPtr;
		lastPtr = lastPtr->getPrevPtr();
		delete cur_ptr;
		size--;
	}
	else
		cout << "Trying to delete from empty list" << endl;
}

template<typename T>
inline void List<T>::del_by_pos(int pos)throw()
{

	Node*begin_ptr = firstPtr;
	Node*end_ptr = lastPtr;
	int counter1 = 0;
	int counter2 = getSize() - 1;

	if (size != 0) {
		if (pos == 0)
			pop_front();
		else if (pos == size-1)
			pop_back();
		else if (pos<0 || pos>=size)
			throw out_of_range("out of range\n");

		else if (pos > 0 && pos < size) {

			while (counter1 != pos-1 && counter2 != pos+1) {
				begin_ptr = begin_ptr->getNextPtr();
				end_ptr = end_ptr->getPrevPtr();
				counter1++;
				counter2--;
			}
		
			if (counter1 == pos-1) {
				Node* tmp_ptr = begin_ptr->getNextPtr();
				begin_ptr->getNextPtr() = begin_ptr->getNextPtr()->getNextPtr();
				begin_ptr->getNextPtr()->getPrevPtr() = begin_ptr;
				delete tmp_ptr;
			}
			else if (counter2 == pos+1) {
				Node* tmp_ptr = end_ptr->getPrevPtr();
				end_ptr->getPrevPtr() = end_ptr->getPrevPtr()->getPrevPtr();
				end_ptr->getPrevPtr()->getNextPtr() = end_ptr;
				delete tmp_ptr;
			}

			size--;
		}
	}
	else
		cout << "Trying to delete from empty list" << endl;
}

template<typename T>
inline void List<T>::dump()
{
	if (size != 0)
	{
		Node*cur_ptr = firstPtr;
		while (cur_ptr != lastPtr->getNextPtr()) {
			cout << cur_ptr->getEl() << endl;
			cur_ptr = cur_ptr->getNextPtr();
		}
	}
}
