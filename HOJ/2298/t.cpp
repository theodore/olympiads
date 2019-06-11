#include <cstdio>
const int N = 100001;
struct Seg { int l, r, cnt, next; };
bool cmp(const Seg &a, const Seg &b) { return a.r != b.r ? a.r < b.r : a.l > b.l; }
inline int max(int a, int b) { return a > b ? a : b; }
int n;
namespace SegSet
{
	Seg seg[N];
	int begin[N], nseg = 0;
	void add_seg(int l, int r, int cnt)
	{
		nseg ++;
		seg[nseg].next = begin[r];
		begin[r] = nseg;
		seg[nseg].l = l;
		seg[nseg].cnt = cnt;
	}
}
namespace Hash
{
	const int MOD = 500009; // prime
	Seg elem[N];
	int begin[MOD];
	int nelem = 0;
	void add(int l, int r)
	{
		int id = ((long long)(l - 1) * n + r - 1) % MOD;
		for (int now = begin[id]; now; now = elem[now].next)
			if (elem[now].l == l && elem[now].r == r)
			{
				elem[now].cnt ++;
				return;
			}
		nelem ++;
		elem[nelem].next = begin[id];
		begin[id] = nelem;
		elem[nelem].l = l, elem[nelem].r = r;
		elem[nelem].cnt = 1;
	}

	void extract_elem() 
	{
		for (int i = 1; i <= nelem; i ++)
		{
			int a = elem[i].cnt, b = elem[i].r - elem[i].l + 1;
			if (a > b) a = b;
			SegSet::add_seg(elem[i].l, elem[i].r, a);
		}
	}
}

int f[N];
int main()
{
	scanf("%d", &n);
	for (int l, r, i = 0; i < n; i ++)
	{
		scanf("%d%d", &r, &l);
		if (l + r + 1 > n) continue;
		Hash::add(l + 1, n - r);
	}
	Hash::extract_elem();
	for (int i = 1; i <= n; i ++)
	{
		f[i] = f[i - 1];
		for (int now = SegSet::begin[i]; now; now = SegSet::seg[now].next)
			f[i] = max(f[i], f[SegSet::seg[now].l - 1] + SegSet::seg[now].cnt);
	}
	printf("%d\n", n - f[n]);
	return 0;
}
