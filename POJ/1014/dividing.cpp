#include <cstdio>
#include <cstring>

//const int maxn(53);
const int maxn(63);
int a[6], c;
bool can[60003];
int w[maxn], n;

bool good()
{
	if (c & 1)
		return false;
	else
		 c >>= 1;
	// split objects
	n = 0;
	for (int i = 0, j; i < 6; ++i)
	{
		for (j = 1; a[i] > j; j <<= 1)
		{
			w[n++] = j * (i + 1);
			a[i] -= j;
		}
		if (a[i])
			w[n++] = a[i] * (i + 1);
	}
#ifdef DB
	for (int i = 0; i < n; ++i)
		printf("%d ", w[i]);
	putchar('\n');
#endif
	// knapsack
	memset(can, 0, sizeof can);
	can[0] = true;
	for (int i = 0; i < n; ++i)
		for (int j = c; j >= w[i]; --j)
			can[j] |= can[j-w[i]];
	return can[c];
}

int main()
{
	for (int flag = 0, _ = 1; ; flag = c = 0, ++_)
	{
		for (int i = 0; i < 6; ++i)
		{
			scanf("%d", &a[i]);
			flag |= a[i];
			c += (i + 1) * a[i];
		}
		if (!flag)
			break;
		printf("Collection #%d:\nCan", _);
		if (!good())
			printf("\'t");
		printf(" be divided.\n\n");
	}
	return 0;
}
