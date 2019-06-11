/** @file rabbit.cpp
 *  @version 1.0
 *  @date Thu Aug 19, 10:09 PM, 2010 +0800
 *  @author Theodore You
 *  This is my implementation for HOJ Problem #1001
 */
#include <cstdio>
#include <cstring>
#include <queue>

namespace deficient
{
	void init();
	void answer();
	inline int hash(int, int, int);
	void add(int, int, int);
	const int maxN(2000010);
	const int maxm(3 * maxN);
	int n, m, N;
	int start[maxN], to[maxm], next[maxm], len[maxm], edge;
	std::queue<int> q;
	bool in[maxN];
	int d[maxN];
#ifdef DB
	void debug();
#endif
}

void deficient::add(int a, int b, int l)
{
	to[++edge] = b;
	len[edge]  = l;
	next[edge] = start[a];
	start[a]   = edge;
}

void deficient::answer()
{
	memset(d, 0x7f, sizeof(d));
	d[0] = 0;
	q.push(0);
	in[0] = true;
	while (!q.empty())
	{
		static int x;
		x = q.front();
		q.pop();
		in[x] = false;
		for (int e = start[x]; e; e = next[e])
			if (d[x] + len[e] < d[to[e]])
			{
				d[to[e]] = d[x] + len[e];
				if (!in[to[e]])
				{
					in[to[e]] = true;
					q.push(to[e]);
				}
			}
	}
	printf("%d\n", d[N]);
#ifdef DB
	debug();
#endif
}

inline int deficient::hash(int x, int y, int d)
{
	if (x == n - 1 || y == -1)
		return 0;
	if (x == -1 || y == m - 1)
		return N;
	return 2 * (x * (m - 1) + y) + d + 1;
}

void deficient::init()
{
	scanf("%d%d", &n, &m);
	N = 2 * (n - 1) * (m - 1) + 1;
	int a, b, t;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m - 1; ++j)
		{
			scanf("%d", &t);
			add(a = hash(i, j, 1), b = hash(i - 1, j, 0), t);
			add(b, a, t);
		}
	for (int i = 0; i < n - 1; ++i)
		for (int j = 0; j < m; ++j)
		{
			scanf("%d", &t);
			add(a = hash(i, j - 1, 1), b = hash(i, j, 0), t);
			add(b, a, t);
		}
	for (int i = 0; i < n - 1; ++i)
		for (int j = 0; j < m - 1; ++j)
		{
			scanf("%d", &t);
			add(a = hash(i, j, 0), b = hash(i, j, 1), t);
			add(b, a, t);
		}
}

int main()
{
	deficient::init();
	deficient::answer();
	return 0;
}

#ifdef DB
void deficient::debug()
{
	for (int i = 0; i <= N; ++i)
	{
		printf("d[%d] = %d\n", i, d[i]);
		for (int e = start[i]; e; e = next[e])
			printf("\t-> %d, %d\n", to[e], len[e]);
	}
}
#endif
