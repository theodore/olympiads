#include <cstdio>
#include <algorithm>

const int maxn = 50003;
const int maxm = 10003;
int n;
int year[maxn], rain[maxn];
int cont[maxn], till[maxn], high[maxn];

void input()
{
    scanf("%d", &n);
    scanf("%d%d", year, rain);
    till[0] = -1;
    for (int i = 1; i < n; ++i)
    {
	scanf("%d%d", year + i, rain + i);
	cont[i] = year[i - 1] + 1 == year[i] ? cont[i - 1] : i;
	till[i] = rain[i - 1] < rain[i] ? till[i - 1] : i - 1;
	int& t = till[i];
	while (t >= 0 && rain[t] < rain[i])
	    t = till[t];
    }
    high[n - 1] = n;
    for (int i = n - 2; i >= 0; --i)
    {
	int& h = high[i] = rain[i + 1] < rain[i] ? high[i + 1] : i + 1;
	while (h < n && rain[h] < rain[i])
	    h = high[h];
    }
}

int answer(const int x, const int y, const int a, const int b)
{
    if (x > y)
	return false;
    if (year[a] == x)
    {
	if (year[b] == y)
	{
	    if (till[b] != a)
		return false;
	    if (cont[b] > a)
		return 2;
	    return true;
	}
	else
	{
	    if (high[a] <= b)
		return false;
	    return 2;
	}
    }
    else if (year[b] == y)
    {
	if (till[b] > a)
	    return false;
	return 2;
    }
    return 2;
}

struct qy_t
{
    int y, id;
    int flag;
    bool operator<(const qy_t& x) const
    {
	return y < x.y;
    }
};

struct q_t
{
    // x, y for year
    int a, b, x, y;
};

int ans[maxm];
qy_t qy[maxm * 2];
q_t q[maxn];

int main()
{
    input();
    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; ++i)
    {
	scanf("%d %d", &qy[2 * i].y, &qy[2 * i + 1].y);
	qy[2 * i].id = qy[2 * i + 1].id = i;
	qy[2 * i].flag = 0;
	qy[2 * i + 1].flag = 1;
    }
    std::sort(qy, qy + 2 * m);
    for (int i = 0, j = -1; i < 2 * m; ++i)
    {
	q_t& x = q[qy[i].id];
	(qy[i].flag ? x.y : x.x) = qy[i].y;
	while (j < n - 1 && year[j + 1] <= qy[i].y)
	    ++j;
	(qy[i].flag ? x.b : x.a) = j;
    }
    for (int i = 0; i < m; ++i)
	ans[i] = answer(q[i].x, q[i].y, q[i].a, q[i].b);
    static const char str[][6] = {"false", "true", "maybe"};
    for (int i = 0; i < m; ++i)
	printf("%s\n", str[ans[i]]);
}
