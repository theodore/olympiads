/** @file rankings.cpp
 *  @version 1.6
 *  @author Theodore You
 *  @date Thu Aug 12 2010 5:08 PM +0800
 *  This is my implementation for HOJ Problem #1901, "Dynamic Rankings".
 *  This is also my first documented source file.
 *  The solution is implemented using a zkw segment tree with every node being a
 *  treap.
 */

#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <ctime>
#include <algorithm>

namespace idyllic
{
	class treap
	{
	private:
		struct node_t
		{
			int	data;
			int	weight;
			int	size;
			int	son[2];
		};
	public:
		void	init(int, int = 0);
		void	change(int, int);
		int		less_than(int);
		int		temp();
	private:
		int		build(int, int);
		void	insert(int, int&);
		void	remove(int, int&);
		int		size();
		int		equal(int, int);
		void	rotate(int&, int);
		void	update(int);
		int		root;
		int		left;
		node_t*	node;
	};
	void	init();
	void	answer();
	void	change(int, int);
	int		query(int, int, int);
	int		less_than(int, int, int);
	const int	maxn(1 << 15);
	const int	INF(-1u >> 1);
	int			n, m, N;
	int			minv, maxv;
	int			count;
	treap		tree[maxn];
}

int main()
{
#ifdef LOCAL
	freopen("in", "r", stdin);
#endif
	idyllic::init();
	idyllic::answer();
	return 0;
}

/// Input and build the tree.
void idyllic::init()
{
	scanf("%d%d", &n, &m);
#ifdef DB
	srand(n * m);
#else
	srand(n * m * time(0));
#endif
	for (N = 1; N < n + 2; N <<= 1);
	minv = INF;
	maxv = ~INF;
	tree[N].init(0);
	for (int i = N + 1; i <= N + n; ++i)
		tree[i].init(1);
	for (int i = N + n + 1; i < N + N; ++i)
		tree[i].init(0);
	for (int i = N - 1; i; --i)
		tree[i].init(2, i + i);
}

/// Deal with every instruction.
void idyllic::answer()
{
	char str[3];
	while (m--)
	{
		static int a, b, c;
		scanf("%s%d%d", str, &a, &b);
		if ('C' == str[0])
		{
#ifdef MDB
			printf("Changing\n");
#endif
			change(a, b);
			minv = std::min(minv, b);
			maxv = std::max(maxv, b);
		}
		else
		{
#ifdef MDB
			printf("Querying\n");
#endif
			scanf("%d", &c);
			printf("%d\n", query(a - 1, b + 1, c));
		}
	}
}

/**
 *  @brief  Change value of a number in logarithmic time.
 *  @param  pos  The position of the value that's about to change.
 *  @param  x  The new value.
 */
void idyllic::change(int pos, int x)
{
	assert(pos <= n);
	int v = tree[N+pos].temp();
	for (int i = N + pos; i; i >>= 1)
		tree[i].change(v, x);
}

/**
 *  @brief  A function designed for the bug in idyllic::change(int, int).
 *  @return  The data of node[root].
 */
int idyllic::treap::temp()
{
	assert(1 == root);
	assert(0 == node[root].son[0]);
	assert(0 == node[root].son[1]);
	return node[1].data;
}

/**
 *  @brief  Answer a query in logarithmic time.
 *  @param  l  Left bound.
 *  @param  r  Right bound.
 *  @param  k  Index k.
 *  @return  The k-th element in (l, r).
 */
int idyllic::query(int l, int r, int k)
{
	for (int min = minv, max = maxv + 1, mid = (min + max) / 2; ;
		mid = (min + max) / 2)
	{
#ifdef MDB
		printf("min = %d, mid = %d, max = %d\n", min, mid, max);
#endif
		assert(min != max);
		count = 0;
		const int t = less_than(l, r, mid);
		if (t < k && k <= t + count)
			return mid;
		else if (k <= t)
			max = mid;
		else
		{
			assert(min != mid);
			min = mid;
		}
	}
}

/**
 *  @brief  Calculate the number of elements less than @p x, and change variable
 *  count, which would be the number of elements equal to @p x.
 *  @param  l  Left bound.
 *  @param  r  Right bound.
 *  @param  x  Value.
 *  @return  The number of elements less than @p x in (l, r).
 */
int idyllic::less_than(int l, int r, int x)
{
	int ret(0);
	for (l += N, r += N; l ^ r ^ 1; l >>= 1, r >>= 1)
	{
		if (~l & 1)
			ret += tree[l^1].less_than(x);
		if (r & 1)
			ret += tree[r^1].less_than(x);
	}
	return ret;
}

/**
 *  @brief  Initialize the treap.
 *  @param  flag  0 -- Nothing.
 *                1 -- Input.
 *                2 -- Generate from sons.
 *  @param  lson  Non-zero iff flag is 2, indicates its left son in segment tree.
 */
