#include <cstdio>
#include <algorithm>

const int maxn = 5003;
int n;
int t[maxn][maxn];

void add(int row, int col, int val)
{
	col = std::min(col, t[row][0] + 1);
	while (t[row][col - 1] > val && col > 1)
		--col;
	std::swap(val, t[row][col]);
	if (val)
		add(row + 1, col, val);
	else
		++t[row][0];
}

int main()
{
	scanf("%d", &n);
	for (int i = 0, x; i < n; ++i)
	{
		scanf("%d", &x);
		add(0, t[0][0] + 1, x);
	}
	int ans = 0, i = 0;
	while (t[i][0])
		printf("%d\n", ans += t[i++][0]);
}
