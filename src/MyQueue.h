#ifndef MY_QUEUE_H
#define MY_QUEUE_H

#include <assert.h>

template <typename elem>
class MyQueue {
public:
	MyQueue();
	~MyQueue();

	int size();
	bool empty();
	elem front();
	elem back();
	void push(elem e);
	void pop();
private:
	struct node{
		elem val;
		node *nxt, *bck;
	} *head, *tail;
	int ssize;
};

template<typename elem>
MyQueue<elem>::MyQueue() {
	head = tail = NULL; ssize = 0;
}

template<typename elem>
MyQueue<elem>::~MyQueue() {
	while (!empty()) pop();
}

template<typename elem>
int MyQueue<elem>::size() {
	return ssize;
}

template<typename elem>
bool MyQueue<elem>::empty() {
	return NULL == head && NULL == tail;
}

template<typename elem>
elem MyQueue<elem>::front() {
	return head->val;
}

template<typename elem>
elem MyQueue<elem>::back() {
	return tail->val;
}

template<typename elem>
void MyQueue<elem>::push(elem e) {
	ssize++;
	node *tmp = new node;
	assert(NULL != tmp);
	tmp->nxt = tail; tmp->bck = NULL; tmp->val = e;
	if (NULL == tail && NULL == head) {
		tail = head = tmp;
		return;
	}
	tail->bck = tmp;
	tail = tmp;
}

template<typename elem>
void MyQueue<elem>::pop() {
	assert(NULL != head);
	ssize--;
	node *tmp = head;
	head = head->bck;
	delete tmp;
	if (NULL != head) head->nxt = NULL;
	else tail = NULL;
}

#endif