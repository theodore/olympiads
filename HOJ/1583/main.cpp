#include <cstdio>
#include <cassert>
#ifdef unix
# define lld "%lld"
#else
# define lld "%I64d"
#endif

const int N(4000010);
const long long INF(-1llu>>1);
int a[2], b[2], d[2];
long long l[2][N];
int h[2], t[2];

long long f(long long c, int x)
{
	return a[x] * c / d[x] + b[x];
}

int main()
{
	int s, n;
	scanf("%d%d", &s, &n);
	for (int i = 0; i < 2; ++i)
		scanf("%d%d%d", a + i, b + i, d + i);
	long long la = 0;
	l[0][t[0]++] = s;
	while (n--)
	{
#ifdef DB
		printf("n = %d\n", n);
#endif
		static long long min[2];
		static bool d;
		min[0] = (h[0] == t[0]) ? INF : l[0][h[0]];
		min[1] = (h[1] == t[1]) ? INF : l[1][h[1]];
		assert(min[0] != INF || min[1] != INF);
		d = min[1] < min[0];
		++h[d];
		if (la == min[d])
			++n;
		else
		{
			l[0][t[0]++] = f(min[d], 0);
			l[1][t[1]++] = f(min[d], 1);
			la = min[d];
		}
	}
	printf(lld"\n", la);
	return 0;
}
