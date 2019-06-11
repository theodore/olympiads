/*
PROB:cowxor
LANG:C++
*/
// ERR: son[] is too small
#include <cstdio>
#include <cassert>

//#define ARR_SIZE 2100010
#define ARR_SIZE 700010

namespace janitor
{
	void input();
	void answer();

	class trie_t
	{
	 public:
		 trie_t();
		 ~trie_t();
		// Returns the position of the best choice for the parameter
		int insert(int);
	 private:
		struct node_t
		{
			//int son[2];
			int son0 : 23;
			int son1 : 23;
			int pos : 18; // The position in num[], if it's a leaf
		};

		int cnt;
		node_t node[ARR_SIZE];
	};

	const int N(100010);
	int n, num[N];
	trie_t trie;
}

janitor::trie_t::trie_t()
	: cnt(22)
{
	for (int i = 0; i < 21; ++i)
	{
		//node[i].son[0] = i + 1;
		//node[i].son[1] = 0;
		node[i].son0 = i + 1;
		node[i].son1 = 0;
		node[i].pos = -1;
	}
	node[21].pos = 0;
#ifdef DB
	fprintf(stderr, "size = %d\n", sizeof(cnt));
#endif
}

janitor::trie_t::~trie_t()
{
}

int janitor::trie_t::insert(int index)
{
	const int & x = num[index];
	int now(0), ret(0), t;
	for (int sh = 20; sh >= 0; --sh)
	/*
	{
		static int dir;
		dir = (x & (1 << sh)) ? 1 : 0;
		if (!node[now].son[dir])
		{
			assert(cnt > 0);
#ifdef DB
			printf("cnt = %d\n", cnt);
#endif
			t = node[now].son[dir] = cnt++;
			node[t].son[0] = node[t].son[1] = 0;
			node[t].pos = -1;
		}
		now = node[now].son[dir];
		if (node[ret].son[!dir])
			ret = node[ret].son[!dir];
		else
		{
			assert(node[ret].son[dir]);
			ret = node[ret].son[dir];
		}
		assert(now != 0);
		assert(ret != 0);
	}
	/*/
	{
		//dir = (x & (1 << sh)) ? 1 : 0;
		if (x & (1 << sh))
		{
			if (!node[now].son1)
			{
				assert(cnt > 0);
				t = node[now].son1 = cnt++;
				node[t].son0 = node[t].son1 = 0;
				node[t].pos = -1;
			}
			now = node[now].son1;
			if (node[ret].son0)
				ret = node[ret].son0;
			else
			{
				assert(node[ret].son1);
				ret = node[ret].son1;
			}
			assert(now != 0);
			assert(ret != 0);
		}
		else
		{
			if (!node[now].son0)
			{
				assert(cnt > 0);
				t = node[now].son0 = cnt++;
				node[t].son0 = node[t].son1 = 0;
				node[t].pos = -1;
			}
			now = node[now].son0;
			if (node[ret].son1)
				ret = node[ret].son1;
			else
			{
				assert(node[ret].son0);
				ret = node[ret].son0;
			}
			assert(now != 0);
			assert(ret != 0);
		}
	}
	//*/
	assert(node[ret].pos != -1);
	node[now].pos = index;
	return node[ret].pos;
}

void janitor::answer()
{
	int l(1), r(1), t;
	for (int i = 1; i <= n; ++i)
	{
		t = trie.insert(i);
#ifdef DB
		printf("insert %d, best is %d\n", i, t);
#endif
		if ((num[l-1] ^ num[r]) < (num[t] ^ num[i]))
		{
			l = t + 1;
			r = i;
		}
	}
	printf("%d %d %d\n", num[l-1] ^ num[r], l, r);
}

void janitor::input()
{
	scanf("%d", &n);
	num[0] = 0;
	for (int i = 1; i <= n; ++i)
	{
		scanf("%d", &num[i]);
		num[i] ^= num[i-1];
	}
}

int main()
{
	freopen("cowxor.in", "r", stdin);
#ifndef GDB
	freopen("cowxor.out", "w", stdout);
#endif
	janitor::input();
	janitor::answer();
	return 0;
}
