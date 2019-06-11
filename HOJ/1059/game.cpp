#include <cstdio>
#include <cstring>

const int maxn = 203;
const int maxm = 40003;
int n;
int start[maxn], to[maxm], next[maxm], edge;

void Add(int a, int b)
{
    to[++edge] = b;
    next[edge] = start[a];
    start[a] = edge;
}

void Init()
{
    memset(start, 0, sizeof start);
    edge = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) {
            int x;
            scanf("%d", &x);
            if (x)
                Add(i, j);
        }
}

int matched[maxn];
bool vis[maxn];

bool Find(int x)
{
    if (x == 0)
        return true;
    for (int e = start[x]; e; e = next[e])
        if (!vis[to[e]]) {
            vis[to[e]] = true;
            if (Find(matched[to[e]])) {
                matched[to[e]] = x;
                return true;
            }
        }
    return false;
}

bool Work()
{
    memset(matched, 0, sizeof matched);
    for (int i = 1; i <= n; ++i) {
        memset(vis, 0, sizeof vis);
        if (!Find(i))
            return false;
    }
    return true;
}

int main()
{
    int _;
    for (scanf("%d", &_); _--; ) {
        Init();
        puts(Work() ? "Yes" : "No");
    }
}
