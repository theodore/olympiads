/*
PROB:job
LANG:C++
*/
#include <iostream>

using namespace std;

int n, numa, numb, a[35], b[35];
int costa[1011], costb[1011], ta[35], tb[35];

int main(){
	freopen("job.in", "r", stdin);
	freopen("job.out", "w", stdout);
	scanf("%d%d%d", &n, &numa, &numb);
	for (int i=0; i<numa; ++i)
		scanf("%d", a+i);
	for (int i=0; i<numb; ++i)
		scanf("%d", b+i);
	//greedy
	for (int i=0; i<n; ++i){
		int to = 0;
		for (int i=1; i<numa; ++i)
			if (ta[i]+a[i] < ta[to]+a[to])
				to = i;
		costa[i] = ta[to] += a[to];

		to = 0;
		for (int i=1; i<numb; ++i)
			if (tb[i]+b[i] < tb[to]+b[to])
				to = i;
		costb[i] = tb[to] += b[to];
	}
	printf("%d ", costa[n-1]);
	int ans = 0;
	for (int i=0; i<n; ++i)
		if (costa[i] + costb[n-i-1] > ans)
			ans = costa[i] + costb[n-i-1];
	printf("%d\n", ans);
	return 0;
}
