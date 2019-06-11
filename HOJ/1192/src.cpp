#include <cstdio>
#include <cmath>

int main()
{
    int n;
    scanf("%d", &n);
    printf("%d\n", int(log(n) / log(2)) + 1);
}
