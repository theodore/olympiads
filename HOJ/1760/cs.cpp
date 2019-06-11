#include <cstdio>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

typedef pair<int, int> state_t;

struct Edge
{
	int vtx;
	Edge *next;
};

const int N_VTX_MAX = 100010;
const int N_EDGE_MAX = 2 * N_VTX_MAX;

map<state_t, int> M;
Edge edge[N_EDGE_MAX], *begin[N_VTX_MAX];
vector<int> color[N_VTX_MAX];
int edge_idx;
int n;

int seq[2 * N_VTX_MAX], n_seq, pos[N_VTX_MAX], depth[N_VTX_MAX];

void add_edge(int u, int v)
{
	Edge *e = &edge[edge_idx ++];
	e->vtx = v, e->next = begin[u], begin[u] = e;
}

void link_vtx(int i, int a, int b)
{
	state_t P = make_pair(a, b);
	if(M.count(P))
		add_edge(i, M[P]), add_edge(M[P], i);
}

void add_vtx(int i, int a, int b)
{
	M[make_pair(a, b)] = i;
	M[make_pair(b, a)] = i;
}

void read_data()
{
	scanf("%d", &n);
	for(int i = 0, a, b, c, d; i < n - 2; i ++)
	{
		scanf("%d%d%d%d", &a, &b, &c, &d);
		a --, b --, c --, d --;
		color[d].push_back(i);
		link_vtx(i, a, b), link_vtx(i, a, c), link_vtx(i, b, c);
		add_vtx(i, a, b), add_vtx(i, a, c), add_vtx(i, b, c);
	}
}

void dfs(int u, int p)
{
	seq[n_seq ++] = u;
	pos[u] = n_seq - 1;
	depth[u] = p == -1 ? 0 : depth[p] + 1;
	for(Edge *e = begin[u]; e; e = e->next)
	{
		int v = e->vtx;
		if(v == p)
			continue;
		dfs(v, u);
		seq[n_seq ++] = u;
	}
}

int log2[2 * N_VTX_MAX];
int st[2 * N_VTX_MAX][30];

void init_st()
{
	for(int i = 0; (1 << i) <= n_seq; i ++)
		log2[1 << i] = i;
	for(int i = 1; i <= n_seq; i ++)
		if(log2[i] == 0)
		   	log2[i] = log2[i - 1];

	for(int i = 0; i < n_seq; i ++)
		st[i][0] = seq[i];
	for(int j = 1; (1 << j) <= n_seq; j ++)
		for(int i = 0; i < n_seq; i ++)
		{
			st[i][j] = st[i][j - 1];
			if(i + (1 << (j - 1)) >= n_seq)
				continue;
			if(depth[st[i + (1 << (j - 1))][j - 1]] < depth[st[i][j]])
				st[i][j] = st[i + (1 << (j - 1))][j - 1];
		}
}

int lca(int u, int v)
{
	int l = min(pos[u], pos[v]),
		r = max(pos[u], pos[v]);
	int len = r - l + 1, mi = log2[len];
	int res = st[l][mi];
	if(depth[st[r - (1 << mi) + 1][mi]] < depth[res])
		res = st[r - (1 << mi) + 1][mi];
	return res;
}

int size[N_VTX_MAX], sum[N_VTX_MAX], weight[N_VTX_MAX];
int ans = 0;

void work()
{
	for(int i = 0; i < n; i ++)
		if(color[i].size())
		{
			int p = color[i][0];
			for(int j = 1; j < (int) color[i].size(); j ++)
				p = lca(p, color[i][j]);
			weight[p] += color[i].size();
		}
}


void solve(int u, int p)
{
	size[u] = 1;
	sum[u] = weight[u];
	for(Edge *e = begin[u]; e; e = e->next)
	{
		int v = e->vtx;
		if(v == p)
			continue;
		solve(v, u);
		if(size[v] == sum[v])
			ans ++;
		size[u] += size[v];
		sum[u] += sum[v];
	}
#if DB & 1
    fprintf(stderr, "%d: %d\n", u, ans);
#endif
}

int main()
{
	read_data();
	dfs(0, -1);
	init_st();
	work();
	solve(0, -1);
	printf("%d\n", ans);
}
