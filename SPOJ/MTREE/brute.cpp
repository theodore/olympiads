#include <cstdio>

#ifndef DB
//# define MSTACK
#endif

typedef long long ll;

const int maxn(100003);
const int maxm(200003);
const int mod(1000000007);
int n;
int start[maxn], to[maxm], next[maxm], weight[maxm], edge;
ll ans(0);
ll d[maxn];

void add(int a, int b, int c)
{
	to[++edge] = b;
	weight[edge] = c;
	next[edge] = start[a];
	start[a] = edge;
}

#ifdef MSTACK
// current node, father, current edge
int s[maxn][3], top;
void search(int px, int pfa)
{
	s[0][0] = px;
	s[0][1] = pfa;
	s[0][2] = start[px];
	top = 1;
	while (top)
	{
again:
		int& x = s[top-1][0];
		int& fa = s[top-1][1];
		int& se = s[top-1][2];
#ifdef DB
		//fprintf(stderr, "popped, %d, %d, %d\n", x, fa, se);
#endif
		for (int e = se; e; e = next[e])
		{
			if (to[e] != fa)
			{
				d[to[e]] = (weight[e] * d[x]) % mod;
				se = next[e];
				s[top][0] = to[e];
				s[top][1] = x;
				s[top][2] = start[to[e]];
				++top;
				goto again;
			}
		}
		--top;
	}
}

#else
void search(int x, int fa)
{
	for (int e = start[x]; e; e = next[e])
	{
		if (to[e] != fa)
		{
			d[to[e]] = (weight[e] * d[x]) % mod;
			search(to[e], x);
		}
	}
}
#endif

int main()
{
#ifdef GDB
	freopen("in", "r", stdin);
#endif
	scanf("%d", &n);
	for (int i = 1, a, b, c; i < n; ++i)
	{
		scanf("%d%d%d", &a, &b, &c);
		add(a, b, c);
		add(b, a, c);
	}
	for (int i = 1; i <= n; ++i)
	{
		d[i] = 1;
		search(i, 0);
		for (int j = i + 1; j <= n; ++j)
			ans = (ans + d[j]) % mod;
	}
	printf("%lld\n", ans);
	return 0;
}
