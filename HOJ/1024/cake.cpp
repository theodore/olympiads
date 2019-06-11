#include <cstdio>
#include <cmath>
#include <algorithm>

double search(double x, double y, int n)
{
	if (n == 1)
		return std::max(x, y) / std::min(x, y);
	double ans = 1e6;
	for (int i = 1; i <= n / 2; ++i)
	{
		ans = std::min(ans, std::max(search(x / n * i, y, i), search(x / n * (n - i), y, n - i)));
		ans = std::min(ans, std::max(search(x, y / n * i, i), search(x, y / n * (n - i), n - i)));
	}
	return ans;
}

int main()
{
	int x, y, n;
	scanf("%d%d%d", &x, &y, &n);
	printf("%.6f\n", search(x, y, n));
}
