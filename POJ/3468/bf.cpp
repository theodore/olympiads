#include <stdio.h>

typedef long long ll;

const int Max_n = 100033;
int n, q;
ll seq[Max_n];

int main()
{
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &seq[i]);
    while (q--) {
        char a;
        int l, r, z;
        scanf(" %c%d%d", &a, &l, &r);
        if (a == 'C') {
            scanf("%d", &z);
            while (l <= r)
                seq[l++] += z;
        } else {
            ll x = 0;
            while (l <= r)
                x += seq[l++];
            printf("%lld\n", x);
        }
    }
}
