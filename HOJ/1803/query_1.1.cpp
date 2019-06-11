/** @file query.cpp
 *  @version 1.1
 *  @date Mon Aug 23 5:00:25 PM, 2010 +0800
 *  @author Theodore You
 *  This is my implementation for HOJ Problem #1803, "Query On A Tree III".
 */
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <ctime>

namespace advocate
{
	const int maxn(100010);
	const int maxm(10010);
	class treap_t
	{
		struct node_t
		{
			int index;
			int data, weight;
			int size, son[2];
		};
	public:
		treap_t(int, int);
		void insert(int, int);
		void insert(int, int, int&);
		void rotate(int&, int);
		void update(int);
		int size();
		int k_th(int);
		node_t node[maxn];
	private:
		int root, cnt;
	};
	void init();
	void answer();
	void answer(int);
	void add(int, int);
	void combine(int, int);
	int n, m;
	int label[maxn];
	int start[maxn], to[maxn*2], next[maxn*2], edge;
	int startq[maxn], query[maxm], nextq[maxm];
	int ans[maxm];
	bool vis[maxn];
	treap_t* treap[maxn];
}

void advocate::treap_t::rotate(int& x, int d)
{
	const int y = node[x].son[d];
	node[x].son[d] = node[y].son[!d];
	node[y].son[!d] = x;
	update(x);
	update(x = y);
}

void advocate::treap_t::update(int x)
{
	node[x].size = node[node[x].son[0]].size + node[node[x].son[1]].size + 1;
}

int advocate::treap_t::k_th(int k)
{
	assert(node[root].size >= k);
	int r(root), t;
	for (t = node[node[r].son[0]].size + 1; t != k; t = node[node[r].son[0]].size + 1)
		if (t < k)
		{
			k -= t;
			r = node[r].son[1];
			assert(r);
		}
		else
		{
			r = node[r].son[0];
			assert(r);
		}
	return node[r].index;
}

void advocate::treap_t::insert(int i, int x, int& p)
{
	if (p == 0)
	{
		p = ++cnt;
		node[p].index = i;
		node[p].data = x;
		node[p].weight = rand();
		node[p].size = 1;
		assert(node[p].son[0] == 0);
		assert(node[p].son[1] == 0);
		return;
	}
	int d = x > node[p].data;
	insert(i, x, node[p].son[d]);
	if (node[node[p].son[d]].weight > node[p].weight)
		rotate(p, d);
	else
		update(p);
}

void advocate::treap_t::insert(int i, int x)
{
#ifdef DB
	printf("inserting %d\n", x);
#endif
	insert(i, x, root);
}

advocate::treap_t::treap_t(int i, int x)
	: root(1), cnt(1)
{
	node[1].index = i;
	node[1].data = x;
	node[1].weight = rand();
	node[1].size = 1;
	node[0].weight = -1;
}

int advocate::treap_t::size()
{
	assert(root);
	return node[root].size;
}

void advocate::combine(int a, int b)
{
	int t;
	if (treap[a]->size() < treap[b]->size())
	{
		t = b;
		b = a;
		a = t;
	}
	t = treap[b]->size();
	for (int i = 1; i <= t; ++i)
	{
		treap[a]->insert(treap[b]->node[i].index, treap[b]->node[i].data);
	}
}

void advocate::answer(int x)
{
	vis[x] = true;
	for (int e = start[x]; e; e = next[e])
		if (!vis[to[e]])
		{
			answer(to[e]);
			if (treap[x] == NULL)
				treap[x] = treap[to[e]];
			else
				combine(x, to[e]);
		}
	if (treap[x] == NULL)
		treap[x] = new treap_t(x, label[x]);
	else
		treap[x]->insert(x, label[x]);
	for (int q = startq[x]; q; q = nextq[q])
		ans[q] = treap[x]->k_th(query[q]);
}

void advocate::add(int a, int b)
{
	to[++edge] = b;
	next[edge] = start[a];
	start[a] = edge;
}

void advocate::init()
{
	scanf("%d", &n);
	for (register int i = 1; i <= n; ++i)
		scanf("%d", label + i);
	int a, b;
	for (int i = 0; i < n - 1; ++i)
	{
		scanf("%d%d", &a, &b);
		add(a, b);
		add(b, a);
	}
	scanf("%d", &m);
	for (int i = 1; i <= m; ++i)
	{
		scanf("%d%d", &a, &b);
		query[i] = b;
		nextq[i] = startq[a];
		startq[a] = i;
	}
#ifdef LOCAL
	srand(n * m);
#else
	srand(n * m * time(0));
#endif
}

void advocate::answer()
{
	answer(1);
	for (int i = 1; i <= m; ++i)
		printf("%d\n", ans[i]);
}

int main()
{
#ifdef DB
	freopen("in", "r", stdin);
#endif
	advocate::init();
	advocate::answer();
	return 0;
}
