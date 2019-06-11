/*
 * $File: 1487_nlogn_mlognlogn.cpp
 * $Date: Sun Jul 25 01:22:26 2010 +0800
 * $Addr: SPOJ or http://61.187.179.132:8080/JudgeOnline/showproblem?problem_id=1803
 * $Algorithm: on-line algorithm, use the dfs-sequence of a tree, and the query of a
 *				sub-tree equals to query in a sub-sequence. and what we do is to 
 *				calculate the kth-largest value in sub-sequence [p, q].
 *				to calculate the kth-largest value in a sub-sequence, we shall build
 *				a tree according to the sequence simular to a segment-tree.
 *				each node in the tree denote a interval [l, r] which contains all 
 *				element ranked in [l, r] after sorted, and they are arranged inside
 *				each node by there original position in the dfs-sequence.
 *				let Query(l, r, p, q, k) denote the query of asking the kth-largest element
 *				in sub-sequence [p, q], and the rank-range is [l, r]. let mid = (l + r) / 2,
 *				and if the number of element ranked in [l, mid] and in the sub-sequence [p, q]
 *				is not greater than k, then the kth-largest element is in rank-range [l, mid], 
 *				otherwise in rank-range [mid + 1, r]. so we can define the function
 *				Get and Query using binary search like this:
 *				
 * 				** the implementation of function GetAmount see the code below. 
 *
 *				function Get(l, r, p, q) // calculate the number in rank-range[l, r] and also
 *										 // in sub-sequence [l, r]
 *					return GetAmount(l, r, q) - GetAmount(l, r, p - 1)
 *				end function
 *
 *				function Qeury(l, r, p, q, k)
 *					if l = r return id[l];
 *					mid <- (l + r) / 2;
 *					cnt <- Get(l, mid, p, q);
 *					if cnt <= k
 *						return Qeury(l, mid, p, q, k)
 *					else
 *						return Qeury(mid + 1, r, p, q, k - cnt)
 *				end function
 *
 *	$Time Complexity: O(n * log(n) + m * log^2(n))
 *	$Result: Accepted on both hybzoj and SPOJ, as the queries is pretty few. when I add
 *			queries to 100000, this algorithm runs much slower than the off-line algorithm 
 *			based on heuristic union of balanced tree as expected.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

/**
 * define STDIO to use standard input and standard output in
 * most of the Online Contesters/Judges.
 */
#define STDIO

/**
 * define MANUAL_STACK to avoid stack overflow in Windows OS,
 * which is usually not necassary for linux.
 */ 
//#define MANUAL_STACK

#define MAXN 100000
#define MAXDEPTH 18
#define MAXQUERY 10000

using namespace std;

// reading optimization
#define BUFSIZE 1000000
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
// end reading optimization

int begin[MAXN + 1], next[MAXN * 2 + 1], end[MAXN * 2 + 1];
int Count = 0;
void AddEdge(int a, int b)
{
	Count ++;
	next[Count] = begin[a];
	begin[a] = Count;
	end[Count] = b;
}

int n, m;
int v[MAXN + 1];
void Init()
{
	scan(n);
	for (int i = 1; i <= n; i ++)
		scan(v[i]);
	for (int i = 1, a, b; i <= n - 1; i ++)
	{
		scan(a); scan(b);
		AddEdge(a, b);
		AddEdge(b, a);
	}
}
int seq[MAXDEPTH + 1][MAXN + 1];
int L[MAXN + 1];
int R[MAXN + 1];
int N;
class Stuff
{
	public:
		int v, pos, id;
};
Stuff a[MAXN + 1];

#ifdef MANUAL_STACK
class Stack
{
	public:
		int x, cur;
		bool first;
		void set(int _x, int _cur, bool _first)
		{x = _x, cur = _cur, first = _first;}
		void get(int &_x, int &_cur, bool &_first)
		{_x = x, _cur = cur, _first = first;}
};
Stack stack[MAXN + 1];
int father[MAXN + 1];
#else
void dfs(int x, int fa)
{
	a[++ N].v = v[x];
	a[N].pos = N;
	a[N].id = x;
	L[x] = N;
	for (int now = begin[x]; now; now = next[now])
		if (end[now] != fa)
			dfs(end[now], x);
	R[x] = N;
}
#endif

void DFS()
{
#ifdef MANUAL_STACK
	int top = 0, x, cur;
	bool first, deepin;
	stack[++ top].set(1, begin[1], true);
	while (top)
	{
		stack[top --].get(x, cur, first);
		if (first)
		{
			a[++ N].v = v[x];
			a[N].pos = N;
			a[N].id = x;
			L[x] = N;
		}
		deepin = false;
		for (int now = cur, ch; now; now = next[now])
			if ((ch = end[now]) != father[x])
			{
				deepin = true;
				father[ch] = x;
				stack[++ top].set(x, next[now], false);
				stack[++ top].set(ch, begin[ch], true);
				break;
			}
		if (!deepin)
			R[x] = N;
	}
#else
	dfs(1, 0);
#endif
}

bool cmpStuff(const Stuff &a, const Stuff &b)
{return a.v < b.v;}

void Build(int l, int r, int dep)
{
	if (l == r)
		seq[dep][l] = a[l].pos;
	else
	{
		int mid = (l + r) >> 1;
		Build(l, mid, dep + 1);
		Build(mid + 1, r, dep + 1);
		int p = l, q = mid + 1, *b = seq[dep + 1], pos = l, *a = seq[dep];
		while (p <= mid && q <= r)
			a[pos ++] = b[(b[p] <= b[q] ? p : q) ++];
		while (p <= mid)
			a[pos ++] = b[p ++];
		while (q <= r)
			a[pos ++] = b[q ++];
	}
}

void BuildTree()
{
	DFS();
	sort(a + 1, a + 1 + N, cmpStuff);
	Build(1, N, 0);
}

int GetAmount(int *a, int left, int right, int v)
{
	int l = left, r = right + 1;
	if (v < a[l]) return 0;
	while (l + 1 < r)
		(a[(l + r) >> 1] <= v ? l : r) = (l + r) >> 1;
	return l - left + 1;
}

int Ask(int p, int q, int k)
{
	int l, r, dep, mid;
	for (l = 1, r = n, dep = 0; mid = (l + r) >> 1, l != r; dep ++)
	{
		int cnt = GetAmount(seq[dep + 1], l, mid, q) - GetAmount(seq[dep + 1], l, mid, p - 1);
		if (cnt >= k)
			r = mid;
		else
			l = mid + 1, k -= cnt;
	}
	return a[l].id;
}

void AnswerQueries()
{
	scan(m);
	for (int i = 1, x, k; i <= m; i ++)
	{
		scan(x); scan(k);
		printf("%d\n", Ask(L[x], R[x], k));
	}
}

void Solve()
{
	BuildTree();
	AnswerQueries();
}

int main()
{
#ifndef STDIO
	freopen("1487.in", "r", stdin);
	freopen("1487.out", "w", stdout);
#endif
	Init();
	Solve();
	return 0;
}

