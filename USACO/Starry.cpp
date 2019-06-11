/*
PROB:starry
LANG:C++
*/
#pragma warning(disable: 4996)
#include <iostream>
#include <cstring>
#define max(a, b) ((a)>(b) ? (a) : (b))
//#define Debug

using namespace std;

const int dx[] = {-1, -1, 0, 1, 1, 1, 0, -1};
const int dy[] = {0, 1, 1, 1, 0, -1, -1, -1};

typedef char plane [110][110];

plane map;

struct C{
	plane shape;
	int n, m, count;

	void init(int);
	bool operator==(C);
	void operator=(const C&);
	void hor();
	void ver();
	void rot();
} cluster[26], temp;
int start;

void C::init(int x){
	n = m = count = 0;
	for (int i=0; i<x; ++i)
		memset(shape[i], 0, 100);
}

void C::hor(){
	for (int i=0; i<n; ++i)
		for (int j=0; j<(m+1)/2; ++j)
			swap(shape[i][j], shape[i][m-1-j]);
}

void C::ver(){
	for (int i=0; i<(n+1)/2; ++i)
		for (int j=0; j<m; ++j)
			swap(shape[i][j], shape[n-1-i][j]);
}

void C::rot(){
	plane temp;
	for (int i=0; i<n; ++i)
		memcpy(temp[i], shape[i], sizeof shape[i]);
	n ^= m ^= n ^= m;
	for (int i=0; i<n; ++i)
		for (int j=0; j<m; ++j)
			shape[i][j] = temp[j][i];
}

bool C::operator==(C r){
	if (count != r.count)
		return false;
	bool equal;
	if (n == r.n && m == r.m){
		for (int _=0; _<4; ++_){
			equal = true;
			for (int i=0; i<n; ++i)
				for (int j=0; j<m; ++j)
					if (shape[i][j] != r.shape[i][j]){
						equal = false;
						goto out1;
					}
out1:
			if (equal)
				return true;
			if (_ == 0 || _ == 2)
				r.ver();
			if (_ == 1)
				r.hor();
		}
	}
	if (n == r.m && m == r.n){
		r.rot();
		for (int _=0; _<4; ++_){
			equal = true;
			for (int i=0; i<n; ++i)
				for (int j=0; j<m; ++j)
					if (shape[i][j] != r.shape[i][j]){
						equal = false;
						goto out2;
					}
out2:
			if (equal)
				return true;
			if (_ == 0 || _ == 2)
				r.ver();
			if (_ == 1)
				r.hor();
		}
	}
	return false;
}

void C::operator=(const C& r){
	n = r.n;
	m = r.m;
	count = r.count;
	for (int i=0; i<n; ++i)
		memcpy(shape[i], r.shape[i], m);
}

void search(int x, int y, int tx = 0, int ty = 0){
	map[x][y] = '*';
	temp.shape[tx][ty] = '*';
	temp.n = max(temp.n, tx + 1);
	temp.m = max(temp.m, (ty-start+100)%100+1);
	++temp.count;
	/*
	if (x && map[x-1][y] == '1')
		search(x-1, y, tx-1, ty);
	if (x && map[x-1][y+1] == '1')
		search(x-1, y+1, tx-1, ty+1);
	if (map[x][y+1] == '1')
		search(x, y+1, tx, ty+1);
	if (map[x+1][y] == '1')
		search(x+1, y, tx+1, ty);
	if (map[x+1][y+1] == '1')
		search(x+1, y+1, tx+1, ty+1);
	if (x && y && map[x-1][y-1] == '1'){
	}
	if (y && map[x][y-1] == '1'){
	}
	if (y && map[x+1][y-1] == '1'){
		if (y == start){
			start = start ? start-1 : 99;
			++temp.m;
		}
		search(x+1, y-1, tx+1, ty?ty-1:99);
	}
	*/
	for (int dir=0; dir<8; ++dir){
		int nx(x+dx[dir]), ny(y+dy[dir]);
		if (nx >= 0 && ny >= 0 && map[nx][ny] == '1'){
			if (ty == start && dir>4){
				start = start ? start-1 : 99;
				++temp.m;
			}
			search(nx, ny, tx+dx[dir], (ty+dy[dir]+100)%100);
		}
	}
}

#ifdef Debug
int num;

void debug(){
	cout << endl;
	for (int i=0; i<num; ++i){
		cout << "Cluster " << i << endl;
		cout << "Cout = " << cluster[i].count << endl;
		for (int j=0; j<cluster[i].n; ++j){
			for (int k=0; k<cluster[i].m; ++k)
				cout << (cluster[i].shape[j][k]=='*' ? '*' : '#');
			cout << endl;
		}
	}
	cout << start << endl;
}

void searched(){
	printf("Search Finished!\n");
	printf("n = %d, m = %d, count = %d\n", temp.n, temp.m, temp.count);
	for (int i=0; i<temp.n; ++i){
		for (int j=0; j<temp.m; ++j)
			printf("%c", temp.shape[i][j]=='*' ? '*' : '#');
		printf("\n");
	}
	printf("\n");
}
#endif

int main(){
	freopen("starry.in", "r", stdin);
	freopen("starry.out", "w", stdout);
	int n, m
#ifndef Debug
		, num(0);
#else
		;
#endif
	scanf("%d%d", &m, &n);
	for (int i=0; i<n; ++i)
		scanf("%s", map[i]);
#ifdef Debug
	for (int i=0; i<n; ++i)
		printf("%s\n", map[i]);
	printf("\n");
#endif
	for (int i=0; i<n; ++i)
		for (int j=0; j<m; ++j)
			if (map[i][j] == '1'){
				temp.init(n);
				start = 0;
				search(i, j);
				if (start){
					char sw[110];
					for (int u=0; u<temp.n; ++u){
						memcpy(sw, temp.shape[u]+start, 100-start);
						memcpy(sw+100-start, temp.shape[u], m-100+start);
						memcpy(temp.shape[u], sw, m);
					}
				}
#ifdef Debug
				searched();
#endif
				bool found(false);
				int inc(num);
				for (int k=0; k<num && !found; ++k)
					if (temp == cluster[k]){
						found = true;
						inc = k;
					}
				if (!found)
					cluster[num++] = temp;
				for (int s=0; s<n; ++s)
					for (int t=0; t<m; ++t)
						if (map[s][t] == '*')
							map[s][t] = 'a' + inc;
			}
	for (int i=0; i<n; ++i)
		printf("%s\n", map[i]);
#ifdef Debug
	debug();
#endif
	return 0;
}
