#include <cstdio>
#include <cstdlib>
#include <cstring>

const int maxn(103);
const int maxm(100003);
int n, m;
int v[maxn], c[maxn];
//int nv[maxn * maxn], cnt;
bool ans[maxm];
int t;

int main()
{
	for (scanf("%d%d", &n, &m); n; scanf("%d%d", &n, &m))
	{
#ifdef DB
		fprintf(stderr, "%d %d\n", n, m);
#endif
		memset(ans, 0, sizeof ans);
		for (int i = 0; i < n; ++i)
			scanf("%d", &v[i]);
		for (int i = 0; i < n; ++i)
			scanf("%d", &c[i]);
		ans[0] = true;
		for (int i = 0; i < n; ++i)
		{
			for (int j = 1; j < c[i]; j <<= 1)
			{
				if ((t = v[i] * j) <= m)
				{
					for (int k = m; k >= t; --k)
						ans[k] |= ans[k - t];
				}
				else
					break;
				c[i] -= j;
			}
			if (c[i] && (t = v[i] * c[i]) <= m)
			{
				for (int k = m; k >= t; --k)
					ans[k] |= ans[k - t];
			}
		}
		/*
		for (int i = 0; i < cnt; ++i)
			for (int j = m; j >= nv[i]; --j)
				ans[j] |= ans[j - nv[i]];
		*/
		int ret(0);
		for (int i = 1; i <= m; ++i)
			ret += ans[i];
		printf("%d\n", ret);
	}
	return 0;
}
