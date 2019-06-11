#define STDIO
#define INPUT   "p1098.in"
#define OUTPUT  "p1098.out"
 
#include <cstdio>
#include <algorithm>
using namespace std;
 
namespace Solve
{
    const int NVTX_MAX = 100005, NARC_MAX = (2000005 + NVTX_MAX) * 2;
    struct Arc
    {
        int tvtx, next;
    };
    Arc arc[NARC_MAX], arc_orig[NARC_MAX];
    int graph[NVTX_MAX], graph_orig[NVTX_MAX],
        nvtx, narc, narc_orig;
 
    void insert_arc_orig(int u, int v);
 
    int next[NVTX_MAX];
    // next[i]: such least j that j >= i and !visited[j]
    int get_tail(int v0);
 
    int ans[NVTX_MAX], nans;
    void work();
 
    void solve(FILE *fin, FILE *fout);
}
 
void Solve::solve(FILE *fin, FILE *fout)
{
    const int BUFFER_LEN = 1024 * 1024 * 5;
    static char buffer[BUFFER_LEN];
    char *ptr = buffer, *buf_end = ptr + 1;
#define PTR_NEXT() \
    { \
        ptr ++; \
        if (ptr == buf_end) \
        { \
            ptr = buffer; \
            buf_end = buffer + fread(buffer, 1, BUFFER_LEN, fin); \
        } \
    }
#define READ_INT(_x_) \
    { \
        while ((*ptr < '0' || *ptr > '9') && *ptr != '-') \
            PTR_NEXT(); \
        bool _nega_ = false; \
        if (*ptr == '-') \
        { \
            _nega_ = true; \
            PTR_NEXT(); \
        } \
        int register _n_ = 0; \
        while (*ptr >= '0' && *ptr <= '9') \
        { \
            _n_ = _n_ * 10 + *ptr - '0'; \
            PTR_NEXT(); \
        } \
        if (_nega_) \
            _n_ = - _n_; \
        (_x_) = (_n_); \
    }
#define READ_UP_CHAR(_c_) \
    { \
        while (*ptr < 'A' || *ptr > 'Z') \
            PTR_NEXT(); \
        (_c_) = *ptr; \
        PTR_NEXT(); \
    }
    PTR_NEXT();
 
    int m;
    READ_INT(nvtx);
    READ_INT(m);
    while (m --)
    {
        int a, b;
        READ_INT(a); a --;
        READ_INT(b); b --;
        insert_arc_orig(a, b);
        insert_arc_orig(b, a);
    }
    for (int i = 0; i < nvtx; i ++)
        insert_arc_orig(i, i);
    work();
    fprintf(fout, "%d\n", nans);
    for (int i = 0; i < nans; i ++)
        fprintf(fout, "%d ", ans[i]);
    fprintf(fout, "\n");
 
#undef PTR_NEXT
#undef READ_INT
#undef READ_UP_CHAR
}
 
void Solve::work()
{
    for (int i = nvtx - 1; i >= 0; i --)
    {
        next[i] = i;
        for (int register s, j = graph_orig[i]; j; j = arc_orig[j].next)
        {
            s = arc_orig[j].tvtx;
            narc ++;
            arc[narc].tvtx = i;
            arc[narc].next = graph[s];
            graph[s] = narc;
        }
    }
    next[nvtx] = nvtx;
    arc[0].tvtx = nvtx;
    arc[0].next = -1;
    static int queue[NVTX_MAX];
    for (int i = 0; i < nvtx; i ++)
        if (next[i] == i)
        {
            next[i] = get_tail(i + 1);
            int qh = 0, qt = 1;
            queue[0] = i;
            while (qh < qt)
            {
                int v0 = queue[qh ++], prev = 0;
                for (int j = graph[v0]; j != -1; j = arc[j].next)
                {
                    int register a = prev + 1, b = arc[j].tvtx - 1;
                    if (a <= b)
                    {
                        for (int register k = a; ; k ++)
                        {
                            k = get_tail(k);
                            if (k > b)
                                break;
                            queue[qt ++] = k;
                            next[k] = get_tail(k + 1);
                        }
                    }
                    prev = arc[j].tvtx;
                }
            }
            ans[nans ++] = qt;
        }
    sort(ans, ans + nans);
}
 
int Solve::get_tail(int v0)
{
    if (next[v0] == v0)
        return v0;
    return next[v0] = get_tail(next[v0]);
}
 
void Solve::insert_arc_orig(int u, int v)
{
    narc_orig ++;
    arc_orig[narc_orig].tvtx = v;
    arc_orig[narc_orig].next = graph_orig[u];
    graph_orig[u] = narc_orig;
}
 
int main()
{
#ifdef STDIO
    Solve::solve(stdin, stdout);
#else
    FILE *fin = fopen(INPUT, "r"),
         *fout = fopen(OUTPUT, "w");
    Solve::solve(fin, fout);
    fclose(fin);
    fclose(fout);
#endif
}