void idyllic::treap::init(int flag, int lson)
{
	left = 0;
	switch(flag)
	{
		case 0:
			assert(lson == 0);
			root = 0;
			node = 0;
			break;
		case 1:
			{
				assert(lson == 0);
				int t;
				scanf("%d", &t);
				maxv			= std::max(maxv, t);
				minv			= std::min(minv, t);
				root			= 1;
				node			= new node_t[2];
				node[0].weight	= -1;
				node[0].size	= 0;
				node[1].data	= t;
				node[1].weight	= 1;
				node[1].size	= 1;
				node[1].son[0]	= 0;
				node[1].son[1]	= 0;
				break;
			}
		case 2:
			{
				assert(lson);
				const int rson	= lson + 1;
				const int ls	= tree[lson].size();
				const int rs	= tree[rson].size();
				const int t		= ls + rs;
				if (t)
				{
					node = new node_t[t+1];
					node[0].weight	= -1;
					node[0].size	= 0;
					register int i, j, p;
					for (i = 1, j = 1, p = 1; i <= ls && j <= rs; ++p)
						node[p].data = (tree[lson].node[i].data
							< tree[rson].node[j].data)
							? tree[lson].node[i++].data
							: tree[rson].node[j++].data;
					if (i <= ls)
						for (; i <= ls; ++p, ++i)
							node[p] = tree[lson].node[i];
					if (j <= rs)
						for (; j <= rs; ++p, ++j)
							node[p] = tree[rson].node[j];
					assert(t + 1 == p);
					root = build(1, t + 1);
				}
				else
				{
					root = 0;
					node = 0;
				}
			}
			break;
		default:
			assert(0);
	}
}

/**
 *  @brief  Build the tree, i.e., update every node, in range [l, r).
 *  @param  l  Left bound.
 *  @param  r  Right bound.
 *  @return  Position of the sub-tree.
 */
int idyllic::treap::build(int l, int r)
{
	if (l == r)
		return 0;
	int m			= (l + r) / 2;
	node[m].son[0]	= build(l, m);
	node[m].son[1]	= build(m + 1, r);
	update(m);
	node[m].weight	= node[m].size;
	return m;
}

/**
 *  @brief  Change a value in the treap.
 *  @param  v  The old value.
 *  @param  x  The new value.
 */
void idyllic::treap::change(int v, int x)
{
	assert(node && root);
	remove(v, root);
	insert(x, root);
}

/**
 *  @brief  Calculate the number of elements less than @p x, and change variable
 *  count, which would be the number of elements equal to @p x.
 *  @param  x  Value.
 *  @return  The number of elements less than @p x in the treap.
 */
int idyllic::treap::less_than(int x)
{
	int ret(0);
	int p(root);
	int add(0);
	for (int t = node[p].data; p; t = node[p].data)
		if (t < x)
		{
			ret += node[node[p].son[0]].size + 1;
			p = node[p].son[1];
		}
		else if (t == x)
		{
			if (!add)
				add = p;
			p = node[p].son[0];
		}
		else
			p = node[p].son[0];
	count += equal(x, add);
	return ret;
}

/**
 *  @brief  Calculate the number of elements equal to @p x.
 *  @param  x  Value.
 *  @param  p  Postion of the root of the sub-tree.
 */
int idyllic::treap::equal(int x, int p)
{
	if (p == 0)
		return 0;
	assert(node[p].data == x);
	register int ret(1), l, r;
	for (l = node[p].son[0]; l; )
	{
		assert(node[l].data <= x);
		if (node[l].data < x)
		{
			l = node[l].son[1];
		}
		else
		{
			ret += node[node[l].son[1]].size + 1;
			l = node[l].son[0];
		}
	}
	for (r = node[p].son[1]; r; )
	{
		assert(node[r].data >= x);
		if (node[r].data > x)
		{
			r = node[r].son[0];
		}
		else
		{
			ret += node[node[r].son[0]].size + 1;
			r = node[r].son[1];
		}
	}
	return ret;
}

/**
 *  @brief  Insert an element.
 *  @param  x  The element to insert.
 *  @param  pos  The position to insert @p x.
 */
void idyllic::treap::insert(int x, int& pos)
{
	if (pos == 0)
	{
		assert(left);
		pos				= left;
		left			= 0;
		node[pos].data	= x;
		node[pos].weight= rand();
		node[pos].size	= 1;
		node[pos].son[0]= 0;
		node[pos].son[1]= 0;
		return;
	}
	int d = x >= node[pos].data;
	insert(x, node[pos].son[d]);
	if (node[node[pos].son[d]].weight > node[pos].weight)
		rotate(pos, d);
	update(pos);
}

/**
 *  @brief  Remove an element.
 *  @param  x  The element to remove.
 *  @param  pos  The postion to remove @p x.
 */
void idyllic::treap::remove(int x, int& pos)
{
	assert(pos);
	if (node[pos].data == x)
	{
		int d = node[node[pos].son[0]].weight < node[node[pos].son[1]].weight;
		if (node[pos].son[d])
		{
			rotate(pos, d);
			remove(x, node[pos].son[!d]);
		}
		else
		{
			assert(left == 0);
			left = pos;
			pos = 0;
			return;
		}
	}
	else
	{
		int d = x >= node[pos].data;
		remove(x, node[pos].son[d]);
	}
	update(pos);
}

/**
 *  @brief  Calculate the size of the treap.
 *  @return  Size of the treap.
 */
int idyllic::treap::size()
{
	if (node)
	{
		assert(root);
		return node[root].size;
	}
	else
	{
		assert(root == 0);
		return 0;
	}
}

/**
 *  @brief  Rotate the treap, it's very common in BST.
 *  @param  x  Root of the treap to rotate.
 *  @param  d  Direction to the son that is going to be the new root.
 */
void idyllic::treap::rotate(int& x, int d)
{
	assert(d == 0 || d == 1);
	const int y = node[x].son[d];
	node[x].son[d]	= node[y].son[!d];
	node[y].son[!d]	= x;
	update(x);
	update(x = y);
}

/**
 *  @brief  Updates field size.
 *  @param  x  The position of the node to be updated
 */
inline void idyllic::treap::update(int x)
{
	node[x].size = node[node[x].son[0]].size + node[node[x].son[1]].size + 1;
}
