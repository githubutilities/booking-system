#include <queue>
#include "MyQueue.h"
#include <iostream>
#include <time.h>

using namespace std;
int MyQueueTest() {
	MyQueue<int> que;
	queue<int> quetmp;
	const int TIME = 2;
	const int MOD = 0x3f3f3f3f;
	srand(rand());
	for (int i = 0; i < TIME; i++) {
		int tmp = rand() % MOD;
		srand(rand());
		if (tmp % 5 == 0 && que.empty()) {
			assert(true != quetmp.empty());
			int a = que.front();;
			int b = quetmp.front();
			assert(a == b);
			a = que.back();
			b = quetmp.back();
			assert(a == b);
			que.pop();
			quetmp.pop();
		}
		else {
			que.push(tmp); quetmp.push(tmp);
		}
	}
	cout << "MyQueue PASSED!" << endl;
	return 0;
}