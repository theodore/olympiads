#include <cstdio>
#include <cstring>
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

using namespace std;

int n;
int to[20010], next[20010], start[10010], edge;

bool vis[10010];
int low[10010], depth[10010], father[10010];

/*
int dfs(int now = 1, int papa = 0, int dep = 0)
{
	low[now] = depth[now] = dep;
	father[now] = papa;
	vis[now] = true;
	int son_num(0), ret(0);
	bool am_I(false);
	for (int e=start[now]; e; e=next[e])
		if (!vis[to[e]]) {
			++son_num;
			ret += dfs(to[e], now, dep+1);
			low[now] = min(low[now], low[to[e]]);
			if (now != 1 && low[to[e]] >= dep)
				am_I = true;
		}
		else
			low[now] = min(low[now], depth[to[e]]);
	if (now == 1 && son_num > 1)
		am_I = true;
#ifdef DB
	if (am_I)
		printf("%d is a cut point\n", now);
#endif
	return ret += am_I;
}
*/

bool cut[10010];

void dfs(int now = 1, int papa = 0, int dep = 0)
{
	vis[now] = true;
	low[now] = depth[now] = dep;
	father[now] = papa;
	
	int num_of_sons(0);
	for (int e=start[now]; e; e=next[e])
		if (vis[to[e]]) {
			if (to[e] != papa) {
				low[now] = min(low[now], depth[to[e]]);
			}
		}
		else {
			++num_of_sons;
			dfs(to[e], now, dep + 1);
			low[now] = min(low[now], low[to[e]]);
			if (now != 1 && low[to[e]] >= depth[now])
				cut[now] = true;
		}
	if (now == 1)
		cut[now] = num_of_sons > 1;
}

int main()
{
	int a, b;
	for (scanf("%d", &n); n; scanf("%d", &n)){
		edge = 0;
		memset(low, 0, sizeof low);
		memset(start, 0, sizeof start);
		memset(vis, 0, sizeof vis);
		memset(cut, 0, sizeof cut);
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
		//printf("%d\n", dfs());
		dfs();
		int ans(0);
		for (int i=1; i<=n; ++i)
			if (cut[i])
				++ans;
		printf("%d\n", ans);
	}
	return 0;
}
