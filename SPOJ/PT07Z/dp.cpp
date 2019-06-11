#include <cstdio>

#define max(a, b) ((a) > (b) ? (a) : (b))

const int maxn(10003);
const int maxm(20003);
int n;
int f[maxn];
int start[maxn], to[maxm], next[maxm], edge;
int ans;

void add(int a, int b)
{
	to[++edge] = b;
	next[edge] = start[a];
	start[a] = edge;
}

void search(const int x, const int fa)
{
	int maxv(0), maxv2(0);
	for (int e = start[x]; e; e = next[e])
		if (fa != to[e])
		{
			search(to[e], x);
			if (f[to[e]] + 1 > maxv)
			{
				maxv2 = maxv;
				maxv = f[to[e]] + 1;
			}
			else if (f[to[e]] + 1 > maxv2)
				maxv2 = f[to[e]] + 1;
		}
	ans = max(ans, maxv + maxv2);
	f[x] = maxv;
}

int main()
{
	scanf("%d", &n);
	for (int i = 1, a, b; i < n; ++i)
	{
		scanf("%d%d", &a, &b);
		add(a, b);
		add(b, a);
	}
	search(1, 0);
	printf("%d\n", ans);
	return 0;
}
