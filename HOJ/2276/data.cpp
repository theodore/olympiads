#include <cstdio>
#include <cstdlib>
#include <algorithm>

int main()
{
    int n, r;
    scanf("%d%d", &n, &r);
    srand(r);
    printf("%d\n", n);
    for (int i = 0; i < n; ++i)
    {
        int a, b;
        do {
            a = rand();
            b = rand();
        } while (a == b);
        if (a > b)
            std::swap(a, b);
        printf("%d %d\n", a, b);
    }
}
