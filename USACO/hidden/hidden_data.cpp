#include <cstdio>
#include <cstdlib>
#include <ctime>

int main(int argc, char** argv)
{
	freopen("hidden.in", "w", stdout);
	srand(time(0));
	int n, m, t;
	if (argc == 1)
		m = 100;
	else
		sscanf(argv[1], "%d", &m);
	if (argc > 2)
		sscanf(argv[2], "%d", &t);
	else
		t = 26;
	printf("%d\n", n=rand()%m + 5);
	for (int i=0; i<n; ++i)
		printf("%c", rand()%t+'a');
	putchar('\n');
	return 0;
}

