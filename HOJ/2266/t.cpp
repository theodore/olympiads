#include <cstdio>
const int N = 1005;

struct Stack
{
    int pos, h, val;
    void set(int _pos, int _h, int _val)
    { pos = _pos, h = _h, val = _val; }
};

inline int max(int a, int b)
{ return a > b ? a : b; }

int cnt[N + N];
void solve()
{
    int n, m;
    scanf("%d%d\n", &n, &m);
    static char s[N];
    static int h[N];
    for (int i = 0; i < m; i ++)
        h[i] = 0;
    int max_len = 0;
    for (int i = 0; i < n; i ++)
    {
        gets(s);
        for (int j = 0; j < m; j ++)
            if (s[j] == '#')
                h[j] = 0;
            else h[j] ++;
        static Stack stack[N];
        int top = 0;
#define INIT_STACK(p) \
        { \
            stack[0].set(p, 0, -p); \
            top = 1; \
        }
        INIT_STACK(-1);

        if (i == 1){
            int asdf =0 ;
        }
        for (int j = 0; j < m; j ++)
        {
            if (s[j] == '#')
            {
                INIT_STACK(j);
                continue;
            }

            while (h[j] < stack[top - 1].h)
                top --;
            int ans = h[j] + (j - stack[top - 1].pos);
            ans = max(ans, stack[top - 1].val + j);
            cnt[ans] ++;
            if (ans > max_len)
                max_len = ans;
            if (h[j] > stack[top - 1].h)
            {
                stack[top].set(j, h[j], max(stack[top - 1].val, h[j] - stack[top - 1].pos));
                top ++;
            }
            else if (h[j] == stack[top - 1].h)
                stack[top - 1].set(j, h[j], max(stack[top - 2].val, h[j] - stack[top - 2].pos));
        }
    }

    for (int i = 1; i <= max_len; i ++)
        if (cnt[i])
        {
            printf("%d x %d\n", cnt[i], i * 2);
            cnt[i] = 0;
        }
}

int main()
{
    int ncase;
    scanf("%d", &ncase);
    while (ncase --)
        solve();
    return 0;
}
