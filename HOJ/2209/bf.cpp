#include <cstdio>
#include <stack>

char s[1007], t[1007];

int Answer(int b, int c) {
    std::stack<int> S;
    for (int i = b; i <= c; ++i) {
        int z = (s[i] == '(' ? 1 : -1);
        if (z == -1 && !S.empty() && S.top() == 1)
            S.pop();
        else
            S.push(z);
    }
    int l = S.size(), r = 0;
    while (!S.empty() && S.top() == 1)
        ++r, S.pop();
    l -= r;
#if DB & 1
    fprintf(stderr, "%d %d\n", l, r);
#endif
    return (l + r) / 2 + (l & 1);
}

int main()
{
    int n, m, a, b, c;
    for (scanf("%d%d%s", &n, &m, s + 1); m--; ) {
        scanf("%d%d%d", &a, &b, &c);
        if (a == 0)
            printf("%d\n", Answer(b, c));
        else if (a == 1)
            for (int i = b; i <= c; ++i)
                s[i] = (s[i] == '(' ? ')' : '(');
        else {
            for (int i = b, j = c; i <= c; ++i, --j)
                t[i] = s[j];
            for (int i = b; i <= c; ++i)
                s[i] = t[i];
        }
    }
}
