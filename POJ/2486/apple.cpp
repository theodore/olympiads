#include <cstdio>
#include <cstring>

#define max(a, b) ((a) > (b) ? (a) : (b))

const int maxn(103);
const int maxm(203);
const int maxp(203);
int n, k;
//int amount[maxn];
int start[maxn], to[maxm], next[maxm], edge;
// max answer, max answer when going back
int f[maxn][maxp][2];

void add(int a, int b)
{
	to[++edge] = b;
	next[edge] = start[a];
	start[a] = edge;
}

void input()
{
	for (int i = 1; i <= n; ++i)
	{
		//scanf("%d", &amount[i]);
		scanf("%d", &f[i][0][0]);
		f[i][0][1] = f[i][0][0];
	}
	edge = 0;
	memset(start, 0, sizeof start);
	for (int i = 1, a, b; i < n; ++i)
	{
		scanf("%d%d", &a, &b);
		add(a, b);
		add(b, a);
	}
}

void search(const int x, const int fa)
{
	for (int e = start[x]; e; e = next[e])
		if (fa != to[e])
		{
			search(to[e], x);
			//for (int i = 1; i <= k; ++i)
			for (int i = k; i >= 1; --i)
			{
				//for (int j = i; j >= 2; --j)
				for (int j = 2; j <= i; ++j)
				{
					f[x][i][1] = max(f[x][i][1], f[to[e]][j-2][1] + f[x][i-j][1]);
					f[x][i][0] = max(f[x][i][0], f[to[e]][j-2][1] + f[x][i-j][0]);
					f[x][i][0] = max(f[x][i][0], f[to[e]][j-1][0] + f[x][i-j][1]);
				}
				f[x][i][0] = max(f[x][i][0], f[to[e]][0][0] + f[x][i-1][1]);
				if (f[x][i-1][0] > f[x][i][0])
					f[x][i][0] = f[x][i-1][0];
				/*
				if (i >= 2 && f[x][i-2][1] > f[x][i][1])
					f[x][i][1] = f[x][i-2][1];
				*/
			}
		}
	for (int i = 1; i <= k; ++i)
	{
		if (f[x][i-1][0] > f[x][i][0])
			f[x][i][0] = f[x][i-1][0];
	/*
		if (i >= 2 && f[x][i-2][1] > f[x][i][1])
			f[x][i][1] = f[x][i-2][1];
	*/
	}
}

int main()
{
#ifdef GDB
	freopen("in", "r", stdin);
#endif
	while (scanf("%d%d", &n, &k) != EOF)
	{
		memset(f, 0, sizeof f);
		input();
		search(1, 0);
#ifdef DB
		for (int i = 0; i <= k; ++i)
			printf("%d, %d\n", i, f[1][i][0]);
#else
		printf("%d\n", f[1][k][0]);
#endif
	}
	return 0;
}
