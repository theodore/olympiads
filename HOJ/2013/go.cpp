#include <cstdio>
#include <algorithm>

typedef long long ll;
const int maxn = 620003;
const int mod = 1000000009;
int n, d;
int block[maxn];

int main()
{
	scanf("%d%d", &n, &d);
	for (int i = 0; i < n; ++i)
		scanf("%d", block + i);
	std::sort(block, block + n);
	int ans = 1;
	for (int i = 1, j = 0; i < n; ++i)
	{
		while (block[i] - block[j] > d)
			++j;
#ifdef DB
		fprintf(stderr, "%d %d\n", i, j);
#endif
		ans = ll(ans) * (i - j + 1) % mod;
	}
	printf("%d\n", ans);
}
