#ifndef MY_SET_H
#define MY_SET_H

#include <stdlib.h>
#include "MyVector.h"
template <typename elem>
class MySet {
public:
	MySet(int(*cp)(elem, elem));
	~MySet();

	int size();
	void insert(elem e);
	void clear();
	bool findOne(elem &ret, elem e, bool(*cp)(elem, elem));
	bool findAll(MyVector<elem> &ret, elem e, bool(*cp)(elem, elem));
	void toArray(MyVector<elem>&);
private:
	int(*cp)(elem, elem);
	struct node {
		node * ch[2]; //0==>left; 1==>right
		elem val;
		int r;
		int(*cp)(elem, elem);
		int cmp(elem x) {
			if (cp(x, val) == 0) return -1;
			return cp(x, val) < 0 ? 0 : 1;
		}
	};
	node * root;
	int ssize;
	void rotate(node * &rt, int d);
	void insert(node * &rt, elem x);
	void freetree(node * &rt);
	void toarray(node * rt, MyVector<elem>&);
	void find(node * rt, MyVector<elem> &ret, elem e, bool(*cp)(elem, elem));
};

template <typename elem>
MySet<elem>::MySet(int(*cmp)(elem, elem)) {
	root = NULL; cp = cmp;
	ssize = 0;
}

template <typename elem>
MySet<elem>::~MySet() {
	clear();
}

template <typename elem>
int MySet<elem>::size() {
	return ssize;
}

template <typename elem>
void MySet<elem>::insert(elem x) {
	insert(root, x);
}

template <typename elem>
void MySet<elem>::clear() {
	if (NULL != root) freetree(root);
	root = NULL; ssize = 0;
}

template <typename elem>
bool MySet<elem>::findOne(elem &ret, elem e, bool(*cp)(elem, elem)) {
	node * tmp = root;
	while (NULL != tmp) {
		if (cp(tmp->val, e)) {
			ret = tmp->val;
			return true;
		}
		int d = tmp->cmp(e);
		if (-1 == d) return false;
		else tmp = tmp->ch[d];
	}
	return false;
}

template <typename elem>
bool MySet<elem>::findAll(MyVector<elem> &ret, elem e, bool(*cp)(elem, elem)) {
	node * tmp = root;
	while (NULL != tmp) {
		if (cp(tmp->val, e)) {
			ret.push_back(tmp->val);
			int d = tmp->cmp(e);
			//if (cp(tmp->val, e)) d = 0;
			if(tmp->ch[0]) find(tmp->ch[0], ret, e, cp);
			if(tmp->ch[1]) find(tmp->ch[1], ret, e, cp);
			return true;
			/*
			int d = -1;
			if (NULL != tmp->ch[0] && cp(tmp->ch[0]->val, e)) d = 0;
			if (NULL != tmp->ch[1] && cp(tmp->ch[1]->val, e)) d = 1;
			if (d == -1) return true;
			else {
				for (tmp = tmp->ch[d]; NULL != tmp; tmp = tmp->ch[d]) {
					if (cp(tmp->val, e)) ret.push_back(tmp->val);
					else return true;
				}
				return true;
			}*/
		}
		int d = tmp->cmp(e);
		if (-1 == d) return false;
		else tmp = tmp->ch[d];
	}
	return false;
}

template <typename elem>
void MySet<elem>::find(node * rt, MyVector<elem> &ret, elem e, bool(*cp)(elem, elem)) {
	if (cp(rt->val, e)) {
		ret.push_back(rt->val);
		if(rt->ch[0]) find(rt->ch[0], ret, e, cp);
		if(rt->ch[1]) find(rt->ch[1], ret, e, cp);
		return;
	} 
	int d = rt->cmp(e);
	if (-1 == d) return;
	if(rt->ch[d]) find(rt->ch[d], ret, e, cp);
}

template <typename elem>
void MySet<elem>::toArray(MyVector<elem>& ret) {
	if(NULL != root) toarray(root, ret);
}

template <typename elem>
void MySet<elem>::insert(node * &rt, elem x) {
	if (NULL == rt) {
		rt = new node();
		rt->ch[0] = rt->ch[1] = NULL;
		rt->val = x; rt->r = rand(); rt->cp = cp;
		ssize++;
	}
	else {
		int d = rt->cmp(x);
		if (-1 == d) return;
		insert(rt->ch[d], x); if (rt->ch[d]->r > rt->r) rotate(rt, d ^ 1);
	}
}

template <typename elem>
void MySet<elem>::rotate(node * &rt, int d) {
	node * k = rt->ch[d ^ 1]; rt->ch[d ^ 1] = k->ch[d]; k->ch[d] = rt; rt = k;
}

template <typename elem>
void MySet<elem>::freetree(node * &rt) {
	if (NULL != rt->ch[0]) freetree(rt->ch[0]);
	if (NULL != rt->ch[1]) freetree(rt->ch[1]);
	delete rt; rt = NULL;
}

template <typename elem>
void MySet<elem>::toarray(node * rt, MyVector<elem> &ret) {
	if (NULL != rt->ch[0]) toarray(rt->ch[0], ret);
	ret.push_back(rt->val);
	if (NULL != rt->ch[1]) toarray(rt->ch[1], ret);
}

#endif MY_SET_H