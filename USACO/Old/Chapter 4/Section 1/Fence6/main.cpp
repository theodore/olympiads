/*
PROB:fence6
LANG:C++
*/
#include <iostream>

using namespace std;

struct E{
	int length, start, end;
	int nums, nume;
	int es[10], ee[10];
} edge[120];

int n, graph[120][120], c;

void add(E& here, int v, int from){
	bool s = false;
	for (int i=0; i<here.nums; ++i)
		if (here.es[i] == from)
			s = true;
	(s ? here.start : here.end) = v;
}

void init(){
	scanf("%d", &n);
	for (int i=1; i<=n; ++i){
		int l;
		E& now = edge[scanf("%d", &l), l];
		scanf("%d%d%d", &now.length, &now.nums, &now.nume);
		for (int j=0; j<now.nums; ++j)
			scanf("%d", now.es+j);
		for (int j=0; j<now.nume; ++j)
			scanf("%d", now.ee+j);
	}
#define now edge[i]
	for (int i=1; i<=n; ++i){
		if (!now.start){
			now.start = ++c;
			for (int j=0; j<now.nums; ++j)
				add(edge[now.es[j]], c, i);
		}
		if (!now.end){
			now.end = ++c;
			for (int j=0; j<now.nume; ++j)
				add(edge[now.ee[j]], c, i);
		}
	}
	for (int i=1; i<=n; ++i)
		graph[now.start][now.end] = graph[now.end][now.start] = now.length;
#undef now
}

int ans = 1 << 30;
bool visited[120];

void dfs(const int s, int now, int dep, int len){
	if (len >= ans || dep == c)
		return;
	if (now == s){
		ans = len;
		return;
	}
	visited[now] = true;
	for (int i=0; i<=c; ++i)
		if (graph[now][i] && !visited[i] && (dep || i!=s))
			dfs(s, i, dep+1, len+graph[now][i]);
	visited[now] = false;
}

void search(int s){
	for (int i=0; i<=c; ++i)
		if (graph[s][i])
			dfs(s, i, 0, graph[s][i]);
}

void debug(){
	for (int i=1; i<=n; ++i)
		printf("%d\t%d %d %d\n", i, edge[i].start, edge[i].end, edge[i].length);
	printf("\n");
	for (int i=1; i<=c; ++i){
		for (int j=1; j<=c; ++j)
			printf("%d ", graph[i][j]);
		printf("\n");
	}
}

//void check(){
//	for (int i=1; i<=c; ++i){
//		for (int j=1; j<=c; ++j)
//			printf("%d ", graph[i][j]);
//		printf("\n");
//	}
//	for (int i=1; i<=c; ++i){
//		for (int j=1; j<=c; ++j)
//			printf("%d\t", dist[i][j]);
//		printf("\n");
//	}
//}

int dist[120][120];

void getit(){
//	debug();
//	for (int i=1; i<=c; ++i)
//		search(i);
//	search(1);
	for (int i=1; i<=c; ++i)
		for (int j=1; j<=c; ++j){
			if (!graph[i][j])
				graph[i][j] = 1<<20;
			if (i == j)
				dist[i][j] = 0;
			else
				dist[i][j] = graph[i][j];
		}

//check();

	for (int k=1; k<=c; ++k){
		for (int i=1; i<k; ++i)
			for (int j=i+1; j<k; ++j)
				ans = min(ans, dist[i][j] + graph[i][k] + graph[k][j]);
		for (int i=1; i<=c; ++i)
			for (int j=1; j<=c; ++j)
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
	}
	printf("%d\n", ans);
}

int main(){
	freopen("fence6.in", "r", stdin);
	freopen("fence6.out", "w", stdout);
	init();
	getit();
	return 0;
}
