#ifndef MYCUSTOMER_H
#define MYCUSTOMER_H

#include <fstream>
#include <stdio.h>
#include <string.h>
#include <string>
using namespace std;

class MyCustomer {
public:
	MyCustomer() {};
	MyCustomer(string name, int need) : name(name), need(need) {}
	void init(istream &fin);
	void write(ostream &fout);
	string getName();
	int getNeed();

	void addNeed(int num);
private:
	string name;
	int need;
};

#endif