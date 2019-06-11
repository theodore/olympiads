#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <deque>

const int Max_n = 2000033;
int n;
char s[Max_n / 2];
int sum[Max_n];
bool cut[Max_n];

void Work(bool z = true)
{
    for (int i = 1; i <= n; i++)
        sum[i] = sum[i + n] = (s[i] == 'C' ? 1 : -1);
    for (int i = 1; i <= n + n; i++)
        sum[i] += sum[i - 1];

    std::deque<int> Q;
    for (int i = 1; i <= n + n; i++) {
        if (!Q.empty() && i - Q.front() > n)
            cut[z ? Q.front() : (n - Q.front())] = true, Q.pop_front();
        while (!Q.empty() && sum[i] < sum[Q.back()])
            Q.pop_back();
        Q.push_back(i);
    }
    if (Q.front() == n)
        cut[n] = true;
}

int main()
{
    int _;
    scanf("%d", &_);
    for (int __ = 1; __ <= _; __++) {
        memset(cut, false, sizeof cut);
        scanf("%s", s + 1);
        n = strlen(s + 1);
        Work();
        std::reverse(s + 1, s + n + 1);
        Work(false);
        int t = 0;
        for (int i = 1; i < n + n; i++)
            t += cut[i];
        printf("Case %d: %d\n", __, t);
    }
}
