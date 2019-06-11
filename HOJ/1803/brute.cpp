/** @file query.cpp
 *  @version 1.0
 *  @author Theodore You
 *  @date Tue Aug 17, 11:16:15 PM, 2010, +0800
 *  This is my solution for HOJ Problem #1803, which will probably get TLE.
 */
#include <cstdio>
#include <cassert>
#include <queue>
#include <utility>

using namespace std;

namespace amicable
{
	void init();
	void answer();
	void add(int, int);
	void build(int);
	const int maxn(100010);
	int n;
	int label[maxn];
	int start[maxn], to[2*maxn], next[2*maxn], edge;
	pair<int, int>* tree[maxn];
	int size[maxn];
	priority_queue<pair<pair<int, int>, int> > h;
	int son[maxn], cur[maxn];
	bool vis[maxn];
}

void amicable::build(int x)
{
	vis[x] = true;
	int & s = size[x];
	assert(s == 0);
	s = 1;
	for (int e = start[x]; e; e = next[e])
	{
		if (vis[to[e]])
			continue;
		if (!size[to[e]])
			build(to[e]);
		assert(size[to[e]]);
		s += size[to[e]];
	}
	for (int e = start[x], i = 0; e; e = next[e], ++i)
	{
		if (vis[to[e]])
			continue;
		h.push(pair<pair<int, int>, int>(tree[to[e]][0], i));
		son[i] = to[e];
		cur[i] = 1;
	}
	h.push(pair<pair<int, int>, int>(pair<int, int>(label[x], x), -1));
	tree[x] = new pair<int, int> [s];
	for (int i = 0; i < s; ++i)
	{
		static pair<pair<int, int>, int> t;
		t = h.top();
		h.pop();
		if (t.second != -1 && cur[t.second] < size[son[t.second]])
		{
			h.push(pair<pair<int, int>, int>
					(tree[son[t.second]][cur[t.second]], t.second));
			++cur[t.second];
		}
		tree[x][i] = t.first;
	}
	assert(h.empty());
	vis[x] = false;
}

void amicable::add(int a, int b)
{
	to[++edge] = b;
	next[edge] = start[a];
	start[a] = edge;
}

void amicable::init()
{
	scanf("%d", &n);
	for (int* i = label + 1; i <= label + n; ++i)
		scanf("%d", i);
	while (--n)
	{
		static int a, b;
		scanf("%d%d", &a, &b);
		add(a, b);
		add(b, a);
	}
	build(1);
}

void amicable::answer()
{
	int m;
	for (scanf("%d", &m); m--; )
	{
		static int a, b;
		scanf("%d%d", &a, &b);
		printf("%d\n", tree[a][size[a]-b].second);
	}
}

int main()
{
	amicable::init();
	amicable::answer();
	return 0;
}
