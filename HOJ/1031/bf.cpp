#include <cstdio>
#include <cstring>
#include <algorithm>

const int maxn = 200003;
size_t n;
char base[maxn];
size_t idx[maxn];

bool cmp(const size_t& a, const size_t& b)
{
    return strncmp(base + a, base + b, n) < 0;
}

int main()
{
    scanf("%s", base);
    n = strlen(base);
    memcpy(base + n, base, n);
    for (size_t i = 1; i <= n; ++i)
	idx[i] = i;
    std::sort(idx + 1, idx + n + 1, cmp);
    for (size_t i = 1; i <= n; ++i)
	putchar(base[idx[i] - 1]);
    putchar('\n');
}
