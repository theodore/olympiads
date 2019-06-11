#include <stdio.h>
#include <float.h>
#include <algorithm>
#include <deque>

#define UPN(a, b) a = std::min(a, b)

#define  FLT_FMT "%.3Lf"
typedef long double Flt_t;
const Flt_t Flt_Max = LDBL_MAX;

const int Max_n = 200007;
int n;
int pos[Max_n], lim[Max_n];
Flt_t ans[Max_n];

void Input()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d%d", &pos[i], &lim[i]);
}

void Output()
{
    for (int i = 0; i < n; i++)
        printf(FLT_FMT "\n", ans[i]);
}

int main()
{
#if DB & 1
    std::deque<int> dq;
#endif
    Input();
    for (int i = 0; i < n; i++) {
        Flt_t& x = ans[i] = Flt_Max;
#if DB & 1
        int z = -1;
#endif
        for (int j = 0; j < i; j++) {
            Flt_t t = pos[i] - pos[j];
            t /= 2;
#if DB & 1
            if (t * t / ans[j] < x) {
                x = t * t / ans[j];
                z = j;
            }
#else
            UPN(x, t * t / ans[j]);
#endif
        }
        UPN(x, (Flt_t)lim[i]);
#if DB & 1
        fprintf(stderr, "%d: %d\t", i, z);
        for (size_t j = 0; j < dq.size(); j++)
            fprintf(stderr, "%d, ", dq[j]);
        fprintf(stderr, "\n");
        while (!dq.empty() && ans[dq.back()] <= x)
            dq.pop_back();
        dq.push_back(i);
#endif
    }
    Output();
}
