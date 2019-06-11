/*
 * $File: kshort.cpp
 * $Date: Sat Jan 23 18:28:39 2010 CST
 *
 * Online judge: p1073
 */
#define INPUT	"kshort.in"
#define OUTPUT	"kshort.out"

#define STDIO

#include <cstdio>
#include <cstring>

namespace Solve
{
	const int NVTX_MAX = 55, NPATH_MAX = 205,
		  NTREE_NODE_MAX = NVTX_MAX * NPATH_MAX,
		  NCANDIDATA_MAX = NPATH_MAX * NVTX_MAX,
		  INF = 1 << 30;

	int graph[NVTX_MAX][NVTX_MAX];
	int nvtx;

	int ntree_node;
	bool arc_used[NTREE_NODE_MAX][NVTX_MAX];

	typedef unsigned int Bitset32_t;
	Bitset32_t vtx_usable[NVTX_MAX / 32 + 1];

	struct Path
	{
		int prev[NVTX_MAX], len,
			dev, // deviation vertex
			dev_tree_node,
			plen_self; // the number of vertices from dev to tvtx.
		void print(FILE *fout) const;
	};
	Path path[NCANDIDATA_MAX];
	int path_tvtx, path_svtx;

	namespace Heap_dijkstra
	{
		struct Node
		{
			int vtx, dist;
		};
		Node data[NVTX_MAX];
		int len, vtx_pos[NVTX_MAX];
		int extract_min_vtx();
		void decrease_dist(int vtx, int dist);
	}
	namespace Heap_path
	{
		int len, data[NCANDIDATA_MAX];
		int extract_min();
		void insert(int num);
	}

	void dijkstra(int svtx, int tvtx, bool *aused, Path &p);

	int calc_kth(int svtx, int tvtx, int k); // return the number of the path, or -1 if not exist

	void solve(FILE *fin, FILE *fout);
}

void Solve::solve(FILE *fin, FILE *fout)
{
	int m, k, a, b;
	fscanf(fin, "%d %d %d %d %d", &nvtx, &m, &k, &b, &a);
	// the graph is reversed so that the path
	// with the min alphabetical can be easily computed.
	a --;
	b --;
	for (int i = 0; i < m; i ++)
	{
		int u, v, l;
		fscanf(fin, "%d %d %d", &v, &u, &l);
		u --;
		v --;
		graph[u][v] = l;
	}
	int ans = calc_kth(a, b, k);
	if (ans == -1)
		fprintf(fout, "No\n");
	else
		path[ans].print(fout);
}

void Solve::Path::print(FILE *fout) const
{
	fprintf(fout, "%d", path_tvtx + 1);
	for (int i = path_tvtx, p; i != path_svtx; i = p)
	{
		p = prev[i];
		fprintf(fout, "-%d", p + 1);
	}
	fprintf(fout, "\n");
}

int Solve::Heap_dijkstra::extract_min_vtx()
{
	int ret = data[0].vtx;
	Node v0 = data[-- len];
	if (len == 0)
		return ret;
	int register pos = 0;
	while (1)
	{
		int register
			ch = (pos << 1) + 1,
			ch1 = (pos + 1) << 1;
		if (ch1 < len && data[ch1].dist < data[ch].dist)
			ch = ch1;
		if (ch < len && data[ch].dist < v0.dist)
		{
			data[pos] = data[ch];
			vtx_pos[data[pos].vtx] = pos;
			pos = ch;
		} else 
		{
			data[pos] = v0;
			vtx_pos[v0.vtx] = pos;
			return ret;
		}
	}
}

void Solve::Heap_dijkstra::decrease_dist(int vtx, int dist)
{
	int register pos = vtx_pos[vtx], par = (pos - 1) >> 1;
	while (pos && dist < data[par].dist)
	{
		data[pos] = data[par];
		vtx_pos[data[pos].vtx] = pos;
		pos = par;
		par = (par - 1) >> 1;
	}
	data[pos].vtx = vtx;
	data[pos].dist = dist;
	vtx_pos[vtx] = pos;
}

#define COMPARE_PATH(_p1_, _p2_) \
({ \
 int register ret; \
 const Path &_a_ = path[(_p1_)], &_b_ = path[(_p2_)]; \
 if (_a_.len < _b_.len) \
	ret = 1; \
 else if (_a_.len > _b_.len) \
	ret = 0; \
 else \
 { \
	int register _p_ = path_tvtx; \
	while (_p_ != path_svtx && _a_.prev[_p_] == _b_.prev[_p_]) \
		_p_ = _a_.prev[_p_]; \
	ret = (int)(_p_ != path_svtx && _a_.prev[_p_] < _b_.prev[_p_]); \
 } \
 ret; \
})
int Solve::Heap_path::extract_min()
{
	int ret = data[0];
	int v0 = data[-- len];
	if (len == 0)
		return ret;
	int register pos = 0;
	while (1)
	{
		int register
			ch = (pos << 1) + 1,
			ch1 = (pos + 1) << 1;
		if (ch1 < len && COMPARE_PATH(data[ch1], data[ch]))
			ch = ch1;
		if (ch < len && COMPARE_PATH(data[ch], v0))
		{
			data[pos] = data[ch];
			pos = ch;
		} else
		{
			data[pos] = v0;
			return ret;
		}
	}
}

