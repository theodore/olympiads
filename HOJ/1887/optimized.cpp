#include <cstdio>

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
	}
}

const int buffer_size(1900007);
char buff[buffer_size];
char* cur = buff;

#define read(x) \
{ \
	for (; *cur < '0' || '9' < *cur; ++cur); \
	x = 0; \
	for (; '0' <= *cur && *cur <= '9'; ++cur) \
		x = x * 10 + *cur - '0'; \
}

int main()
{
	fread(buff, 1, buffer_size, stdin);
	read(n);
	for (int i = 1, a, b, c; i < n; ++i)
	{
		read(a); read(b); read(c);
		add(a, b, c);
		add(b, a, c);
	}
	work(1, 0);
	printf(lld"\n", ans);
	return 0;
}
