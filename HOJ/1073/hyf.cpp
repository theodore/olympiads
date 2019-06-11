#include <iostream>
#include <queue>
#include <cstdio>
#include <cstring>
using namespace std;
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAXN 51
#define MAXM 2501
#define INFINITE 100000000

class Node
{
public:
	int id;
	int dist;
	int child[MAXN];
	void set(int _id, int _dist)
	{
		memset(child,0,sizeof(child));
		id = _id, dist = _dist;
	}
}node[1000000];

class Path
{
public:
	int L;
	int path[MAXN];
	int keyPoint;
	int dist;
	Path():L(0),keyPoint(0),dist(0) {memset(path,0,sizeof(path));}
	friend bool operator<(const Path &a, const Path &b)
	{
		if(b.dist!=a.dist)
			return b.dist<a.dist;
		return memcmp(b.path,a.path,sizeof(int)*MAX(a.L,b.L))<0;
	}
	void print()
	{
		printf("%d",path[0]);
		for(int i = 1; i < L; i++)
			printf("-%d",path[i]);
		printf("\n");
	}
};

int map[MAXN][MAXN] = {0};

class Trie
{
public:
	int head,k;
    Trie():head(-1),k(0)
	{
	    head = k;
		node[k++].set(1,0);
	}
	void Add(int x, const Path &a, int L)
	{
		if(L==a.L)
			return;
		if(node[x].child[a.path[L]])
			Add(node[x].child[a.path[L]],a,L+1);
		else
		{
			node[x].child[a.path[L]] = k;
			node[k].set(a.path[L],node[x].dist+map[a.path[L-1]][a.path[L]]);
			Add(k++,a,L+1);
		}
	}
	void Add(const Path &a)
	{
		Add(head,a,1);
	}
	int GetSize()
	{
		return k;
	}
}tree;

int cnt = 0, tot = 0, nowpoint;
int n,m,K,a,b,co;
int g[MAXN] = {0}, end[MAXM] = {0}, next[MAXM] = {0}, cost[MAXM] = {0};
int g2[MAXN] = {0}, end2[MAXM] = {0}, next2[MAXM] = {0}, cost2[MAXM] = {0};
int Queue[MAXN], p[MAXN], list[MAXN], buffer[MAXN];
bool bl[MAXN], used[MAXN];
priority_queue<Path> heap;

void AddEdge(int a, int b, int c)
{
	++cnt;
	end[cnt] = b;
	next[cnt] = g[a];
	g[a] = cnt;
	cost[cnt] = c;
	end2[cnt] = a;
	next2[cnt] = g2[b];
	g2[b] = cnt;
	cost2[cnt] = c;
}

int spfa(int s, int t)
{
	tot++;
	int front = 0, rear = 0, tmp, tmp2, now;
	for(int i = 1; i <= n; i++)
		p[i] = INFINITE, bl[i] = 0;
	p[t] = 0, bl[t] = true;
	Queue[rear++] = t;
	while(front!=rear)
	{
		tmp = Queue[front];
		for(int i = g2[tmp]; i; i=next2[i])
			if(!used[tmp2=end2[i]]&&p[tmp]+cost2[i]<p[tmp2])
			{
				p[tmp2] = p[tmp]+cost2[i];
				if(!bl[tmp2])
				{
					bl[tmp2] = true;
					Queue[rear] = tmp2;
					rear = rear+1==n?0:rear+1;
				}
			}
		bl[tmp] = false;
		front = front+1==n?0:front+1;
	}
	co = 0, now = s;
	tmp = 0, tmp2 = INFINITE;
	for(int i = g[s]; i; i=next[i])
		if(!used[end[i]]&&node[nowpoint].child[end[i]]==0)
			if(cost[i]+p[end[i]]<tmp2||(cost[i]+p[end[i]]==tmp2)&&end[i]<tmp)
				tmp2 = cost[i]+p[end[i]], tmp = end[i];
	p[s] = tmp2;
	if(p[s]==INFINITE)
		return p[s];
	now = tmp, list[co++] = tmp;
	while(now!=t)
	{
		tmp = INFINITE;
		for(int i = g[now]; i; i=next[i])
			if(!used[tmp2=end[i]]&&p[now]==p[tmp2]+cost[i])
				tmp = MIN(tmp,tmp2);
		now = tmp, list[co++] = now;
	}
	return p[s];
}

void update(int s, int path[], int L, int dist)
{
	Path tmp;
	dist += spfa(s,b);
	if(dist>=INFINITE)
		return;
	tmp.L = L+co, tmp.dist = dist;
	for(int i = 0; i < L; i++)
		tmp.path[i] = path[i];
	for(int i = 0; i < co; i++)
		tmp.path[L+i] = list[i];
	tmp.keyPoint = L-1;
	heap.push(tmp);
}

void init()
{
	int u,v,l;
	scanf("%d %d %d %d %d",&n,&m,&K,&a,&b);
	for(int i = 0; i < m; i++)
		scanf("%d %d %d",&u,&v,&l), AddEdge(u,v,l), map[u][v] = l;
}

void solve()
{
	int L,now,dist;
	Path tmp;
	buffer[0] = a;
	update(a,buffer,1,0);
	for(int i = 0; i < K-1; i++)
	{
		if(heap.empty())
			break;
		tmp = heap.top();
		tree.Add(tmp);
		heap.pop();
		//tmp.print();
		L = dist = 0, nowpoint = tree.head;
		memset(used,0,sizeof(used));
		for(int i = 0; i < tmp.keyPoint; i++)
		{
			buffer[L++] = tmp.path[i], used[tmp.path[i]] = true, dist += map[tmp.path[i]][tmp.path[i+1]];
			nowpoint = node[nowpoint].child[tmp.path[i+1]];
		}
		for(int i = tmp.keyPoint; i < tmp.L-1; i++)
		{
			buffer[L++] = (now=tmp.path[i]), used[tmp.path[i]] = true;
			update(tmp.path[i],buffer,L,dist);
			dist += map[tmp.path[i]][tmp.path[i+1]];
			nowpoint = node[nowpoint].child[tmp.path[i+1]];
		}
	}
}

void print()
{
	if(heap.empty())
		printf("No\n");
	else
	{
		Path node = heap.top();
		node.print();
	}
	//printf("%d\n",tree.GetSize());
}

int main(void)
{
	init();
	solve();
	print();
	return 0;
}
