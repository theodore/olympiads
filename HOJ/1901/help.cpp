#include <cstdio>

int n, N, start[1000000], end[1000000];

int main()
{
	fscanf(fopen("in", "r"), "%d", &n);
	for (N = 1; N <= n + 1; N <<= 1);
	printf("N = %d\n", N);
	start[N] = end[N] = 0;
	for (int i = N + 1; i <= N + n; ++i)
	{
		start[i] = i - N;
		end[i] = i - N + 1;
	}
	for (int i = N + n + 1; i < N + N; ++i)
	{
		//start[i] = end[i] = 0;
		start[i] = i - N;
		end[i] = i - N + 1;
	}
	for (int i = N - 1; i; --i)
	{
		start[i] = start[i+i];
		end[i] = end[i+i+1];
	}
	for (; ; )
	{
		scanf("%d", &n);
		printf("[%d, %d)\n", start[n], end[n]);
	}
}
