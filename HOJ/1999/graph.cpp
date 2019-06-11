#include <cstdio>

int n, s;

void input()
{
	scanf("%d%d", &n, &s);
	for (int i = 1, a, b, c; i < n; ++i)
	{
		scanf("%d%d%d", &a, &b, &c);
		printf("\t%d -- %d [label = %d]\n", a, b, c);
	}
}

int main()
{
	freopen("core.dot", "w", stdout);
	printf("graph {\n");
	input();
	printf("}\n");
	return 0;
}
