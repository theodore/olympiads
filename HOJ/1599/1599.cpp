#include <cstdio>

int a, b, c, ans, cc[81];

int main()
{
	int bb, ccc;
	scanf("%d%d%d", &a, &bb, &ccc);
	for (; a; --a)
		for (b = bb; b; --b)
			for (c = ccc; c; --c)
			{
			//	printf("a = %d, b = %d, c = %d\n", a, b, c);
				++cc[a + b + c];
			}
	for (int i = 3; i <= 80; ++i)
//		printf("cc[%d] = %d\n", i, cc[i]);
		if (cc[i] > cc[ans])
			ans = i;
	printf("%d\n", ans);
	return 0;
}
