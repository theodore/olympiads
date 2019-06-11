#include <cstdio>
#include <cstdlib>
#include <algorithm>

int main()
{
    int n, m, r;
    scanf("%d%d%d", &n, &m, &r);
    srand(r);
    printf("%d %d\n", n, m);
    int a[1000];
    for (int i = 0; i < n; i++)
        a[i] = i + 1;
    std::random_shuffle(a, a + n);
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    puts("");
    while (m--) {
        int l, r, k;
        l = rand() % n + 1;
        r = rand() % n + 1;
        if (l > r)
            std::swap(l, r);
        k = rand() % (r - l + 1) + 1;
        printf("%d %d %d\n", l, r, k);
    }
}
