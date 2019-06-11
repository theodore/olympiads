#include <cstdio>
#include <algorithm>

namespace
{
    const int maxn = 500007;
    const int maxN = 1500007;
    const int maxq = 2000007;
    const int inf = ~0u >> 2;

    struct Point
    {
	int x, y;
	bool operator<(const Point& z) const
	{ return x < z.x; }
    };

    struct Rectangle
    {
	int x0, y0, x1, y1;
	int ans[4];
	int answer() const
	{ return ans[0] + ans[1] - ans[2] - ans[3]; }
    };

    struct Query
    {
	int x, y;
	int id, no;
	void init(const int i, const int n, const int xx, const int yy)
	{ x = xx; y = yy; id = i; no = n; }
	bool operator<(const Query& z) const
	{ return x < z.x; }
    };

    struct Sort_t
    {
	int real;
	int id, flag;
	void init(const int r, const int i, const int f)
	{ real = r; id = i; flag = f; }
	bool operator<(const Sort_t& z) const
	{ return real < z.real; }
    };

    Point p[maxn];
    Rectangle rect[maxn];
    Query q[maxq];
    Sort_t tmp[maxn * 3];
    int bit[maxN];
}

void getint(int& x)
{
    int c;
    while ((c = getchar()) < '0' || c > '9')
	;
    x = c - '0';
    while ((c = getchar()) >= '0' && c <= '9')
	x = x * 10 + c - '0';
}

int main()
{
    int n, m;
    getint(n);
    getint(m);
    for (int i = 0; i < n; ++i)
    {
	getint(p[i].x);
	getint(p[i].y);
	tmp[i].init(p[i].y, i, 2);
    }
    for (int i = 0; i < m; ++i)
    {
	getint(rect[i].x0);
	getint(rect[i].y0);
	getint(rect[i].x1);
	getint(rect[i].y1);
	tmp[i * 2 + n].init(rect[i].y0, i, 0);
	tmp[i * 2 + n + 1].init(rect[i].y1, i, 1);
    }

    std::sort(tmp, tmp + n + m + m);
    if (tmp[0].flag == 2)
	p[tmp[0].id].y = 2;
    else
	(tmp[0].flag ? rect[tmp[0].id].y1 : rect[tmp[0].id].y0) = 2;
    int N = 2;
    for (int i = 1; i < n + m + m; ++i)
    {
	N += tmp[i].real != tmp[i - 1].real;
	if (tmp[i].flag == 2)
	    p[tmp[i].id].y = N;
	else
	    (tmp[i].flag ? rect[tmp[i].id].y1 : rect[tmp[i].id].y0) = N;
    }

    for (int i = 0; i < m; ++i)
    {
	q[i * 4].init(i, 0, rect[i].x1, rect[i].y1);
	q[i * 4 + 1].init(i, 1, rect[i].x0 - 1, rect[i].y0 - 1);
	q[i * 4 + 2].init(i, 2, rect[i].x0 - 1, rect[i].y1);
	q[i * 4 + 3].init(i, 3, rect[i].x1, rect[i].y0 - 1);
    }

    std::sort(p, p + n);
    p[n].x = p[n].y = inf;
    std::sort(q, q + m * 4);

#define lowbit(x) ((x) & -(x))
    for (int i = 0, j = 0; j < m * 4; ++j)
    {
	while (p[i].x <= q[j].x)
	    for (int z = p[i++].y; z <= N; z += lowbit(z))
		++bit[z];
	int& ans = rect[q[j].id].ans[q[j].no];
	for (int z = q[j].y; z; z -= lowbit(z))
	    ans += bit[z];
    }

    for (int i = 0; i < m; ++i)
	printf("%d\n", rect[i].answer());
}
