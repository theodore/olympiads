// Error #1: didn't call update in first and find_min
// Error #2: didn't turn rev to false when passing it down
// Error #3: didn't call update when seeking pred and succ, similar to #1
// Error #4: confusing min, min_pos with data, pos in update
#include <cstdio>

namespace deviate
{
	// input and initialize data, min, dir of node[0], node[1], node[n+2]
	// or you only have to initialize min?
	void init();
	int build(const int, const int, const int);
	void answer();
	int first();
	int find_min();
	void rotate(const int);
	void splay(const int, const int = 0);
	struct node_t
	{
		// put down rev
		// update min, min_pos, dir, size
		void update();
		bool operator<(const node_t&);
		bool rev;
		int data, pos, min, min_pos;
		// dir, 0/1 for sons, 2 for here
		int dir, size;
		int father, son[2];
	};
	const int N(100010);
	const int INF(-1u>>1);
	node_t node[N];
	int n, root;
#ifdef DB
	void tab(int);
	void output(int = -1, int = 0);
#endif
}

void deviate::node_t::update()
{
	if (rev)
	{
		int t = son[0];
		son[0] = son[1];
		son[1] = t;
		node[son[0]].rev ^= 1;
		node[son[1]].rev ^= 1;
		rev = false;
	}
	size = 1 + node[son[0]].size + node[son[1]].size;
	dir = node[son[1]] < node[son[0]];
	/*
	// really in need here?
	min = data;
	min_pos = pos;
	*/
	if (node[son[dir]].min < data || (node[son[dir]].min == data && node[son[dir]].min_pos < pos))
	{
		min = node[son[dir]].min;
		min_pos = node[son[dir]].min_pos;
	}
	else
	{
		dir = 2;
		min = data;
		min_pos = pos;
	}
}

bool deviate::node_t::operator<(const node_t & p)
{
	if (min != p.min)
		return min < p.min;
	else
		return min_pos < p.min_pos;
}

void deviate::init()
{
	scanf("%d", &n);
	for (int i = 2; i <= n + 1; ++i)
	{
		scanf("%d", &node[i].data);
		node[i].pos = i;
	}
	node[0].min = INF;// = node[1].min = node[n+2].min = INF;
	node[1].data = node[n+2].data = INF;
}

int deviate::build(const int l, const int r, const int f)
{
	if (l == r)
		return 0;
	int mid = (l + r) / 2;
	node[mid].father = f;
	/*
	//here, or in update()?
	node[mid].min = node[mid].data;
	node[mid].min_pos = node[mid].pos;
	*/
	node[mid].son[0] = build(l, mid, mid);
	node[mid].son[1] = build(mid + 1, r, mid);
	node[mid].update();
	return mid;
}

int deviate::first()
{
	int ret = root;
	for (node[ret].update(); node[ret].son[0]; node[ret].update())
		ret = node[ret].son[0];
	return ret;
}

int deviate::find_min()
{
	int ret = root;
	for (node[ret].update(); node[ret].dir != 2; node[ret].update())
		ret = node[ret].son[node[ret].dir];
	return ret;
}

void deviate::rotate(const int y)
{
	const int x = node[y].father;
	const int d = y == node[x].son[1];
	node[y].father = node[x].father;
	node[node[x].father].son[x==node[node[x].father].son[1]] = y;
	node[x].son[d] = node[y].son[!d];
	node[node[y].son[!d]].father = x;
	node[y].son[!d] = x;
	node[x].father = y;
	node[x].update();
	node[y].update();
}

void deviate::splay(const int x, const int y)
{
#ifdef DB
	//printf("%s|%d, %d\n", __PRETTY_FUNCTION__, x, y);
	//output();
#endif
	for (int f = node[x].father; f != y; f = node[x].father)
	{
		static int gf;
		gf = node[f].father;
		if (gf == y)
			rotate(x);
		else
		{
			if ((x == node[f].son[1]) ^ (f == node[gf].son[1]))
			{
				rotate(x);
				rotate(x);
			}
			else
			{
				rotate(f);
				rotate(x);
			}
		}
	}
	if (y == 0)
		root = x;
}

void deviate::answer()
{
	for (int i = 2; i <= n; ++i)
	{
#ifdef DB
		printf("i = %d\n", i);
		output();
#endif
		int dest = first(), next = find_min();
		int pred, succ;
		splay(next);
		printf("%d ", node[node[next].son[0]].size + i - 2);
#ifdef DB
		putchar(10);
#endif
		pred = node[next].son[0];
		for (node[pred].update(); node[pred].son[1]; node[pred].update())
			pred = node[pred].son[1];
		succ = node[next].son[1];
		for (node[succ].update(); node[succ].son[0]; node[succ].update())
			succ = node[succ].son[0];
		splay(pred);
		splay(succ, pred);
		node[succ].son[0] = 0;
		node[succ].update();
		node[pred].update();
		splay(dest);
		splay(succ, dest);
		node[node[succ].son[0]].rev ^= 1;
	}
#ifdef DB
	output();
#endif
	printf("%d\n", n);
}

int main()
{
#ifdef LOCAL
	freopen("in", "r", stdin);
#ifndef GDB
	freopen("out", "w", stdout);
#endif
#endif
	deviate::init();
	deviate::root = deviate::build(1, deviate::n + 3, 0);
	deviate::answer();
	return 0;
}

#ifdef DB
void deviate::tab(int x)
{
	for (int i = 0; i < x; ++i)
		printf("| ");
}
void deviate::output(int pos, int t)
{
	if (pos == -1)
		pos = root;
	tab(t++);
	node_t & x = node[pos];
	printf("%d, data = %d, son = {%d, %d}, dir = %d, rev = %d, size = %d, father = %d, pos = %d, min = %d, min_pos = %d\n", pos, x.data, x.son[0], x.son[1], x.dir, x.rev, x.size, x.father, x.pos, x.min, x.min_pos);
	//printf("%d, data = %d, pos = %d, dir = %d, min = %d, min_pos = %d\n", pos, x.data, x.pos, x.dir, x.min, x.min_pos);
	if (x.son[0])
		output(x.son[0], t);
	if (x.son[1])
		output(x.son[1], t);
	if (pos == root)
		putchar(10);
}
#endif
