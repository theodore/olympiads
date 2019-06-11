#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>

#define MAXN 501

using namespace std;

int N,K,r,c,match[MAXN],ans = 0;
bool map[MAXN][MAXN],vis[MAXN];

bool dfs(int pos) {

	for (int i = 1; i <= N; i++)
		if (map[pos][i] && !vis[i])
		{
			vis[i] = 1;
			int t = match[i];
			match[i] = pos;
			if (!t || dfs(t)) return 1;
			match[i] = t;
		}
	return 0;
}

int main() {

	scanf("%d %d",&N,&K);
	for (int i = 1; i <= K; i++)
	{
		scanf("%d %d",&r,&c);
		map[r][c] = 1;
	}

	memset(match,0,sizeof(match));
	for (int i = 1; i <= N; i++)
	{
		memset(vis,0,sizeof(vis));
		if (dfs(i)) ans++;
	}
	printf("%d\n",ans);

	return 0;
}
