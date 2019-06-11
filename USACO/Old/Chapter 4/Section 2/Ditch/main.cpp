/*
PROB:ditch
LANG:C++
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <cstring>

using namespace std;

const int inf = 1<<30;

int n, m, ans;
int graph[210][210];

int flow[210];
int pre[210];

void reduce(int now, int f){
	if (now){
		graph[pre[now]][now] -= f;
		graph[now][pre[now]] += f;
		reduce(pre[now], f);
	}
}

int dist[210], cur[210];
queue<int> q;


// SAP, with bugs though
void getit(){
	q.push(m-1);
//	while (!q.empty()){
//		int now = q.front();
//		q.pop();
//		for (int i=0; i<m-1; ++i)
//			if (graph[i][now] && !dist[i]){
//				dist[i] = dist[now] + 1;
//				q.push(i);
//			}
//	}

	for (; ;){
		memset(flow, 0, sizeof(flow));
		flow[0] = inf;
		q.push(0);
		while (!q.empty()){
			int now = q.front();
			q.pop();
//			bool g = false;
			for (int i=1; i<m; ++i){
//				if (graph[now][i] > 0 && dist[now] == dist[i]+1 && !flow[i]){
				if (graph[now][i] > 0 && !flow[i]){
//					g = true;
					flow[i] = min(flow[now], graph[now][i]);
					pre[i] = now;
					q.push(i);
				}
			}
//			if (!g){
//				g = false;
//				for (int i=1; i<m; ++i)
//					if (graph[now][i] > 0 && (!g || dist[now] > dist[i])){
//						g = true;
//						dist[now] = dist[i] + 1;
//					}
//			}
//			if (!g){
//				dist[now] = inf;
//				now = pre[now];
//			}
		}
		if (!flow[m-1])
			break;
		ans += flow[m-1];
		reduce(m-1, flow[m-1]);
	}
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
	getit();
	printf("%d\n", ans);
	return 0;
}
