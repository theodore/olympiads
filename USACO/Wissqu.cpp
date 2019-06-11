/*
PROB:wissqu
LANG:C++
*/
#pragma warning(disable: 4996)
#include <iostream>

using namespace std;

char pas[5][5], out[20][10];
int ans, num[] = {3, 3, 3, 4, 3};

const int dx[] = {-1, -1, 0, 1, 1, 1, 0, -1}, dy[] = {0, 1, 1, 1, 0, -1, -1, -1};

bool possible(int x, int y, int c){
	if (pas[x][y] - 'A' == c)
		return false;
	int nx, ny;
	for (int dir=0; dir<8; ++dir)
		if ((nx=x+dx[dir]) >= 0 && nx < 4 && (ny=y+dy[dir]) >= 0 && ny < 4 && pas[nx][ny]-'A' == c)
			return false;
	return true;
}

bool vis[5][5], output;

bool print(){
	for (int i=0; i<16; ++i)
		printf("%s\n", out[i]);
	return true;
}

void search(int dep = 0){
	if (dep == 16){
		++ans;
		if (!output)
			output = print();
	}
	else if (dep){
		for (int next=0; next<5; ++next)
			if (num[next])
				for (int i=0; i<4; ++i)
					for (int j=0; j<4; ++j)
						if (!vis[i][j] && possible(i, j, next)){
							vis[i][j] = true;
							char t = pas[i][j];
							sprintf(out[dep], "%c %d %d", pas[i][j] = 'A' + next, i+1, j+1);
							--num[next];
							search(dep + 1);
							++num[next];
							pas[i][j] = t;
							vis[i][j] = false;
						}
	}
	else
		for (int i=0; i<4; ++i)
			for (int j=0; j<4; ++j)
				if (!vis[i][j] && possible(i, j, 3)){
					vis[i][j] = true;
					char t = pas[i][j];
					--num[3];
					sprintf(out[dep], "%c %d %d", pas[i][j] = 'D', i+1, j+1);
					++num[3];
					search(dep + 1);
					pas[i][j] = t;
					vis[i][j] = false;
				}
}

int main(){
	freopen("wissqu.in", "r", stdin);
	freopen("wissqu.out", "w", stdout);
	for (int i=0; i<4; ++i)
		scanf("%s", pas[i]);
	search();
	printf("%d\n", ans);
	return 0;
}
