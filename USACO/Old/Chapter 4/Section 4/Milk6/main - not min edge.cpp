/*
PROB:milk6
LANG:C++
*/
#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

int n, m;
int dist[37], graph[37][37];
int now[37], pre[37];
int cnt[37];

struct E{
	static int num;
	int to, from;
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

int main()
{
	freopen("milk6.in", "r", stdin);
	freopen("milk6.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for (int i=0; i<m; ++i){
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		graph[a][b] = c;
		edge[E::num].from = a;
		edge[E::num++].to = b;
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
	bool S[37] = {false, true};
	q.push(1);
	while (!q.empty()){
		int now = q.front();
		q.pop();
		for (int i=1; i<=n; ++i)
			if (graph[now][i] > 1 && !S[i]){
				S[i] = true;
				q.push(i);
			}
	}
	char ans[2012];
	ans[0] = 0;
	for (int i=0; i<m; ++i)
		if (S[edge[i].from] && !S[edge[i].to]){
			char tmp[7];
			sprintf(tmp, "%d\n", i+1);
			strcat(ans, tmp);
		}
	printf("%d\n%s", strlen(ans)/2, ans);
    return 0;
}
