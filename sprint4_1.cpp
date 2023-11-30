#include <iostream>
#include <Windows.h> // Sleep( )
#include <vector>
#include<fstream>
using namespace std;

class queue1 {
public:
	queue1() { NI = 7; NO = 3; capacity = 100; }
	queue1(int NI1, int NO1, int cap) { NI = NI1; NO = NO1; capacity = cap; }

	int NI, NO, capacity;
	int itime = 0, T = 1, lost = 0, ni, no, high = 0, sum = 0;	//고정값들, 초기에는 손실 0
	float average = 0, fullness;
	int NofPackets[120];

	int que() {

		ofstream xx;	//txt파일 생성
		xx.open("aa.txt");
		if (!xx) {
			cout << "can't open file" << endl;
			return 666;
		}
		vector <int> queue;

		while (itime < 120) {
			itime += T;

			Sleep(T * 10);  // milliseconds
			cout << "  Elapsed time[sec] = " << itime << endl;	//시간 기록

			//입력
			ni = rand() % NI;
			cout << "ni: " << ni << endl;


			if (capacity < queue.size() + ni) {	//overflow하면
				lost += queue.size() + ni - capacity;	//손실 발생, lost는 손실 누적 값
				ni = capacity - queue.size();	//용량에 맞게 잘려서 ni값 바꿔주기
				cout << "overflow" << endl;
			}

			for (int i = 0; i < ni; i++) {
				queue.push_back(rand() % 20);
				cout << queue[queue.size() - 1] << " in " << queue.size() << endl;
			}
			cout << endl;

			//출력
			no = rand() % NO;
			cout << "no: " << no << endl;

			if (no > queue.size()) {
				no = queue.size();
				cout << "underflow" << endl;
			}

			for (int i = 0; i < no; i++) {
				int ii = queue[0];

				if (queue.size() != 0) {
					cout << ii << " out " << queue.size() << endl;
					queue.erase(queue.begin());
				}
			}
			cout << endl;
			NofPackets[itime - 1] = queue.size();
			cout << "NofPackets: " << NofPackets[itime - 1] << endl << endl;

			if (high < NofPackets[itime - 1]) { //최대 계산
				high = NofPackets[itime - 1];
			}

			sum += NofPackets[itime - 1];	//전체 합 계산
		}	//while 끝

		average = sum / 120;	//평균 계산
		fullness = average / capacity * 100;	//평균 채워진 퍼센트
		int j = 0;
		for (auto a : NofPackets) {
			j++;
			xx << j << " " << a << endl;	//txt파일로 입력, 파일 최소한으로 여닫기
		}

		cout << "highest: " << high << " average: " << average << endl;
		cout << " Queue fullness: " << fullness << " Packet loss rate: " << lost << endl;	//실험값 cout
		xx.close();
	}
};

int main() {
    srand(time(NULL));

    queue1 qq;
    cout << "test ni and no :" << endl;
    qq.que();
    cout << "\n-----------------------------------------\n";

    int testni = 10;
    int testno = 15;
    queue1 qq1(testni, testno, 100);
    cout << "ni = " << testni << " no = " << testno << ":" << endl;
    qq1.que();

    return 1;
}
