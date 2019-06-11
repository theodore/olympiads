/*
TASK: bigbrn
LANG: C++
*/
#pragma warning(disable: 4996)
#include <iostream>
#define min(a, b) ((a) < (b) ? (a) : (b))
#define MIN(a, b, c) min(a, min(b, c))

using namespace std;

int n, m, ans[1010][1010];
bool grid[1010][1010];

int main(){
	freopen("bigbrn.in", "r", stdin);
	freopen("bigbrn.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for (int i=0; i<m; ++i){
		int x, y;
		scanf("%d%d", &x, &y);
		grid[x][y] = true;
	}
	int ret(0);
	for (int i=1; i<=n; ++i)
		for (int j=1; j<=n; ++j){
			if (grid[i][j])
				ans[i][j] = 0;
			else
				ans[i][j] = MIN(ans[i-1][j], ans[i][j-1], ans[i-1][j-1]) + 1;
			if (ans[i][j] > ret)
				ret = ans[i][j];
		}
	printf("%d\n", ret);
	return 0;
}
