/*
PROB:game1
LANG:C++
*/
#include <iostream>

using namespace std;

int board[105];
int f[105][105][2];//0 first, 1 second

int main(){
	freopen("game1.in", "r", stdin);
	freopen("game1.out", "w", stdout);
	int n;
	scanf("%d", &n);
	for (int i=0; i<n; ++i)
		scanf("%d", board+i);
	for (int len=0; len<n; ++len)
		for (int i=0; i<n-len; ++i)
			if (!len){
				f[i][i+len][0] = board[i];
				f[i][i+len][1] = 0;
			}
			else{
				f[i][i+len][0] = max(f[i][i+len-1][1] + board[i+len], f[i+1][i+len][1] + board[i]);
				f[i][i+len][1] = min(f[i][i+len-1][0], f[i+1][i+len][0]);
			}
	printf("%d %d\n", f[0][n-1][0], f[0][n-1][1]);
	return 0;
}