void Solve::Heap_path::insert(int num)
{
	int pos = (len ++), par = (pos - 1) >> 1;
	while (pos && COMPARE_PATH(num, data[par]))
	{
		data[pos] = data[par];
		pos = par;
		par = (par - 1) >> 1;
	}
	data[pos] = num;
}
#undef COMPARE_PATH

void Solve::dijkstra(int svtx, int tvtx, bool *aused, Path &p)
{
	int dist[NVTX_MAX], plen[NVTX_MAX];
	Heap_dijkstra::len = nvtx - 1;
	for (int register i = nvtx - 2; i >= 0; i --)
	{
		dist[i] = Heap_dijkstra::data[i].dist = INF;
		Heap_dijkstra::data[i].vtx = i;
		Heap_dijkstra::vtx_pos[i] = i;
	}
	dist[svtx] = 0;
	if (svtx != nvtx - 1)
	{
		Heap_dijkstra::data[svtx].vtx = nvtx - 1;
		Heap_dijkstra::vtx_pos[nvtx - 1] = svtx;
		dist[nvtx - 1] = INF;
	}
	plen[svtx] = 0;
	for (int register i = nvtx - 1; i >= 0; i --)
		if ((vtx_usable[i >> 5] & (1 << (i & 31)))
				&& graph[svtx][i] && !aused[i])
		{
			int register d1 = graph[svtx][i];
			if (d1 < dist[i])
			{
				dist[i] = d1;
				Heap_dijkstra::decrease_dist(i, d1);
				p.prev[i] = svtx;
				plen[i] = plen[svtx] + 1;
			}
		}

	while (Heap_dijkstra::len)
	{
		int v0 = Heap_dijkstra::extract_min_vtx(), d0 = dist[v0], plen1 = plen[v0] + 1;
		if (v0 == tvtx)
		{
			p.len = d0;
			p.plen_self = plen1 - 1;
			return;
		}
		if (d0 == INF)
			break;
		for (int register i = nvtx - 1; i >= 0; i --)
			if ((vtx_usable[i >> 5] & (1 << (i & 31))) && graph[v0][i])
			{
				int register d1 = d0 + graph[v0][i];
				if (d1 < dist[i])
				{
					dist[i] = d1;
					Heap_dijkstra::decrease_dist(i, d1);
					p.prev[i] = v0;
					plen[i] = plen1;
				} else if (d1 == dist[i] && p.prev[i] > v0)
				{
					p.prev[i] = v0;
					plen[i] = plen1;
				}
			}
	}
	p.len = INF;
}

int Solve::calc_kth(int svtx, int tvtx, int k)
{
#define UNSET(_p_) \
	{ \
		vtx_usable[(_p_) >> 5] &= ~(1 << ((_p_) & 31)); \
	}
	path_tvtx = tvtx;
	path_svtx = svtx;
	memset(vtx_usable, ~0, sizeof(vtx_usable));
	dijkstra(svtx, tvtx, arc_used[0], path[0]);
	if (path[0].len == INF)
		return -1;
	path[0].dev = svtx;
	path[0].dev_tree_node = 0;
	ntree_node = 1;
	Heap_path::insert(0);
	int npath = 1;
	int vtx_devpath[NVTX_MAX], nvtx_devpath;
	while (-- k)
	{
		if (!Heap_path::len)
			return -1;
		Path &p0 = path[Heap_path::extract_min()];

		nvtx_devpath = 0;

		// mark the arcs newly added to T[i]
		ntree_node += p0.plen_self;
		int cur_tree_node = ntree_node - 1;
		for (int i = tvtx, prev; i != p0.dev; i = prev)
		{
			prev = p0.prev[i];
			cur_tree_node --;
			if (prev == p0.dev)
				cur_tree_node = p0.dev_tree_node;
			arc_used[cur_tree_node][i] = true;
			vtx_devpath[nvtx_devpath ++] = i;
		}
		vtx_devpath[nvtx_devpath ++] = p0.dev;

		// avoid loop
		memset(vtx_usable, ~0, sizeof(vtx_usable));
		for (int i = p0.dev; i != svtx; i = p0.prev[i])
			UNSET(i);
		UNSET(svtx);

		for (int i = nvtx_devpath - 1; i; i --)
		{
			int register s = vtx_devpath[i];
			UNSET(s);
			dijkstra(s, tvtx, arc_used[cur_tree_node], path[npath]);
			if (path[npath].len != INF)
			{
				for (int register j = s, prev; j != svtx; j = prev)
				{
					prev = p0.prev[j];
					path[npath].len += graph[prev][j];
					path[npath].prev[j] = prev;
				}
				path[npath].dev = s;
				path[npath].dev_tree_node = cur_tree_node;
				Heap_path::insert(npath ++);
			}
			if (cur_tree_node == p0.dev_tree_node)
				cur_tree_node = ntree_node - p0.plen_self;
			else cur_tree_node ++;
		}
	}
	if (!Heap_path::len)
		return -1;
	return Heap_path::extract_min();
#undef UNSET
}

int main()
{
#ifdef STDIO
	Solve::solve(stdin, stdout);
#else
	FILE *fin = fopen(INPUT, "r"),
		 *fout = fopen(OUTPUT, "w");
	Solve::solve(fin, fout);
	fclose(fin);
	fclose(fout);
#endif
}

