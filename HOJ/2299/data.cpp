#include <cstdio>
#include <cstdlib>

const int mod = 1000;

int R()
{
    return rand() % mod - mod / 2;
}

int main()
{
    int x;
    scanf("%d", &x);
    srand(x);
    printf("%d\n", 100);
    for (int i = 0; i < 100; ++i)
	printf("%d %d %d %d\n", R(), R(), R(), R());
}
