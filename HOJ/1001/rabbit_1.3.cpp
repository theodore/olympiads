/** @file rabbit.cpp
 *  @version 1.3
 *  @date Thu Aug 20, 12:45 PM, 2010 +0800
 *  @author Theodore You
 *  This is my implementation for HOJ Problem #1001
 */
#include <cstdio>
#include <cstring>

namespace deficient
{
	const int maxN(2000010);
	const int maxm(3 * maxN);
	void init();
	void answer();
	inline int hash(int, int, int);
	//void add(int, int, int);
	int n, m, N;
	int start[maxN], to[maxm], next[maxm], len[maxm], edge;
	bool in[maxN];
	int d[maxN];
	int head, tail, q[maxN];
}

//void deficient::add(int a, int b, int l)
#define add(a, b, l) \
{ \
	to[++edge] = b; \
	len[edge]  = l; \
	next[edge] = start[a]; \
	start[a]   = edge; \
}

void deficient::answer()
{
	memset(d, 0x7f, sizeof(d));
	d[0] = 0;
	q[0] = 0;
	tail = 1;
	in[0] = true;
	while (head != tail)
	{
		static int x;
		x = q[head++];
		if (head == maxN)
			head = 0;
		in[x] = false;
		for (int e = start[x]; e; e = next[e])
			if (d[x] + len[e] < d[to[e]])
			{
				d[to[e]] = d[x] + len[e];
				if (!in[to[e]])
				{
					in[to[e]] = true;
					q[tail++] = to[e];
					if (tail == maxN)
						tail = 0;
				}
			}
	}
	printf("%d\n", d[N]);
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
