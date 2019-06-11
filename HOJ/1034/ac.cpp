#include <cstdio>
#include <algorithm>

const int maxn = 100003;
int n;

int Fight(int a, int b)
{
    if (a > b)
        return 2;
    else if (a == b)
        return 1;
    else
        return 0;
}

int Win(int mine[], int yours[])
{
    int myl = 0, myr = n - 1, yourl = 0, yourr = n - 1;
    int ret = 0;
    for (int _ = n; _--; ) {
        if (mine[myr] > yours[yourr]) {
            ret += 2;
            myr--;
            yourr--;
        } else if (mine[myl] > yours[yourl]) {
            ret += 2;
            myl++;
            yourl++;
        } else {
            ret += Fight(mine[myl], yours[yourr]);
            myl++;
            yourr--;
        }
    }
    return ret;
}

int main()
{
    static int mine[maxn], yours[maxn];
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
        scanf("%d", &mine[i]);
    for (int i = 0; i < n; ++i)
        scanf("%d", &yours[i]);
    std::sort(mine, mine + n);
    std::sort(yours, yours + n);
    printf("%d %d\n", Win(mine, yours), 2 * n - Win(yours, mine));
}
