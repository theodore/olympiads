/** @file better.cpp
 *  @brief JSOI2009, bottle, a better approach.
 *  @author Theodore You <theodoreyou@gmail.com>
 *  @date Thu, 14 Apr 2011 22:50:48 +0800
 */

#include <cstdio>
#include <cmath>
#include <bitset>
#include <algorithm>

const int maxn = 1007;
const int maxf = 1000;
const int maxp = 3503;
const int sqrtv = 31633;
int l[maxf * maxn], lc;
int v[maxn];
int p[maxp], pc;

void initp(const int n)
{
    static std::bitset<sqrtv> n_p;
    p[0] = 2;
    pc = 1;
    for (int i = 3; i <= n; i += 2)
    {
	if (!n_p[i])
	{
	    p[pc++] = i;
	    for (int j = i * i; j <= n; j += i + i)
		n_p[j] = true;
	}
	    /*
	for (int j = 1, bdry = n / i; p[j] < bdry && i % p[j]; ++j)
	    n_p[i * p[j]] = true;
		*/
    }
}

int fac[maxp], cnt[maxp], fc;

void search(const int d, const int f = 1)
{
    if (d == fc)
    {
	l[lc++] = f;
	return;
    }
    for (int i = 0, j = 1; i <= cnt[d]; ++i, j *= fac[d])
	search(d + 1, f * j);
}

void factorize(const int n)
{
    for (int i = 0; i < n; ++i)
    {
	int x = v[i];
	fc = -1;
	for (int j = 0; x != 1 && j < pc; ++j)
	{
	    if (x % p[j] == 0)
	    {
		fac[++fc] = p[j], cnt[fc] = 0;
		do ++cnt[fc]; while (x /= p[j], x % p[j] == 0);
	    }
	}
	if (x != 1)
	    fac[++fc] = x, cnt[fc] = 1;
	++fc;
	search(0);
    }
}

int main()
{
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; ++i)
	scanf("%d", v + i);
    int z = v[0];
    for (int i = 1; i < n; ++i)
	z = std::max(z, v[i]);
    initp(sqrt(z) + 1);
    factorize(n);
    std::sort(l, l + lc);
    if (k == 1)
    {
	printf("%d\n", l[lc - 1]);
	return 0;
    }
    for (int i = lc - 2, c = 1; i; --i)
	if (l[i] == l[i + 1])
	{
	    if (++c == k)
	    {
		printf("%d\n", l[i]);
		return 0;
	    }
	}
	else
	    c = 1;
}
