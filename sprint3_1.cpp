#include <vector>
#include<iostream>
using namespace std;

vector <int> queue;
int main() {
	int k = 5, lost = 0, capacity = 100, n = 3;

	if (capacity < queue.size() + k) {	//overflow하면
		lost += queue.size() + k - capacity;	//손실 발생
		k = capacity - queue.size();	//용량에 맞게 잘려서 k값 바꿔주기

	}

	cout << "lost: " << lost << endl;

	for (int i = 0; i < k; i++) {	//값 넣기
		queue.push_back(rand() % 20);
		cout << queue[queue.size() - 1] << " in " << queue.size() << endl;
	}

	for (int i = 0; i < n; i++) {
		if (queue.size() != 0) { //no  underflow(queue에 값이 존재)
			cout << queue[0] << " out " << queue.size() << endl;

			queue.erase(queue.begin());
		}
	}
}
