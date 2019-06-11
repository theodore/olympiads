#include <iostream>
#include <cstdio>
#include <cstdlib>
#define ll long long
#define MAXN 30
#define MAXLEN 50
#define MAXNODE MAXN*MAXLEN*MAXLEN*3
#define MAXEDGE MAXNODE*MAXN*3
#define INFINIT 1000000000

#define DIFFRENT 0
#define SAME_SHORT 1
#define SAME_LONG 2

using namespace std;

ll code[MAXN+1];
int n;
int cnt = 0;
int S = 0,T;
int L[MAXN+1];
int id[MAXN+1][MAXLEN+1][MAXLEN+1][3];
void Init()
{
    scanf("%d",&n);
    scanf("\n");
    for (int i = 0; i<n; i++)
    {
	char s[MAXLEN+1];
	char ch;
	while (true)
	{
	    scanf("%c",&ch);
	    if (ch == '\n') break;
	    s[L[i]++] = ch;
	}
	scanf("\n");
	while (L[i]&&s[L[i]-1]!='0'&&s[L[i]-1]!='1') L[i]--;
	if (L[i] == 0)
	{
	    printf("0\n");
	    exit(0);
	}
	for (int j = 0; j<L[i]; j++)
	    code[i] = (code[i]<<1) + s[j]-'0';
    }
}

#ifdef DB
int db_hash[MAXNODE+1][4];
#endif

int Count = 0;
int begin[MAXNODE+1],end[MAXEDGE+1],next[MAXEDGE+1],cost[MAXEDGE+1];
void AddEdge(int a,int b,int c)
{
    Count++;
    next[Count] = begin[a];
    begin[a] = Count;
    end[Count] = b;
    cost[Count] = c;
}

bool match(ll a,ll b,int p)
{
    return ((a&(((ll)1<<(p))-1)) == (b&(((ll)1<<(p))-1)));
}

int Dfs(int a,int l1,int l2,int flag)
{
    if (id[a][l1][l2][flag]) return id[a][l1][l2][flag];
    int tmp = id[a][l1][l2][flag] = ++cnt;
    if (flag == DIFFRENT)
    {
	for (int i = 0; i<n; i++)
	    if (l2+L[i]<=L[a]&&match(code[a]>>l2,code[i],L[i]))
	    {
		if (l2+L[i]<=l1)
		    AddEdge(tmp,Dfs(a,l1,l2+L[i],DIFFRENT),0);
		else
		    AddEdge(tmp,Dfs(a,l2+L[i],l1,DIFFRENT),0);
	    }else
		if (l2+L[i]>L[a]&&match(code[a]>>l2,code[i],L[a]-l2))
		    AddEdge(tmp,Dfs(i,L[a]-l2,l1-l2,DIFFRENT),l2+L[i]-L[a]);
    }
    if (flag == SAME_LONG)
    {
	for (int i = 0; i<n; i++)
	    if (l2+L[i]<=L[a]&&match(code[a]>>l2,code[i],L[i]))
		AddEdge(tmp,Dfs(a,l1,l2+L[i],SAME_LONG),0);
	    else
		if (l2+L[i]>L[a]&&match(code[a]>>l2,code[i],l1-l2))
		    AddEdge(tmp,Dfs(i,L[a]-l2,L[a]-l2,SAME_SHORT),l2+L[i]-L[a]);
    }
    if (flag == SAME_SHORT)
    {
	for (int i = 0; i<n; i++)
	    if (L[i]+l1<=L[a]&&match(code[a]>>l1,code[i],L[i]))
		AddEdge(tmp,Dfs(a,l1+L[i],l2+L[i],SAME_SHORT),0);
	    else
		if (L[i]+l1>L[a]&&match(code[a]>>l1,code[i],L[a]-l1))
		    AddEdge(tmp,Dfs(i,L[i],L[a]-l1,SAME_LONG),l1+L[i]-L[a]);
	for (int i = 0; i<n; i++)
	    for (int j = i+1; j<n; j++)
		if (match(code[i],code[j],min(L[i],L[j])))
		{
		    int b = L[i]>L[j]?i:j,c = i^j^b;
		    if (l1+L[b]<=L[a]&&match(code[a]>>l1,code[b],L[b]))
			AddEdge(tmp,Dfs(a,l1+L[b],l2+L[c],DIFFRENT),0);
		    else
			if (l1+L[b]>L[a]&&l2+L[c]<=L[a]&&match(code[a]>>l1,code[b],L[a]-l1))
			    AddEdge(tmp,Dfs(b,L[a]-l1,L[c],DIFFRENT),L[b]+l1-L[a]);
			else
			    if (l1+L[b]>L[a]&&l2+L[c]>L[a]&&match(code[a]>>l1,code[b],L[a]-l1))
				AddEdge(tmp,Dfs(b,L[c],L[a]-l1,DIFFRENT),L[b]+l1-L[a]);
		}
    }
#ifdef DB
    db_hash[tmp][0] = a;
    db_hash[tmp][1] = l1;
    db_hash[tmp][2] = l2;
    db_hash[tmp][3] = flag;
#endif
    return tmp;
}

