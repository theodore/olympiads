#include <cstdio>
#include <cmath>
#include <cassert>
#include <bitset>

const int maxn = 1000000007;
const int maxp = 50848007;
int n, root;
int p[maxp], pc;

void mkp()
{
    static std::bitset<maxn> not_p;
    pc = 1;
    p[0] = 2;
    for (int i = 3; i <= n; i += 2)
	if (!not_p[i])
	{
	    p[pc++] = i;
	    if (i <= root)
		for (int j = i * i; j <= n; j += i + i)
		    not_p[j] = true;
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
