#include <cstdlib>

template <typename data_t>
void Tree::Treap<data_t>::node_t::init(const data_t& data)
{
	v = data;
	w = rand();
#ifdef DB
	if (w == 981821953)
		w = 1;
#endif
	c = 1;
	s[0] = s[1] = 0;
}

template <typename data_t>
Tree::Treap<data_t>::Treap(const size_t n)
	: node(new node_t[n + 3]), path(new int[n + 3]), root(0), nc(0)
{
	static bool not_set_rand = true;
	if (not_set_rand)
	{
		not_set_rand = false;
		srand('y' + 'm' + 'f' + 'o' + 'r' + 'z');
	}
	node[0].w = -1;
}

template <typename data_t>
Tree::Treap<data_t>::~Treap()
{
	delete[] node;
	delete[] path;
}

template <typename data_t>
void Tree::Treap<data_t>::insert(const data_t& data)
{
	if (root == 0)
	{
		root = ++nc;
		node[nc].init(data);
	}
	else
	{
		int pos = root, add, n = -1;
		while (node[pos].v != data)
		{
			path[++n] = pos;
			add = node[pos].v < data;
			if (node[pos].s[add])
				pos = node[pos].s[add];
			else
				break;
		}
		if (node[pos].v == data)
			++node[pos].c;
		else
		{
			node[pos].s[add] = ++nc;
			node[nc].init(data);
			for (int i = n; i >= 0; --i)
			{
				int x = path[i];
				int d = node[node[x].s[0]].w < node[node[x].s[1]].w;
				if (node[node[x].s[d]].w > node[x].w)
				{
					if (i)
					{
						node_t& z = node[path[i - 1]];
						z.s[z.s[1] == x] = rotate(x, d);
					}
					else
						root = rotate(x, d);
				}
				else
					break;
			}
		}
	}
}

template <typename data_t>
void Tree::Treap<data_t>::remove(const data_t& data)
{
	int pos = root, fa = 0;;
	while (pos && node[pos].v != data)
	{
		fa = pos;
		pos = node[pos].s[node[pos].v < data];
	}
	if (pos && --node[pos].c == 0)
	{
		int d;
		for (; ; )
		{
			node_t& x = node[pos];
			d = node[x.s[0]].w < node[x.s[1]].w;
			if (x.s[d])
			{
				fa = (fa ? node[fa].s[node[fa].s[1] == pos] : root) = rotate(pos, d);
				pos = node[fa].s[!d];
			}
			else
				break;
		}
		if (fa == 0)
			root = 0;
		else
			node[fa].s[node[fa].s[1] == pos] = 0;
	}
}

template <typename data_t>
int Tree::Treap<data_t>::find(const data_t& data)
{
	int pos = root;
	while (pos && node[pos].v != data)
		pos = node[pos].s[node[pos].v < data];
	return pos;
}

template <typename data_t>
int Tree::Treap<data_t>::rotate(const int x, const int d)
{
	const int y = node[x].s[d];
	node[x].s[d] = node[y].s[!d];
	node[y].s[!d] = x;
	return y;
}

#ifdef DB
template <typename data_t>
void Tree::Treap<data_t>::output()
{
	fprintf(stderr, "root = %d, nc = %d\n", root, nc);
	for (int i = 0; i <= nc; ++i)
		fprintf(stderr, "%d: v = %d, w = %d, c = %d, s = {%d, %d}\n",
				i, node[i].v, node[i].w, node[i].c, node[i].s[0], node[i].s[1]);
	fprintf(stderr, "\n");
}
#endif
