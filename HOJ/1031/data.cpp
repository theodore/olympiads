#include <cstdio>
#include <cstdlib>

int main()
{
    int n, r;
    scanf("%d%d", &n, &r);
    for (srand(r); n--; )
	putchar(rand() % 26 + 'A');
    putchar('\n');
}
