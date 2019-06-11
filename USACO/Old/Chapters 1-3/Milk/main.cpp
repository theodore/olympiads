/*
ID:theodor8
PROB:milk
LANG:C++
*/
#include <iostream>
using namespace std;

struct Farmer{
	int price, amount;
};
Farmer a[5010];

int cmp(const void* a, const void* b){
	return ((Farmer*)a)->price - ((Farmer*)b)->price;
}
int main()
{
	freopen("milk.in", "r", stdin);
	freopen("milk.out", "w", stdout);
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i=0; i<m; ++i)
		scanf("%d%d", &a[i].price, &a[i].amount);
	qsort(a, m, sizeof(Farmer), cmp);
	int now = 0, i = 0, mon = 0;
	while (now < n)
		if (now + a[i].amount <= n){
			now += a[i].amount;
			mon += a[i].price * a[i++].amount;
		}
		else{
			mon += (n-now) * a[i].price;
			now = n;
		}
	printf("%d\n", mon);
	return 0;
}
