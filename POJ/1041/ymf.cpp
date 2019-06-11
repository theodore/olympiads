#include <cstring>
#include <cstdlib>
#include <cstdio>

#define min(a, b) ((a) < (b) ? (a) : (b))

#define maxm 1995
#define maxn 45

int start[maxn], next[maxm << 1], to[maxm << 1], Id[maxm << 1];
int rec[maxm][3], deg[maxn];
int Stack[maxm], m;
bool act[maxm << 1];

int cmp(const void *a, const void *b)
{
	return (*(int *)b - *(int *)a);
}

void add(int a, int b, int id, int e)
{
	next[e] = start[a];
	start[a] = e;
	to[e] = b;
	Id[e] = id;
	act[e - 1] = 1;
}

void find(int u)
{
	for (int now = start[u]; now; now = next[now])
		if (act[now - 1])
		{
			act[now - 1] = act[(now - 1) ^ 1] = 0;
			find(to[now]);
			Stack[++m] = Id[now];
		}
}

int main()
{
	int a, b;
	for (scanf("%d%d", &a, &b); a || b; scanf("%d%d", &a, &b))
	{
		int cnt = 0;
		m = -1;
		//memset(start, 0, sizeof(start));
		memset(deg, 0, sizeof deg);
		do
		{
			rec[++cnt][1] = a;
			rec[cnt][2] = b;
			scanf("%d", &rec[cnt][0]);
			deg[a]++;
			deg[b]++;
			scanf("%d%d", &a, &b);
		} while (a || b);
		bool bad = false;
		for (int i = 1; i <= maxn; i++)
			if (deg[i] & 1)
			{
				bad = true;
				break;
			}
		if (bad)
			printf("Round trip does not exist.\n");
		else
		{
			qsort(rec + 1, cnt, sizeof(rec[0]), cmp);
			for (int i = 1; i <= cnt; i++)
			{
				add(rec[i][1], rec[i][2], rec[i][0],
					(i << 1) - 1);
				add(rec[i][2], rec[i][1], rec[i][0],
					i << 1);
			}
			find(1);
			for (int i = m; i > 0; i--)
				printf("%d ", Stack[i]);
			printf("%d\n", Stack[0]);
		}
	}
	return 0;
}
