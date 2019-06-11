#include "bignum.h"

Int work(int n, int d)
{
	Int sum = 1, t;
	if (d == 0)
		return 1;
	else
	{
		t = work(n, d - 1);
		for (int i = 0; i < n; i++)
			sum *= t;
		sum = sum + 1;
	}
	return sum;
}

int main()
{
#ifdef LOCAL
	freopen("ans", "w", stdout);
#endif
	int n, d;
	Int x = 1, t;
	scanf("%d%d", &n, &d);
	if (d == 0)
	{
		printf("1\n");
		return 0;
	}
	if (n == 0)
	{
		printf("0\n");
		return 0;
	}
	t = work(n, d - 1);
	for (int i = 0; i < n - 1; i++)
		x *= t;
	x = (x - 1) * t + 1;
	x.output();
	putchar(10);

}

