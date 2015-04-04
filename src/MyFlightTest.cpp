#include "MySet.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include "MyFlight.h"
#include <fstream>
using namespace std;

int MyFlightTest() {
	MySet<MyFlight*> ss(cmpByFlightID);
	ifstream in("in.txt", std::ios::in);
	MyFlight arr[10];
	for (int i = 0; i < 4; i++) {
		arr[i].init(in);
		ss.insert(&arr[i]);
	}
	
	string query;
	while (cin >> query) {
		MyFlight ret;
		MyVector<MyFlight*> res;
		res.clear();
		ret.setFlightID(query);
		if (ss.findAll(res, &ret, findByFlightID)){
			for (int i = 0; i < res.size(); i++) {
				res[i]->write(cout);
			}
		}
		else cout << "not found" << endl;
	}
	return 0;
}