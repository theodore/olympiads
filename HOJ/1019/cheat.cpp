#include <cstdio>
#include <list>

int n;
char str[6][3];
long long f[33];
std::list<int> l[3];

int calc(int x)
{
    for (int i = 0; i < 3; ++i)
    {
	l[i].clear();
	l[i].push_front(10);
    }
    for (int i = x++; i >= 1; --i)
	l[0].push_front(i);
    for (int c = 0, p = -1; ; ++c)
    {
#if DB & 1
	if (c > 100)
	    return 0;
	typedef std::list<int>::iterator I;
	for (int j = 0; j < 3; ++j, fprintf(stderr, "\n"))
	{
	    fprintf(stderr, "%c: ", 'A' + j);
	    for (I i = l[j].begin(); i != l[j].end(); ++i)
		fprintf(stderr, "%d ", *i);
	}
	fprintf(stderr, "\n");
#endif
	if (l[1].size() == x || l[2].size() == x)
	    return c;
	for (int i = 0; i < 6; ++i)
	{
	    int from = str[i][0] - 'A', to = str[i][1] - 'A';
	    if (l[from].front() < l[to].front() && l[from].front() != p)
	    {
		l[to].push_front(p = l[from].front());
		l[from].pop_front();
		break;
	    }
	}
    }
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < 6; ++i)
	scanf("%s", str[i]);
    for (int i = 1; i <= 3; ++i)
	f[i] = calc(i);
    int a = (f[3] - f[2]) / (f[2] - f[1]);
    int b = f[2] - f[1] * a;
    for (int i = 4; i <= n; ++i)
	f[i] = f[i - 1] * a + b;
    printf("%lld\n", f[n]);
}
