// Once more using treap
// Start: Mon Jul 26, 2:15 PM, 2010 (UTC+0800)
#include <cstdio>
#include <cstdlib>
#include <cassert>

namespace locale
{
	void init();
	// where, what
	void insert(int&, int);
	void remove(int&, int);
	int k_th(int, int);
	int smaller_than(int, int);
	void rotate(int&, int);
	void update(int);

	struct node_t
	{
		void init(int);
		int data, weight;
		int size, son[2];
	};

	const int N(200010);
	int root(0), cnt(1);
	node_t node[N];
}

void locale::rotate(int & x, int d)
{
	const int y = node[x].son[d];
	node[x].son[d] = node[y].son[!d];
	node[y].son[!d] = x;
	update(x);
	update(x = y);
}

void locale::update(int x)
{
	int & s = node[x].size = 1;
	if (node[x].son[0])
		s += node[node[x].son[0]].size;
	if (node[x].son[1])
		s += node[node[x].son[1]].size;
}

void locale::init()
{
	srand(23443);
	node[0].weight = -1;
	node[0].size = 0;
}

void locale::node_t::init(int x)
{
	data = x;
	weight = rand();
	size = 1;
	son[0] = son[1] =0;
}

void locale::insert(int & pos, int x)
{
	if (pos)
	{
		if (x == node[pos].data)
			return;
		const int d = x > node[pos].data;
		insert(node[pos].son[d], x);
		if (node[node[pos].son[d]].weight > node[pos].weight)
			rotate(pos, d);
		update(pos);
	}
	else
	{
		pos = cnt++;
		node[pos].init(x);
	}
}

void locale::remove(int & pos, int x)
{
	if (!pos)
		return;
	if (node[pos].data == x)
	{
		const int d = node[node[pos].son[1]].weight > node[node[pos].son[0]].weight;
		if (node[pos].son[d] == 0)
			pos = 0;
		else
		{
			rotate(pos, d);
			remove(node[pos].son[!d], x);
			update(pos);
		}
	}
	else
	{
		const int d = x > node[pos].data;
		remove(node[pos].son[d], x);
		update(pos);
	}
}

int locale::k_th(int pos, int k)
{
	const int t = node[node[pos].son[0]].size + 1;
	if (k == t)
		return node[pos].data;
	else if (k < t)
		return k_th(node[pos].son[0], k);
	else
		return k_th(node[pos].son[1], k - t);
}

int locale::smaller_than(int pos, int x)
{
	if (pos == 0)
		return 0;
	if (node[pos].data < x)
		return node[node[pos].son[0]].size + 1 + smaller_than(node[pos].son[1], x);
	else
		return smaller_than(node[pos].son[0], x);
}

int main()
{
	locale::init();
	int x, _;
	char str[5];
	int & r = locale::root;
	for (scanf("%d", &_); _; --_)
	{
		scanf("%s%d", str, &x);
		switch(str[0])
		{
			case 'I': locale::insert(r, x); break;
			case 'D': locale::remove(r, x); break;
			case 'K':
				if (x <= locale::node[r].size)
					printf("%d\n", locale::k_th(r, x));
				else
					printf("invalid\n");
				break;
			case 'C': printf("%d\n", locale::smaller_than(r, x)); break;
			default: assert(0); //This should never happen
		}
#ifdef DB
		printf("root = %d\n", r);
#endif
	}
	return 0;
}
