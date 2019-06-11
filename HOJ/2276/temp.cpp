#include <cctype>
#include <cstdio>
#include <algorithm>
#include <list>

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

std::list<Elmt> list;
int n, l, h;
int ans;

int main()
{
    getint(n);
    for (int i = 0; i < n; ++i) {
        getint(l);
        getint(h);
        while (!list.empty() && h < list.front().h)
            list.pop_front();
        int np = i;
        while (!list.empty() && list.back().h <= l)
            np = list.back().p, list.pop_back();
        list.push_back(Elmt(np, l));
        UPX(ans, i - list.front().p);
    }
    printf("%d\n", ans + 1);
}
