#include <cstdio>
#include <cstring>
#include <queue>

int n, start[10010], to[20010], nextt[20010];

struct ans_t{
	int dist, dest;
} ans;

int dist[10010];
std::queue<int> q;
int main(){
	scanf("%d", &n);
	for (int i=1; i<n; ++i){
		int a, b, t;
		scanf("%d%d", &a, &b);
		nextt[t=i*2-1] = start[a];
		to[t] = b;
		start[a] = t;
		nextt[++t] = start[b];
		to[t] = a;
		start[b] = t;
	}
	q.push(1);
	while(!q.empty()){
		int now(q.front());
		q.pop();
		if (dist[now] > ans.dist){
			ans.dist = dist[now];
			ans.dest = now;
		}
		for (int e=start[now]; e; e=nextt[e])
			if (!dist[to[e]] && to[e]!=1){
				dist[to[e]] = dist[now] + 1;
				q.push(to[e]);
			}
	}
	memset(dist, 0, sizeof dist);
	q.push(ans.dest);
	while (!q.empty()){
		int now(q.front());
		q.pop();
		if (dist[now] > ans.dist)
			ans.dist = dist[now];
		for (int e=start[now]; e; e=nextt[e])
			if (!dist[to[e]] && to[e]!=ans.dest){
				dist[to[e]] = dist[now] + 1;
				q.push(to[e]);
			}
	}
	printf("%d\n", ans.dist);
	return 0;
}
