#include <cstdio>
#include <cstring>
#include <cstdlib>

int M, N, K, H, Seed;
char map[100][100];

int main() {
    scanf("%d %d %d %d %d", &M, &N, &K, &H, &Seed);
    srand(Seed);
    printf("%d %d %d %d\n", M, N, K, H);
    for (int i = 1; i <= M; i++)
	for (int j = 1; j <= N; j++)
	{
	    int t = rand() % 10;
	    if (t <= 3) map[i][j] = '.';
	    else if (t <= 6) map[i][j] = '#';
	    else map[i][j] = rand() % K + 'A';
	}
    map[1][1] = '$'; map[M][N] = '@';
    map[M][1] = map[1][N] = '@';
    for (int i = 1; i <= M; i++, printf("\n"))
	for (int j = 1; j <= N; j++)
	    printf("%c", map[i][j]);
    for (int i = 0; i < 1 << K; i++) printf("%d ", rand() % 100);
    printf("\n");

    return 0;
}