void BuildGraph()
{
    cnt = 0;
    for (int i = 0; i<n; i++)
	for (int j = i+1; j<n; j++)
	{
	    int a = L[i]>L[j]?i:j,b = i^j^a;
	    if (match(code[a],code[b],L[b]))
	    {
		AddEdge(S,Dfs(a,L[b],L[b],SAME_SHORT),L[a]);
		AddEdge(S,Dfs(a,L[a],L[b],SAME_LONG),L[a]);
	    }
	}
    for (int i = 0; i<n; i++)
	for (int j = i+1; j<n; j++)
	    for (int k = j+1; k<n; k++)
	    {
		int a = i,b = j,c = k;
		if (L[a]<L[b]) swap(a,b);
		if (L[a]<L[c]) swap(a,c);
		if (L[b]<L[c]) swap(b,c);
		if (match(code[a],code[b],L[b])&&match(code[b],code[c],L[c]))
		    AddEdge(S,Dfs(a,L[b],L[c],DIFFRENT),L[a]);
	    }
    T = ++cnt;
    for (int i = 0; i<n; i++)
	if (id[i][L[i]][L[i]][DIFFRENT])
	    AddEdge(id[i][L[i]][L[i]][DIFFRENT],T,0);
}
int Minpath[MAXNODE+1],q[MAXNODE+1], pre[MAXNODE+1];
bool hash[MAXNODE+1];

#ifdef DB
void db_o(const int x)
{
    printf("%d,%d,%d,%d %d\n", db_hash[x][0], db_hash[x][1], db_hash[x][2], db_hash[x][3], Minpath[x]);
    if (pre[x])
	db_o(pre[x]);
}
#endif

void SPFA()
{
    for (int i = 0; i<=cnt; i++)
	Minpath[i] = INFINIT;
    Minpath[S] = 0;
    hash[S] = true;
    q[1] = S;
    int head = 0,tail = 1;
    while (head!=tail)
    {
	if ((++head) == MAXNODE) head = 0;
	int t = q[head],tmp;
	for (int now = begin[t];now; now = next[now])
	    if (Minpath[t]+cost[now]<Minpath[tmp=end[now]])
	    {
		Minpath[tmp] = Minpath[t]+cost[now];
#ifdef DB
		pre[tmp] = t;
#endif
		if (!hash[tmp])
		{
		    hash[tmp] = true;
		    if ((++tail) == MAXNODE) tail = 0;
		    q[tail] = tmp;
		}
	    }
	hash[t] = false;
    }
    if (Minpath[T] == INFINIT)
	printf("-1\n");
    else
	printf("%d\n",Minpath[T]);
#ifdef DB
    db_o(T);
#endif
}

void Solve()
{
    BuildGraph();
    SPFA();
}

int main()
{
    Init();
    Solve();
    return 0;
}
