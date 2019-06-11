#include <cstdio>

const int p = 29341;

int test(int a)
{
	// return a ^ (p - 1) % p
	int ret = 1;
	for (int i = 1; i < p; ++i)
		ret = ret * a % p;
	return ret;
}

int main()
{
	printf("2: %d\n", test(2));
	printf("3: %d\n", test(3));
	printf("5: %d\n", test(5));
	printf("7: %d\n", test(7));
	printf("11: %d\n", test(11));
	printf("13: %d\n", test(13));
	return 0;
}
