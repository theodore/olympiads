#include <cstdio>
#include <algorithm>
#include <list>

#define pb push_back

const int Max_v = 100007;
const int Max_d = 300007;
int n;
int vtx[Max_v], vtx_next[Max_d], vtx_to[Max_d], vtx_id[Max_d], vtxcnt;

void Add_Vtx(int a, int b, int id)
{
    vtx_to[++vtxcnt] = b;
    vtx_next[vtxcnt] = vtx[a];
    vtx[a] = vtxcnt;
    vtx_id[vtxcnt] = id;
}

const int Max_e = 200007;
int start[Max_v], to[Max_e], next[Max_e], edge;
std::list<int> ofcolor[Max_v];
int color[Max_v];

void Add(int a, int b)
{
    to[++edge] = b;
    next[edge] = start[a];
    start[a] = edge;
}

void Init()
{
    scanf("%d", &n);
    for (int i = 1; i <= n - 2; i++) {
        int a, b, c, d;
        scanf("%d%d%d%d", &a, &b, &c, &d);
        color[i] = d;
        ofcolor[d].pb(i);
        if (a > b) std::swap(a, b);
        if (a > c) std::swap(a, c);
        if (b > c) std::swap(b, c);
        Add_Vtx(a, b, i);
        Add_Vtx(a, c, i);
        Add_Vtx(b, c, i);
    }
    for (int v = 1; v <= n; v++) {
        static int previd[Max_v];
        for (int e = vtx[v]; e; e = vtx_next[e]) {
            int t = vtx_to[e];
            if (previd[t]) {
                Add(previd[t], vtx_id[e]);
                Add(vtx_id[e], previd[t]);
            } else {
                previd[t] = vtx_id[e];
            }
        }
        for (int e = vtx[v]; e; e = vtx_next[e])
            previd[vtx_to[e]] = 0;
    }
}

const int Max_q = 100007;
int query[Max_q], qto[2 * Max_q], qnext[2 * Max_q], qcnt;

void Add_q(int a, int b)
{
    qto[++qcnt] = b;
    qnext[qcnt] = query[a];
    query[a] = qcnt;
}

int clow[Max_v];

void InitQ()
{
    for (int c = 1; c <= n; c++)
        if (!ofcolor[c].empty()) {
            int x = ofcolor[c].front();
            //clow[c] = x;
            for (ofcolor[c].pop_front(); !ofcolor[c].empty();
                    ofcolor[c].pop_front()) {
                int t = ofcolor[c].front();
                Add_q(x, t);
                Add_q(t, x);
            }
        }
}

int depth[Max_v];
int father[Max_v];
int low[Max_v];

int GetFather(int x)
{
    int f = x;
    while (father[f] != f)
        f = father[f];
    for (int i = x, t; i != f; i = t)
        t = father[i], father[i] = f;
    return f;
}

void Tarjan(int x, int f, int d)
{
    depth[x] = d;
    for (int e = start[x]; e; e = next[e])
        if (to[e] != f) {
            Tarjan(to[e], x, d + 1);
            father[to[e]] = x;
        }
    int c = color[x];
    if (!clow[c] || d < depth[clow[c]])
        clow[c] = x;
    for (int q = query[x]; q; q = qnext[q]) {
        int t = GetFather(qto[q]);
        if (depth[t] == 0)
            continue;
        if (depth[t] < depth[clow[c]])
            clow[c] = t;
    }
}

int DP(int x, int f)
{
    low[x] = clow[color[x]];
    int ret = 0;
    for (int e = start[x]; e; e = next[e])
        if (to[e] != f) {
            ret += DP(to[e], x);
            int t = low[to[e]];
            if (depth[t] < depth[low[x]])
                low[x] = t;
        }
#if DB & 1
    fprintf(stderr, "%d: %d, low %d, %d\n", x, ret + (low[x] == x), low[x], depth[low[x]]);
#endif
    return ret + (low[x] == x);
}

int Work()
{
    InitQ();
    n -= 2;
    for (int i = 1; i <= n; i++)
        father[i] = i;
    Tarjan(1, 0, 1);
    return DP(1, 0);
}

int main()
{
    Init();
    printf("%d\n", Work() - 1);
}
