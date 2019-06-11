#include <cstdio>

const int max_n = 200003;
int n, m;
bool good[max_n];

int main()
{
    scanf("%d%d", &n, &m);
    for (int a, b; m--; ) {
        scanf("%d%d", &a, &b);
        good[a] = good[b] = true;
    }
    for (int i = 1; i <= n; i++)
        if (!good[i]) {
            puts("NIE");
            return 0;
        }
    puts("TAK");
}
