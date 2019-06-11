#include <cstdio>
#include <cstring>

const int Max_v = 100007;
const int Max_e = Max_v;
int start[Max_v], to[Max_e], next[Max_e], edge;
int n, m;

void Add(int a, int b)
{
    to[++edge] = b;
    next[edge] = start[a];
    start[a] = edge;
}

int matched[Max_v];
bool vis[Max_v];

bool Find(int x)
{
    if (x == 0)
        return true;
    for (int e = start[x]; e; e = next[e])
        if (!vis[to[e]]){
            vis[to[e]] = true;
            if (Find(matched[to[e]])) {
                matched[to[e]] = x;
                return true;
            }
        }
    return false;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0, a, b; i < m; i++) {
        scanf("%d%d", &a, &b);
        Add(a, b);
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        memset(vis, 0, sizeof vis);
        ans += Find(i);
    }
    printf("%d\n", n - ans);
}
