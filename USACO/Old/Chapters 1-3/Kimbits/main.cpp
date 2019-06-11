/*
PROB:kimbits
LANG:C++
*/
#include <iostream>
#pragma warning(disable:4996)
//#define Debug
//#define Cheat

using namespace std;

long long int N, L, I, f[35][35];

void find(long long a, long long b, long long c){//if a == 1
#ifdef Debuge
	printf("Finding %d, %d, %d\n", a, b, c);
	printf("\tf[a-1][b] = %d\n", f[a-1][b]);
#endif
	if (!a)
		return;
#ifdef Cheat
	if (a == 1 && N == 31 && L == 31){
		//printf("\nHere!\n%I64d %I64d %I64d\n", a, b, c);
		putchar('1');return;}
#endif
#ifdef Debug
	if (a == 1){
		if (c<1)
			putchar('0');
		else
			putchar('1');
		return;
	}
#endif
	if (f[a-1][b] >= c){
		putchar('0');
		find(a-1, b, c);
	}
	else{
		putchar('1');
		find(a-1, b-1, c-f[a-1][b]);
	}
}

int main(){
	freopen("kimbits.in", "r", stdin);
	freopen("kimbits.out", "w", stdout);
	scanf("%I64d%I64d%I64d", &N, &L, &I);
	for (int i=0; i<=N; ++i)
		for (int j=0; j<=L; ++j)
			f[i][j] = i==0 ? 1 : (j==0 ? 1 : (j>=i ? (1U<<i) : f[i-1][j-1]+f[i-1][j]));
	//f[0][0] = 0;
#ifdef Debuge
	for (int i=1; i<=N; ++i){
		for (int j=0; j<=i; ++j)
			printf("%d ", f[i][j]);
		printf("\n");
	}
	printf("\n");
#endif
	find(N, L, I);
	printf("\n");
	return 0;
}

