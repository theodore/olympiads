#include <cstdio>

const int maxn = 10003;
int n, m;
int sf[maxn], st[maxn];
int f[maxn];

void input()
{
	scanf("%d%d", &n, &m);
	for (int i = 1, a, b; i <= n; ++i)
	{
		scanf("%d%d", &a, &b);
		st[i] = st[i - 1] + a;
		sf[i] = sf[i - 1] + b;
	}
}

#define TimOrz(i, j) (f[j] + (m + st[i] - st[j]) * (sf[n] - sf[j]))
#define G(i) (st[i] * (sf[n] - sf[i]))
#define slope(k, j) ((f[j] - G(j) - f[k] + G(k)) / double(sf[j] - sf[k]))

int deque[maxn], front, back;
int* q = deque;

void dp()
{
	for (int i = 1; i <= n; ++i)
	{
		while (front < back && slope(q[front], q[front + 1]) < m + st[i])
			++front;
		f[i] = TimOrz(i, q[front]);
		while (back > front && slope(q[back - 1], i) > slope(q[back], i))
			--back;
		deque[++back] = i;
	}
}

int main()
{
	input();
	dp();
	printf("%d\n", f[n]);
}
