/*
PROB:inflate
LANG:C++
*/
// Standard knapsack problem, i first or v first?
#include <cstdio>
#define max(a, b) ((a) > (b) ? (a) : (b))

int n, m, value[10010], cost[10010];
int ans[10010];

int main()
{
	freopen("inflate.in", "r", stdin);
	freopen("inflate.out", "w", stdout);
	scanf("%d%d", &m, &n);
	for (int i=0; i<n; ++i)
		scanf("%d%d", value+i, cost+i);
	/*
	for (int i=0; i<n; ++i)
		//for (int j=m; j>=cost[i]; --j)
		for (int j=cost[i]; j<=m; ++j)
			ans[j] = max(ans[j], ans[j-cost[i]] + value[i]);
	*/
	for (int i=1; i<=m; ++i) {
		ans[i] = ans[i-1];
		for (int j=0; j<n; ++j)
			if (i >= cost[j])
				ans[i] = max(ans[i], ans[i-cost[j]] + value[j]);
	}
	printf("%d\n", ans[m]);
	return 0;
}

