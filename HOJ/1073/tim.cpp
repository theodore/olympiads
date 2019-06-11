#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <queue>


#define MAXN 50
#define MAXM MAXN*MAXN
#define MAXK 201

#define INFINITE 1000000000

#define MAX(a,b) ((a)>(b)?(a):(b))

//#define FILEIO
//#define DEBUG

using namespace std;

int n,m,K,S,T;
int Count = 0;
int begin[MAXN+1], end[MAXM+1], next[MAXM+1], cost[MAXM+1];
void AddEdge(int a, int b, int c){
	Count++;
	next[Count] = begin[a];
	begin[a] = Count;
	end[Count] = b;
	cost[Count] = c;
}

void Init(){
	scanf("%d%d%d%d%d",&n,&m,&K,&S,&T);
	while (m--){
		int t1,t2,t3;
		scanf("%d%d%d",&t1,&t2,&t3);
		AddEdge(t1,t2,t3);
	}
}
typedef char vtx_t;
typedef long long hash_t;

class Path{
public:
	vtx_t path[MAXN+1];
	int nodeid[MAXN+1];
	int midcost[MAXN+1];
	vtx_t nvtx;
	vtx_t deviation_pos;
	int deviation_node_id;
	int cost;
	int parentpath;
	inline friend bool operator < (const Path &a, const Path &b){
		if (a.cost != b.cost) return a.cost > b.cost ? 1 : 0;
		return memcmp(a.path,b.path,sizeof(vtx_t) * MAX(a.nvtx, b.nvtx)) > 0 ? 1 : 0;
	}
};
Path KthPath[MAXK+1];


void GetMidCost(Path &p){
	for (int i = 0; i<p.nvtx-1; i++){
		vtx_t vtx0 = p.path[i], vtx1 = p.path[i+1];
		for (int now = begin[vtx0]; now; now = next[now])
			if (end[now] == vtx1){
				p.midcost[i] = cost[now];
				break;
			}
	}
}

class Node{
public:
	vtx_t vtx;
	int fatherid;
	hash_t sonset;
	hash_t fatherset;
	void AddSon(vtx_t vtx){
		sonset |= ((hash_t)1 << (hash_t) vtx);
	}
};

Node node[MAXK * MAXN * MAXN+1];

priority_queue<Path> PathSet;

void Out(const Path &p){
	printf("%d",p.path[0]);
	for (int i = 1; i<p.nvtx; i++)
		printf("-%d",p.path[i]);
#ifdef DEBUG
	printf(" | %d",p.cost);
#endif
	printf("\n");
}

class VtxPath{
public:
	int cost;
	vtx_t path[MAXN];
	vtx_t nvtx;
	inline void push_vtx(vtx_t vtx){
		path[nvtx++] = vtx;
	}
};
VtxPath Minpath[MAXN+1];
#define Cover(hash, vtx) (((hash_t)hash) | ((hash_t)1 << (hash_t)(vtx)))
#define Covered(hash, vtx) ((((hash_t)hash) >> ((hash_t)vtx)) & 1)
#define Uncover(hash, vtx) (((hash_t)hash) & (~((hash_t)1 << (hash_t)(vtx))))

int MaxCost = 0;
queue<int> q;
int cmpVtxPath(const VtxPath &a, const VtxPath &b){
	if (a.cost != b.cost) return a.cost - b.cost;
	return memcmp(a.path,b.path,MAX(a.nvtx, b.nvtx));
}

int cntNode = 0;
void CreateNode(vtx_t vtx, int fatherid, hash_t sonset, hash_t fatherset){
	cntNode++;
	node[cntNode].vtx = vtx;
	node[cntNode].fatherid = fatherid;
	node[fatherid].AddSon(vtx);
	node[cntNode].sonset = sonset;
	node[cntNode].fatherset = fatherset;
}
void InitShortestPath(){
	for (int i = 1; i<=n; i++)
		Minpath[i].cost = INFINITE;
	Minpath[S].cost = 0;
	Minpath[S].push_vtx(S);
	hash_t hash = Cover(0, S);
	q.push(S);
	VtxPath pathtmp;
	while (!q.empty()){
		int t = q.front(),tmp;
		q.pop();
		for (int now = begin[t]; now; now = next[now]){
			tmp = end[now];
			pathtmp = Minpath[t];
			pathtmp.push_vtx(tmp);
			pathtmp.cost += cost[now];
			if (cmpVtxPath(pathtmp, Minpath[tmp]) < 0){
				Minpath[tmp] = pathtmp;
				if (!Covered(hash, tmp)){
					hash = Cover(hash, tmp);
					q.push(tmp);
				}
			}
		}
		hash = Uncover(hash, t);
	}
	if (Minpath[T].cost == INFINITE){
		printf("no\n");
		exit(0);
	}
	KthPath[1].cost = Minpath[T].cost;
	KthPath[1].nvtx = Minpath[T].nvtx;
	memcpy(KthPath[1].path, Minpath[T].path, sizeof(vtx_t) * (Minpath[T].nvtx));
	KthPath[1].deviation_pos = 1;
	KthPath[1].deviation_node_id = 2;
	for (int i = 0; i<KthPath[1].nvtx; i++)
		KthPath[1].nodeid[i] = i+1;
	KthPath[1].parentpath = 0;
	GetMidCost(KthPath[1]);
	CreateNode(KthPath[1].path[0], 0, Cover(0, KthPath[1].path[1]), 0);
	hash_t fatherset = 0;
	for (int i = 1; i<KthPath[1].nvtx-1; i++){
		fatherset = Cover(fatherset, KthPath[1].path[i-1]);
		CreateNode(KthPath[1].path[i], i, Cover(0,KthPath[1].path[i+1]), fatherset);
	}
	fatherset = Cover(fatherset, KthPath[1].path[KthPath[1].nvtx-2]);
	CreateNode(KthPath[1].path[KthPath[1].nvtx-1], KthPath[1].nvtx-1, 0, fatherset);
	MaxCost = MAX(MaxCost,KthPath[1].cost);
}

