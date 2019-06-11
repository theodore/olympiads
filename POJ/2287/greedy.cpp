#include <cstdio>
#include <cassert>
#include <algorithm>

const int maxn = 1003;
int n;
int a[maxn];
int b[maxn];

int main()
{
	while(scanf("%d", &n), n)
	{
		for (int i = 0; i < n; ++i)
			scanf("%d", a + i);
		for (int i = 0; i < n; ++i)
			scanf("%d", b + i);
		std::sort(a, a + n);
		std::sort(b, b + n);
		int ans = 0, tie = 0;
		for (int ah = 0, at = n - 1, bh = 0, bt = n - 1; ; )
		{
			while (ah <= at && a[ah] > b[bh])
			{
				++ans;
				++ah;
				++bh;
			}
			while (ah <= at && a[at] > b[bt])
			{
				++ans;
				--at;
				--bt;
			}
			if (ah <= at)
			{
				if (a[ah++] == b[bt--])
					++tie;
			}
			else
				break;
		}
		ans -= n - tie - ans;
		printf("%d\n", ans * 200);
	}
}
