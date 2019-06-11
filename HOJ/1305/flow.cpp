#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>

#define OP(x) ((((x) - 1) ^ 1) + 1)
#define UPN(a, b) a = std::min(a, b)

const int Max_n = 53;
const int Max_v = 333;
const int Max_e = 5666;
int S, T;
int start[Max_v], to[Max_e], next[Max_e], cap[Max_e], edge;

void Add(int a, int b, int c)
{
    to[++edge] = b;
    next[edge] = start[a];
    start[a] = edge;
    cap[edge] = c;
}

void Ins(int a, int b, int c)
{
    Add(a, b, c);
    Add(b, a, 0);
}

unsigned dist[Max_v];

bool BFS()
{
    memset(dist, 0xff, sizeof dist);
    dist[S] = 0;
    std::queue<int> Q;
    for (Q.push(S); !Q.empty(); ) {
        int x = Q.front();
        Q.pop();
        for (int e = start[x], t; e; e = next[e])
            if (cap[e] && dist[x] + 1 < dist[t = to[e]]) {
                dist[t] = dist[x] + 1;
                if (t == T)
                    return true;
                Q.push(t);
            }
    }
    return false;
}

int Flow(int x, int f)
{
    if (x == T)
        return f;
    int r = 0;
    for (int e = start[x]; e && f; e = next[e])
        if (cap[e] && dist[x] + 1 == dist[to[e]]) {
            int t = Flow(to[e], std::min(cap[e], f));
            r += t;
            f -= t;
            cap[e] -= t;
            cap[OP(e)] += t;
        }
    if (!r)
        dist[x] = UINT_MAX;
    return r;
}

int Dinics()
{
    int r = 0;
    while (BFS())
        r += Flow(S, INT_MAX);
    return r;
}

int main()
{
    int n, k;
    char s[Max_n][Max_n];
    scanf("%d%d", &n, &k);
    S = 6 * n;
    T = S + 1;
    for (int i = 0; i < n; i++)
        Ins(S, i * 3, 0);
    for (int i = 0; i < n; i++)
        Ins((i + n) * 3, T, 0);
    for (int i = 0; i < n; i++) {
        Ins(i * 3, i * 3 + 1, 10000);
        Ins(i * 3, i * 3 + 2, k);
    }
    for (int i = n; i < 2 * n; i++) {
        Ins(i * 3 + 1, i * 3, 10000);
        Ins(i * 3 + 2, i * 3, k);
    }
    for (int i = 0; i < n; i++) {
        scanf("%s", s[i]);
        for (int j = 0; j < n; j++)
            if (s[i][j] == 'Y')
                Ins(i * 3 + 1, (j + n) * 3 + 1, 1);
            else
                Ins(i * 3 + 2, (j + n) * 3 + 2, 1);
    }
    for (int f = 1; ; f++) {
        for (int i = 0; i < 2 * n; i++)
            cap[i * 2 + 1]++;
        if (Dinics() != n) {
            printf("%d\n", f - 1);
            return 0;
        }
    }
}
