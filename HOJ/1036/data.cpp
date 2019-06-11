#include <cstdio>
#include <cstdlib>

const char s[][10] = {"QMAX", "QSUM"};

const int mod = 600000;

//*
int main()
{
    int n, m, r;
    scanf("%d%d%d", &n, &m, &r);
    srand(r);
    printf("%d\n", n);
    for (int i = 2; i <= n; ++i)
	printf("%d %d\n", rand() % (i - 1) + 1, i);
    for (int i = 0; i < n; ++i)
	printf("%d ", rand() % mod - mod / 2);
    printf("\n%d\n", m);
    while (m--)
	if (rand() & 1)
	    printf("CHANGE %d %d\n", rand() % n + 1, rand() % mod - mod / 2);
	else
	    printf("%s %d %d\n", s[rand() & 1], rand() % n + 1, rand() % n + 1);
}
/*/

int main()
{
    int n, m, r;
    scanf("%d%d%d", &n, &m, &r);
    srand(r);
    printf("%d\n", n);
    for (int i = 2; i <= n; ++i)
	printf("%d %d\n", i -1, i);
    for (int i = 0; i < n;  ++i)
	printf("%d ", rand() % mod);
    printf("\n%d\n", m);
    while (m--)
	printf("QMAX %d %d\n", 12, n - 323);
	//printf("CHANGE %d %d\n", rand() % n + 1, rand() % mod);
}
//*/
