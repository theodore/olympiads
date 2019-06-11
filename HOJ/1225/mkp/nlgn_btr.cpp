#include <cstdio>
#include <cmath>
#include <cassert>
#include <bitset>

const int maxn = 1000000007;
const int maxp = 50848007;
int n, root;
int p[maxp], pc;

#define not_P(x) (not_p[(x) >> 5] >> ((x) & 31) & 1)

void mkp()
{
    static int not_p[maxn / 64 + 1];
    pc = 1;
    p[0] = 2;
    for (int i = 3; i <= n; i += 2)
	if (!not_P(i >> 1))
	{
	    p[pc++] = i;
	    if (i <= root)
		for (int j = i * i; j <= n; j += i + i)
		    not_p[j >> 6] |= 1 << ((j >> 1) & 31);
	}
}

void output()
{
    //printf("%d\n", pc);
}

int main()
{
    scanf("%d", &n);
    root = int(sqrt(n)) + 1;
    assert(n <= maxn);
    mkp();
    output();
}
