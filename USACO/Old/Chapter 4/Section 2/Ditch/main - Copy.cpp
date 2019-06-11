/*
PROB:ditch
LANG:C++
*/
#include <iostream>
#include <cstring>

using namespace std;

int n, m, ans;
int graph[210][210];

int flow[210] = {1<<30};
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
	if (now == m-1){
		ans += flow[now];
		reduce(now, flow[now]);
		memset(vis, 0, sizeof(vis));
		memset(flow, 0, sizeof(flow));
		flow[0] = 1<<30;
		search();
		return;
	}
	vis[now] = true;
	for (int i=0; i<m; ++i)
		if (!vis[i] && graph[now][i]){
			pre[i] = now;
			flow[i] = min(flow[now], graph[now][i]);
			search(i);
		}
	vis[now] = false;
}

int main(){
	freopen("ditch.in", "r", stdin);
	freopen("ditch.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for (int i=0; i<n; ++i){
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		graph[a-1][b-1] += c;
	}
	search();
	printf("%d\n", ans);
	return 0;
}
