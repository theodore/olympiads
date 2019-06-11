#include <cstdio>

struct x
{
	int a : 3;
	//int b[2] : 1;
	int (b : 2)[2];
};

int main()
{
	x xx;
	printf("%d\n", sizeof xx);
	return 0;
}
