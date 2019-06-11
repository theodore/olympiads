#include <cstdio>
#include <cassert>

const int maxn = 503;
int n, m;
int a[maxn], b[maxn];
FILE *out;

void input(int& x, int r[])
{
	scanf("%d", &x);
	for (int i = 0; i < x; ++i)
		scanf("%d", &r[i]);
}

int nn, ans[maxn];

bool in(const int n, int s[])
{
	if (nn == 0)
		return true;
	int i = 0;
	for (int j = 0; j < n; ++j)
		if (s[j] == ans[i])
			if (++i == nn)
				break;
	return i == nn;
}

int main(int argc, char* argv[])
{
	assert(argc == 2);
	input(n, a);
	input(m, b);
	freopen(argv[1], "r", stdin);
	scanf("%d", &nn);
	for (int i = 0; i < nn; ++i)
		scanf("%d", &ans[i]);
	int r = !(in(n, a) && in(m, b));
	printf("ret = %d\n", r);
	return r;
}
