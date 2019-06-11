#include <cstdio>
#include <cstring>
#include <algorithm>

struct sort_t
{
    char c;
    int p;
    bool operator<(const sort_t&) const;
};

const int maxn = 100003;
const int maxp = 19; // max 16
int n, p, pow;
char base[maxn * 2];
int rank[maxp][maxn];
sort_t arr[maxn];

bool sort_t::operator<(const sort_t& b) const
{
    return c < b.c;
}

const int maxm = maxn + 7;
int bucket[maxn], val[maxm], next[maxm], edge;
sort_t swp[maxn];

void add(int a, int b)
{
    val[++edge] = b;
    next[edge] = bucket[a];
    bucket[a] = edge;
}

void sort()
{
    edge = 0;
    for (int i = 0; i < n; ++i)
	add(rank[pow][(arr[i].p + (1 << pow)) % n], i);
    for (int i = n, j = n - 1; j >= 0; --j)
	for (int& x = bucket[j]; x; x = next[x])
	    swp[--i] = arr[val[x]];
    edge = 0;
    for (int i = 0; i < n; ++i)
	add(rank[pow][swp[i].p], i);
    for (int i = n, j = n - 1; j >= 0; --j)
	for (int& x = bucket[j]; x; x = next[x])
	    arr[--i] = swp[val[x]];
}

#ifdef DB
void db_o(int i)
{
    fprintf(stderr, "%d:\n", i);
    fprintf(stderr, "arr\n");
    for (int j = 0; j < n; ++j)
	fprintf(stderr, " (%c,%d)", arr[j].c, arr[j].p);
    fprintf(stderr, "\nrank\n");
    for (int j = 0; j < n; ++j)
	fprintf(stderr, " %d", rank[i][j]);
    fprintf(stderr, "\n\n");
}
#endif

int main()
{
    fread(base, 1, sizeof base, stdin);
    n = strlen(base);
    while (base[n] == '\n' || base[n] == '\r' || !base[n])
	--n;
    ++n;
    memcpy(base + n, base, n);
    for (p = 1; (1 << p) <= n; ++p)
	;
    for (int i = 0; i < n; ++i)
    {
	arr[i].c = base[i];
	arr[i].p = i;
    }
    std::sort(arr, arr + n);
    rank[0][arr[0].p] = 0;
    for (int j = 1, c = 0; j < n; ++j)
	rank[0][arr[j].p] = c += (arr[j].c != arr[j - 1].c);
#ifdef DB
    db_o(0);
#endif
    for (int i = 1; i <= p; ++i)
    {
	pow = i - 1;
	sort();
	rank[i][arr[0].p] = 0;
	for (int j = 1, c = 0; j < n; ++j)
	    rank[i][arr[j].p] = c += (rank[i - 1][arr[j].p] != rank[i - 1][arr[j - 1].p] ||
		    rank[i - 1][(arr[j].p + (1 << pow)) % n] != rank[i - 1][(arr[j - 1].p + (1 << pow)) % n]);
	if (rank[i][arr[n - 1].p] == n - 1)
	    break;
#ifdef DB
	db_o(i);
#endif
    }
#ifdef DB
    db_o(p);
#endif
    for (int i = 0; i < n; ++i)
	putchar(base[arr[i].p + n - 1]);
    putchar('\n');
}
