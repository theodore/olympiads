#include "bignum.h"

int d, n;
Int fact[33], comb[33], ans[17], sum[17];

inline void calc_comb()
{
	fact[0] = 1;
	for (int i=1; i<=n; ++i)
		fact[i] = fact[i-1] * i;
	for (int i=0; i<=n; ++i)
		comb[i] = fact[n] / (fact[i] * fact[n-i]);
}

#ifdef DB
inline void debug()
{
	for (int i=0; i<=n; ++i)
	{
		printf("fact[%d] = ", i);
		fact[i].output();
		putchar('\n');
	}
	putchar('\n');
	for (int i=0; i<=n; ++i)
	{
		printf("comb[%d] = ", i);
		comb[i].output();
		putchar('\n');
	}
}
#endif

Int t, s;
inline void go()
{
	calc_comb();
#ifdef DB
	//debug();
#endif
	ans[0] = 1;
	for (int i=1; i<d; ++i)
		sum[i] = 1;
	for (int i=1; i<=d; ++i)
	{
		for (int j=1; j<=n; ++j)
		{
			//Int t(ans[i-1]), s(1);
			t = ans[i-1];
			s = 1;
			for (int k=1; k<j; ++k)
				//t = t * ans[i-1];
				t *= ans[i-1];
			for (int k=0; k<n-j; ++k)
				s = s * sum[i-1];
			ans[i] = ans[i] + comb[j] * t * s;
		}
		for (int j = i + 1; j < d; ++j)
			sum[j] = sum[j] + ans[i];
#ifdef DB
		printf("ans[%d] = ", i);
		ans[i].output();
		putchar(10);
#endif
	}
}

// Notice: n == 0? d == 0?
int main()
{
#ifdef LOCAL
#ifndef GDB
	freopen("out", "w", stdout);
#endif
#endif
	scanf("%d%d", &n, &d);
	go();
	ans[d].output();
	putchar(10);
	return 0;
}

