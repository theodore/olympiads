#include <cstdio>
#include <cstdlib>

char s[][10] = {"Open", "Ask", "Close"};
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, -1, 0, 1};

int main()
{
    int n, m, r;
    scanf("%d%d%d", &n, &m, &r);
    srand(r);
    printf("%d\n", n);
    for (int a, b, c, d; m--; )
    {
	a = rand() % n + 1;
	b = rand() % 2 + 1;
	do {
	    int dd = rand() % 4;
	    c = a + dx[dd];
	    d = b + dy[dd];
	} while (!(c >= 1 && c <= n && d >= 1 && d <= 2));
	printf("%s %d %d %d %d\n", s[rand() % 3], b, a, d, c);
    }
    printf("Exit\n");
    //fprintf(stderr, "%d\n", r);
}
