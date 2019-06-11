#include <cstdio>
#include <cstring>
 
int N, M, gdet;
int pre[16][65537];
 
void pre_work() {
 
    int x;
 
    scanf("%d %d", &N, &M);
    for (int i = 1; i <= N; i++)
    {
        scanf("%d", &x);
        for (int t = 0; t < 16; t++)
            pre[t][(x & ((1 << (t + 1)) - 1)) + 1]++;
    }
 
    for (int t = 0; t < 16; t++)
    {
        int bound = 1 << (t + 1);
        for (int i = 1; i <= bound; i++)
            pre[t][i] += pre[t][i - 1];
    }
}
 
void work() {
 
    char cmd[4];
    int x;
    long long ans = 0;
 
    for (int i = 1; i <= M; i++)
    {
        scanf("%s %d", cmd, &x);
        if (*cmd == 'Q')
        {
            int m = 1 << (x + 1);
            int st = (m >> 1) - gdet, ed = (m - 1) - gdet;
            st = ((st % m) + m) % m;
            ed = ((ed % m) + m) % m;
             
            int cnt = pre[x][ed + 1] - pre[x][st];
            ans += st <= ed ? cnt : pre[x][m] + cnt;
        }
        else
        {
            gdet += x;
            if (gdet >= 65536) gdet -= 65536;
            if (gdet < 0) gdet += 65536;
        }
    }
    printf("%lld\n", ans);
}
 
int main() {
 
    pre_work();
    work();
 
    return 0;
}
