#include <cstdio>

const int maxn(10003);
const int maxN(1000007);
const int maxm(2000007);

int start[maxn], to[maxm], next[maxm], edge;

int vis[maxN];
int match[maxN];
int lc;
int l[maxN];

bool find_aug_path(const int x)
{
	//vis[x] = true;
	//l[lc++] = x;
	for (int e = start[x], u, t; e; e = next[e])
		if (!vis[u = to[e]])
		{
			vis[u] = true;
			l[lc++] = u;
			t = match[u];
			match[u] = x;
			if (!t || find_aug_path(t))
				return true;
			match[u] = t;
		}
	return false;
}

void add(int a, int b)
{
	to[++edge] = b;
	next[edge] = start[a];
	start[a] = edge;
}

/*
void getint(int& x)
{
	static char ch;
	while ((ch = getchar()) < '0' || ch > '9')
		;
	x = ch - '0';
	while ((ch = getchar()) >= '0' && ch <= '9')
		x = x * 10 + ch - '0';
}
*/

char buf[BUFSIZ];
char *p = buf + BUFSIZ;

#define read() \
	if (p == buf + BUFSIZ) fread(p = buf, 1, BUFSIZ, stdin);

void getint(int& x)
{
	read();
	while (*p < '0' || *p > '9')
	{
		++p;
		read();
	}
	x = 0;
	while (*p >= '0' && *p <= '9')
	{
		x = x * 10 + *p - '0';
		++p;
		read();
	}
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
