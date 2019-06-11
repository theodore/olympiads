#include <cstdio>
#include <cmath>
#include <cassert>

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
    for (int i = 3, *pi = pre + 3; i <= n; i += 2, pi += 2)
    {
	if (!not_P(i))
	    p[pc++] = i, *pi = i;
	int ppp = *pi;
	for (int j = 1, lim = n / i, z = 2 * i, *pz = pre + z; p[j] <= lim; ++j)
	{
	    z += (p[j] - p[j - 1]) * i;
	    pz += (p[j] - p[j - 1]) * i;
	    not_p[(z) >> 5] |= 1 << (z & 31);
	    *pz = p[j];
	    if (p[j] == ppp)
	    {
#if DB >= 1
		fprintf(stderr, "break %d\n", ppp);
#endif
		break;
	    }
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
