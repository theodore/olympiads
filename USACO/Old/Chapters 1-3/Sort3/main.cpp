/*
ID:theodor8
PROB:sort3
LANG:C++
*/
#include <iostream>
using namespace std;
#pragma warning(disable:4996)

int n, a, b, ans, num[1010];
void calc(){
	int n2(a), n3(n-1);
	for (int i=0; i<a; ++i)
		if (num[i] == 2){
			for (; num[n2]!=1; ++n2);
			swap(num[i], num[n2]);
			++ans;
		}
		else if (num[i] == 3){
			for (; num[n3]!=1; --n3);
			swap(num[i], num[n3]);
			++ans;
		}
	for (int i=a; i<a+b; ++i)
		if (num[i] != 2)
			++ans;
}
int main(){
	freopen("sort3.in", "r", stdin);
	freopen("sort3.out", "w", stdout);
	scanf("%d", &n);
	for (int i=0; i<n; ++i){
		scanf("%d", &num[i]);
		if (num[i] == 1)
			++a;
		else if (num[i] == 2)
			++b;
	}
	calc();
	printf("%d\n", ans);
	return 0;
}
