/*
ID:theodor8
PROB:numtri
LANG:C++
*/
#include <iostream>
using namespace std;
//#pragma warning(disable:4996)

int n, num[1010][1010], ans[1010][1010];
int main(){
	freopen("numtri.in", "r", stdin);
	freopen("numtri.out", "w", stdout);
	scanf("%d", &n);
	int Ans = 0;
	for (int i=1; i<=n; ++i)
		for (int j=1; j<=i; ++j){
			scanf("%d", &num[i][j]);
			if (i == 1)
				ans[i][j] = num[i][j];
			else if (j == 1)
				ans[i][j] = ans[i-1][j] + num[i][j];
			else if (j == i)
				ans[i][j] = ans[i-1][j-1] + num[i][j];
			else
				ans[i][j] = max(ans[i-1][j], ans[i-1][j-1]) + num[i][j];
			Ans = ans[i][j]>Ans ? ans[i][j] : Ans;
		}
	printf("%d\n", Ans);
	return 0;
}
