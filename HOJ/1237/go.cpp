#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

typedef long long ll;

const int maxn = 100003;
int n;
int a[maxn], b[maxn];
ll f[maxn];

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		scanf("%d%d", &a[i], &b[i]);
	std::sort(a + 1, a + n + 1);
	std::sort(b + 1, b + n + 1);
	memset(f, 0x0f, sizeof f);
	f[0] = 0;
	for (int i = 1; i <= n; ++i)
	{
		if (a[i] != b[i])
			f[i] = std::min(f[i], f[i - 1] + std::abs(a[i] - b[i]));
		if (i > 1 && a[i] != b[i - 1] && a[i - 1] != b[i])
			f[i] = std::min(f[i], f[i - 2] + std::abs(a[i] - b[i - 1]) + std::abs(a[i - 1] - b[i]));
		if (i > 2)
		{
			if (a[i] != b[i - 2] && a[i - 1] != b[i] && a[i - 2] != b[i - 1])
				f[i] = std::min(f[i], f[i - 3] + std::abs(a[i] - b[i - 2]) + std::abs(a[i - 1] - b[i]) + std::abs(a[i - 2] - b[i - 1]));
			if (b[i] != a[i - 2] && b[i - 1] != a[i] && b[i - 2] != a[i - 1])
				f[i] = std::min(f[i], f[i - 3] + std::abs(b[i] - a[i - 2]) + std::abs(b[i - 1] - a[i]) + std::abs(b[i - 2] - a[i - 1]));
		}
	}
	if (f[n] == 0x0f0f0f0f0f0f0f0fll)
		f[n] = -1;
	printf("%I64d\n", f[n]);
}
