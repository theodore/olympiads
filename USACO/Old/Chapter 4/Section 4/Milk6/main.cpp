/*
PROB:milk6
LANG:C++
*/
#include <iostream>
#include <queue>
#include <cstring>
//#define Data

using namespace std;

int n, m;
int dist[37], graph[37][37];
int now[37], pre[37];
int cnt[37];

struct E{
	static int num;
	int to, from, cost;
} edge[1013];
int E::num = 0;

queue<int> q;

void reduce(int now, int f){
	if (pre[now]){
		graph[pre[now]][now] -= f;
		graph[now][pre[now]] += f;
		reduce(pre[now], f);
	}
}

#ifndef Data
int main()
{
	freopen("milk6.in", "r", stdin);
	freopen("milk6.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for (int i=0; i<m; ++i){
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		graph[a][b] += c;
		edge[E::num].from = a;
		edge[E::num].to = b;
		edge[E::num++].cost = c;
	}
	// get the dist
	q.push(n);
	++cnt[0];
	while (!q.empty()){
		int now = q.front();
		q.pop();
		for (int i=1; i<n; ++i)
			if (graph[i][now] && !dist[i]){
				dist[i] = dist[now] + 1;
				++cnt[dist[i]];
				q.push(i);
			}
	}
	// there we go
	// remember present arc, and gap
	int i = 1;
	int flow[37];
	int amount = 0;
	for (int j=1; j<=n; ++j)
		now[j] = 2;
	while (dist[1] < n){
		if (i == 1){
			memset(flow, 0, sizeof flow);
			flow[i] = 1 << 25;
		}
		bool found = false;
		for (int j=now[i]; j<=n; ++j)
			if (dist[i] == dist[j] + 1 && graph[i][j] > 0 && !flow[j]){
				found = true;
				now[i] = j;
				pre[j] = i;
				flow[j] = min(flow[i], graph[i][j]);
				i = j;
				break;
			}
		if (i == n){
			amount += flow[i];
			reduce(i, flow[i]);
			now[i=1] = 2;
		}
		if (!found){
			int od = dist[i];
			for (int j=0; j<=n; ++j)
				if (graph[i][j] > 0 && (!found || dist[j] < dist[i]) && !flow[j]){
					found = true;
					dist[i] = dist[j] + 1;
				}
			if (found){
				if (--cnt[od] == 0 && cnt[od+1])
					goto done;
				++cnt[dist[i]];
			}
			else
				if (i != 1){
					dist[i] = n;
					i = pre[i];
				}
				else
					dist[i] = n;
		}
	}
done:
	printf("%d ", amount);





	memset(graph, 0, sizeof graph);
	for (int i=0; i<m; ++i)
		graph[edge[i].from][edge[i].to] = edge[i].cost;
	for (int i=1; i<=n; ++i)
		for (int j=1; j<=n; ++j)
			if (graph[i][j])
				++graph[i][j];
	i = 1;
	amount = 0;
	for (int j=1; j<=n; ++j)
		now[j] = 2;
	// get the dist, again
	q.push(n);
	memset(cnt, 0, sizeof cnt);
	memset(dist, 0, sizeof dist);
	++cnt[0];
	while (!q.empty()){
		int now = q.front();
		q.pop();
		for (int i=1; i<n; ++i)
			if (graph[i][now] && !dist[i]){
				dist[i] = dist[now] + 1;
				++cnt[dist[i]];
				q.push(i);
			}
	}
	// once more
	while (dist[1] < n){
		if (i == 1){
			memset(flow, 0, sizeof flow);
			flow[i] = 1 << 25;
		}
		bool found = false;
		for (int j=now[i]; j<=n; ++j)
			if (dist[i] == dist[j] + 1 && graph[i][j] > 0 && !flow[j]){
				found = true;
				now[i] = j;
				pre[j] = i;
				flow[j] = min(flow[i], graph[i][j]);
				i = j;
				break;
			}
		if (i == n){
			amount += flow[i];
			reduce(i, flow[i]);
			now[i=1] = 2;
		}
		if (!found){
			int od = dist[i];
			for (int j=0; j<=n; ++j)
				if (graph[i][j] > 0 && (!found || dist[j] < dist[i]) && !flow[j]){
					found = true;
					dist[i] = dist[j] + 1;
				}
			if (found){
				if (--cnt[od] == 0 && cnt[od+1])
					goto donea;
				++cnt[dist[i]];
			}
			else
				if (i != 1){
					dist[i] = n;
					i = pre[i];
				}
				else
					dist[i] = n;
		}
	}
donea:

//cout << "\n************\n";
//for (int i=1; i<=n; ++i){
//	for (int j=1; j<=n; ++j)
//		printf("%d ", graph[i][j]);
//	printf("\n");
//}
//printf("\n*****************\n");





	bool S[37] = {false, true};
	q.push(1);
	while (!q.empty()){
		int now = q.front();
		q.pop();
		for (int i=1; i<=n; ++i)
			if (graph[now][i] > 0 && !S[i]){
				S[i] = true;
				q.push(i);
			}
	}


//	for (int i=1; i<=n; ++i)
//		if (S[i])
//			cout << i << endl;









	char ans[2012];
	ans[0] = 0;
	int fuck = 0;
	for (int i=0; i<m; ++i)
		if (S[edge[i].from] && !S[edge[i].to]){
			char tmp[7];
			sprintf(tmp, "%d\n", i+1);
			strcat(ans, tmp);
			++fuck;
		}
	printf("%d\n%s", fuck, ans);
    return 0;
}
#else
int main(){
	freopen("milk6.in", "r", stdin);
	freopen("case4.dot", "w", stdout);
	cin >> n >> m;
	for (int i=0; i<m; ++i){
		int a, b, c;
		cin >> a >> b >> c;
		printf("%d -> %d [label = %d]\n", a, b, c);
	}
	return 0;
}
#endif
