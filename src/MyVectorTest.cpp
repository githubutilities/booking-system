#include <vector>
#include <iostream>
#include "MyVector.h"
using namespace std;
int MyVectorTest() {
	MyVector<int> vec;
	vector<int> vv;
	const int TIME = 10000;
	for (int i = 0; i < TIME; i++) {
		int tmp = rand();
		if (tmp % 5 == 0) vec.pop_back(), vv.pop_back();
		else vec.push_back(tmp), vv.push_back(tmp);
		assert(vv.size() == vec.size());
		for (int i = 0; i < vec.size(); i++) {
			assert(vec[i] == vv[i]);
		}
	}
	cout << "MyVector Pass!" << endl;
	return 0;
}