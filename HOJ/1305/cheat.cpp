#include <limits.h>
#include <stdio.h>
#include <algorithm>

#define UPN(a, b) a = std::min(a, b)

const int Max_n = 70;
int n, k;
char s[Max_n][Max_n];

int main()
{
    scanf("%d%d", &n, &k);
    int ans = INT_MAX;
    for (int i = 0; i < n; i++) {
        scanf("%s", s[i]);
        int z = 0;
        for (int j = 0; j < n; j++)
            z += s[i][j] == 'Y';
        UPN(ans, z);
    }
    for (int i = 0; i < n; i++) {
        int z = 0;
        for (int j = 0; j < n; j++)
            z += s[j][i] == 'Y';
        UPN(ans, z);
    }
    printf("%d\n", std::min(n, ans + k));
}
