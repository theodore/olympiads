#include <cstdio>

#define min(a, b) ((a) < (b) ? (a) : (b))

#define MSTACK

const int maxn(100003);
const int maxm(200003);
int n;
int start[maxn], to[maxm], next[maxm], edge;
// f[i]: minimum answer on subtree i.
// g[i]: minimum answer on subtree i, when i is chosen.
int f[maxn], g[maxn];

void add(int a, int b)
{
	to[++edge] = b;
	next[edge] = start[a];
	start[a] = edge;
}

#ifdef MSTACK
// x, fa, se, whether searched
int s[maxn][3], top;
void search(const int px, const int pfa)
{
	s[1][0] = px;
	s[1][1] = pfa;
	s[1][2] = start[px];
	s[1][3] = 0;
	top = 1;
	while (top)
	{
next:
		const int& x	= s[top][0];
		const int& fa	= s[top][1];
		int& se			= s[top][2];
		int& vis		= s[top][3];
		for (int e = se; e; e = next[e])
			if (fa != to[e])
			{
				if (vis)
				{
					f[x] += g[to[e]];
					g[x] += f[to[e]];
					vis = 0;
				}
				else
				{
					vis = 1;
					se = e;
					++top;
					s[top][0] = to[e];
					s[top][1] = x;
					s[top][2] = start[to[e]];
					s[top][3] = 0;
					goto next;
				}
			}
		++g[x];
		f[x] = min(f[x], g[x]);
		--top;
	}
}
#else
void search(const int x, const int fa)
{
	f[x] = 0;
	g[x] = 1;
	for (int e = start[x]; e; e = next[e])
		if (fa != to[e])
		{
			search(to[e], x);
			f[x] += g[to[e]];
			g[x] += f[to[e]];
		}
	f[x] = min(f[x], g[x]);
}
#endif

const int buff_size(1500003);
char buff[buff_size];
char* p = buff;

#define read(x) \
{ \
	for (; *p < '0' || '9' < *p; ++p); \
	for (x = 0; '0' <= *p && *p <= '9'; ++p) \
		x = x * 10 + *p - '0'; \
}
//#define read(x) scanf("%d", &x)

int main()
{
	fread(buff, 1, buff_size, stdin);
	read(n);
	for (int i = 1, a, b; i < n; ++i)
	{
		read(a);
		read(b);
		add(a, b);
		add(b, a);
	}
	search(1, 0);
	printf("%d\n", f[1]);
	return 0;
}
