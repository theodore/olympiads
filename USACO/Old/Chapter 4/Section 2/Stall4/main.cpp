/*
PROB:stall4
LANG:C++
*/
#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

const int inf = 1<<30;
int n, m, ans;
int graph[410][410];

int flow[410];
int pre[410];

void reduce(int now, int f){
	if (now){
		graph[pre[now]][now] -= f;
		graph[now][pre[now]] += f;
		reduce(pre[now], f);
	}
}

queue<int> q;

void getit(){
	for(; ;){
		memset(flow, 0, sizeof(flow));
		flow[0] = inf;
		q.push(0);
		while (!q.empty()){
			int now = q.front();
			q.pop();
			for (int i=1; i<=n+m+1; ++i)
				if (graph[now][i] > 0 && !flow[i]){
					flow[i] = min(flow[now], graph[now][i]);
					q.push(i);
					pre[i] = now;
				}
		}
		if (!flow[n+m+1])
			break;
		ans += flow[n+m+1];
		reduce(n+m+1, flow[n+m+1]);
	}
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
	getit();
	printf("%d\n", ans);
	return 0;
}
