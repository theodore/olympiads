#include <cstdio>
#include <cstdlib>
#include <unistd.h>

const int maxn = 5003;
int n, m;
int v[maxn];

int main()
{
	freopen("g.dot", "w", stdout);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i)
		scanf("%d", &v[i]);
	printf("digraph {\n");
	for (int i = 0; i < m; ++i)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		printf("\t\"%d,%d\" -> \"%d,%d\"\n", a, v[a], b, v[b]);
	}
	printf("}\n");
	fclose(stdout);
	system("dot -Tpng -o g.png g.dot");
	if (!fork())
		system("feh g.png");
}
