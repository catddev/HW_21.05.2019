#pragma once
#include<iostream>
#include<exception>
#include<string>

//Реализуйте двусвязной список с указанным прототипом. 
//B функции main протестируйте все реализованные методы

template<typename T>
class List {
private:
	class Node {
		T el;
		Node* nextPtr;
		Node* prevPtr;
	public:
		Node(T el, Node*nextPtr, Node* prevPtr) {
			this->el = el;
			this->nextPtr = nextPtr;
			this->prevPtr = prevPtr;
		}
		T& getEl() { return el; }
		Node*& getNextPtr() { return nextPtr; }
		Node*& getPrevPtr() { return prevPtr; }
		void setEl(T el) { this->el = el; }
		void setNextPtr(T* ptr) { this->nextPtr = ptr; }
		void setPrevPtr(T* ptr) { this->prevtPtr = ptr; }
	};
	Node* firstPtr, *lastPtr;
	int size;

public:
	List();
	~List();
	int getSize();
	void push_back(T el);
	void push_front(T el);
	void pop_front();
	void pop_back();
	void dump();
};
