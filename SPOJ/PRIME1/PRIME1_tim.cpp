#include <cstdio>
#include <cstdlib>

typedef long long signed ll;

int e[30], e2[30];

inline void init()
{
	e2[0] = 1;
	for (int i = 1; i < 30; ++i)
		e2[i] = e2[i-1] * 2;
}

// Calculate a^(p-1) % p, if it's 1, p will probably be prime
int calc(int a, int p)
{
#ifdef DB
	printf("calc(%d, %d)\n", a, p);
#endif
	e[0] = a % p;
	for (int i = 1; i < 30; ++i)
		e[i] = ll(e[i-1]) * e[i-1] % p;
#ifdef DB
	for (int i = 1; i < 30; ++i)
		printf("%d, %d\n", i, e[i]);
#endif
	ll ret(1);
	int n(p-1);
	for (int i=29; i>=0 && n; --i)
		if (e2[i] <= n)
		{
			ret = ret * e[i] % p;
			n -= e2[i];
		}
#ifdef DB
	printf("n = %d, ret = %d\n", n, ret);
#endif
	return ret;
}

bool is_prime(int x)
{
	/*
	if (x <= 13)
		return x == 3 || x == 5 || x == 7 || x == 11 || x == 13;
	else
		return calc(2, x) == 1 && calc(3, x) == 1 && calc(5, x) == 1 && calc(7, x) == 1 && calc(11, x) == 1 && calc(13, x) == 1;
	*/
	if (x <= 11)
		return x == 3 || x == 5 || x == 7 || x == 11;
	else
		return calc(2, x) == 1 && calc(3, x) == 1 && calc(5, x) == 1 && calc(7, x) == 1 && calc(11, x) == 1;// && calc(13, x) == 1;
}

int main()
{
#ifdef LOCAL
	freopen("out", "w", stdout);
#endif
	init();
	int _, a, b;
	for (scanf("%d", &_); _; --_)
	{
		scanf("%d%d", &a, &b);
		if (a <= 2)
			printf("2\n");
		if (!(a & 1))
			++a;
		for (int i=a; i<=b; i+=2) {
#ifdef DB
	//		printf("i = %d\n", i);
#endif
			if (is_prime(i))
				printf("%d\n", i);
#ifdef DB
			putchar('\n');
#endif
		}
		putchar('\n');
	}
	return 0;
}

