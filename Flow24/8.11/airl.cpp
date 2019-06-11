#include <climits>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <string>

#define OP(x) ((((x) - 1) ^ 1) + 1)

const int Max_v = 230;
const int Max_e = 20300;
int S, T;
int start[Max_v], to[Max_e], next[Max_e], cap[Max_e], fee[Max_e], edge;

void Add(int a, int b, int c, int d)
{
    to[++edge] = b;
    next[edge] = start[a];
    start[a] = edge;
    cap[edge] = c;
    fee[edge] = d;
}

void Ins(int a, int b, int c, int d)
{
    Add(a, b, c, d);
    Add(b, a, 0, -d);
}

int dist[Max_v], flow[Max_v], pre[Max_v];

bool SPFA()
{
    static bool in[Max_v];
    memset(dist, 0x3f, sizeof dist);
    dist[S] = 0;
    flow[S] = INT_MAX;
    std::queue<int> q;
    for (q.push(S); !q.empty(); ) {
        int x = q.front();
        q.pop();
        in[x] = false;
        for (int e = start[x], t; e; e = next[e])
            if (cap[e] && dist[x] + fee[e] < dist[t = to[e]]) {
                dist[t] = dist[x] + fee[e];
                flow[t] = std::min(flow[x], cap[e]);
                pre[t] = e;
                if (!in[t]) {
                    in[t] = true;
                    q.push(t);
                }
            }
    }
    return dist[T] != 0x3f3f3f3f;
}

int SSPA()
{
    int r = 0, f = 0;
    while (SPFA()) {
        f += flow[T];
        r += flow[T] * dist[T];
        for (int i = T; i != S; i = to[OP(pre[i])]) {
            cap[pre[i]] -= flow[T];
            cap[OP(pre[i])] += flow[T];
        }
    }
    if (f != 2) {
        puts("No Solution!");
        exit(0);
    } else {
        return -r;
    }
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    S = n + n + 1;
    T = S + 1;
    using std::string;
    using std::cin;
    std::map<string, int> id;
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        id[s] = i;
        Ins(i, i + n, 1, -1);
    }
    Ins(1, 1 + n, 1, 0);
    Ins(n, n + n, 1, 0);
    for (int i = 0; i < m; i++) {
        string a, b;
        cin >> a >> b;
        int x = id[a], y = id[b];
        if (x > y)
            std::swap(x, y);
        Ins(x + n, y, 2, 0);
    }
    Ins(S, 1, 2, 0);
    Ins(n + n, T, 2, 0);
    printf("%d\n", SSPA());
}
