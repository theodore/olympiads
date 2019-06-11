#include <cstdio>
#include <cstdlib>

const int maxn(10003);
const int maxm(40003);
int n, m;
int start[maxn], to[maxm], next[maxm], edge;
bool vis[maxn];

void add(int a, int b)
{
	to[++edge] = b;
	next[edge] = start[a];
	start[a] = edge;
}

void search(int x, int f)
{
	vis[x] = true;
	for (int e = start[x]; e; e = next[e])
		if (to[e] != f)
		{
			if (vis[to[e]])
			{
				printf("NO\n");
				exit(0);
			}
			else
				search(to[e], x);
		}
}

const int buffer_size(180003);
char buff[buffer_size];
char* p = buff;

#define read(x) \
{ \
	for (; *p < '0' || *p > '9'; ++p); \
	for (x = 0; *p >= '0' && *p <= '9'; ++p) \
		x = x * 10 + *p - '0'; \
}

int main()
{
	fread(buff, 1, buffer_size, stdin);
	read(n); read(m);
	if (m < n - 1)
	{
		printf("NO\n");
		return 0;
	}
	for (int i = 0, a, b; i < m; ++i)
	{
		read(a); read(b);
		add(a, b);
		add(b, a);
	}
	search(1, 0);
	for (int i = 1; i <= n; ++i)
		if (!vis[i])
		{
			printf("NO\n");
			return 0;
		}
	printf("YES\n");
	return 0;
}
