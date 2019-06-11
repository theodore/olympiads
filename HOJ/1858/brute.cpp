#include <cstdio>

int max(int a, int b)
{
	return (a > b) ? a : b;
}

int z[100];

int main()
{
	freopen("in", "r", stdin);
	freopen("ans", "w", stdout);
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++i)
		scanf("%d", &z[i]);
	while (m--)
	{
		static int a, b, c, r, p;
		scanf("%d%d%d", &a, &b, &c);
		switch(a)
		{
			case 0: case 1:
				for (int i = b; i <= c; ++i)
					z[i] = a;
				break;
			case 2:
				for (int i = b; i <= c; ++i)
					z[i] ^= 1;
				break;
			case 3:
				r = 0;
				for (int i = b; i <= c; ++i)
					r += z[i];
				printf("%d\n", r);
				break;
			case 4:
				r = p = 0;
				for (int i = b; i <= c; ++i)
					if (z[i])
						++p;
					else
					{
						r = max(r, p);
						p = 0;
					}
				printf("%d\n", max(r, p));
				break;
		}
	}
	return 0;
}
