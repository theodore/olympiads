#include <cstdio>
#include <cstdlib>

int main()
{
    int r;
    scanf("%d", &r);
    srand(r);
    printf("%d\n", rand() % 1000000000);
}
