/*
ID:theodor8
PROG:money
LANG:C++
*/
#include <cstdio>
using namespace std;
#pragma warning(disable:4996)

int v, coin[30], n;
long long ans[10010][30];
int main(){
	freopen("money.in", "r", stdin);
	freopen("money.out", "w", stdout);
	scanf("%d%d", &v, &n);
	for (int i=0; i<v; ++i)
		scanf("%d", &coin[i]);

	for (int i=0; i<v; ++i)
		ans[0][i] = 1;
	for (int i=1; i<=n; ++i)
		if (i%coin[0] == 0)
			ans[i][0] = 1;
	for (int i=1; i<=n; ++i)
		for (int j=1; j<v; ++j){
				ans[i][j] = ans[i][j-1];
				if (i >= coin[j])
					ans[i][j] += ans[i-coin[j]][j];
		}

	printf("%lld\n", ans[n][v-1]);
	return 0;
}
