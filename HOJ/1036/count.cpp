/** @file count.cpp
 *  @brief ZJOI2008 count.
 *  Solved by blocked tree.
 *  @author Thedore You <theodoreyou@gmail.com>
 *  @date Thu, 14 Apr 2011 09:33:45 +0800
 */

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>

const int maxn = 30007;
const int maxm = 60007;
int n;
int start[maxn], to[maxm], next[maxm], edge;
int num[maxn], father[maxn], depth[maxn], blkid[maxn], sum[maxn], maxv[maxn];
int blk_father[maxn], blk_depth[maxn], blk_size[maxn], bc;

void add(const int a, const int b)
{
    to[++edge] = b;
    next[edge] = start[a];
    start[a] = edge;
}

void mktree(const int x, const int f)
{
    static const int blksiz = int(sqrt(n));
    father[x] = f;
    depth[x] = depth[f] + 1;
    if (blkid[x] == 0)
    {
	blkid[x] = ++bc;
	blk_size[bc] = 1;
	blk_father[bc] = f;
	blk_depth[bc] = depth[x];
	sum[x] = maxv[x] = num[x];
    }
    else
    {
	sum[x] = sum[f] + num[x];
	maxv[x] = std::max(maxv[f], num[x]);
    }
    int& size = blk_size[blkid[x]];
    for (int e = start[x]; e; e = next[e])
	if (to[e] != f)
	{
	    if (size < blksiz)
	    {
		++size;
		blkid[to[e]] = blkid[x];
	    }
	    mktree(to[e], x);
	}
}

void update(const int x, const int id)
{
    sum[x] = sum[father[x]] + num[x];
    maxv[x] = std::max(maxv[father[x]], num[x]);
    for (int e = start[x]; e; e = next[e])
	if (to[e] != father[x] && blkid[to[e]] == id)
	    update(to[e], id);
}

void change(const int x, const int v)
{
    num[x] = v;
    if (blkid[father[x]] == blkid[x])
    {
	sum[x] = sum[father[x]] + num[x];
	maxv[x] = std::max(maxv[father[x]], num[x]);
    }
    else
	sum[x] = maxv[x] = num[x];
    for (int e = start[x]; e; e = next[e])
	if (to[e] != father[x] && blkid[to[e]] == blkid[x])
	    update(to[e], blkid[x]);
}

const int& getsum(const int& a, const int& b)
{
    static int c;
    return c = a + b;
}

int ask(int a, int b, const int& (*f)(const int&, const int&), int ret, int v[])
{
    int* p;
    while (blkid[a] != blkid[b])
    {
	p = blk_depth[blkid[a]] < blk_depth[blkid[b]] ? &b : &a;
	ret = f(ret, v[*p]);
	*p = blk_father[blkid[*p]];
    }
    while (a != b)
    {
	p = depth[a] < depth[b] ? &b : &a;
	ret = f(ret, num[*p]);
	*p = father[*p];
    }
    ret = f(ret, num[a]);
    return ret;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1, a, b; i < n; ++i)
    {
	scanf("%d%d", &a, &b);
	add(a, b);
	add(b, a);
    }
    for (int i = 1; i <= n; ++i)
	scanf("%d", num + i);
    srand(n * n);
    mktree(rand() % n + 1, 0);
    int m, a, b;
    char s[11];
    for (scanf("%d", &m); m--; )
    {
	scanf("%s%d%d", s, &a, &b);
	switch (s[1])
	{
	case 'H': change(a, b); break;
	case 'M': printf("%d\n", ask(a, b, std::max, -999999, maxv)); break;
	case 'S': printf("%d\n", ask(a, b, getsum, 0, sum)); break;
	}
    }
}
