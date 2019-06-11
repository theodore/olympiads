#include <stdio.h>
#include <float.h>
#include <algorithm>
#include <deque>

#define UPN(a, b) a = std::min(a, b)

#define FLT_FMT "%.3Lf"
typedef long double Flt_t;

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
    std::deque<int> dq;
    Input();
    for (int i = 0; i < n; i++) {
        Flt_t& x = ans[i] = lim[i];
        while (!dq.empty()) {
            int j = dq.back();
            Flt_t t = pos[i] - pos[j];
            t /= 2;
            UPN(x, t * t / ans[j]);
            if (ans[j] <= x)
                dq.pop_back();
            else
                break;
        }
        dq.push_back(i);
    }
    Output();
}
