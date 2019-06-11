// Google Code Jam 2010, fence
// 10^10 <= L <= 10^18
// 1 <= N <= 100
// 1 <= Bi <= 100,000
// Start: 6:36 PM, Jun 24, 2010
#include <cstdio>
#include <cstring>
#include <cassert>
#include <queue>

long long l;
int n, max, board[100], ans[100000];

std::queue <int> q;
bool in[100000];
void spfa()
{
	memset(ans, 0x7f, sizeof ans);
	for (int i=0; i<n; ++i)
		if (board[i] < board[max]) {
			ans[board[i]] = 1;
			q.push(board[i]);
		}
	while (!q.empty()) {
		static int now, t;
		now = q.front();
		q.pop();
		in[now] = false;
		for (int i=0; i<n; ++i) {
			t = now + board[i];
			if (t == board[max])
				continue;
			else if (t < board[max]) {
				if (ans[t] > ans[now] + 1) {
					ans[t] = ans[now] + 1;
					if (!in[t]) {
						in[t] = true;
						q.push(t);
					}
				}
			}
			else {
				t -= board[max];
				if (ans[t] > ans[now]) {
					ans[t] = ans[now];
					if (!in[t]) {
						in[t] = true;
						q.push(t);
					}
				}
			}
		}
	}
}

// Remember to init everything
void answer()
{
	scanf("%lld%d", &l, &n);
	if (l < 10000000000LL && board[max] > 100) {
		int a[1];
		a[0xfffffff] = 12213;
	}
	max = 0;
	for (int i=0; i<n; ++i) {
		scanf("%d", board + i);
		if (board[i] > board[max])
			max = i;
	}
	long long k(l / board[max]);
	int t(l % board[max]);
	if (t == 0)
		printf("%lld\n", k);
	else {
		spfa();
		if (ans[t] == 0x7f7f7f7f)
			printf("IMPOSSIBLE\n");
		else
			printf("%lld\n", k + ans[t]);
	}
}

int main()
{
#ifdef LOCAL
	freopen("fence.in", "r", stdin);
	freopen("fence.out", "w", stdout);
#endif
	int _;
	scanf("%d", &_);
	for (int i=1; i<=_; ++i) {
		printf("Case #%d: ", i);
		answer();
	}
	return 0;
}

