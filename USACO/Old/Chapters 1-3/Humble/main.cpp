/*
ID:theodor8
PROB:humble
LANG:C++
*/
//Wrong algorithm, pi*pi is not considered
#include <iostream>
#pragma warning(disable:4996)
using namespace std;

int k, n, prime[100], ans[101][100001];
int main(){
	//freopen("humble.in", "r", stdin);
	//freopen("humble.out", "w", stdout);
	scanf("%d%d", &k, &n);
	for (int i=1; i<=k; ++i)
		scanf("%d", &prime[i]);
	for (int i=1; i<=k; ++i){
		int c(0), count(1), tmp[100001];
		for (tmp[0]=prime[i]; ans[i-1][count]; ++count)
			tmp[count] = ans[i-1][count] * prime[i];
		int iter(0);
		for (int j=1; j<=n; ++j){
			if (ans[i-1][j-c] && iter<count)
				ans[i][j] = ans[i-1][j-c]>tmp[iter]?tmp[++c,iter++]:ans[i-1][j-c];
			else if (ans[i-1][j-c])
				ans[i][j] = ans[i-1][j-c];
			else if (iter<count)
				ans[i][j] = tmp[iter++];
			else
				break;
		}
	}
	//printf("%d\n", ans[k][n]);
	for (int i=1; i<=k; ++i){
		for (int j=1; j<=n; ++j)
			printf("%d ", ans[i][j]);
		printf("\n");
	}
	return 0;
}
