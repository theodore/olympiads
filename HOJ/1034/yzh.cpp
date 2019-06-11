#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

#define maxn 1000001
using namespace std;

int n, a[maxn], b[maxn];

#define For(a,b,c) for(int a = b ; a <= c ; a++)

int Get(int A, int B)
{
    if (A > B)
        return 2;
    if (A == B)
        return 1;
    return 0;
}

int solve(int a[], int b[])
{
    bool HryzH = true;
    int ret = 0;
    int h1 = 1, h2 = 1, t1 = n, t2 = n;
    do {
        if (h1 == t1) {
            ret += Get(a[h1], b[h2]);
            break;
        }
        if (a[h1] > b[h2]) {
            ret += 2;
            h1++;
            h2++;
        } else {
            if (a[h1] < b[h2]) {
                ret += Get(a[h1], b[t2]);
                h1++;
                t2--;
            } else {
                if (a[t1] > b[t2]) {
                    ret += 2;
                    t1--;
                    t2--;
                } else {
                    ret += Get(a[h1], b[t2]);
                    h1++;
                    t2--;
                }
            }
        }
    } while (HryzH);
    return ret;
}

int main()
{
    scanf("%d", &n);
    For(i, 1, n) scanf("%d", &a[i]);
    For(i, 1, n) scanf("%d", &b[i]);
    sort(a + 1, a + n + 1);
    sort(b + 1, b + n + 1);
    cout << solve(a, b) << ' ' << 2 * n - solve(b, a) << endl;
    return 0;
}
