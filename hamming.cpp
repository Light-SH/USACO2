/*
ID: wuyue171
PROG: hamming
LANG: C++
*/
#include <iostream>
#include <cstring>
#include <cmath>
#include <fstream>
using namespace std;

/*解题思路： 直接遍历1到最大的B位二进制数，依次比较当前数与已找到n个数之间是否满足D距离要求，直到找到N个编码。*/

int cur_n = 0, N;    //已找到和要找到的
int B, D;            //B位二进制数，D个hamming distance
int ans[65];         //存满足的codewords

bool isHam(int x) {
	for (int i = 0; i < cur_n; i++) {
		int temp = x^ans[i];
		int count = 0;
		while (temp) {
			temp = temp&(temp - 1);
			count++;
		}
		if (count < D)
			return false;
	}
	return true;
}

int main() {
	ifstream fin("hamming.in");
	ofstream fout("hamming.out");
	fin >> N >> B >> D;
	int max = pow(2, B) - 1;
	ans[0] = 0;
	cur_n = 1;	
	
	for (int i = 1; i <= max; i++) {
		if (cur_n != N) {    //找到N个才停
			if (isHam(i)) {
				ans[cur_n] = i;
				cur_n++;
			}
		}
		else
			break;
	}

	for (int i = 0; i < cur_n; i++) {
		if ((i + 1) % 10 == 0 || i == N - 1) {
			fout << ans[i] << endl;
		}
		else
			fout << ans[i] << " ";
	}
	//system("pause");
	return 0;
}
