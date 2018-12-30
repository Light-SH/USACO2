/*
ID: wuyue171
PROG: frac1
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>

using namespace std;
/*解题思路：直接枚举所有真分数，其中可 进行部分优化，再进行排序*/

int N;
int st[12880];    //记录Fract的序号

int gcd(int a, int b) {     //求是否有最小公约数
	return b == 0 ? a : gcd(b, a%b);
}

struct fract {
	int fenzi;    //分子：真分数
	int fenmu;    //分母
}Fract[12880];

int cmp(int a, int b) {
	return ((Fract[a].fenzi*Fract[b].fenmu) < (Fract[b].fenzi*Fract[a].fenmu)) ? 1 : 0;
}

int main() {
	ofstream fout("frac1.out");
	ifstream fin("frac1.in");
	fin >> N;
	Fract[0].fenzi = 0, Fract[0].fenmu = 1;    //设置第一个值
	int num = 1;
	for (int i = 1; i <= N; i++) {
		for (int j = i + 1; j <= N; j++) {    //真分数
			if (gcd(j, i) == 1) {
				Fract[num].fenzi = i;
				Fract[num].fenmu = j;
				num++;
			}
		}
	}
	Fract[num].fenzi = 1, Fract[num].fenmu = 1;
	num += 1;

	for (int i = 0; i < num; i++) {
		st[i] = i;
	}
	sort(st, st + num, cmp);

	for (int i = 0; i < num; i++) {
		fout << Fract[st[i]].fenzi << "/" << Fract[st[i]].fenmu << endl;
	}
}

