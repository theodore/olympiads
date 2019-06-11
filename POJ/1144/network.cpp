// POJ 1144 network
#include <cstdio>
#include <cstring>
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
//#define DB
#define SUB

using namespace std;

int n;
int to[20010], next[20010], start[10010], edge;
int ans;

bool hash[10010];
int vis[10010], depth[10010], ancestor[10010];

int dfs(int father = 0, int now = 1, int dep = 0){
	vis[now] = 1;
	ancestor[now] = depth[now] = dep;
	int sons(0), ret(0);
#define T to[e]
	for (int e=start[now]; e; e=next[e]){
		if (vis[T] == 1)
			ancestor[now] = min(ancestor[now], depth[T]);
		else if (!vis[T]){
			++sons;
			ret += dfs(now, T, dep+1);
			ancestor[now] = min(ancestor[now], ancestor[T]);
			if (now != 1 && !hash[now] && ancestor[T] >= dep)
				ret += hash[now] = true;
		}
	}
	if (now == 1 && !hash[now] && sons > 1)
		++ret;
#undef T
	vis[now] = 2;
	return ret;
}

// remember to memset vis, depth, ...
int main(){
#ifndef SUB
	freopen("network.in", "r", stdin);
	freopen("network.out", "w", stdout);
#endif
	int a, b;
	for (scanf("%d", &n); n; scanf("%d", &n)){
		ans = edge = 0;
		memset(vis, 0, sizeof vis);
		memset(start, 0, sizeof start);
		memset(hash, 0, sizeof hash);
		for (scanf("%d", &a); a; scanf("%d", &a))
			while (getchar() != '\n'){
				scanf("%d", &b);
				to[++edge] = b;
				next[edge] = start[a];
				start[a] = edge;
				to[++edge] = a;
				next[edge] = start[b];
				start[b] = edge;
			}
		printf("%d\n", dfs());
	}
	return 0;
}

