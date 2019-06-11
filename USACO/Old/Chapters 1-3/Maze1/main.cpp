/*
ID:theodor8
PROB:maze1
LANG:C++
*/
#include <iostream>
using namespace std;
#pragma warning(disable:4996)

int h, w;
char maze[220][100];
int dis[220][100];
int q[3810][2], front, back;
const int add_x[] = {-1, 0, 1, 0},
	add_y[] = {0, 1, 0, -1};

inline void eq(const int& x, const int& y, const int& v){
	if (!dis[x][y] || dis[x][y] > v){
		q[back][0] = x;
		q[back++][1] = y;
		dis[x][y] = v;
		if (back == 3800)
			back = 0;
	}
}
inline void dq(int& x, int& y){
	x = q[front][0];
	y = q[front++][1];
	if (front == 3800)
		front = 0;
}
inline void search(){
	for (int i=1; i<2*w+1; i+=2){
		if (maze[0][i] == ' ')
			eq(1, i, 1);
		if (maze[2*h][i] == ' ')
			eq(2*h-1, i, 1);
	}
	for (int i=1; i<2*h+1; i+=2){
		if (maze[i][0] == ' ')
			eq(i, 1, 1);
		if (maze[i][2*w] == ' ')
			eq(i, 2*w-1, 1);
	}
	while (front != back){
		int x, y;
		dq(x, y);
		for (int dir=0; dir<4; ++dir){
			int nx(x+add_x[dir]),
				ny(y+add_y[dir]);
			if (nx>0 && nx<2*h && ny>0 && ny<2*w && maze[nx][ny]==' '){
				nx += add_x[dir];
				ny += add_y[dir];
				if (!dis[nx][ny] || dis[nx][ny]>dis[x][y]+1)
					eq(nx, ny, dis[x][y]+1);
			}
		}
	}
}
int main(){
	freopen("maze1.in", "r", stdin);
	freopen("maze1.out", "w", stdout);
	char qwerty;
	scanf("%d%d%c", &w, &h, &qwerty);
	for (int i=0; i<2*h+1; ++i)
		for (int j=0; j<=2*w+1; ++j)
			scanf("%c", &maze[i][j]);
	search();
	int ans(dis[1][1]);
	for (int i=1; i<2*h; i+=2)
		for (int j=1; j<2*w; j+=2)
			if (dis[i][j] > ans)
				ans = dis[i][j];
	printf("%d\n", ans);
	return 0;
}
