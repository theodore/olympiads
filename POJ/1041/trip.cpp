#include <cstdio>
#include <cstdlib>
#include <cstring>

#define min(a, b) ((a) < (b) ? (a) : (b))
#define OP(x) ((((x) - 1) ^ 1) + 1)

const int maxn(53);
const int maxm(4003);
const int n(44);
int m;
int start[maxn], to[maxm], next[maxm], num[maxm], edge;
bool vis[maxm];
int deg[maxn];
int ans[2003];
int list[maxm], lc;
int rec[maxm][3];

void add(int a, int b, int c)
{
	to[++edge] = b;
	num[edge] = c;
	next[edge] = start[a];
	start[a] = edge;
}

int ncmp(const void* a, const void* b)
{
	return ((int*)b)[2] - ((int*)a)[2];
}

void find(int x)
{
	for (int e = start[x]; e; e = next[e])
		if (!vis[e])
		{
			vis[e] = vis[OP(e)] = true;
			find(to[e]);
			ans[++m] = num[e];
		}
}

int main()
{
	int a, b, c;
	for (scanf("%d%d", &a, &b); a || b; scanf("%d%d", &a, &b))
	{
		edge = 0;
		m = -1;
		memset(deg, 0, sizeof deg);
		memset(vis, 0, sizeof vis);
		memset(start, 0, sizeof start);
		int cnt(0);
		do
		{
			scanf("%d", &c);
			rec[cnt][0] = a;
			rec[cnt][1] = b;
			rec[cnt][2] = c;
			++cnt;
			++deg[a];
			++deg[b];
			scanf("%d%d", &a, &b);
		} while (a || b);
		bool bad = false;
		for (int i = 1; i <= n; ++i)
			if (deg[i] & 1)
			{
				bad = true;
				break;
			}
		if (bad)
			printf("Round trip does not exist.\n");
		else
		{
			qsort(rec, cnt, sizeof rec[0], ncmp);
			for (int i = 0; i < cnt; ++i)
			{
				add(rec[i][0], rec[i][1], rec[i][2]);
				add(rec[i][1], rec[i][0], rec[i][2]);
			}
			find(1);
			for (int i = m; i > 0; --i)
				printf("%d ", ans[i]);
			printf("%d\n", ans[0]);
		}
	}
	return 0;
}
