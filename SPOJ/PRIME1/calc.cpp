#include <cstdio>
#define go(x) printf("x^%d mod %d = %d\n", n-1, n, calc(x, n));

int e2[30], e[30];

void init()
{
	e2[0] = 1;
	for (int i=1; i<30; ++i)
		e2[i] = e2[i-1] * e2[i-1];:q


int calc(int a, int p)
{
	int n = p - 1;
}

int main()
{
	init();
	int n;
	scanf("%d", &n);
	go(2);
	go(3);
	go(5);
	go(7);
	go(11);
	go(13);
}

