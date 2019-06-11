#include <cstdio>
#include <cstring>

const int maxn(10003);
const int maxN(1000007);
const int maxm(1010007);
int n;
int start[maxN], to[maxm], next[maxm], edge;

void add(int a, int b)
{
	to[++edge] = b;
	next[edge] = start[a];
	start[a] = edge;
}

int match[maxN];
bool vis[maxn];
int l[maxn], lc;

bool find_aug_path(const int x)
{
	vis[x] = true;
	l[lc++] = x;
	for (int e = start[x]; e; e = next[e])
	{
		int u = to[e];
		if (!match[u])
		{
			match[x] = u;
			return true;
		}
		else if (!vis[match[u]] && find_aug_path(match[u]))
		{
			match[x] = u;
			return true;
		}
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
	for (int i = 0, a, b; i < m; ++i)
	{
		getint(a);
		getint(b);
		add(a, i);
		add(b, i);
	}
	for (int i = 1; ; ++i)
	{
		//memset(vis, 0, sizeof vis);
		lc = 0;
		if (!find_aug_path(i))
		{
			printf("%d\n", i - 1);
			return 0;
		}
		for (int j = 0; j < lc; ++j)
			vis[l[j]] = false;
	}
	return 0;
}
