#include <cstdio>

const int maxn(10003);
const int maxN(1000003);
const int maxm(2000003);
int start[maxn], to[maxm], next[maxm], edge;

void add(const int a, const int b)
{
	to[++edge] = b;
	next[edge] = start[a];
	start[a] = edge;
}

bool vis[maxN];
int l[maxN], lc;
int match[maxN];

bool find_aug_path(const int x)
{
	for (int e = start[x], t, u; e; e = next[e])
		if (!vis[u = to[e]])
		{
			vis[u] = true;
			l[lc++] = u;

			t = match[u];
			match[u] = x;
			if (!t || find_aug_path(t))
				return true;
			match[u] = t;

			if (!match[u])
			{
				match[u] = x;
				return true;
			else if 
		}
	return false;
}

void getint(int& x)
{
	static char ch;
	while ((ch = getchar()) < '0' || ch > '9')
		;
	x = ch - '0';
	while ((ch = getchar()) >= '0' && ch <= '9')
		x = x * 10 + ch - '0';
}

int main()
{
	int m;
	getint(m);
	for (int i = 0, x; i < m; ++i)
	{
		getint(x);
		add(x, i);
		getint(x);
		add(x, i);
	}
	for (int i = 1; ; ++i)
	{
		lc = 0;
		if (!find_aug_path(i))
		{
			printf("%d\n", i - 1);
			return 0;
		}
		for (int i = 0; i < lc; ++i)
			vis[l[i]] = false;
	}
	return 0;
}
