#include <cstdio>
#include <stack>

const int Max_v = 100003;
const int Max_e = 400007;
int n;
int start[Max_v], edgecnt[Max_v], to[Max_e], next[Max_e], edge;
bool vis[Max_v];
std::stack<int> S;

void Add(int a, int b)
{
    to[++edge] = b;
    next[edge] = start[a];
    start[a] = edge;
    edgecnt[a]++;
}

void Work(int x)
{
    vis[x] = true;
    S.push(x);
    for (int e = start[x]; e; e = next[e])
        if (!vis[to[e]])
            Work(to[e]);
}

bool Check()
{
    for (int i = 1; i <= n; i++)
        if (!vis[i]) {
            Work(i);
            int s = S.size(), c = 0;
            if (s < 3)
                return false;
            while (!S.empty())
                c += edgecnt[S.top()], S.pop();
            if (c / 2 < s)
                return false;
        }
    return true;
}

int main()
{
    int m;
    scanf("%d%d", &n, &m);
    for (int i = 0, a, b; i < m; i++) {
        scanf("%d%d", &a, &b);
        Add(a, b);
        Add(b, a);
    }
    puts(Check() ? "TAK" : "NIE");
}
