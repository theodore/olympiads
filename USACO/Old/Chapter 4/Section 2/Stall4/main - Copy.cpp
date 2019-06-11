/*
PROB:stall4
LANG:C++
*/
#include <iostream>
#include <cstring>

using namespace std;

const int inf = 1<<30;
int n, m, ans;
int graph[210][210];

int flow[210] = {inf};
bool vis[210];
int pre[210];

void reduce(int now, int f){
	if (now){
		graph[pre[now]][now] -= f;
		graph[now][pre[now]] += f;
		reduce(pre[now], f);
	}
}

void search(int now = 0){
	if (now == n+m+1){
		ans += flow[now];
		reduce(now, flow[now]);
		memset(vis, 0, sizeof(vis));
		memset(flow, 0, sizeof(flow));
		flow[0] = inf;
		search();
		return;
	}
	vis[now] = true;
	for (int i=0; i<=n+m+1; ++i)
		if (!vis[i] && graph[now][i]){
			pre[i] = now;
			flow[i] = min(flow[now], graph[now][i]);
			search(i);
		}
	vis[now] = false;
}

int main(){
	freopen("stall4.in", "r", stdin);
	freopen("stall4.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for (int i=1; i<=n; ++i){
		graph[0][i] = 1;
		int x;
		for (scanf("%d", &x); x; --x){
			int j;
			scanf("%d", &j);
			graph[i][j+n] = 1;
			graph[j+n][n+m+1] = 1;
		}
	}
	search();
	printf("%d\n", ans);
	return 0;
}
