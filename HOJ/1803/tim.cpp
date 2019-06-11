/*
 * $File: 1487_treap.cpp
 * $Date: Sun Jul 25 11:40:37 2010 +0800
 * $Addr: SPOJ or http://61.187.179.132:8080/JudgeOnline/showproblem?problem_id=1803
 * $Algorithm: off-line algorithm, using Balanced Tree, heuristically union balanced trees by adding 
 *			each node in the small tree into the bigger tree.
 * $Time Complexity: every node is inserted at most log(n) times, because when the node is added twice,
 *				the size of the corresponding bigger tree must be at least twice bigger of the first time,
 *				and each insert costs O(log(n)), each query costs O(log(n))so we obtained a time complexity of 
 *				O(n * log^2(n) + m * log(n))
 * $Result: using Treap can be Accepted on hybzoj, But Time Limit Exceed on SPOJ....
 *			using Splay Time Limit Exceed at everywhere...
 * $Editorial: cause the amount of queries is not that many, this algorithm runs slower than 
 *			others, but under abundant queries such as 1000000, this algorithm runs much faster than
 *			that of others.
 * $Author: Tim
 */

#include <cstdio>
#include <cstdlib>

#define MAXN 100000
#define MAXM 10000
#define MAXQUERY 10000

using namespace std;

#define BUFSIZE 100000
char buf[BUFSIZE], *pt = buf + BUFSIZE, *pend = buf + BUFSIZE;
#define read() \
	do{ \
		if (pt >= pend) \
		{ \
			pt = buf; \
			fread(buf, 1, BUFSIZE, stdin); \
		} \
	} while(0) 

#define scan(t) \
{ \
	t = 0; \
	read(); \
	bool nega = false; \
	while (!(((*pt) >= '0' && (*pt) <= '9') || (*pt == '-'))) {pt ++; read();} \
	if ((*pt) == '-') {nega = true, pt ++; read();} \
	while (((*pt) >= '0' && (*pt) <= '9')) {t = t * 10 + (*(pt ++)) - '0'; read();}\
	if (nega) t = -t; \
}

int n, m;
int begin[MAXN + 1], next[MAXN * 2 + 1], end[MAXN * 2 + 1];
int Count = 0;
void AddEdge(int a, int b)
{
	Count ++;
	next[Count] = begin[a];
	begin[a] = Count;
	end[Count] = b;
}

int Count_query;
int begin_query[MAXN + 1], next_query[MAXQUERY + 1], query[MAXQUERY + 1], ans[MAXQUERY + 1];
void AddQuery(int x, int k)
{
	Count_query ++;
	next_query[Count_query] = begin_query[x];
	begin_query[x] = Count_query;
	query[Count_query] = k;
}

class Node
{
	public:
		int lt, rt, v, size, p;
};
Node node[MAXN + 1];
int root[MAXN + 1];
void Init()
{
	scan(n);
	for (int i = 1, v; i <= n; i ++)
	{
		scan(v);
		node[i].v = v;
		node[i].size = 1;
		node[i].p = rand();
		root[i] = i;
	}
	for (int i = 1, a, b; i <= n - 1; i ++)
	{
		scan(a); scan(b);
		AddEdge(a, b);
		AddEdge(b, a);
	}
	scan(m);
	for (int i = 1, x, k; i <= m; i ++)
	{
		scan(x); scan(k);
		AddQuery(x, k);
	}
}


int q[MAXN + 1];
int father[MAXN + 1];

int AskKth(int x, int k)
{
	int lc;
	while (true)
	{
		lc = node[x].lt;
		if (k <= node[lc].size)
			x = lc;
		else if (k == node[lc].size + 1)
			return x;
		else
			x = node[x].rt, k -= node[lc].size + 1;
	}
}

void RightRotate(int &x)
{
	int lc = node[x].lt;
	node[x].lt = node[lc].rt;
	node[lc].rt = x;
	node[lc].size = node[x].size;
	node[x].size = node[node[x].lt].size + node[node[x].rt].size + 1;
	x = lc;
}

void LeftRotate(int &x)
{
	int rc = node[x].rt;
	node[x].rt = node[rc].lt;
	node[rc].lt = x;
	node[rc].size = node[x].size;
	node[x].size = node[node[x].lt].size + node[node[x].rt].size + 1;
	x = rc;
}

void Add(int &x, int y)
{
	if (!x)
	{
		node[y].lt = node[y].rt = 0;
		node[y].p = rand();
		node[y].size = 1;
		x = y;
	}
	else
	{
		node[x].size ++;
		if (node[y].v <= node[x].v)
		{
			Add(node[x].lt, y);
			if (node[node[x].lt].p < node[x].p)
				RightRotate(x);
		}
		else
		{
			Add(node[x].rt, y);
			if (node[node[x].rt].p < node[x].p)
				LeftRotate(x);
		}
	}
}

int Union(int v0, int v1)
	// Add nodes in tree rooted v1 to tree rooted v0 and return the root
{
	static int q[MAXN + 1];
	q[1] = v1;
	int head = 0, tail = 1;
	while (head != tail)
	{
		int t = q[++ head];
		if (node[t].lt)
			q[++ tail] = node[t].lt;
		if (node[t].rt)
			q[++ tail] = node[t].rt;
		Add(v0, q[head]);
	}
	return v0;
}

void Solve()
{
	// BFS
	q[1] = 1;
	for (int head = 0, tail = 1; head != tail; )
		for (int t = q[++ head], now = begin[t], ch; now; now = next[now])
			if ((ch = end[now]) != father[t])
				father[ch] = t, q[++ tail] = ch;

	// Answer queries
	for (int i = n, x, fa; i >= 1; i --)
	{
		x = q[i], fa = father[x];
		for (int now = begin_query[x]; now; now = next_query[now])
			ans[now] = AskKth(root[x], query[now]);
		if (x == 1)
			break;
		if (node[root[fa]].size > node[root[x]].size)
			root[fa] = Union(root[fa], root[x]);
		else
			root[fa] = Union(root[x], root[fa]);
	}
	for (int i = 1; i <= m; i ++)
		printf("%d\n", ans[i]);
}

int main()
{
	freopen("1487.in", "r", stdin);
	freopen("1487.ans", "w", stdout);
	srand(42);
	Init();
	Solve();
	return 0;
}

