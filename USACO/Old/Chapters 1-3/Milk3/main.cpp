/*
ID:theodor8
PROB:milk3
LANG:C++
*/
#include <iostream>
using namespace std;

int cmp(const void* a, const void* b){
	return *(int*)a - *(int*)b;
}
int main(){
	int a, b, c, ans[40], num = 0;
	freopen("milk3.in", "r", stdin);
	freopen("milk3.out", "w", stdout);
	scanf("%d%d%d", &a, &b, &c);
	if (a > b)
		swap(a, b);
	if (a >= c){
		printf("%d\n", c);
		return 0;
	}
	else if (b >= c)
		while (c > 0){
			ans[num++] = c;
			c -= a;
		}
	else if (a+b >= c){
		ans[num++] = c - b;
		ans[num++] = c;
		ans[num++] = a;
		ans[num++] = b;

		//C -> B
		if (a != b){
			int ct = c, at = a;
			while (ct > b && at > 0){
				ans[num++] = ct -= b-a;
				at -= b-a;
			}
			//at ran out	1 9 10
		}
		
		//a, b, c should all be original
		int b_o = b;
		while (c > 0 && b > 0){
			c -= a;
			if (c > 0)
				ans[num++] = c;
			else
				ans[num++] = b_o - b;
			b -= a;
			if (b < 0 && c > b)
				ans[num++] = c - b;
		}
	}
	else{
		ans[num++] = c;
		ans[num++] = c - b;
		ans[num++] = c - a - b;

		if (a != b)
			ans[num++] = c - b + a;

		while (c > 0 && b > 0){
			c -= a;
			b -= a;
			if (c > 0)
				ans[num++] = c;
		}
	}
	qsort(ans, num, sizeof(int), cmp);
	int b4 = ans[0];
	printf("%d", b4);
	for (int i=1; i<num; ++i)
		if (ans[i] != b4)
			printf(" %d", b4=ans[i]);
	printf("\n");
	return 0;
}
