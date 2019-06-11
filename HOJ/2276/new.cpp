#include <cctype>
#include <cstdio>
#include <algorithm>

#define UPX(a, b) a = std::max(a, b)

void getint(int& x)
{
    int c, neg = 1;;
    while (!isdigit(c = getchar()) && c != '-')
        ;
    if (c == '-')
        neg = -1, c = getchar();
    x = c - '0';
    while (isdigit(c = getchar()))
        x = x * 10 + c - '0';
    x *= neg;
}

struct Elmt {
    Elmt() {}
    Elmt(int a, int b) : p(a), h(b) {}
    int p, h;
};

const int maxn = 1000003;
//std::list<Elmt> list;
int n, l, h;
int ans;
Elmt list[maxn];
int ll, lr;

int main()
{
    getint(n);
    for (int i = 0; i < n; ++i) {
        getint(l);
        getint(h);
        while (ll != lr && h < list[ll].h)
            ++ll;
        int np = i;
        while (ll != lr && list[lr - 1].h <= l)
            np = list[lr - 1].p, --lr;
        list[lr++] = Elmt(np, l);
        UPX(ans, i - list[ll].p);
    }
    printf("%d\n", ans + 1);
}
