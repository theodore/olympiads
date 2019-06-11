#include <cstdio>
#include <cstring>
const int N = 21, S = (1 << N) + 1;
int n, m;
int g[N];
int d[S], p[S], s[S]; // dist, previous, incoming strategy
int q[S], ans[S];
int main()
{
    while (scanf("%d%d", &n, &m), n)
    {
        memset(g, 0, sizeof(int) * n);
        for (int a, b; m --; )
        {
            scanf("%d%d", &a, &b);
            g[a] |= 1 << b;
            g[b] |= 1 << a;
        }
        memset(d, 0x3f, sizeof(int) * (1 << n));
        int start = (1 << n) - 1, end = -1;
        d[start] = 0; p[start] = -1; s[start] = -1;
        q[0] = start;
        for (int qh = 0, qt = 1; qh != qt; qh ++)
        {
            int s0 = q[qh], d1 = d[s0] + 1;
            if (s0 == 0) { end = s0; break; }
            int s_base = 0;
            for (int i = 0; i < n; i ++)
                if ((s0 >> i) & 1)
                    s_base |= g[i];
            for (int i = 0; i < n; i ++)
            {
                int s1 = s_base & (~(1 << i));
                if (d1 < d[s1])
                {
                    d[s1] = d1;
                    p[s1] = s0;
                    s[s1] = i;
                    q[qt ++] = s1;
                }
            }
        }
        if (end == -1)
            puts("Impossible");
        else
        {
            m = 0;
            for (int now = end; now != -1; now = p[now])
                ans[m ++] = s[now];
            printf("%d:", m - 1);
            for (int i = m - 2; i >= 0; i --)
                printf(" %d", ans[i]);
            printf("\n");
        }
    }
}
