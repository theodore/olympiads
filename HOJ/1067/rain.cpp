#include <cstdio>

const int maxn = 50003;
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

int find(const int x)
{
    int l = -1, r = n, m;
    while (m = (l + r) / 2, l + 1 < r)
	(year[m] > x ? r : l) = m;
    return l;
}

int answer(const int x, const int y)
{
    const int a = find(x);
    const int b = find(y);
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

int main()
{
    input();
    int m;
    scanf("%d", &m);
    for (int i = 0, a, b; i < m; ++i)
    {
	scanf("%d %d", &a, &b);
	static const char str[][6] = {"false", "true", "maybe"};
	if (a <= b)
	    printf("%s\n", str[answer(a, b)]);
	else
	    printf("false\n");
    }
}
