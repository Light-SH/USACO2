/*
ID: wuyue171
PROG: preface
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
using namespace std;
/*解题思路：直接枚举，把数字拆分，然后统计*/

const string number[4][9] = { { "I","II","III","IV","V","VI","VII","VIII","IX" },  //个位 1-9
							  { "X","XX","XXX","XL","L","LX","LXX","LXXX","XC" },  //十位 10-90
							  { "C","CC","CCC","CD","D","DC","DCC","DCCC","CM" },  //百位 100-900
							  { "M","MM","MMM","","","","","","" } };              //千位 1000-3000

int mark[100] = { 0 };    //用于标记每个字母
int s[10] = { 0 };        //用于存每个位上的数
int n;

void add(int x) {
	//先将每个数字拆分，从个位开始存
	s[0] = 0;       //多少位
	while (x > 0) {
		s[++s[0]] = x % 10;
		x /= 10;
	}
	for (int i = 1; i <= s[0]; i++) {
		if (s[i]) {   //考虑到s[i]==0时不会对结果产生影响
			for (int j = 0; number[i - 1][s[i] - 1][j]; j++)      //具体到number中的具体字母
				mark[number[i - 1][s[i] - 1][j]]++;
		}
	}
}

int main() {
	ifstream fin("preface.in");
	ofstream fout("preface.out");
	fin >> n;
	for (int i = 1; i <= n; i++) {
		add(i);
	}
	if (mark['I']) fout << "I " << mark['I'] << endl;
	if (mark['V']) fout << "V " << mark['V'] << endl;
	if (mark['X']) fout << "X " << mark['X'] << endl;
	if (mark['L']) fout << "L " << mark['L'] << endl;
	if (mark['C']) fout << "C " << mark['C'] << endl;
	if (mark['D']) fout << "D " << mark['D'] << endl;
	if (mark['M']) fout << "M " << mark['M'] << endl;

	return 0;
}
