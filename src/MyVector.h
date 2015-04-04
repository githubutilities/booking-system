#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include <assert.h>
#include <stdio.h>

#include <iostream>
template <typename elem>
class MyVector {
public:
	MyVector();
	~MyVector();

	int size();
	void push_back(elem &e);
	elem back();
	void pop_back();
	void del(int idx);
	void clear();
	
	elem operator [] (const int i);
private:
	elem *arr;
	int numUsed, numAlloc;
	void doubleCapacity();
	void shrinkCapacity();
};

template <typename elem>
MyVector<elem>::MyVector() {
	numUsed = 0; numAlloc = 4;
	arr = new elem[numAlloc];
}

template <typename elem>
MyVector<elem>::~MyVector() {
	delete[] arr;
}

template <typename elem>
int MyVector<elem>::size() {
	return numUsed;
}

template <typename elem>
void MyVector<elem>::push_back(elem &e) {
	arr[numUsed] = e;
	numUsed++;
	if (numUsed == numAlloc) doubleCapacity();
}

template <typename elem>
elem MyVector<elem>::back() {
	return arr[numUsed - 1];
}

template <typename elem>
void MyVector<elem>::pop_back() {
	numUsed--;
	if (numUsed < numAlloc / 3 && numAlloc > 4) shrinkCapacity();
}

template <typename elem>
void MyVector<elem>::del(int idx) {
	for (int i = idx; i + 1 < numUsed; i++) 
		arr[i] = arr[i + 1];
	numUsed--;
	if (numUsed < numAlloc / 3 && numAlloc > 4) shrinkCapacity();
}

template <typename elem>
void MyVector<elem>::clear() {
	delete[] arr;
	numUsed = 0; numAlloc = 4;
	arr = new elem[numAlloc];
}

template <typename elem>
elem MyVector<elem>::operator[] (const int i) {
	assert(i >= 0 && i < numUsed);
	return arr[i];
}

template <typename elem>
void MyVector<elem>::doubleCapacity() {
	elem * tmp = arr;
	numAlloc <<= 1;
	arr = new elem[numAlloc];
	//memcpy(arr, tmp, numUsed * sizeof(int));
	for (int i = 0; i < numUsed; i++) arr[i] = tmp[i];
	delete[] tmp;
}

template <typename elem>
void MyVector<elem>::shrinkCapacity() {
	elem * tmp = arr;
	numAlloc >>= 1;
	arr = new elem[numAlloc];
	for (int i = 0; i < numUsed; i++) arr[i] = tmp[i];
	delete[] tmp;
}

#endif