#include <cstdio>
#include <algorithm>

#define ls(x) ((x) << 1)
#define rs(x) (ls(x) + 1)
#define L (l ^ 1)
#define R (r ^ 1)

typedef bool Node_t[3][2];

const int maxn = 100007;
const int maxN = (1 << 18);
int N;
bool con[maxn][3];
Node_t tree[maxN];

void update(int x)
{
#if DB >= 2
    fprintf(stderr, " %d\n", x);
#endif
    Node_t& z = tree[x + N];
    // dist = 1
    z[2][0] = con[x][0];
    z[2][1] = con[x + 1][0];
    z[0][0] = con[x][1];
    z[1][1] = con[x][2];
    // dist = 2
    z[0][1] = (z[0][0] && z[2][1]) || (z[2][0] && z[1][1]);
    z[1][0] = (z[2][0] && z[0][0]) || (z[1][1] && z[2][1]);
    // dist = 3
    z[0][0] |= z[0][1] && z[2][1];
    z[1][1] |= z[1][0] && z[2][1];
    z[2][0] |= z[0][1] && z[1][1];
    z[2][1] |= z[1][0] && z[1][1];
    for (x = (x + N) >> 1; x; x >>= 1)
    {
	Node_t& v = tree[x];
	Node_t& a = tree[ls(x)];
	Node_t& b = tree[rs(x)];
	for (int i = 0; i < 2; ++i)
	    for (int j = 0; j < 2; ++j)
	    {
		v[i][j] = false;
		for (int k = 0; k < 2; ++k)
		    v[i][j] |= a[i][k] && b[k][j];
	    }
	v[2][0] = a[2][0] || (a[0][0] && a[1][1] && b[2][0]);
	v[2][1] = b[2][1] || (b[0][0] && b[1][1] && a[2][1]);
    }
}

bool askl(int r)
{
    for (r += N; r; r >>= 1)
	if (r & 1)
	{
	    if (tree[R][2][1])
		return true;
	    if (!tree[R][0][0] || !tree[R][1][1])
		return false;
	}
    return false;
}

bool askr(int l)
{
    for (l += N; l; l >>= 1)
	if (~l & 1)
	{
	    if (tree[L][2][0])
		return true;
	    if (!tree[L][0][0] || !tree[L][1][1])
		return false;
	}
    return false;
}

bool ask(int l, const int a, int r, const int b)
{
    bool lc[2] = {}, rc[2] = {}, t[2];
    lc[a] = rc[b] = true;
    lc[a ^ 1] = askl(l);
    rc[b ^ 1] = askr(r - 1);
    for (l += N - 1, r += N; l ^ r ^ 1; l >>= 1, r >>= 1)
    {
	if (~l & 1)
	{
	    for (int i = 0; i < 2; ++i)
	    {
		t[i] = false;
		for (int j = 0; j < 2; ++j)
		    t[i] |= lc[j] && tree[L][j][i];
	    }
	    lc[0] = t[0];
	    lc[1] = t[1];
	}
	if (r & 1)
	{
	    for (int i = 0; i < 2; ++i)
	    {
		t[i] = false;
		for (int j = 0; j < 2; ++j)
		    t[i] |= tree[R][i][j] && rc[j];
	    }
	    rc[0] = t[0];
	    rc[1] = t[1];
	}
    }
    return (lc[0] && rc[0]) || (lc[1] && rc[1]);
}

int main()
{
    char s[11];
    int n, a, b, c, d;
    scanf("%d", &n);
    for (N = 4; N < n + 2; N <<= 1)
	;
    while (scanf("%s%d%d%d%d", s, &b, &a, &d, &c) != 1)
    {
#if DB >= 1
	fprintf(stderr, "%s %d %d %d %d\n", s, b, a, d, c);
#endif
	switch (s[0])
	{
	case 'O':
	case 'C':
	    if (a == c)
	    {
		con[a][0] = s[0] == 'O';
		update(a);
		if (a > 1)
		    update(a - 1);
	    }
	    else
	    {
		a = std::min(a, c);
		con[a][b] = s[0] == 'O';
		update(a);
	    }
	    break;
	default:
	    if (a > c)
	    {
		std::swap(a, c);
		std::swap(b, d);
	    }
	    printf(ask(a, b - 1, c, d - 1) ? "Y\n" : "N\n");
	}
    }
}
