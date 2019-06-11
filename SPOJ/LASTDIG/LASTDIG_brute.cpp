#include <cstdio>

int a, b;

int main()
{
#ifdef LOCAL
	freopen("input", "r", stdin);
	freopen("answer", "w", stdout);
#endif
	int _;
	for (scanf("%d", &_); _; --_)
	{
		scanf("%d%d", &a, &b);
		int ret(1);
		for (int i = 0; i < b; ++i)
			ret = ret * a % 10;
		printf("%d\n", ret);
	}
	return 0;
}