bool AugPath(vtx_t Source, hash_t GlobalBannedVtx, hash_t SourceBannedVtx, vtx_t PrevPath[], vtx_t PrevNvtx, int PrevNodeId[], int PrevCost){
	for (int i = 1; i<=n; i++)
		Minpath[i].cost = INFINITE;
	memset(&Minpath[Source],0,sizeof(VtxPath));
	Minpath[Source].push_vtx(Source);
	VtxPath pathtmp;
	q.push(Source);
	hash_t hash = Cover(0,Source);
	while (!q.empty()){
		int t = q.front(),tmp;
		q.pop();
		for (int now = begin[t]; now; now = next[now]){
			tmp = end[now];
			if (!Covered(GlobalBannedVtx, tmp)){
				if (t == Source && Covered(SourceBannedVtx, tmp)) continue;
				pathtmp = Minpath[t];
				pathtmp.cost += cost[now];
				pathtmp.push_vtx(tmp);
				if (cmpVtxPath(pathtmp, Minpath[tmp]) < 0){
					Minpath[tmp] = pathtmp;
					if (!Covered(hash, tmp)){
						hash = Cover(hash,tmp);
						q.push(tmp);
					}
				}
			}
			hash = Uncover(hash,t);
		}
	}
	if (Minpath[T].cost == INFINITE) return false;

	MaxCost = MAX(MaxCost, Minpath[T].cost + PrevCost);
	Path p;
	memset(&p,0,sizeof(Path));
	p.cost = Minpath[T].cost + PrevCost;
	p.deviation_node_id = PrevNodeId[PrevNvtx+1];
	p.deviation_pos = PrevNvtx+1;
	for (int i = 0; i<PrevNvtx; i++){
		p.path[i] = PrevPath[i];
		p.nodeid[i] = PrevNodeId[i];
	}
	p.path[PrevNvtx] = Source;
	p.nodeid[PrevNvtx] = PrevNodeId[PrevNvtx];
	for (int i = 1; i<Minpath[T].nvtx; i++){
		p.path[PrevNvtx + i] = Minpath[T].path[i];
		p.nodeid[PrevNvtx + i] = cntNode + i;
	}
	p.nvtx = PrevNvtx + Minpath[T].nvtx;
	GetMidCost(p);
	p.parentpath = 0;
	hash_t fatherset = node[PrevNodeId[PrevNvtx]].fatherset;
	fatherset = Cover(fatherset, Source);
	CreateNode(Minpath[T].path[1], PrevNodeId[PrevNvtx], Cover(0, Minpath[T].path[2]), fatherset);
	for (int i = 2; i<Minpath[T].nvtx; i++){
		fatherset = Cover(fatherset, Minpath[T].path[i-1]);
		CreateNode(Minpath[T].path[i], cntNode, Cover(0, Minpath[T].path[i+1]), fatherset);
	}
	PathSet.push(p);
}
void Augment(int kth){
	Path p = KthPath[kth];
	Path pathtmp;
	int PrevCost = 0;
	for (int i = 0; i<p.deviation_pos-1; i++)
		PrevCost += p.midcost[i];
	for (int i = p.deviation_pos - 1; i<p.nvtx - 1; i++){
		AugPath(p.path[i], node[p.nodeid[i]].fatherset, node[p.nodeid[i]].sonset, p.path, i, p.nodeid, PrevCost);
		PrevCost += p.midcost[i];
	}
}

void Solve(){
	InitShortestPath();
	//Out(KthPath[1]);
	for (int k = 2; k<=K; k++){
		Augment(k-1);
		if (PathSet.empty()){
			printf("No\n");
			return;
		}
		KthPath[k] = PathSet.top();
	//	Out(KthPath[k]);
		// CreateNodes
		PathSet.pop();
	}
	Out(KthPath[K]);
}

int main(){
#ifdef FILEIO
	freopen("kshort.in","r",stdin);
	freopen("kshort.out","w",stdout);
#endif
	Init();
	Solve();
	return 0;
}

