#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

const int N = 20005;

struct Tnode {
	Tnode *lch, *rch;
	int size, count, RP;
	int key;
} nodebuf[N * 30];
int cnodebuf;
int h[N], g[N], b[N];
int lID, rID, lVal, rVal, n, m, arg;
long long ans;
Tnode *rt[N << 2], *null;

inline void update(Tnode *t)
{
	t->size = t->lch->size + t->rch->size + t->count;
}

void zag(Tnode *(&x))
{
	Tnode *y = x->lch; x->lch = y->rch; y->rch = x;
	update(x);
	update(y);
	x = y;
}

void zig(Tnode *(&x))
{
	Tnode *y = x->rch; x->rch = y->lch; y->lch = x;
	update(x);
	update(y);
	x = y;
}

void treap_modify(Tnode *(&t), int val, int c)
{
	if (t == null) {
		t = nodebuf + cnodebuf++;
		t->size = t->count = c;
		t->key = val;
		t->lch = t->rch = null;
		t->RP = (rand() << 15) + rand();
		return;
	}
	t->size += c;
	if (val == t->key)
		t->count += c;
	else if (val < t->key) {
		treap_modify(t->lch, val, c);
		if (t->lch->RP < t->RP) zag(t);
	} else {
		treap_modify(t->rch, val, c);
		if (t->rch->RP < t->RP) zig(t);
	}
}

Tnode *build(int l, int r)
{
	Tnode *ret = null;
	for (int i = l; i <= r; ++i) treap_modify(ret, g[i], 1);
	return ret;
}

int treap_getless(Tnode *t, int lim)
{
	if (t == null) return 0;
	if (t->key <= lim) 
		return t->count + t->lch->size + treap_getless(t->rch, lim);
	else 
		return treap_getless(t->lch, lim);
}

int treap_getexact(Tnode *t, int val)
{
	while (t != null && t->key != val)
		if (val < t->key) t = t->lch; else t = t->rch;
	if (t == null) return 0; else return t->count;
}

void merge(int t, int l, int r)
{
	if (l == r) {
		rt[t] = build(l, r);
		return;
	}
	int mid = l + r >> 1;
	merge(t * 2 + 1, l, mid);
	merge(t * 2 + 2, mid + 1, r);
	int p, q = mid + 1;
	for (int i = l; i <= mid; ++i) {
		while (q <= r && g[q] < g[i]) ++q;
		ans += q - mid - 1;
	}
	int tot = 0;
	p = l; q = mid + 1;
	while (tot < r - l + 1) {
		bool flag;
		if (p == mid + 1) flag = true; else
		if (q == r + 1) flag = false; else
		if (g[p] < g[q]) flag = false; else flag = true;
		if (flag)
			b[tot++] = g[q++];
		else
			b[tot++] = g[p++];
	}
	memcpy(g + l, b, tot * sizeof(int));
	rt[t] = build(l, r);
}

int query(int t, int l, int r, int p1, int p2)
{
	if (p1 <= l && r <= p2) 
		return 2 * (treap_getless(rt[t], rVal - 1) - treap_getless(rt[t], lVal)) + 
				treap_getexact(rt[t], lVal) + treap_getexact(rt[t], rVal);
	int mid = l + r >> 1;
	int ret = 0;
	if (p1 <= mid) ret += query(t * 2 + 1, l, mid, p1, p2);
	if (mid < p2) ret += query(t * 2 + 2, mid + 1, r, p1, p2);
	return ret;
}

void modifyL(int t, int l, int r)
{
	treap_modify(rt[t], h[lID], -1);
	treap_modify(rt[t], h[rID], 1);
	if (l == r) return;
	int mid = l + r >> 1;
	if (lID <= mid) modifyL(t * 2 + 1, l, mid); else modifyL(t * 2 + 2, mid + 1, r);
}

void modifyR(int t, int l, int r)
{
	treap_modify(rt[t], h[rID], -1);
	treap_modify(rt[t], h[lID], 1);
	if (l == r) return;
	int mid = l + r >> 1;
	if (rID <= mid) modifyR(t * 2 + 1, l, mid); else modifyR(t * 2 + 2, mid + 1, r);
}

int main()
{
	null = nodebuf + cnodebuf++;
	null->count = null->size = 0;
	null->lch = null->rch = null;
	null->RP = 0x7fffffff;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) scanf("%d", &h[i]);
	memcpy(g, h, sizeof(g));
	merge(0, 1, n);
	scanf("%d", &m);
	printf("%lld\n", ans);
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d", &lID, &rID);
		if (lID > rID) swap(lID, rID);
		if (h[lID] == h[rID]) {
			printf("%lld\n", ans);
			continue;
		}
		if (h[lID] < h[rID]) {
			++ans; 
			arg = 1;
		} else {
			--ans;
			arg = -1;
		}
		modifyL(0, 1, n);
		modifyR(0, 1, n);
		swap(h[lID], h[rID]);
		if (lID + 1 == rID) {
			printf("%lld\n", ans);
			continue;
		}
		lVal = h[lID], rVal = h[rID];
		if (lVal > rVal) swap(lVal, rVal);
		ans += arg * query(0, 1, n, lID + 1, rID - 1);
		printf("%lld\n", ans);
	}
	fclose(stdout);
}
