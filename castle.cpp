/*
ID: wuyue171
PROG: castle
LANG: C++
*/
#include <iostream>
#include <fstream>

/*解题思路：   

把每个格点都抽象为一个顶点，建图，后进行连通分量测试

    1    2    3    4    5    6    7
  ####|####|####|####|####|####|#####
1 #   |   #|#   |   #|#   |    |    #
  ####|   #|####|   #|#   |####|    #
 -----|----|----|----|----|----|-----
  ####|#   |####|#  #|#  #|####|#   #
2 #  #|#   |   #|#  #|#  #|#  #|#   #
  #  #|####|   #|####|#  #|####|#   #
 -----|----|----|----|----|----|-----
  #   |####|   #|####|#  #|####|#   #
3 #   |    |   #|#  #|#  #|#  #|#   #
  #   |####|####|#  #|####|#  #|#   #
 -----|----|----|----|----|----|-----
  #  #|####|####|    |####|   #|#   #
4 #  #|#   |    |    |    |   #|#   #
  ####|####|####|####|####|####|#####
*/
using namespace std;

int m, n;                //m行n列
int roomN;               //room数
int room[51][51];        //room[i][j]==k 代表顶点（i,j）属于room k
int rsize[50 * 50 + 1];   //rsize[1]=5,代表 room1 由5个顶点组成
int Smax;                //最大room size
int wall[51][51][4];     //wall[i][j][0]=1代表顶点（i，j）west边有wall，第三维0代表west,1代表north,2代表east,3代表south
int visited[51][51];     //visited[i][j]=1代表此顶点是否被访问过

void dfs(int, int);

int main() {
	ofstream fout("castle.out");
	ifstream fin("castle.in");
	fin >> m >> n;

	int temp;
	for (int i = 1; i <= n; i++) {        //设置顶点(i,j)的wall
		for (int j = 1; j <= m; j++) {
			fin >> temp;
			for (int k = 0; k < 4; k++) {
				/*
				1:wall to the west
				2:wall to the north
				3:wall to the east
				4:wall to the south
				*/
				wall[i][j][k] = (temp >> k) & 1;  //e.g.  temp=11, 1011 , [0],[1],[3]设为1
			}
		}
	}

	for (int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			if (!visited[i][j]) {   
				++roomN;       //更新room number
				dfs(i, j);     //递归更新，将一个房间内所有顶点都访问一遍
				Smax = (rsize[roomN] > Smax) ? rsize[roomN] : Smax;     //当前编号roomN的room的rsize与Smax比较
			}
		}
	}
	fout << roomN << endl << Smax << endl;

	/*
	B
	AC    B在A的正上方，C在A的正右方

	reverse所有顶点，只用考虑remove两个方向的wall，即north east
	*/
	int roomA, roomB, roomC;
	int ans_x, ans_y;   //被移动的wall的顶点
	char direction;     //标识被拆掉的wall的方向
	Smax = 0;
	//reverse
	for (int i = 1; i <= m; i++) {
		for (int j = n; j >= 1; j--) {
			roomA = room[j][i];
			roomB = room[j - 1][i];
			roomC = room[j][i + 1];
			//拆north wall,判断条件：j>1，不到顶； 此顶点有north wall；roomA和roomB本就不属于一间room；拆墙后两房间大小后>Smax
			if (j > 1 && wall[j][i][1] && roomA != roomB && rsize[roomA] + rsize[roomB] > Smax) {
				Smax = rsize[roomA] + rsize[roomB];
				ans_x = j;
				ans_y = i;
				direction = 'N';
			}
			//拆east wall,判断条件：i<m,不到最右；此顶点有east wall；roomA和roomC本就不属于一间room；拆墙后两房间大小后>Smax
			else if (i < m && wall[j][i][2] && roomA != roomC && rsize[roomA] + rsize[roomC] > Smax) {
				Smax = rsize[roomA] + rsize[roomC];
				ans_x = j;
				ans_y = i;
				direction = 'E';
			}
		}
	}
	fout << Smax << endl << ans_x << " " << ans_y << " " << direction << endl;
}


void dfs(int i, int j) {
	if (room[i][j] == roomN)     //若此顶点(i,j)已属于roomN，返回
		return;        
	
	visited[i][j] = 1;  //房间roomN的顶点(i,j)已被访问
	rsize[roomN]++;     //roomN的大小+1
	room[i][j] = roomN;
	if (!wall[i][j][0])   //顶点（i，j）的west没有wall
		dfs(i, j - 1);
	if (!wall[i][j][1])   //顶点（i.j)的north没有wall
		dfs(i - 1, j);
	if (!wall[i][j][2])   //顶点（i,j）的east没有wall
		dfs(i, j + 1);
	if (!wall[i][j][3])   //顶点（i,j）的south没有wall
		dfs(i + 1, j);
}
