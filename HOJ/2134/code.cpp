#include <cstdio>
#include <algorithm>

const int mod = 100000001;
int n, A, B, C, a1;
long long now;
int nowl;

int main()
{
	double ans = 0;
	scanf("%d%d%d%d%d", &n, &A, &B, &C, &a1);
	now = a1;
	int t = nowl = a1 % C + 1;
	for (int i = 1; i < n; ++i)
	{
		long long next;
		int nextl;
		next = (now * A + B) % mod;
		nextl = next % C + 1;
		ans += std::min(nowl, nextl) / double(nowl) / nextl;
		now = next;
		nowl = nextl;
	}
	ans += std::min(t, nowl) / double(nowl) / t;
	printf("%.3f\n", ans);
}
