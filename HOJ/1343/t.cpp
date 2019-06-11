/**************************************************************
    Problem: 1343
    User: zxytim
    Language: C++
    Result: Accepted
    Time:60 ms
    Memory:1092 kb
****************************************************************/
 
#include <cstdio>
#include <cstdlib>
#include <cstring>
 
#define MAX_RECT 100
#define MAX_POINT MAX_RECT * 4
 
#define MAXN MAX_POINT * 4 * 2 // two layers
#define MAXM MAXN * MAX_RECT * 3 * 2
 
//#define P(x, flag) (((x) << 1) + (flag) - 1)
int P(int x, int flag)
{
    return (x << 1) + flag - 1;
}
 
#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MAX(x, y) ((x) > (y) ? (x) : (y))
 
using namespace std;
 
class Point
{
    public:
        int x, y;
        Point(int _x, int _y):x(_x),y(_y){}
        Point(){}
        void set(int _x, int _y)
        {
            x = _x, y = _y;
        }
        inline friend bool operator == (const Point &a, const Point &b)
        {
            return a.x == b.x && a.y == b.y;
        }
};
 
class Rect
{
    public:
        Point a, b;
};
Rect rect[MAX_RECT + 1];
int nrect;
void Init()
{
    scanf("%d", &nrect);
    for (int i = 1; i <= nrect; i ++)
        scanf("%d%d%d%d", &rect[i].a.x, &rect[i].a.y, &rect[i].b.x, &rect[i].b.y);
}
 
Point p[MAX_POINT + 1];
 
int Count = 0;
int begin[MAXN + 1], end[MAXM + 1], next[MAXM + 1], cost[MAXM + 1];
void AddEdge(int a, int b, int v) // Add both directions
{
    Count ++;
    next[Count] = begin[a];
    begin[a] = Count;
    end[Count] = b;
    cost[Count] = v;
 
    Count ++;
    next[Count] = begin[b];
    begin[b] = Count;
    end[Count] = a;
    cost[Count] = v;
}
 
int npoint;
int n;
 
#define CrossRect(a, b, c, d) (a.x < d.x && b.x > c.x && a.y < d.y && b.y > c.y)
#define Cross(a, b, x, y) (((a.x > x) ^ (b.x > x)) && a.y < y && b.y < y)
 
int Dist(const Point &a, const Point &b)
{
    int x = a.x - b.x, y = a.y - b.y;
    if (x < 0)
        x = -x;
    if (y < 0)
        y = -y;
    return x + y;
}
 
void AddPoint(const Point &a)
{
    bool boo = true;
    for (int i = 1; i <= nrect; i ++)
        if (a.x > rect[i].a.x && a.x < rect[i].b.x && a.y > rect[i].a.y && a.y < rect[i].b.y)
        {
            boo = false;
            break;
        }
    if (boo)
        p[++ npoint] = a;
}
 
void Part()
{
    double x = (rect[1].a.x + rect[1].b.x) * 0.5;
    double y = (rect[1].a.y + rect[1].b.y) * 0.5;
    Point a, b;
    for (int i = 1; i <= npoint; i ++)
        for (int j = i + 1; j <= npoint; j ++)
        {
            a.set(MIN(p[i].x, p[j].x), MIN(p[i].y, p[j].y));
            b.set(MAX(p[i].x, p[j].x), MAX(p[i].y, p[j].y));
            bool boo = true;
            for (int k = 1; k <= nrect; k ++)
                if (CrossRect(a, b, rect[k].a, rect[k].b))
                {
                    boo = false;
                    break;
                }
            if (boo)
            {
                int flagi = 0, flagj = 0;
                if (Cross(a, b, x, y))
                    flagj = 1;
                int d = Dist(p[i], p[j]);
                AddEdge(P(i, flagi), P(j, flagj), d);
                AddEdge(P(i, !flagi), P(j, !flagj), d);
            }
        }
}
 
void BuildGraph()
{
    for (int i = 1; i <= nrect; i ++)
    {
        AddPoint(rect[i].a);
        AddPoint(rect[i].b);
        AddPoint(Point(rect[i].a.x, rect[i].b.y));
        AddPoint(Point(rect[i].b.x, rect[i].a.y));
    }
    Part();
}
 
int S;
int father[MAX_RECT + 1];
int Getfather(int x)
{
    if (x == father[x])
        return x;
    return father[x] = Getfather(father[x]);
}
 
void Union(int a, int b)
{
    a = Getfather(a), b = Getfather(b);
    if (rect[a].a.x < rect[b].a.x)
        father[b] = a;
    else if (rect[a].a.x == rect[b].a.x && rect[a].a.y < rect[b].a.y)
        father[b] = a;
    else
        father[a] = b;
}
 
void FindStartPoint()
{
    for (int i = 1; i <= nrect; i ++)
        father[i] = i;
    for (int i = 1; i <= nrect; i ++)
        for (int j = 1; j <= nrect; j ++)
            if (CrossRect(rect[i].a, rect[i].b, rect[j].a, rect[j].b))
                Union(i, j);
    int id = Getfather(1);
    Point pt = rect[id].a;
    for (int i = 1; i <= npoint; i ++)
        if (pt == p[i])
        {
            S = i;
            break;
        }
}
 
int T;
int d[MAXN + 1];
int q[MAXN + 1];
bool hash[MAXN + 1];
int Find(int x, int y)
{
    for (int i = 1; i <= npoint; i ++)
        if (p[i].x == x && p[i].y == y)
            return i;
    return -1;
}
 
void SPFA()
{
    T = P(S, 1);
    S = P(S, 0);
    memset(d, 0x3f, sizeof(d));
    d[S] = 0;
    hash[S] = true;
    q[1] = S;
    int head = 0, tail = 1;
    while (head != tail)
    {
        if ((++ head) == MAXN)
            head = 0;
        int t = q[head];
        for (int now = begin[t], tmp, dt; now; now = next[now])
            if ((dt = d[t] + cost[now]) < d[tmp=end[now]])
            {
                d[tmp] = dt;
                if (!hash[tmp])
                {
                    hash[tmp] = true;
                    if ((++ tail) == MAXN)
                        tail = 0;
                    q[tail] = tmp;
                }
            }
        hash[t] = false;
    }
    printf("%d\n", d[T]);
}
 
 
void Solve()
{
    BuildGraph();
    FindStartPoint();
    SPFA();
}
 
int main()
{
    Init();
    Solve();
    return 0;
}
