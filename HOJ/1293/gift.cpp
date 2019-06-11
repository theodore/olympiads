#include <cstdio>
#include <queue>
#include <utility>

using namespace std;

const int maxk = 63;
typedef pair<int, int> P;
priority_queue<P> interval;
queue<int> pebble[maxk];

int main()
{
	int n, k;
	scanf("%d%d", &n, &k);
	int r = 0;
	for (int i = 0; i < k; ++i)
	{
		int x, t;
		for (scanf("%d", &x); x--; )
		{
			scanf("%d", &t);
			pebble[i].push(t);
		}
		t = pebble[i].front();
		pebble[i].pop();
		r = max(r, t);
		interval.push(P(-t, i));
	}
	int ans = -1u >> 1;
	for (; ; )
	{
		P t = interval.top();
		interval.pop();
		ans = min(ans, r + t.first);
		if (pebble[t.second].empty())
			break;
		r = max(r, pebble[t.second].front());
		interval.push(P(-pebble[t.second].front(), t.second));
		pebble[t.second].pop();
	}
	printf("%d\n", ans);
}
