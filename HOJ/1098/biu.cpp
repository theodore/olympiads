#include <cctype>
#include <cstdio>
#include <algorithm>
#include <list>
#include <queue>

#define pb push_back

const int Max_v = 100003;
const int Max_e = 4000003;
int n, m;
int start[Max_v], to[Max_e], next[Max_e], edge;
int ans[Max_v];

inline int getint()
{
    int c;
    while (!isdigit(c = getchar()))
        ;
    int x = c - '0';
    while (isdigit(c = getchar()))
        x = x * 10 + c - '0';
    return x;
}

void Add(int a, int b)
{
    to[++edge] = b;
    next[edge] = start[a];
    start[a] = edge;
}

void Input()
{
    n = getint();
    m = getint();
    for (int i = 0, a, b; i < m; i++) {
        a = getint();
        b = getint();
        Add(a, b);
        Add(b, a);
    }
}

int Work()
{
    std::list<int> L;
    std::queue<int> Q;
    static int vis[Max_v];
    for (int i = 1; i <= n; i++)
        L.pb(i);
    int cnt = -1, now = 0;
    while (cnt++, !L.empty()) {
        int x = L.front();
        L.pop_front();
        Q.push(x);
        ans[cnt] = now;
        while (now++, !Q.empty()) {
            x = Q.front();
            Q.pop();
            for (int e = start[x]; e; e = next[e])
                vis[to[e]] = now;
            for (std::list<int>::iterator i = L.begin(); i != L.end(); )
                if (vis[*i] != now) {
                    Q.push(*i);
                    i = L.erase(i);
                } else {
                    i++;
                }
        }
        ans[cnt] = now - ans[cnt] - 1;
    }
    return cnt;
}

int main()
{
    Input();
    int t;
    printf("%d\n", t = Work());
    std::sort(ans, ans + t);
    for (int i = 0; i < t - 1; i++)
        printf("%d ", ans[i]);
    printf("%d\n", ans[t - 1]);
}
