#ifndef MY_STACK_H
#define MY_STACK_H

#include <assert.h>
//TODO NULL indentifier not found
#define NULL 0
template <typename elem>
class MyStack {
public:
	MyStack();
	~MyStack();

	bool empty();
	elem top();
	void pop();
	void push(elem e);
private:
	struct node {
		elem val;
		node * nxt;
	} *head;
};

template <typename elem>
MyStack<elem>::MyStack() {
	head = NULL;
}

template <typename elem>
MyStack<elem>::~MyStack() {
	node * tmp = head;
	while (NULL != head) {
		tmp = head;
		head = head->nxt;
		delete tmp;
	}
	head = NULL;
}

template <typename elem>
bool MyStack<elem>::empty() {
	return head == NULL;
}

template <typename elem>
elem MyStack<elem>::top() {
	return head->val;
}

template <typename elem>
void MyStack<elem>::pop() {
	assert(NULL != head);
	node * tmp = head;
	head = head->nxt;
	delete tmp;
}

template <typename elem>
void MyStack<elem>::push(elem e) {
	node * tmp = new node;
	assert(NULL != tmp);
	tmp->val = e;
	tmp->nxt = head;
	head = tmp;
	return;
}

#endif