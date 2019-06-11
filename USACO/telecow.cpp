/*
PROB:telecow
LANG:C++
*/
#pragma warning(disable: 4996)
#include <cstdio>
#include <cstring>
#define OT(x) ((x)>n ? (x)-n : (x)+n)
#define OP(x) ((((x) - 1) ^ 1) + 1)
#define infinity (1<<29)
#define min(a, b) ((a) < (b) ? (a) : (b))
//#define DB

namespace wxj {
	struct E {
		int a, b;
	};
	E edge[610];
	int n, m, s, t;
	int remove(-1), flow_ans;
	int start[210], to[2610], next[2610], cap[2610];
	int dist[210], pre[210], flow[210];
	bool removed[110];
	
	int max_flow(int, int);
};

int wxj::max_flow(int s, int t)
{
	int ret(0);
	// build the graph
	int index(0);
	memset(start, 0, sizeof start);
	for (int i=0; i<m; ++i) {
#define A edge[i].a
#define B edge[i].b
		to[++index] = B;
		cap[index] = infinity;
		next[index] = start[OT(A)];
		start[OT(A)] = index;
		
		to[++index] = OT(A);
		cap[index] = 0;
		next[index] = start[B];
		start[B] = index;
		
		to[++index] = A;
		cap[index] = infinity;
		next[index] = start[OT(B)];
		start[OT(B)] = index;
		
		to[++index] = OT(B);
		cap[index] = 0;
		next[index] = start[A];
		start[A] = index;
#undef A
#undef B
	}
	for (int i=1; i<=n; ++i)
		if (i != s && i != t && i!=remove && !removed[i]) {
			to[++index] = OT(i);
			cap[index] = 1;
			next[index] = start[i];
			start[i] = index;
			
			to[++index] = i;
			cap[index] = 0;
			next[index] = start[OT(i)];
			start[OT(i)] = index;
		}
	// there we go!
	memset(dist, 0, sizeof dist);
	s = OT(s);
	int i(s);
	while (dist[s] < n*2) {
		if (i == s) {
			memset(flow, 0, sizeof flow);
			flow[i] = infinity;
		}
		bool found(false);
		for (int e=start[i]; e; e=next[e])
			if (dist[to[e]]+1==dist[i] && !flow[to[e]] && cap[e]) {
				found = true;
				flow[to[e]] = min(flow[i], cap[e]);
				pre[i = to[e]] = e;
				break;
			}
		if (i == t) {
			ret += flow[i];
			for (; i!=s; i=to[OP(pre[i])]) {
				cap[pre[i]] -= flow[t];
				cap[OP(pre[i])] += flow[t];
			}
		}
		if (!found) {
			dist[i] = n*2;
			for (int e=start[i]; e; e=next[e])
				if (cap[e] && dist[to[e]] < dist[i])
					dist[i] = dist[to[e]] + 1;
			if (i != s)
				i = to[OP(pre[i])];
		}
	}
	return ret;
}

int main()
{
	freopen("telecow.in", "r", stdin);
	freopen("telecow.out", "w", stdout);
	scanf("%d%d%d%d", &wxj::n, &wxj::m, &wxj::s, &wxj::t);
	for (int i=0; i<wxj::m; ++i)
		scanf("%d%d", &wxj::edge[i].a, &wxj::edge[i].b);
	printf("%d\n", wxj::flow_ans=wxj::max_flow(wxj::s, wxj::t));
	bool first_output(true);
	for (int i=1; i<=wxj::n; ++i) {
#ifdef DB
		printf("i = %d\n", i);
#endif
		if (i == wxj::s || i == wxj::t)
			continue;
		wxj::remove = i;
		int temp(wxj::max_flow(wxj::s, wxj::t));
		if (temp + 1 == wxj::flow_ans) {
			if (first_output) {
				first_output = false;
				printf("%d", i);
			}
			else
				printf(" %d", i);
			wxj::removed[i] = true;
			if ((wxj::flow_ans=temp) == 0)
				break;
		}
	}
	printf("\n");
	return 0;
}
