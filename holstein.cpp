/*
ID: wuyue171
PROG: holstein
LANG: C++
*/
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

/*解题思路：   直接DFS*/

int v, g;     //v：维生素种数  g:喂法个数
int G[25];    //所需的v种维他命数
int a[15][25]; //feed#1-v
int ans[16], t = 0, ans_t = 25;  //当前共考虑t种feed
int cur[25] = { 0 };
int output[16];

bool check() {
	for (int i = 0; i < v; i++) {   //还没满足要求
		if (cur[i] < G[i])     
			return false;
	}
	ans_t = t;
	for (int i = 1; i <= t; i++)   //满足要求后，将ans[i]中存的数据传给output，返回true，结束递归
		output[i] = ans[i];
	return true;
}

void DFS(int k) {   //k代表feed#k
	if (t >= ans_t)
		return;
	if (check())    //是否已经满足要求
		return;
	if (k == g)     //所有喂法都考虑了
		return;
	
	for (int i = 0; i < v; i++)
		cur[i] += a[k][i];
	ans[++t] = k;
	DFS(k + 1);
	--t;
	for (int i = 0; i < v; i++)
		cur[i] -= a[k][i];
	DFS(k + 1);
}

int main() {
	ofstream fout("holstein.out");
	ifstream fin("holstein.in");
	fin >> v;
	for (int i = 0; i < v; i++)
		fin >> G[i];
	fin >> g;
	for (int i = 0; i < g; i++) {
		for (int j = 0; j < v; j++)
			fin >> a[i][j];
	}
	DFS(0);
	fout << ans_t << " ";
	for (int i = 1; i < ans_t; i++)
		fout << output[i] + 1 << " ";
	fout << output[ans_t] + 1 << endl;
	return 0;
}

