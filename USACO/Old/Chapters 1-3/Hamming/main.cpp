/*
ID:theodor8
PROB:hamming
LANG:C++
*/
#include <iostream>
using namespace std;
#pragma warning(disable:4996)

inline int hamming(int a, int b){
	int ret(0);
	while (a!=0 || b!=0){
		if (a&1 ^ b&1)
			++ret;
		a >>= 1;
		b >>= 1;
	}
	return ret;
}
int num[70], count(1);
int main(){
	freopen("hamming.in", "r", stdin);
	freopen("hamming.out", "w", stdout);
	int n, b, d;
	scanf("%d%d%d", &n, &b, &d);
	for (int i=1; count<n; ++i){
		for (int j=0; j<count; ++j)
			if (hamming(i, num[j]) < d)
				goto bad;
		num[count++] = i;
bad:;
	}
	for (int i=0; i<count; ++i){
		if (i%10)
			printf(" ");
		printf("%d", num[i]);
		if (i%10 == 9)
			printf("\n");
	}
	if (count%10)
		printf("\n");
	return 0;
}
