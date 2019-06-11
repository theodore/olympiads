#include <cstdio>
#include <cstdlib>

const int maxn = 100007;
const int maxm = 200007;
int n;
int start[maxn], to[maxm], next[maxm], edge;
int color[maxn];
int father[maxn], depth[maxn];

void add(const int a, const int b)
{
    to[++edge] = b;
    next[edge] = start[a];
    start[a] = edge;
}

void change(int a, int b, int c)
{
    while (a != b)
	if (depth[a] < depth[b])
	    color[b] = c, b = father[b];
	else
	    color[a] = c, a = father[a];
    color[a] = c;
}

int ask(int pa, int pb)
{
    int a[] = {pa, 0, 0};
    int b[] = {pb, 0, 0};
    int* p = a;
    while (a[0] != b[0])
    {
	p = depth[a[0]] < depth[b[0]] ? b : a;
	if (p[2] != color[p[0]])
	    p[2] = color[p[0]], ++p[1];
	p[0] = father[p[0]];
    }
    if (p[2] != color[p[0]])
	p[2] = color[p[0]], ++p[1];
    return a[1] + b[1] - (a[2] == b[2]);
}

void mktree(const int x, const int f)
{
    father[x] = f;
    depth[x] = depth[f] + 1;
    for (int e = start[x]; e; e = next[e])
	if (to[e] != f)
	    mktree(to[e], x);
}

int main()
{
    int _;
    scanf("%d%d", &n, &_);
    srand(n * _);
    for (int i = 1; i <= n; ++i)
	scanf("%d", color + i);
    int a, b, c;
    for (int i = 1; i < n; ++i)
    {
	scanf("%d%d", &a, &b);
	add(a, b);
	add(b, a);
    }
    int root = rand() % n + 1;
    mktree(root, 0);
    for (char s[3]; _--; )
	if (scanf("%s%d%d%d", s, &a, &b, &c) == 3)
	    printf("%d\n", ask(a, b));
	else
	    change(a, b, c);
}
