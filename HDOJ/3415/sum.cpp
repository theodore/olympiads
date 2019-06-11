#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <deque>

const int Max_n = 200033;
int n, k;
int seq[Max_n];

int main()
{
    int _;
    for (scanf("%d", &_); _--; ) {
        scanf("%d%d", &n, &k);
        for (int i = 1; i <= n; i++)
            scanf("%d", &seq[i]), seq[n + i] = seq[i];
        for (int i = 1; i <= n + n; i++)
            seq[i] += seq[i - 1];
        int ans = INT_MIN, ansl = -1, ansr = -1;
        std::deque<int> Q;
        Q.push_back(0);
        for (int i = 1; i <= n + n; i++) {
            while (i - Q.front() > k)
                Q.pop_front();
            int x = seq[i] - seq[Q.front()];
            if (x > ans)
                ans = x, ansl = Q.front() + 1, ansr = i;
            while (!Q.empty() && seq[Q.back()] > seq[i])
                Q.pop_back();
            Q.push_back(i);
        }
        if (ansl > n)
            ansl -= n;
        if (ansr > n)
            ansr -= n;
        printf("%d %d %d\n", ans, ansl, ansr);
    }
}
