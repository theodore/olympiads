/*
ID:theodor8
LANG:C++
PROB:milk2
*/
#include <iostream>
#include <algorithm>
using namespace std;

struct Node{
	bool start;
	int when;
};
int n;
Node time_node[10010];
bool cmp(const Node& a, const Node& b)
{
	if (a.when != b.when)
		return a.when < b.when;
	return a.start;
}
void solve()
{
	int milking=0, idle=0, last_start=0, last_end=0, now=0;
	for (int i = 0; i < 2*n; ++i)
		if (time_node[i].start)
			if (now)
				++now;
			else{
				last_start = time_node[i].when;
				if (last_end)
					idle = (time_node[i].when - last_end)>idle?(time_node[i].when - last_end):idle;
				++now;
			}
		else{
			--now;
			if (!now){
				last_end = time_node[i].when;
				if (last_start)
					milking = (time_node[i].when - last_start)>milking?(time_node[i].when - last_start):milking;
			}
		}
	if (!milking)
		milking = time_node[2*n-1].when - time_node[0].when;
	printf("%d %d\n", milking, idle);
}



int main()
{
	freopen("milk2.in", "r", stdin);
	freopen("milk2.out", "w", stdout);
	scanf("%d", &n);
	for (int i=0; i<n; ++i){
		int start, end;
		scanf("%d%d", &start, &end);
		time_node[2*i].when = start;
		time_node[2*i].start = true;
		time_node[2*i+1].when = end;
		time_node[2*i+1].start = false;
	}
	sort(time_node, time_node+2*n, cmp);
	solve();
	return 0;
}
