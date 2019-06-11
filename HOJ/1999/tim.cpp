#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define BUFSIZE 1000000
char buf[BUFSIZE], *pt = buf + BUFSIZE, *pend = buf + BUFSIZE;
#define read() \
	do{ \
		if (pt >= pend) \
		{ \
			pt = buf; \
			fread(buf, 1, BUFSIZE, stdin); \
		} \
	} while(0) 

#define scan(t) \
{ \
	t = 0; \
	read(); \
	bool nega = false; \
	while (!(((*pt) >= '0' && (*pt) <= '9') || (*pt == '-'))) {pt ++; read();} \
	if ((*pt) == '-') {nega = true, pt ++; read();} \
	while (((*pt) >= '0' && (*pt) <= '9')) {t = t * 10 + (*(pt ++)) - '0'; read();}\
	if (nega) t = -t; \
}


#define MAXN 500010
#define MAXM MAXN * 2

int begin[MAXN + 1], end[MAXM + 1], next[MAXM + 1], cost[MAXM + 1];
int Count = 0;
void AddEdge(int a, int b, int v)
{
	Count ++;
	next[Count] = begin[a];
	begin[a] = Count;
	end[Count] = b;
	cost[Count] = v;
}

int n, s;
void Init()
{
	scan(n); scan(s);
	int a, b, c;
	for (int i = 1; i <= n - 1; i ++)
	{
		scan(a); scan(b); scan(c);
		AddEdge(a, b, c);
		AddEdge(b, a, c);
	}
}

int d[MAXN + 1];
int q[MAXN + 1];
bool hash[MAXN + 1];
int father[MAXN + 1];
int BFS(int S, bool flag = false)
{
	int head, tail, t;
	head = 0, tail = 1;
	q[1] = S;
	if (!flag)
	{
		memset(hash, 0, sizeof(hash));
		hash[S] = true;
		father[S] = 0;
	}
	d[S] = 0;
	int maxD = 0, maxID = 0;
	while (head != tail)
	{
		t = q[++head];
		if (d[t] > maxD)
			maxD = d[t], maxID = t;
		for (int now = begin[t], tmp; now; now = next[now])
		{
			tmp = end[now];
			if (!hash[tmp])
			{
				father[tmp] = t;
				hash[tmp] = true;
				d[tmp] = d[t] + cost[now];
				q[++tail] = tmp;
			}
		}
	}
	return flag ? maxD : maxID;
}

int dist[MAXN + 1], v[MAXN + 1];
int a[MAXN + 1];
int val_head[MAXN + 1];
int val_tail[MAXN + 1];
int pos[MAXN + 1];
int val[MAXN + 1];
int id[MAXN + 1];
void Solve()
{
	int u = BFS(BFS(1));
	memset(hash, 0, sizeof(hash));
	int cnt = 0;
	while (u)
	{
		hash[u] = true;
		a[++cnt] = u;
		u = father[u];
	}
	for (int i = 1; i <= cnt; i ++)
	{
		dist[i] = d[a[i]];
		v[i] = BFS(a[i], true);
	}
	for (int i = 1, t; i <= cnt; i ++)
	{
		val_head[i] = v[i];
		t = 0;
		for (int now = begin[a[i]]; now; now = next[now])
			if (end[now] == a[i - 1])
			{
				t = cost[now];
				break;
			}
		val_head[i] = MAX(val_head[i], t + val_head[i - 1]);
	}
	for (int i = cnt, t; i >= 1; i --)
	{
		t = 0;
		for (int now = begin[a[i]]; now; now = next[now])
			if (end[now] == a[i + 1])
			{
				t = cost[now];
				break;
			}
		val_tail[i] = MAX(val_tail[i + 1] + t, v[i]);
	}
	
	int head = 1, tail = 0;
	int ans = 0x7fffffff;
	int front = 0;
	dist[0] = 0x7fffffff;
	for (int i = 1; i <= cnt; i ++)
	{
		while (head <= tail && pos[head] - dist[i] > s)
			head ++;
		while (head <= tail && val[tail] <= v[i])
			tail --;
		tail ++;
		pos[tail] = dist[i];
		val[tail] = v[i];
		while (dist[front] - dist[i] > s)
			front ++;
		int tmp = MAX(val[head], MAX(val_head[front], val_tail[i]));
		if (tmp < ans)
			ans = tmp;
	}
	printf("%d\n", ans);
}

int main()
{
	Init();
	Solve();
	return 0;
}
