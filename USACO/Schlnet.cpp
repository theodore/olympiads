/*
PROB: schlnet
LANG: C++
*/
#pragma warning(disable: 4996)
#include <iostream>
//#define Debug
//#define NO_OUT

using namespace std;

int n, ofcomp[110], m, indeg[110];
bool orig[110][110], graph[110][110], to[110], from[110];

void labelto(int x){
//#ifdef Debug
//	printf("Labling to %d\n", x);
//#endif
	to[x] = true;
	for (int i=1; i<=n; ++i)
		if (orig[x][i] && !to[i])
			labelto(i);
}

void labelfrom(int x){
//#ifdef Debug
//	printf("Labling from %d\n", x);
//#endif
	from[x] = true;
	for (int i=1; i<=n; ++i)
		if (orig[i][x] && !from[i])
			labelfrom(i);
}

void get_new(){
	for (int i=1; i<=n; ++i){
		if (!ofcomp[i]){
			labelto(i);
			labelfrom(i);
			++m;
			for (int j=1; j<=n; ++j){
				if (to[j] && from[j])
					ofcomp[j] = m;
				to[j] = from[j] = false;
			}
		}
	}
	for (int i=1; i<=n; ++i)
		for (int j=1; j<=n; ++j)
			if (orig[i][j])
				graph[ofcomp[i]][ofcomp[j]] = true;
}

void debug(){
	for (int i=1; i<=n; ++i)
		for (int j=1; j<=n; ++j)
			if (orig[i][j])
				printf("%d -> %d\n", i, j);
	for (int i=1; i<=n; ++i)
		printf("ofcomp[%d] = %d\n", i, ofcomp[i]);
	for (int i=1; i<=m; ++i)
		for (int j=1; j<=m; ++j)
			if (graph[i][j])
				printf("%d -> %d\n", i, j);
}

int ans;

int ans1(){
	for (int i=1; i<=m; ++i)
		for (int j=1; j<=m; ++j)
			if (graph[i][j] && i != j)
				++indeg[j];
	for (int i=1; i<=m; ++i)
		if (!indeg[i])
			++ans;
	return ans;
}

int outdeg[110];

int ans2(){
	if (m == 1)
		return 0;
	int ret(0);
	for (int i=1; i<=m; ++i)
		for (int j=1; j<=m; ++j)
			if (graph[i][j] && i != j)
				++outdeg[i];
	for (int i=1; i<=m; ++i)
		if (!outdeg[i])
			++ret;
	return max(ans, ret);
}

int main(){
	freopen("schlnet.in", "r", stdin);
#ifndef NO_OUT
	freopen("schlnet.out", "w", stdout);
#endif
	scanf("%d", &n);
	for (int i=1; i<=n; ++i){
		int j;
		for (scanf("%d", &j); j; scanf("%d", &j))
			orig[i][j] = true;
	}
	get_new();
#ifdef Debug
	debug();
#else
	printf("%d\n", ans1());
	printf("%d\n", ans2());
#endif
	return 0;
}
