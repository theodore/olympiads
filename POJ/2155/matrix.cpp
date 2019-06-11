// First BIT
// Thu Aug 5, 10:31 AM
#include <cstdio>
#include <cstring>

int c[1010][1010], n;

inline int lowbit(int x)
{
	return x & -x;
}

void change(int x0, int y0)
{
	for (int x = x0; x <= n; x += lowbit(x))
		for (int y = y0; y <= n; y += lowbit(y))
			c[x][y] ^= 1;
}

void change(int x, int y, int xx, int yy)
{
	change(x, y);
	change(x, yy + 1);
	change(xx + 1, y);
	change(xx + 1, yy + 1);
}

int ask(int x0, int y0)
{
	int ret(0);
	for (int x = x0; x; x -= lowbit(x))
		for (int y = y0; y; y -= lowbit(y))
			ret ^= c[x][y];
	return ret;
}

int main()
{
#ifdef LOCAL
	freopen("in", "r", stdin);
#endif
	int _, t, x, y, xx, yy;
	char str[5];
	for (scanf("%d", &_); _--; )
	{
		memset(c, 0, sizeof(c));
		for (scanf("%d%d", &n, &t); t--; )
		{
			scanf("%s%d%d", str, &x, &y);
			if (str[0] == 'C')
			{
				scanf("%d%d", &xx, &yy);
				change(x, y, xx, yy);
			}
			else
				printf("%d\n", ask(x, y));
		}
		if (_)
			putchar(10);
	}
	return 0;
}
