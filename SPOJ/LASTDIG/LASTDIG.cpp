#include <cstdio>

int a, b;

int main()
{
	int _;
	for (scanf("%d", &_); _; --_)
	{
		scanf("%d%d", &a, &b);
		a %= 10;
		if (b == 0)
			printf("1\n");
		else if (a == 0)
			printf("0\n");
		//else if (b == 0)
		//	printf("1\n");
		else
		{
			b %= 4;
			if (b == 0)
				b = 4;
			int ret(1);
			for (int i = 0; i < b; ++i)
				ret *= a;
			printf("%d\n", ret % 10);
		}
	}
	return 0;
}
