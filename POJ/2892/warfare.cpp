#include <cstdio>
#include <algorithm>

#define ls(x) ((x) << 1)
#define rs(x) (ls(x) + 1)

const int maxn = 50003;
const int maxN = (1 << 17) + 11;
int n, N;
int target_list[maxn], tc;
int left[maxN], con[maxN], right[maxN], size[maxN];
int count[maxn];

void restore();
void remove(int);
int query(int);

void remove(int x)
{
	target_list[tc++] = x;
	if (++count[x] == 1)
	{
		x += N;
		left[x] = con[x] = right[x] = 0;
		for (x >>= 1; x; x >>= 1)
		{
			left[x] = left[ls(x)] + (left[ls(x)] == size[ls(x)]) * left[rs(x)];
			right[x] = right[rs(x)] + (right[rs(x)] == size[rs(x)]) * right[ls(x)];
			con[x] = std::max(std::max(con[ls(x)], con[rs(x)]), right[ls(x)] + left[rs(x)]);
		}
	}
}

void restore()
{
	int x = target_list[--tc];
	if (--count[x] == 0)
	{
		x += N;
		left[x] = con[x] = right[x] = 1;
		for (x >>= 1; x; x >>= 1)
		{
			left[x] = left[ls(x)] + (left[ls(x)] == size[ls(x)]) * left[rs(x)];
			right[x] = right[rs(x)] + (right[rs(x)] == size[rs(x)]) * right[ls(x)];
			con[x] = std::max(std::max(con[ls(x)], con[rs(x)]), right[ls(x)] + left[rs(x)]);
		}
	}
}

int query(int x)
{
	if (!con[x += N])
		return 0;
	int ret = 1;
	for (bool rex = true, lex = true; x && (rex || lex); x >>= 1)
	{
		if ((~x & 1) && rex)
		{
			ret += left[x ^ 1];
			rex = left[x ^ 1] == size[x ^ 1];
		}
		if ((x & 1) && lex)
		{
			ret += right[x ^ 1];
			lex = right[x ^ 1] == size[x ^ 1];
		}
	}
	return ret;
}

int main()
{
	int m;
	scanf("%d%d", &n, &m);
	for (N = 4; N - 2 < n; N <<= 1)
		;
	for (int i = N + 1; i <= N + n; ++i)
		size[i] = left[i] = con[i] = right[i] = 1;
	for (int i = N - 1; i; --i)
		size[i] = left[i] = con[i] = right[i] = con[ls(i)] + con[rs(i)];
	char str[7];
	int x;
	while (m--)
	{
		scanf("%s", str);
		if (str[0] == 'R')
			restore();
		else
		{
			scanf("%d", &x);
			if (str[0] == 'D')
				remove(x);
			else
				printf("%d\n", query(x));
		}
	}
}
