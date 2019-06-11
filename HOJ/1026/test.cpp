#include <cstdio>
#include <cstdlib>

bool is(int x)
{
	int c = 0;
	int bit[17];
	for (; x; x /= 10)
		bit[c++] = x % 10;
	bit[c] = 100;
	for (int i = 0; i < c; ++i)
		if (abs(bit[i] - bit[i + 1]) < 2)
			return false;
	return true;
}

int calc(int x)
{
	int r = 0;
	for (int i = 1; i <= x; ++i)
		r += is(i);
	return r;
}

int main()
{
	/*
	for (int i = 1; i < 10; ++i)
		printf("%4d", calc(i));
	printf("\n");
	for (int i = 19; i < 100; i += 10)
		printf("%4d", calc(i));
	printf("\n");
	for (int i = 199; i < 1000; i += 100)
		printf("%4d", calc(i));
	printf("\n");
	*/
	for (int i = 1; i <= 100; i *= 10)
	{
		int t = 0, x;
		for (int j = i * 2 - 1; j < 10 * i; j += i)
		{
			//printf("%3d", (x = calc(j)) - t);
			//t = x;
			printf("%3d", calc(j) - calc(j / i * i - 1));
		}
		printf("\n");
	}
}
