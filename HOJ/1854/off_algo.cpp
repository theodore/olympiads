#include <cstdio>

const int maxn(10003);
const int maxm(2000003);
int f[maxn];
bool all[maxn];
int cnt[maxn];

int getfather(const int x)
{
	int fa = x;
	while (f[fa] != fa)
		fa = f[fa];
	for (int i = x, next; i != fa; i = next)
	{
		next = f[i];
		f[i] = fa;
	}
	return fa;
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
	int m;
	getint(m);
	for (int i = 0, a, b; i < m; ++i)
	{
		getint(a);
		getint(b);
		if (f[a] == 0)
		{
			f[a] = a;
			cnt[a] = 1;
		}
		if (f[b] == 0)
		{
			f[b] = b;
			cnt[b] = 1;
		}
		int fa = getfather(a);
		int fb = getfather(b);
		if (fa == fb)
			all[fa] = true;
		else
		{
			f[fa] = fb;
			all[fb] |= all[fa];
			cnt[fb] += cnt[fa];
		}
	}
	for (int i = 1; ; ++i)
	{
		if (f[i] == 0)
		{
			printf("%d\n", i - 1);
			return 0;
		}
		int fa = getfather(i);
		if (!all[fa] && --cnt[fa] == 0)
		{
			printf("%d\n", i - 1);
			return 0;
		}
	}
	return 0;
}
