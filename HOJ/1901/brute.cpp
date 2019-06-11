#include <cstdio>
#include <cstdlib>
#include <algorithm>

using std::sort;

int a[10100], b[10100], n, m;
FILE* in;

int main()
{
	in = fopen("in", "r");
	fscanf(in, "%d%d", &n, &m);
	for (int i = 1; i <= n; ++i)
		fscanf(in, "%d", a + i);
	char s[10];
	int x, y, z;
	while (m--)
	{
#ifdef DB
		printf("m = %d\n", m);
#endif
		fscanf(in, "%s%d%d", s, &x, &y);
		if (s[0] == 'C')
			a[x] = y;
		else
		{
			fscanf(in, "%d", &z);
			for (int i = x, j = 1; i <= y; ++i, ++j)
				b[j] = a[i];
			sort(b + 1, b + y - x + 2);
			if (s[0] == 'Q')
				printf("%d\n", b[z]);
			else
			{
				int i = 1;
				for (; i < y - x + 2 && b[i] < z; ++i);
				printf("%d\n", i - 1);
			}
		}
	}
}
