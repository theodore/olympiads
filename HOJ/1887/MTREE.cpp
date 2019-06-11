#include <cstdio>
#include <cassert>

#define MSTACK

#ifdef unix
# define lld "%lld"
#else
# define lld "%I64d"
#endif

typedef long long ll;

const int maxn(100003);
const int maxm(200003);
const ll mod(1000000007);
int n;
int start[maxn], to[maxm], next[maxm], edge;
ll weight[maxm];
ll sum[maxn];
ll ans(0);

void add(int a, int b, int c)
{
	to[++edge] = b;
	weight[edge] = c;
	next[edge] = start[a];
	start[a] = edge;
}

#ifdef MSTACK
// current node, father, start edge, whether searched
int s[maxn][4], top;

void work(int x, int fa)
{
	s[0][0] = x;
	s[0][1] = fa;
	s[0][2] = start[x];
	s[0][3] = 0;
	top = 1;
	while (top)
	{
again:
		//static int now, se, p, vis;
		int& now = s[top-1][0];
		int& p = s[top-1][1];
		int& se = s[top-1][2];
		int& vis = s[top-1][3];
		for (int e = se; e; e = next[e])
			if (to[e] != p)
			{
				if (!vis)
				{
					vis = true;
					se = e;
					s[top][0] = to[e];
					s[top][1] = now;
					s[top][2] = start[to[e]];
					s[top][3] = 0;
					++top;
					goto again;
				}
				ans = (ans + weight[e]) % mod;
				ll t;
				t = weight[e] * sum[to[e]] % mod;
				ans = (ans + t) % mod;
				t = weight[e] * (1 + sum[to[e]]) % mod;
				ans = (ans + sum[now] * t) % mod;
				t = sum[to[e]] * weight[e] % mod;
				sum[now] = (sum[now] + weight[e] + t) % mod;
				vis = false;
			}
		--top;
#ifdef DB
		fprintf(stderr, "x = %d, ans = %lld\n", now, ans);
#endif
	}
}

#else
void work(int x, int fa)
{
	for (int e = start[x]; e; e = next[e])
		if (to[e] != fa)
		{
			work(to[e], x);
			ans = (ans + weight[e]) % mod;
			assert(ans > 0);
			ans = (ans + weight[e] * sum[to[e]]) % mod;
			assert(ans > 0);
			ll t;
			t = weight[e] * (1 + sum[to[e]]) % mod;
			assert(t > 0);
			ans = (ans + sum[x] * t) % mod;
			assert(ans > 0);
			t = (sum[to[e]] % mod) * (weight[e] % mod) % mod;
#ifdef DB
			fprintf(stderr, "%lld * %lld\n", sum[to[e]], weight[e]);
#endif
			assert(t >= 0);
			sum[x] = (sum[x] + weight[e] + t) % mod;
			assert(sum[x] > 0);
			/*
			ans += weight[e] * (1 + sum[to[e]]) * (1 + sum[x]);
			ans %= mod;
			sum[x] = (sum[x] + weight[e] * (sum[to[e]] + 1)) % mod;
			*/
		}
#ifdef DB
	fprintf(stderr, "x = %d, ans = %lld\n", x, ans);
#endif
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
	work(1, 0);
	printf(lld"\n", ans);
	return 0;
}
