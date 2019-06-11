#include <cstdio>
#include <algorithm>

using std::sort;

const int maxn = 100003;
int n;
int mine[maxn], yours[maxn];

bool cmp(int a, int b)
{
    return a > b;
}

void SolveMax()
{
    sort(mine, mine + n, cmp);
    sort(yours, yours + n, cmp);
    int ans = 0;
    for (int i = 0, l = 0, r = n - 1; i < n; ++i)
        if (mine[l] > yours[i]) {
            ans += 2, ++l;
        } else if (mine[l] < yours[i]) {
            --r;
        } else if (mine[r] > yours[n - 1]) {
            ++ans, ++l;
        } else {
            if (mine[r] == yours[i])
                ++ans;
            --r;
        }
    printf("%d ", ans);
}

void SolveMin()
{
    sort(mine, mine + n);
    sort(yours, yours + n);
    int ans = 0;
    for (int i = 0, l = 0, r = n - 1; i < n; ++i)
        if (mine[l] < yours[i]) {
            ++l;
        } else if (mine[l] > yours[i]) {
            ans += 2, --r;
        } else if (mine[r] > yours[n - 1]) {
            ans += 2, --r;
        } else if (mine[r] == yours[n - 1]) {
            if (mine[r] == yours[i])
                ++ans;
            else
                ans += 2;
            --r;
        } else {
            ++ans, ++l;
        }
    printf("%d\n", ans);
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
        scanf("%d", &mine[i]);
    for (int i = 0; i < n; ++i)
        scanf("%d", &yours[i]);
    SolveMax();
    SolveMin();
}
