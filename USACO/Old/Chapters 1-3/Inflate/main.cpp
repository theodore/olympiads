/*
ID:theodor8
PROB:inflate
LANG:C++
*/
#include <iostream>
using namespace std;
#pragma warning(disable:4996)

int t, n, w[10010], c[10010], ans[10010];
int main(){
	freopen("inflate.in", "r", stdin);
	freopen("inflate.out", "w", stdout);
	scanf("%d%d", &t, &n);
	for (int i=1; i<=n; ++i)
		scanf("%d%d", &w[i], &c[i]);
	for (int i=1; i<=n; ++i)
		for (int j=1; j<=t; ++j)
			if (j>=c[i] && ans[j]<ans[j-c[i]]+w[i])
				ans[j] = ans[j-c[i]]+w[i];
	printf("%d\n", ans[t]);
	return 0;
}
