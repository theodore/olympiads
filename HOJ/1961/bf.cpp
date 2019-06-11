#include <cstdio>
#include <cstring>
#include <algorithm>

const int maxn = 103;
const int maxb = 7003;
int n;
int bag[maxn];
int l[maxn * maxb], lc;
int A[maxn * maxb], B[maxn * maxb], C[maxn * maxb];

int rm(const int id)
{
	int *a = A, *b = B, *c = C;
	a[0] = 1;
	a[1] = 0;
	b[0] = c[0] = 0;
	for (int i = 0; i < n; ++i)
		if (i != id)
		{
			int& ac = a[0];
			int& bc = b[0] = 0;
			int& cc = c[0] = 0;
			int h = 1;
			for (int j = 1; j <= ac; ++j)
			{
				b[++bc] = a[j] + bag[i];
				while (b[h] < a[j])
					c[++cc] = b[h++];
				h += (b[h] == a[j]);
				c[++cc] = a[j];
			}
			while (h <= bc)
				c[++cc] = b[h++];
			std::swap(a, c);
		}
	return a[0] - 1;
}

int id;

bool test(const int x)
{
	static bool first = true;
	int *a = A, *b = B, *c = C;
	if (first)
	{
		std::swap(a, c);
		a[0] = 1;
		a[1] = 0;
		b[0] = c[0] = 0;
		for (int i = 0; i < n; ++i)
			if (i != id)
			{
				int& ac = a[0];
				int& bc = b[0] = 0;
				int& cc = c[0] = 0;
				int h = 1;
				for (int j = 1; j <= ac; ++j)
				{
					b[++bc] = a[j] + bag[i];
					while (b[h] < a[j])
						c[++cc] = b[h++];
					h += (b[h] == a[j]);
					c[++cc] = a[j];
				}
				while (h <= bc)
					c[++cc] = b[h++];
				std::swap(a, c);
			}
		std::swap(a, c);
		first = false;
	}
	int& ac = a[0];
	int& bc = b[0] = 0;
	int h = 1;
	for (int i = 1; i <= ac; ++i)
	{
		b[++bc] = a[i] + x;
		while (b[h] < a[i])
			++h;
		if (b[h] == a[i])
			return false;
	}
	return true;
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
		scanf("%d", &bag[i]);
	int max = rm(0);
	for (int i = 1, t; i < n; ++i)
		if ((t = rm(i)) > max || (t == max && bag[i] < bag[id]))
		{
			max = t;
			id = i;
		}
#ifdef DB
	fprintf(stderr, "%d\n", __LINE__);
	fprintf(stderr, "max = %d\n", max);
#endif
	for (int i = 1; ; ++i)
		if (test(i))
		{
			printf("%d %d\n", bag[id], i);
			return 0;
		}
}
