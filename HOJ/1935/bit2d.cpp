#include <cstdio>
#include <algorithm>
#include <map>
#include <vector>

#define lowbit(x) ((x) & -(x))

struct point
{
    int x, y;
};

bool p_cmpx(const point& a, const point& b)
{
    return a.x < b.x;
}

bool p_cmpy(const point& a, const point& b)
{
    return a.y < b.y;
}

struct rectangle
{
    int x0, y0, x1, y1;
    int mx0, my0, mx1, my1;
    //int id;
};

struct sort_t
{
    int real, mapped;
    int id, flag;
    bool operator<(const sort_t& o) const
    {
	return real < o.real;
    }
};

const int maxn = 500003;
//const int maxm = 10000;
int n, m;
point p[maxn];
rectangle rect[maxn];
//sort_t tmp[maxm];
std::vector<sort_t> tmp;

void deal_with_x()
{
    tmp.resize(m + m + n);
    for (int i = 0; i < m; ++i)
    {
	tmp[i * 2].real = rect[i].x0;
	tmp[i * 2].flag = 0;
	tmp[i * 2 + 1].real = rect[i].x1;
	tmp[i * 2 + 1].flag = 1;
	tmp[i * 2].id = tmp[i * 2 + 1].id = i;
    }
    for (int i = 0, M = m + m; i < n; ++i)
    {
	tmp[i + M].real = p[i].x;
	tmp[i + M].flag = 2;
	tmp[i + M].id = i;
    }
    std::sort(tmp.begin(), tmp.end());
    //std::sort(tmp, tmp + m + m + n);
    tmp[0].mapped = 1;
    if (tmp[0].flag == 2)
	p[tmp[0].id].x = 1;
    else
	(tmp[0].flag ? rect[tmp[0].id].mx1 : rect[tmp[0].id].mx0) = 1;
    for (int i = 1, c = 1; i < m + m + n; ++i)
    {
	tmp[i].mapped = c += tmp[i].real != tmp[i - 1].real;
	if (tmp[i].flag == 2)
	    p[tmp[i].id].x = c;
	else
	    (tmp[i].flag ? rect[tmp[i].id].mx1 : rect[tmp[i].id].mx0) = c;
    }
    /*
    std::sort(p, p + n, p_cmpx);
    for (int i = 0, j = 0; i < n; ++i)
    {
	while (j < 2 * m && p[i].x > tmp[j].real)
	    ++j;
	if (j < 2 * m)
	    p[i].mx = tmp[j].mapped;
	else
	    p[i].mx = -1;
    }
    */
}

void deal_with_y()
{
    for (int i = 0; i < m; ++i)
    {
	tmp[i * 2].real = rect[i].y0;
	tmp[i * 2].flag = false;
	tmp[i * 2 + 1].real = rect[i].y1;
	tmp[i * 2 + 1].flag = true;
	tmp[i * 2].id = tmp[i * 2 + 1].id = i;
    }
    for (int i = 0, M = m + m; i < n; ++i)
    {
	tmp[i + M].real = p[i].y;
	tmp[i + M].flag = 2;
	tmp[i + M].id = i;
    }
    std::sort(tmp.begin(), tmp.end());
    //std::sort(tmp, tmp + m + m + n);
    tmp[0].mapped = 1;
    if (tmp[0].flag == 2)
	p[tmp[0].id].y = 1;
    else
	(tmp[0].flag ? rect[tmp[0].id].my1 : rect[tmp[0].id].my0) = 1;
    for (int i = 1, c = 1; i < m + m + n; ++i)
    {
	tmp[i].mapped = c += tmp[i].real != tmp[i - 1].real;
	if (tmp[i].flag == 2)
	    p[tmp[i].id].y = c;
	else
	    (tmp[i].flag ? rect[tmp[i].id].my1 : rect[tmp[i].id].my0) = c;
    }
    /*
    std::sort(p, p + n, p_cmpy);
    for (int i = 0, j = 0; i < n; ++i)
    {
	while (j < 2 * m && p[i].y > tmp[j].real)
	    ++j;
	if (j < 2 * m)
	    p[i].my = tmp[j].mapped;
	else
	    p[i].my = -1;
    }
    */
}

//int bit[maxm][maxm];
std::map<int, std::map<int, int> > bit;

void add(const int x, const int y)
{
    if (x <= 0 || y <= 0)
	return;
    static int N = m * 2 + n;
    for (int i = x; i <= N; i += lowbit(i))
	for (int j = y; j <= N; j += lowbit(j))
	    ++bit[i][j];
}

int ask(const int x, const int y)
{
    if (x <= 0 || y <= 0)
	return 0;
    int ans = 0;
    for (int i = x; i; i ^= lowbit(i))
	for (int j = y; j; j ^= lowbit(j))
	    ans += bit[i][j];
    return ans;
}

void solve()
{
    for (int i = 0; i < n; ++i)
	add(p[i].x, p[i].y);
    for (int i = 0; i < m; ++i)
	printf("%d\n", ask(rect[i].mx1, rect[i].my1)
		+ ask(rect[i].mx0 - 1, rect[i].my0 - 1)
		- ask(rect[i].mx0 - 1, rect[i].my1)
		- ask(rect[i].mx1, rect[i].my0 - 1));
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i)
	scanf("%d%d", &p[i].x, &p[i].y);
    for (int i = 0; i < m; ++i)
    {
	scanf("%d%d%d%d", &rect[i].x0, &rect[i].y0, &rect[i].x1, &rect[i].y1);
	//rect[i].id = i;
    }
    deal_with_x();
    deal_with_y();
    solve();
}
