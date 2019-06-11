/*
 * Date: 11/01/15
 * Problem: LCIS
 */
#include <cstdio>
#include <cstring>

namespace solve
{
	static const int maxn = 3005;
	int n, a[maxn], b[maxn];
	inline int max(int x, int y)
	{
		return x > y ? x : y;
	}
	
	void solve();
	int work();
}

void solve::solve()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++) scanf("%d", &b[i]);
	printf("%d\n", work());
}

int solve::work()
{
	int f1[maxn], f2[maxn];
	memset(f1, 0, sizeof(f1));
	memset(f2, 0, sizeof(f2));
	for (int i = 1; i <= n; i++)
	{
		int k = 0;
		for (int j = 1; j <= n; j++)
		{
			f2[j] = f1[j];
			if ((a[i] == b[j]) && (f1[k] + 1 > f2[j]))
			{
				f2[j] = f1[k] + 1;
			}
			else if((a[i] > b[j]) && (f1[j] > f1[k]))
			{
				k = j;
			}
		}
		memcpy(f1, f2, sizeof(f2));
	}
	int ret = 0;
	for (int i = 0; i <= n; i++)
		ret = max(ret, f1[i]);
	return ret;
}

int main()
{
	solve::solve();
	return 0;
}
