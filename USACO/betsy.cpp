/*
PROB:betsy
LANG:C++
*/
#include <cstdio>

using namespace std;

int n, count, ans;
int num_cant[10][10];
bool vis[10][10];

int dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1};

bool good(int x, int y){
#define J(x, y) (x >=0 && y >= 0 && x < n && y < n && !vis[x][y])
	if (!J(x, y))
		return false;
	if (x==n-1 && !y)
		return true;
	int nx, ny;
	bool res[4];
	for (int dir=0; dir<4; ++dir){
		nx = x + dx[dir];
		ny = y + dy[dir];
		res[dir] = J(nx, ny);
	}
#undef J
	// if 0&2 is good and 1&3 is bad or if 0&2 is bad and 1&3 is good
	if ((res[0] && res[2] && !res[1] && !res[3]) || (!res[0] && !res[2] && res[1] && res[3]))
		return false;
	else
		return true;
}

bool dead(int x, int y){
	return !vis[x][y] && num_cant[x][y] >= 3;
}

void search(int x = 0, int y = 0){
	if (x==n-1 && !y){
		if (count == n*n-1)
			++ans;
		return;
	}
#define J(x, y) (x >=0 && y >= 0 && x < n && y < n)// && !vis[x][y])
	int nx, ny;
	for (int dir=0; dir<4; ++dir){
		nx = x+dx[dir];
		ny = y+dy[dir];
		if (J(nx, ny) && dead(nx, ny))
			return;
	}
	count += vis[x][y] = true;
	for (int dir=0; dir<4; ++dir){
		nx = x+dx[dir];
		ny = y+dy[dir];
		if (J(nx, ny))
			++num_cant[nx][ny];
	}
	int dd(0);
	for (int dir=0; dir<4; ++dir){
		nx = x+dx[dir];
		ny = y+dy[dir];
		if (J(nx, ny))
			dd += dead(nx, ny);
	}
	if (!dd){
		for (int dir=0; dir<4; ++dir){
			nx = x+dx[dir];
			ny = y+dy[dir];
			if (good(nx, ny))
				search(nx, ny);
		}
	}
	else if (dd == 1){
		for (int dir=0; dir<4; ++dir){
			nx = x+dx[dir];
			ny = y+dy[dir];
			if (J(nx, ny) && dead(nx, ny)){
				search(nx, ny);
				break;
			}
		}
	}
	vis[x][y] = false;
	--count;
	for (int dir=0; dir<4; ++dir){
		nx = x+dx[dir];
		ny = y+dy[dir];
		if (J(nx, ny))
			--num_cant[nx][ny];
	}
#undef J
}

void everythingb4(){
	for (int i=0; i<n; ++i){
		++num_cant[0][i];
		++num_cant[i][0];
		++num_cant[n-1][i];
		++num_cant[i][n-1];
	}
	num_cant[n-1][0] = -1;
}

int main(){
	freopen("betsy.in", "r", stdin);
	freopen("betsy.out", "w", stdout);
	scanf("%d", &n);
	everythingb4();
	search();
	printf("%d\n", ans);
	return 0;
}

