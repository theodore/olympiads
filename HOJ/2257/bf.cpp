/** @file bf.cpp
 *  @brief JSOI2009, bottle, frute force.
 *  @author Theodore You <theodoreyou@gmail.com>
 *  @date Thu, 14 Apr 2011 21:29:16 +0800
 */

#include <cstdio>
#include <cmath>
#include <algorithm>

const int maxn = 1007;
const int maxf = 1000;
int l[maxf * maxn], lc;

int main()
{
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 0, j, x; i < n; ++i)
    {
	scanf("%d", &x);
	for (j = 1; j * j < x; ++j)
	    if (x % j == 0)
		l[lc++] = j, l[lc++] = x / j;
	if (j * j == x)
	    l[lc++] = j;
    }
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
