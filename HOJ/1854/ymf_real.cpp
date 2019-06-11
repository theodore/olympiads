#include <cstdio>
#include <cstring>
#include <cstdlib>

#define MAXR 10001
#define MAXN 1000001
#define MAXM 2000001

int N,match[MAXN];
int fir[MAXR],next[MAXM],end[MAXM],ECnt;

void AddEdge(int st,int ed)
{
	next[++ECnt] = fir[st];
	fir[st] = ECnt;
	end[ECnt] = ed;
}

bool vis[MAXN];
int stack[MAXN],top;

bool dfs(int u)
{
	int t;
	for (int now = fir[u],v; now; now = next[now])
		if (!vis[v = end[now]])
		{
			vis[v] = 1;
			stack[++top] = v;
			t = match[v];
			match[v] = u;
			if (!t || dfs(t)) return 1;
			match[v] = t;
		}
	return 0;
}

void getint(int& x)
{
	static char ch;
	while ((ch = getchar()) < '0' || ch > '9')
		;
	x = ch - '0';
	while ((ch = getchar()) >= '0' && ch <= '9')
		x = x * 10 + ch - '0';
}

int main()
{
	getint(N);
	for (int i = 1, x; i <= N; i++)
	{
		getint(x); AddEdge(x,i);
		getint(x); AddEdge(x,i);
	}

	for (int i = 1; ;i++)
	{
		top = 0;
		if (!dfs(i)) {printf("%d\n",i - 1); break;}
		while (top) vis[stack[top--]] = 0;
	}
	return 0;
}
