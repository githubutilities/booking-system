#include <stack>
#include <iostream>
#include "MyStack.h"
#include <time.h>
using namespace std;

int MyStackTest() {
	MyStack<int> stk;
	stack<int> stktmp;
	const int MOD = 0x3f3f3f3f;
	const int TIME = 1000000;
	srand(TIME);
	for (int i = 0; i < TIME; i++) {
		srand((unsigned int)rand());
		int tmp = rand();
		if (tmp % 5 == 0 && !stk.empty()) {
			assert(stktmp.empty() != true);
			int a = stk.top(); stk.pop();
			int b = stktmp.top(); stktmp.pop();
			assert(a == b);
		}
		else {
			stk.push(tmp); stktmp.push(tmp);
		}
	}
	cout << "MyStack PASS!" << endl;
	return 0;
}