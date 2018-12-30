/*
ID: wuyue171
PROG: sort3
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
using namespace std;
/*解题思路：先找交换一次能使两个数位置正确的交换，再找一次交换只能成一个的交换(三个位置要通过2次调换)*/

int N;
int input[1000], ordered[1000];
int state[4][4];  //记录1-3区中1-3的个数

int main() {
	ofstream fout("sort3.out");
	ifstream fin("sort3.in");
	fin >> N;
	for (int i = 0; i < N; i++) {
		fin >> input[i];
		ordered[i] = input[i];
	}
	sort(ordered, ordered + N);    //排序
	for (int i = 0; i < N; i++) {
		state[ordered[i]][input[i]]++;    //[应在位置][实际位置]
	}
	//交换1：一次交换能有两个正确位置,代价为需要交换位置的较小数
	int ex1_3 = min(state[1][3], state[3][1]);    //1区中的3 和 3区中的1交换，次数为其中的较小值
	int ex1_2 = min(state[1][2], state[2][1]);    //1区中的2 和 2区中的1交换，次数为其中的较小值
	int ex2_3 = min(state[2][3], state[3][2]);    //2区中的3 和 3区中的2交换，次数为其中的较小值
	//交换2：一次交换只有一个正确位置，代价为需要交换的数的个数，1-2-3之间的轮流调换，只用交换2次
	int count = state[1][2] + state[1][3] - ex1_2 - ex1_3;   //除去交换1，1区中仍需调换的1的个数
	count *= 2;      //因为2-3-1，需要调换2次，所以交换2共需count*2次
	fout << count + ex1_2 + ex1_3 + ex2_3 << endl;
	return 0;

}
