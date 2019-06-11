#include <cstdio>
#include <cstdlib>
#include <ctime>

namespace advocate
{
#define maxn 100010
#define maxm 10010
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
		void insert(int, int, int&);
		void rotate(int&, int);
		int k_th(int);
		node_t node[maxn];
		int root, cnt;
	};
	void init();
	void answer(int);
	treap_t* combine(int, int);
	int n, m;
	int label[maxn];
	int start[maxn], to[maxn*2], next[maxn*2], edge;
	int startq[maxn], query[maxm], nextq[maxm];
	int ans[maxm];
	bool vis[maxn];
	treap_t* treap[maxn];
}

#define update(x) \
{ \
	node[x].size = node[node[x].son[0]].size + node[node[x].son[1]].size + 1; \
}

void advocate::treap_t::rotate(int& x, int d)
{
	const int y = node[x].son[d];
	node[x].son[d] = node[y].son[!d];
	node[y].son[!d] = x;
	update(x);
	x = y;
	update(x);
}

int advocate::treap_t::k_th(int k)
{
	int r(root), t;
	for (t = node[node[r].son[0]].size + 1; t != k; t = node[node[r].son[0]].size + 1)
		if (t < k)
		{
			k -= t;
			r = node[r].son[1];
		}
		else
		{
			r = node[r].son[0];
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
		return;
	}
	int d = x > node[p].data;
	insert(i, x, node[p].son[d]);
	if (node[node[p].son[d]].weight > node[p].weight)
		rotate(p, d);
	else
		update(p);
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

advocate::treap_t* advocate::combine(int a, int b)
{
	int t(treap[b]->node[treap[b]->root].size);
	for (int i = 1; i <= t; ++i)
	{
		treap[a]->insert(treap[b]->node[i].index, treap[b]->node[i].data, treap[a]->root);
	}
	return treap[a];
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
			{
				if (treap[x]->node[treap[x]->root].size
						< treap[to[e]]->node[treap[to[e]]->root].size)
				{
					treap_t* t = treap[x];
					treap[x] = treap[to[e]];
					treap[to[e]] = t;
				}
				treap[x] = combine(x, to[e]);
				delete treap[to[e]];
				treap[to[e]] = NULL;
			}
		}
	if (treap[x] == NULL)
		treap[x] = new treap_t(x, label[x]);
	else
		treap[x]->insert(x, label[x], treap[x]->root);
	for (int q = startq[x]; q; q = nextq[q])
		ans[q] = treap[x]->k_th(query[q]);
}

#define add(a, b) \
{ \
	advocate::to[++advocate::edge] = b; \
	advocate::next[advocate::edge] = advocate::start[a]; \
	advocate::start[a] = advocate::edge; \
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
	srand(n * m * time(0));
}

int main()
{
	advocate::init();
	advocate::answer(1);
	for (int i = 1; i <= advocate::m; ++i)
		printf("%d\n", advocate::ans[i]);
	return 0;
}
