/*
ID:theodor8
TASK:frac1
LANG:C++
*/
#include <iostream>
using namespace std;
#pragma warning(disable:4996)

inline int gcd(int a, int b){
	int r(a%b);
	while (r != 0)
		a=b, b=r, r=a%b;
	return b;
}
struct F{
	int num, den;
}	frac[8000];
int num;
inline int MINUS(int ln, int ld, int rn, int rd){
	int g(gcd(ld, rd));
	ln *= rd/g;
	rn *= ld/g;
	return ln-rn;
}
int cmp(const void* a, const void* b){
	return MINUS(((F*)a)->num, ((F*)a)->den, ((F*)b)->num, ((F*)b)->den);
}
int main(){
	freopen("frac1.in", "r", stdin);
	freopen("frac1.out", "w", stdout);
	int n;
	scanf("%d", &n);
	for (int i=1; i<=n; ++i)
		for (int j=1; j<=i; ++j)
			if (gcd(i, j) == 1)
				frac[num].num=j, frac[num++].den=i;
	qsort(frac, num, sizeof(frac[0]), cmp);
	printf("0/1\n");
	for (int i=0; i<num; ++i)
		printf("%d/%d\n", frac[i].num, frac[i].den);
	return 0;
}
