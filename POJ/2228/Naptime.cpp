#pragma warning(disable: 4996)
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))
//#define Debug

using namespace std;

int n, m, v[3900], ans[3900][2];

int main(){
#ifndef ONLINE_JUDGE
	freopen("naptime.in", "r", stdin);
	freopen("naptime.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	for (int i=0; i<n; ++i)
		scanf("%d", v+i);
	// suppose the last day isn't chosen
	for (int i=1; i<n; ++i){
		for (int j=max(m-i-1, 0); j<=min(m, n-i-1); ++j){
			int t = max(ans[j][0], ans[j][1]);
			if (j!=m)
				ans[j][1] = max(ans[j+1][0], j==m-1?0:ans[j+1][1] + v[i]);
			ans[j][0] = t;
#ifdef Debug
			for (int k=0; k<2; ++k)
				printf("ans[%d][%d][%d] = %d\n", i, j, k, ans[j][k]);
#endif
		}
#ifdef Debug
		printf("\n");
#endif
	}
	int ret=ans[0][0];
#ifdef Debug
	printf("%d\n", ret);
#endif
	// what if the last day is chosen
	memset(ans, 0, sizeof ans);
	ans[m-1][1] = v[0];
	for (int i=1; i<n; ++i){
		for (int j=max(m-i-1, 0); j<=min(m, n-i-1); ++j){
			int t = max(ans[j][0], ans[j][1]);
			if (j!=m)
				ans[j][1] = max(ans[j+1][0], j==m-1?0:ans[j+1][1] + v[i]);
			ans[j][0] = t;
#ifdef Debug
			for (int k=0; k<2; ++k)
				printf("ans[%d][%d][%d] = %d\n", i, j, k, ans[j][k]);
#endif
		}
#ifdef Debug
		printf("\n");
#endif
	}
	printf("%d\n", max(ret, ans[0][1]));
	return 0;
}
