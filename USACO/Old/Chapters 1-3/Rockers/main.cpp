/*
PROB:rockers
LANG:C++
*/
#include <iostream>
//#define Debug

using namespace std;

int n, t, m;
int f[22][22][22], Time[22];
int main(){
	freopen("rockers.in", "r", stdin);
	freopen("rockers.out", "w", stdout);
	scanf("%d%d%d", &n, &t, &m);
	for (int i=1; i<=n; ++i)
		scanf("%d", Time+i);

	for (int i=1; i<=n; ++i)
		for (int j=1; j<=m; ++j)
			for (int k=0; k<=t; ++k){
				if (!k)
					f[i][j][k] = f[i][j-1][t];
				else if (k < Time[i])
					f[i][j][k] = max(f[i][j-1][t], f[i-1][j][k]);
				else
					f[i][j][k] = max(f[i-1][j][k-Time[i]] + 1, f[i-1][j][k]);
			}
#ifdef Debug
	for (int i=1; i<=n; ++i){
		for (int j=1; j<=m; ++j)
			for (int k=1; k<=t; ++k)
				printf("f[%d][%d][%d] = %d\n", i, j, k, f[i][j][k]);
		printf("\n");
	}
#else
	printf("%d\n", f[n][m][t]);
#endif
	return 0;
}
