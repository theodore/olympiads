#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
 
const int MAXN = 500;
const int MAXM = MAXN;
const int MAXVTX = (MAXN + 1) * (MAXM + 1);
const int MAXE = MAXN * MAXM * 2;
const int MAXPE = MAXE * 2;
 
int N, M, S, T, ecnt;
 
struct Edge {
 
    int to, c;
    Edge *next;
 
} edges[MAXPE + 1], *head[MAXVTX + 1];
 
void add_edge(int st, int ed, int c) {
 
    edges[++ecnt].next = head[st];
    head[st] = edges + ecnt;
    edges[ecnt].to = ed;
    edges[ecnt].c = c;
}
 
void add_pair(int st, int ed, int c) {
 
//    printf("%d %d %d\n", st, ed, c);
    add_edge(st, ed, c);
    add_edge(ed, st, c);
}
 
int get_id(int x, int y) {
 
    return x * (M + 1) + y;
}
 
void pre_work() {
 
    scanf("%d %d", &N, &M);
    static char buff[MAXM + 3];
    for (int i = 0; i < N; i++)
    {
        scanf("%s", buff);
        for (int j = 0; j < M; j++)
        {
            bool lb, lt;
            lt = buff[j] == '\\';
            lb = lt ^ 1;
            add_pair(get_id(i, j), get_id(i + 1, j + 1), lb);
            add_pair(get_id(i + 1, j) ,get_id(i, j + 1), lt);
        }
    }
     
    S = get_id(0, 0), T = get_id(N, M);
}
 
struct Pair {
 
    int key, v;
    Pair() {}
    Pair(int _key, int _v) {
 
        key = _key, v = _v;
    }
 
    bool operator<(const Pair &b) const {
 
        return key > b.key;
    }
};
 
void work() {
 
    std::priority_queue<Pair> heap;
    static int dist[MAXVTX + 1];
    static bool mask[MAXVTX + 1];
    memset(dist, 0x3f, sizeof(dist));
    dist[S] = 0;
    heap.push(Pair(0, S));
    while (!heap.empty())
    {
        Pair t;
        int u = t.v, v, td;
        mask[u] = 1;
        for (Edge *ptr = head[u]; ptr; ptr = ptr -> next)
            if ((td = dist[u] + ptr -> c) < dist[v = ptr -> to])
            {
                heap.push(Pair(td, v));
                dist[v] = td;
            }
 
        if (u == T)
        {
            printf("%d\n", dist[T]);
            return;
        }
        while (!heap.empty() && mask[(t = heap.top()).v]) heap.pop();
    }
    printf("NO SOLUTION\n");
}
 
int main() {
 
    pre_work();
    work();
 
    return 0;
}
