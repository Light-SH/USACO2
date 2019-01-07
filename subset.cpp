/*
ID: wuyue171
PROG: subset
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
using namespace std;
/*解题思路：动态规划 ，d[i][j]表示1-i个数中和为j的方法数，d[i][j]=d[i-1][j]+d[i-1][j-i]
            设1-n的和为sum，即求  d[i][sum/2]/2

*/

int n;
int sum = 0;
long long dp[100][1000];

int main() {
	ifstream fin("subset.in");
	ofstream fout("subset.out");
	fin >> n;
	for (int i = 1; i <= n; i++)
		sum += i;
	dp[0][0] = 1;        //动态规划的边界
	if (sum % 2 == 0) {
		for (int i = 1; i <= n; i++) {
			dp[i][0] = 1;
			for (int j = 1; j <= i*(i+1) / 2; j++)
				dp[i][j] = dp[i - 1][j] + dp[i - 1][j - i];
		}
	}
	fout << dp[n][sum / 2] / 2 << endl;
	return 0;
}
