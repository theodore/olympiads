#include <cstdio>
#include <cstring>

//const int maxn = 10003;
const int maxl = 53;
const int maxn = 500003;
const int maxs = 1000003;

class trie_t
{
public:
	static trie_t& instance();
	void init();
	int match(const char string[]);
#ifdef DB
	void db_output() const;
#endif
private:
	trie_t();
	void make_empty();
	void add(const char string[]);
	void set_pre();

	struct node_t
	{
		void init();
		int son[26];
		int pre;
		int word_cnt;
        bool matched;
	};

	node_t node[maxn];
	int node_cnt;
};

trie_t::trie_t()
{
}

void trie_t::node_t::init()
{
	memset(son, 0, sizeof son);
	pre = 0;
	word_cnt = 0;
	matched = false;
}

void trie_t::make_empty()
{
	node_cnt = 1;
}

void trie_t::init()
{
	make_empty();
	int n;
	scanf("%d", &n);
	node[1].init();
	char s[maxl];
	for (int i = 0; i < n; ++i)
	{
		scanf("%s", s);
		add(s);
	}
	set_pre();
}

void trie_t::add(const char s[])
{
	int j = 1;
	for (int n = int(strlen(s)), i = 0; i < n; ++i)
	{
		if (node[j].son[s[i] - 'a'])
			j = node[j].son[s[i] - 'a'];
		else
		{
			j = node[j].son[s[i] - 'a'] = ++node_cnt;
			node[j].init();
		}
	}
	++node[j].word_cnt;
}

void trie_t::set_pre()
{
	static int q[maxn], f[maxn], c[maxn]; // queue, father, content
	int head = 0, tail = 1;
	q[0] = 1;
	f[0] = 0;
	c[0] = 0;
	node[0].pre = 0;
	while (head != tail)
	{
		const int x = q[head];
		const int ct = c[head];
		int fa = f[head++];
		for (node[x].pre = 1, fa = node[fa].pre; fa; fa = node[fa].pre)
		{
			if (node[fa].son[ct])
			{
				node[x].pre = node[fa].son[ct];
				break;
			}
		}
		if (x == 1)
			node[x].pre = 0;
		for (int i = 0; i < 26; ++i)
			if (node[x].son[i])
			{
				q[tail] = node[x].son[i];
				f[tail] = x;
				c[tail++] = i;
			}
	}
	node[1].pre = 1;
}

int trie_t::match(const char s[])
{
	int ans = 0;
	for (int n = int(strlen(s)), i = 0, j = 1; i < n; ++i)
	{
#ifdef DB
		fprintf(stderr, "i = %d, j = %d\n", i, j);
#endif
		do
		{
			if (node[j].son[s[i] - 'a'])
			{
				j = node[j].son[s[i] - 'a'];
				if (node[j].word_cnt && !node[j].matched)
				{
					for (int k = j; k != 1; k = node[k].pre)
					{
						ans += !node[k].matched * node[k].word_cnt;
						node[k].matched = true;
					}
#ifdef DB
					fprintf(stderr, "matched\n");
#endif
				}
				break;
			}
			else
			{
				j = node[j].pre; // node[1].pre == 1
#if 0
				if (node[j].is_word)
				{
					ans += !node[j].matched;
					node[j].matched = true;
#ifdef DB
					fprintf(stderr, "j to %d\n", j);
					fprintf(stderr, "matched\n");
#endif
				}
#endif
			}
		} while (j != 1 || node[j].son[s[i] - 'a']);
	}
	return ans;
}

trie_t& trie_t::instance()
{
	static trie_t ret;
	return ret;
}

int main()
{
	int _;
	trie_t& trie = trie_t::instance();
	for (scanf("%d", &_); _--; )
	{
		trie.init();
#ifdef DB
		fprintf(stderr, "init finished\n");
		trie.db_output();
#endif
		static char s[maxs];
		scanf("%s", s);
		printf("%d\n", trie.match(s));
	}
#ifdef DB
	trie.db_output();
#endif
}

#ifdef DB
void trie_t::db_output() const
{
	for (int i = 1; i <= node_cnt; ++i)
	{
		printf("node %d:", i);
		printf("  pre = %d", node[i].pre);
		printf("  matched = %d", node[i].matched);
		printf("  word_cnt = %d\n", node[i].word_cnt);
		for (int j = 0; j < 26; ++j)
			if (node[i].son[j])
			{
				printf("  son %c = %d\n", 'a' + j, node[i].son[j]);
			}
		printf("\n");
	}
}
#endif
