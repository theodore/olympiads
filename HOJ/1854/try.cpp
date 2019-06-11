#include <cstdio>
#include <algorithm>

const int maxn(10003);
const int maxN(20007);
const int maxm(20007);
int start[maxN], to[maxm], next[maxm], edge;

void add(const int a, const int b)
{
	to[++edge] = b;
	next[edge] = start[a];
	start[a] = edge;
}

int match[maxN];

bool find_aug_path(const int x)
{
	for (int e = start[x]; e; e = next[e])
	{
		int u = to[e];
		if (!match[u])
		{
			match[u] = x;
			match[x] = u;
			return true;
		}
		else if (find_aug_path(match[u]))
		{
			match[u] = x;
			match[x] = u;
			return true;
		}
	}
	return false;
}

int main()
{
	int m;
	scanf("%d", &m);
	for (int i = 0, a, b; i < m; ++i)
	{
		scanf("%d%d", &a, &b);
		if (a > b)
			std::swap(a, b);
		b += maxn;
		add(a, b);
		add(b, a);
	}
	for (int i = 1; ; ++i)
		if (!find_aug_path(i))
		{
			printf("%d\n", i - 1);
			return 0;
		}
	return 0;
}
