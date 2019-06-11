/*
PROB:milk6
LANG:C++
*/
#pragma warning(disable: 4996)
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define infinity (1<<29)
#define min(a, b) ((a) < (b) ? (a) : (b))
//#define DB

// 32, 1000

namespace wxj {
	struct E {
		int a, b, c, n;
	} edge[1010];
	int n, m;
	//const int con = 1000;
	int cap[35][35], dist[35], pre[35], flow[35];
	long long int flow_ans;
	int remove(-1);
	int ans[1010];

	long long int max_flow(int s, int t);
	int cmp(const void*, const void*);
	int int_cmp(const void*, const void*);
};

long long int wxj::max_flow(int s, int t)
{
	long long int ret(0);
	memset(cap, 0, sizeof cap);
	// maybe memset some more
	memset(dist, 0, sizeof dist);
	pre[s] = s;
	// build a new graph for max flow
	//if (remove == -1)
	//	for (int i=0; i<m; ++i) {
	//		cap[edge[i].a][edge[i].b] += edge[i].c * con;
	//		//cap[edge[i].b][edge[i].a] += edge[i].c * con;
	//	}
	//else
	for (int i=0; i<m; ++i)
		if (i != remove) {
			cap[edge[i].a][edge[i].b] += edge[i].c;
			//cap[edge[i].b][edge[i].a] += edge[i].c;
		}
	// there we go!
	int i(s);
	while (dist[s] < n) {
		if (i == s) {
			memset(flow, 0, sizeof flow);
			flow[i] = infinity;
		}
		bool found(false);
		for (int j=1; j<=n; ++j)
			if (dist[j]+1==dist[i] && !flow[j] && cap[i][j]) {
				found = true;
				flow[j] = min(flow[i], cap[i][j]);
				pre[j] = i;
				i = j;
				break;
			}
		if (i == t) {
			ret += flow[i];
			while (i != s) {
				cap[pre[i]][i] -= flow[t];
				cap[i][pre[i]] += flow[t];
				i = pre[i];
			}
		}
		if (!found) {
			dist[i] = n;
			for (int j=1; j<=n; ++j)
				if (cap[i][j] && dist[j] < dist[i])
					dist[i] = dist[j] + 1;
			i = pre[i];
		}
	}
	return ret;
}

// compare function for qsort
// first sort by capacity, from lagest to smallest
// then sort by num, in case of tie, from smallest to largest
int wxj::cmp(const void* a, const void * b)
{
	if (((E*)a)->c != ((E*)b)->c)
		return ((E*)b)->c - ((E*)a)->c;
	return ((E*)a)->n - ((E*)b)->n;
}

int wxj::int_cmp(const void* a, const void* b)
{
	return *(int*)a - *(int*)b;
}

int main()
{
	freopen("milk6.in", "r", stdin);
	freopen("milk6.out", "w", stdout);
	using wxj::n;
	using wxj::m;
	using wxj::edge;
	using wxj::max_flow;
	using wxj::flow_ans;
	using wxj::E;
	using wxj::cmp;
	scanf("%d%d", &n, &m);
	for (int i=0; i<m; ++i) {
		scanf("%d%d%d", &edge[i].a, &edge[i].b, &edge[i].c);
		edge[i].n = i;
	}
	printf("%lld ", flow_ans = max_flow(1, n));
	qsort(edge, m, sizeof(E), cmp);
	for (int e=0; e<m; ++e) {
		wxj::remove = e;
		long long int temp(max_flow(1, n));
#ifdef DB
		printf("flow_ans = %d, temp = %d\n", flow_ans, temp);
#endif
		if (temp + edge[e].c == flow_ans) {
			edge[e].c = 0;
			wxj::ans[++wxj::ans[0]] = edge[e].n+1;
			if ((flow_ans = temp) == 0)
				break;
		}
	}
	qsort(wxj::ans+1, wxj::ans[0], 4, wxj::int_cmp);
	for (int i=0; i<=wxj::ans[0]; ++i)
		printf("%d\n", wxj::ans[i]);
	return 0;
}
