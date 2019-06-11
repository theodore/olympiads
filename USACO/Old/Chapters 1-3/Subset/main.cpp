/*
ID:theodor8
PROB:subset
LANG:C++
*/
#include <iostream>
using namespace std;
#pragma warning(disable:4996)

int n, foo[40][800];
int main(){
	freopen("subset.in", "r", stdin);
	freopen("subset.out", "w", stdout);
	scanf("%d", &n);
	if (((1+n)*n/2)&1){
		printf("%d\n", 0);
		return 0;
	}
	foo[1][1] = 1;
	for (int i=2; i<=n; ++i)
		for (int j=1; j<=(1+i)*i/2; ++j){
			foo[i][j] = foo[i-1][j];
			if (j>i)
				foo[i][j] += foo[i-1][j-i];
		}
	printf("%d\n", foo[n][(1+n)*n/4]);
	return 0;
}
