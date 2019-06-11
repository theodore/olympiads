// start: 02:50 PM
#include <stdio.h>
#include <algorithm>
#include <list>

struct Data { int x, y; };
struct Edge : Data { int a, b; };
typedef std::list<Data>::iterator LI;

struct CMP {
    int A, B;   // A for x, B for y
    CMP(int a, int b) : A(a), B(b)
    {
        return;
#if DB & 2
        fprintf(stderr, "%d %d\n", a, b);
#endif
        while (b) { int t = b; b = a % b; a = t; }
        A /= a; B /= a;     // XXX Can't do this, a may be 0
    }
    bool operator()(const Data& a, const Data& b) const
    { return A * a.x + B * a.y < A * b.x + B * b.y; }
};

const int Max_v = 203;
const int Max_e = 10033;
int n, m;
Edge edge[Max_e];
std::list<Data> L;

void Input()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++)
        scanf("%d%d%d%d", &edge[i].a, &edge[i].b, &edge[i].x, &edge[i].y);
}

int father[Max_v];
int GetFather(int x)
{
    int f = x;
    while (father[f] != f)
        f = father[f];
    for (int i = x, fa; i != f; i = fa)
        fa = father[i], father[i] = f;
    return f;
}

Data MST(const CMP& cmp)
{
    std::sort(edge, edge + m, cmp);
    for (int i = 0; i < n; i++)
        father[i] = i;
    Data ans = {0, 0};
    for (int i = 0, a, b; i < m; i++)
        if ((a = GetFather(edge[i].a)) != (b = GetFather(edge[i].b))) {
            ans.x += edge[i].x;
            ans.y += edge[i].y;
            father[a] = b;
        }
    return ans;
}

void Expand(const LI A, const LI B)
{
    CMP z(A->y - B->y, B->x - A->x);
    Data t = MST(z);
    if (z(t, *A) && z(t, *B)) {
        const LI i = L.insert(B, t);
        Expand(A, i);
        Expand(i, B);
    }
}

void GenAns()
{
    Data ans = *L.begin();
    for (LI i = L.begin(); i != L.end(); ++i)
        if (i->x * i->y < ans.x * ans.y)
            ans = *i;
    printf("%d %d\n", ans.x, ans.y);
}

// XXX 48264942694 XXX
// FIXME **TOY** FIXME
int main()
{
    Input();
    L.push_back(MST(CMP(1, 0)));
    L.push_back(MST(CMP(0, 1)));
#if DB & 1
    fprintf(stderr, "%d,%d %d,%d\n", L.begin()->x, L.begin()->y, (++L.begin())->x, (++L.begin())->y);
#endif
    Expand(L.begin(), --L.end());
    GenAns();
}
