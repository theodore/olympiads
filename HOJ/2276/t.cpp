#include <cstdio>
#include <ctype.h>
 
int getint()
{
    int ret, ch, sign = 1;
    while (!(isdigit(ch = getchar()) || ch == '-'));
    if (ch == '-') ret = 0, sign = -1;
    else ret = ch - '0';
    while (isdigit(ch = getchar()))
        ret = ret * 10 + ch - '0';
    return ret * sign;
}
 
const int N = 1000000;
struct Queue
{
    int val, pos;
    void set(int _v, int _p) { val = _v, pos = _p; }
} queue[N];
 
int main()
{
    int n = getint();
    int qh = 0, qt = 1, ans = 1;
    queue[0].set(getint(), 0); getint();
    for (int i = 1; i < n; i ++)
    {
        int lo = getint(), hi = getint();
        while (qh < qt && queue[qh].val > hi)
            qh ++;
        if (qh < qt)
        {
            int val = i - queue[qh].pos + 1;
            if (val > ans)
                ans = val;
        }
        int pos = i;
        while (qh < qt && queue[qt - 1].val < lo)
        {
            pos = queue[qt - 1].pos;
            qt --;
        }
        queue[qt].set(lo, pos);
        qt ++;
    }
    printf("%d\n", ans);
    return 0;
}
