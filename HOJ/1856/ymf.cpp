#include <cstdio>
#include <cstdlib>
#include <cstring>

#define P 20100403

int N,M,a,b,c = 1;
//a == fac(m)
//b == fac(n + 1)
//c == fac(n + m)

int Ni(int x) {

	int p = P - 2,Res = 1;
	while (p)
	{
		if (p & 1) Res = ((long long)Res * x) % P;
		x = ((long long)x * x) % P;
		p >>= 1;
	}
	return Res;
}

int main() {

	scanf("%d %d",&N,&M);
	if (N < M) {printf("0\n"); return 0;}

	for (int i = 2; i <= M; i++) c = ((long long)c * i) % P;
	a = c;
	for (int i = M + 1; i <= N + 1; i++) c = ((long long)c * i) % P;
	b = c;
	for (int i = N + 2; i <= N + M; i++) c = ((long long)c * i) % P;
	c = ((long long)c * (N - M + 1)) % P;
	printf("%lld\n",((((long long)c * Ni(a)) % P) * Ni(b)) % P);
	return 0;
}
