#include <cstdio>
#include <cmath>
#include <cassert>

//const int maxn = 1000000007;
//const int maxp = 50848007;
const int maxn = 100000007;
const int maxp = 5761555;
int n, root;
int p[maxp], pc;
int pre[maxn];

#define not_P(x) (not_p[(x) >> 5] >> ((x) & 31) & 1)

void mkp()
{
    static int not_p[maxn / 32 + 1];
    pc = 1;
    p[0] = 2;
    for (int i = 3; i <= n; i += 2)
    {
	if (!not_P(i))
	    p[pc++] = i, pre[i] = i;
	for (int j = 1, lim = n / i; p[j] <= lim; ++j)
	{
	    not_p[(p[j] * i) >> 5] |= 1 << (p[j] * i & 31);
	    pre[p[j] * i] = p[j];
	    if (!(i % p[j]))
		break;
	}
    }
}

void output()
{
    printf("%d\n", pc);
}

int main()
{
    scanf("%d", &n);
    root = int(sqrt(n)) + 1;
    assert(n <= maxn);
    mkp();
    output();
}
