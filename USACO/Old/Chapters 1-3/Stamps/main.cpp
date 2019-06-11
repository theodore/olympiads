/*
ID:theodor8
LANG:C++
TASK:stamps
*/
#include <iostream>
#pragma warning(disable:4996)

using namespace std;

int k, n, stamp[50], ans[2000000];
void calc(const int now){
	ans[now] = k + 1;
	for (int i=0; i<n; ++i)
		if (now >= stamp[i] && ans[now] > ans[now-stamp[i]])
			ans[now] = ans[now-stamp[i]] + 1;
}
int main(){
	freopen("stamps.in", "r", stdin);
	freopen("stamps.out", "w", stdout);
	scanf("%d%d", &k, &n);
	for (int i=0; i<n; ++i)
		scanf("%d", &stamp[i]);
	int most = 1;
	for (; ;++most){
		calc(most);
		if (ans[most] > k){
			printf("%d\n", most-1);
			return 0;
		}
	}
	return 0;
}
