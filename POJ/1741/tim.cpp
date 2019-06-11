#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

#define MAXN 10000
#define MAXM MAXN*2

using namespace std;

int n,K;
int Count = 0;
int begin[MAXN+1],end[MAXM+1],next[MAXM+1],cost[MAXM+1];
void AddEdge(int a,int b,int c){
	Count++;
	next[Count] = begin[a];
	begin[a] = Count;
	end[Count] = b;
	cost[Count] = c;
}
void Solve();
void Init(){
	while (true){
		scanf("%d%d",&n,&K);
		if (n == 0 && K == 0)
			break;
		else
			Solve();
	}
}


bool hash[MAXN+1];
int size[MAXN+1];
int GetSize(int x,int fa){
	size[x] = 1;
	for (int now = begin[x]; now; now = next[now])
		if (!hash[end[now]] && end[now]!=fa)
			size[x] += GetSize(end[now],x);
	return size[x];
}

int GetBestRoot(int x){
	GetSize(x,0);
	while (true){
		int MaxSize = 0,id = 0;
		for (int now = begin[x]; now; now = next[now])
			if (!hash[end[now]] && MaxSize < size[end[now]])
				MaxSize = size[id = end[now]];
		if (MaxSize <= (size[x] >> 1))
			break;
		size[x] -= size[id], size[id] += size[x], x = id;
	}
	return x;
}
int dist[MAXN+1];
int cnt;
void GetDist(int x,int fa,int d){
	if (d>K) return;
	dist[++cnt] = d;
	for (int now = begin[x]; now; now = next[now])
		if (!hash[end[now]] && end[now] != fa)
			GetDist(end[now],x,d + cost[now]);
}
int cmp(const void *a,const void *b){
	return (*(int *)a) - (*(int *)b);
}
int dfs(int x){
	x = GetBestRoot(x);
	hash[x] = true;
	int ret = 0;
	for (int now = begin[x]; now; now = next[now])
		if (!hash[end[now]])
			ret += dfs(end[now]);
	cnt = 0;
	GetDist(x,0,0);
	qsort(dist+1,cnt,sizeof(dist[0]),cmp);


	int l = 1, r = cnt;
	while (l<r){
		if (dist[l] + dist[r]<=K) ret += r-l, l++;
		else r--;
	}
	for (int now = begin[x]; now; now = next[now])
		if (!hash[end[now]]){
			int limit = K - cost[now] * 2;
			cnt = 0;
			GetDist(end[now],0, 0);
			qsort(dist+1,cnt,sizeof(dist[0]),cmp);
			int l = 1, r = cnt;
			while (l<r){
				if (dist[l] + dist[r]<=limit) ret -= r-l, l++;
				else r--;
			}
		}
	hash[x] = false;
	return ret;
}

void Solve(){
	Count = 0;
	memset(begin,0,sizeof(begin));
	int t1,t2,t3;
	for (int i = 1; i<n; i++){
		scanf("%d%d%d",&t1,&t2,&t3);
		AddEdge(t1,t2,t3);
		AddEdge(t2,t1,t3);
	}
	printf("%d\n",dfs(1));
}

int main(){
	Init();
	return 0;
}
