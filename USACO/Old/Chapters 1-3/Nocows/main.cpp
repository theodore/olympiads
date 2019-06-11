/*
USER:theodor8
LANG:C++
TASK:nocows
*/
#include <iostream>
using namespace std;
#pragma warning(disable:4996)

const int mod(9901);
int n, k;
int f[210][110];
int main(){
	//freopen("nocows.in", "r", stdin);
	//freopen("nocows.out", "w", stdout);
	scanf("%d%d", &n, &k);
	if (!(n&1)){
		printf("0\n");
		return 0;
	}

	//for (int i=1; i<n; i+=2)
	//	f[n][k] += f[i][k-1]*f[n-i-1][k-1];
	for (int i=1; i<=k; ++i)
		f[1][i] = 1;
	for (int x=1; x<=n; x+=2)
		for (int y=1; y<=k; ++y){
			for (int i=1; i<x; i+=2)
				f[x][y] = (f[x][y] + f[i][y-1]*f[x-i-1][y-1])%mod;		//mod
			//printf("%d,%d\n\t%d\n", x, y, f[x][y]);
		}
	printf("%d\n", (((f[n][k] - f[n][k-1])%mod)+mod)%mod);
	return 0;
}
