#include <cstdio>
#include <cstdlib>

const int turn[] = {0x15, 0x2a, 0x24};
int n, m;
int state[9];
int l[23], lc;

void add(int a, int b, int c, int d)
{
	int& t = l[lc];
	if (a)
		t = 0;
	else
		t = 0x3f;
	if (b)
		t ^= turn[0];
	if (c)
		t ^= turn[1];
	if (d)
		t ^= turn[2];
	++lc;
}

int cmp(const void* a, const void* b)
{
	return *(int*)a - *(int*)b;
}

bool nice(int x)
{
	for (int i = 0; i < 6; ++i)
		if (state[i] == 1)
		{
			if (!(l[x] & (1 << (5 - i))))
				return false;
		}
		else if(state[i] == 2)
		{
			if (l[x] & (1 << (5 - i)))
				return false;
		}
	return true;
}

int main()
{
	scanf("%d%d", &n, &m);
	int t;
	for (scanf("%d", &t); t != -1; scanf("%d", &t))
		state[(t - 1) % 6] = 1;
	for (scanf("%d", &t); t != -1; scanf("%d", &t))
		state[(t - 1) % 6] = 2;
	for (int a = 0; a < 2; ++a)
		for (int b = 0; b < 2; ++b)
			for (int c = 0; c < 2; ++c)
				for (int d = 0; d < 2; ++d)
					if (a + b + c + d <= m && ((a ^ b ^ c ^ d) & 1) == (m & 1))
						add(a, b, c, d);
#ifdef DB
	printf("%d\n", lc);
	for (int i = 0; i < lc; ++i)
		printf("%x\n", l[i]);
#endif
	qsort(l, lc, sizeof l[0], cmp);
	for (int i = 0; i < lc; ++i)
		if ((i == 0 || l[i] != l[i-1]) && nice(i))
		{
#ifdef DB
			printf("%x nice\n", l[i]);
#endif
			for (int j = 0; j < n; ++j)
				putchar((l[i] & (1 << (5 - (j % 6)))) ? '1' : '0');
			putchar('\n');
		}
	return 0;
}
