/*
PROB:snail
LANG:C++
*/
#pragma warning(disable: 4996)
#include <iostream>
#include <cstring>
#include <cmath>
//#define Debug
//#define NO_OUT_FILE
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

using namespace std;

int n;
int grid[123][123];
int ans;
const int dx[] = {-1, 0, 1, -1}, dy[] = {0, 1, 0, -1};

#ifdef Debug
void display(){
	printf("\n");
	for (int i=0; i<n; ++i){
		for (int j=0; j<n; ++j)
			printf("%d", grid[j][i]);
		printf("\n");
	}
}
#endif

// got trouble at (x, y), facing dir:
//     0 - up
//     1 - right
//     2 - down
//     3 - left
//    -1 - init
void search(const int x = 0, const int y = 0, const int dir = -1, int now = 0){
	ans = max(ans, now);
#ifdef Debug
	printf("Searching %c, %d, %d, %d\n", 'A'+x, y, dir, now);
	display();
#endif
	if (dir == -1){
		int next;
		for (next = 0; next < n && !grid[0][next]; ++next)
			grid[0][next] = 2, ++now;
		search(0, next-1, 1, now);
		memset(grid[0], 0, 4 * next);
		for (next = now = 0; next < n && !grid[next][0]; ++next)
			grid[next][0] = 2, ++now;
		search(next-1, 0, 2, now);
	}
	else{
		int ndir, o=now;
		int next;
		bool fin(false);
		switch(ndir = dir==3 ? 0 : dir+1){
		case 0:
		case 2:
			for (next = x+dx[ndir]; next>=0 && next<n; next+=dx[ndir])
				if (grid[next][y] == 0)
					grid[next][y] = 2, ++now;
				else if (grid[next][y] == 1)
					break;
				else{
					ans = max(ans, now);
					fin = true;
					break;
				}
			if (!fin && next != x + dx[ndir])
				search(next-dx[ndir], y, ndir, now);
			//for (int i=min(x, next-dx[ndir]); i<max(x, next-dx[ndir]); ++i)
				//grid[i][y] = 0;
			// new solution, below 3 are the same as this
			if (next > x)
				for (int i=x+dx[ndir]; i<next; ++i)
					grid[i][y] = 0;
			else
				for (int i=next-dx[ndir]; i<x; ++i)
					grid[i][y] = 0;
			break;
		case 1:
		case 3:
			for (next = y+dy[ndir]; next>=0 && next<n; next+=dy[ndir])
				if (grid[x][next] == 0)
					grid[x][next] = 2, ++now;
				else if (grid[x][next] == 1)
					break;
				else{
					ans = max(ans, now);
					fin = true;
					break;
				}
			if (!fin && next != y + dy[ndir])
				search(x, next-dy[ndir], ndir, now);
			/// TODO: It can be wrong here!
			//memset(grid[x]+min(y, next-dy[ndir]), 0, 4 * abs(y - next));
			// @TODO who cares, we got a new solution
			if (next > y)
				memset(grid[x]+y+dy[ndir], 0, 4 * (next - y - 1));
			else
				memset(grid[x]+next-dy[ndir], 0, 4 * (y - next - 1));
			break;
		}
		now = o;
		fin = false;
		switch(ndir = dir ? dir-1 : 3){
		case 0:
		case 2:
			for (next = x+dx[ndir]; next>=0 && next<n; next+=dx[ndir])
				if (grid[next][y] == 0)
					grid[next][y] = 2, ++now;
				else if (grid[next][y] == 1)
					break;
				else{
					ans = max(ans, now);
					fin = true;
					break;
				}
			if (!fin && next != x + dx[ndir])
				search(next-dx[ndir], y, ndir, now);
			//for (int i=min(x, next-dx[ndir]); i<max(x, next-dx[ndir]); ++i)
				//grid[i][y] = 0;
			if (next > x)
				for (int i=x+dx[ndir]; i<next; ++i)
					grid[i][y] = 0;
			else
				for (int i=next-dx[ndir]; i<x; ++i)
					grid[i][y] = 0;
			break;
		case 1:
		case 3:
			for (next = y+dy[ndir]; next>=0 && next<n; next+=dy[ndir])
				if (grid[x][next] == 0)
					grid[x][next] = 2, ++now;
				else if (grid[x][next] == 1)
					break;
				else{
					ans = max(ans, now);
					fin = true;
					break;
				}
			if (!fin && next != y + dy[ndir])
				search(x, next-dy[ndir], ndir, now);
			// TODO: It can be wrong here!
			//memset(grid[x]+min(y, next-dy[ndir]), 0, 4 * abs(y - next));
			if (next > y)
				memset(grid[x]+y+dy[ndir], 0, 4 * (next - y - 1));
			else
				memset(grid[x]+next-dy[ndir], 0, 4 * (y - next - 1));
			break;
		}
	}
}

int main(){
	freopen("snail.in", "r", stdin);
#ifndef NO_OUT_FILE
	freopen("snail.out", "w", stdout);
#endif
	int m;
	scanf("%d%d", &n, &m);
	for (int i=0; i<m; ++i){
		char t[11];
		scanf("%s",  t);
		char* p = t+1;
		int s = (*p) - '0';
		while (*(++p))
			s = s * 10 + (*p) - '0';
		grid[t[0] - 'A'][s-1] = 1;
	}
	if (grid[0][0]){
		printf("0\n");
		return 0;
	}
	search();
	printf("%d\n", ans);
	return 0;
}
