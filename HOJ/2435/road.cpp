#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

const int Max_v = 1000007;
const int Max_e = 2000007;
int n;
int start[Max_v], to[Max_e], next[Max_e], leng[Max_e], edge;
int size[Max_v];

void Add(int a, int b, int c)
{
    to[++edge] = b;
    next[edge] = start[a];
    start[a] = edge;
    leng[edge] = c;
}

ll Answer()
{
    static int Q[Max_v], head, tail;
    static bool vis[Max_v];
    vis[1] = true;
    for (Q[0] = 1, head = 0, tail = 1; head != tail; ) {
        int x = Q[head++];
        for (int e = start[x], t; e; e = next[e])
            if (!vis[t = to[e]]) {
                vis[t] = true;
                Q[tail++] = t;
            }
    }
    ll r = 0;
    while (--tail) {
        int x = Q[tail];
        size[x] = 1;
        vis[x] = false;
        int z;
        for (int e = start[x], t; e; e = next[e])
            if (!vis[t = to[e]])
                size[x] += size[t];
            else
                z = e;
        r += (long long)abs(n - size[x] - size[x]) * leng[z];
    }
    return r;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1, a, b, c; i < n; i++) {
        scanf("%d%d%d", &a, &b, &c);
        Add(a, b, c);
        Add(b, a, c);
    }
    printf("%lld\n", Answer());
}
