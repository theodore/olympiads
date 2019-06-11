#include <cstdio>
#include <algorithm>

using std::sort;

const int N_MAX = 1000,
		PRIME_MAX = 31625,
	  N_PRIME_MAX = PRIME_MAX,
	  N_DIV_MAX = 400000;

int divisors[N_DIV_MAX];
int ndivisors;

int prime[N_PRIME_MAX];
int nprime;

bool not_prime[N_PRIME_MAX];
void init_prime()
{
	for (int i = 2; i <= PRIME_MAX; i ++)
	{
		if (!not_prime[i])
			prime[nprime ++] = i;
		for (int *p = prime, pmax = PRIME_MAX / i; *p <= pmax; p ++)
		{
			not_prime[*p * i] = true;
			if (!(i % (*p)))
				break;
		}
	}
}

int factor[60];
int cnt_factor[60];
int nfactor;

int hash[PRIME_MAX];
void dfs(int pos, int val)
{
	if (pos == -1)
	{
		if (val < PRIME_MAX)
			hash[val] ++;
		else divisors[ndivisors ++] = val;
		return;
	}
	for (int i = cnt_factor[pos], f = factor[pos]; i >= 0; i --, val *= f)
		dfs(pos - 1, val);
}

int main()
{
	init_prime();

	int n, m;
	scanf("%d%d", &n, &m);
	if (m > n)
	{
		puts("0");
		return 0;
	}
	for (int i = 0; i < n; i ++)
	{
		int num;
		scanf("%d", &num);
		nfactor = 0;
		for (int j = 0; j < nprime; j ++)
		{
			int p = prime[j];
			if (p > num)
				break;
			if (num % p == 0)
			{
				factor[nfactor] = p;
				int &t = cnt_factor[nfactor];
				t = 1;
				num /= p;
				while (num % p == 0)
				{
					num /= p;
					t ++;
				}
				nfactor ++;
			}
		}
		if (num != 1)
		{
			factor[nfactor] = num;
			cnt_factor[nfactor] = 1;
			nfactor ++;
		}
		dfs(nfactor - 1, 1);
	}

	sort(divisors, divisors + ndivisors);

	for (int i = ndivisors - 1; i >= 0;)
	{
		int j = i;
		while (divisors[j] == divisors[i])
			j --;
		if (i - j >= m)
		{
			printf("%d\n", divisors[i]);
			return 0;
		}
		i = j;
	}

	for (int i = PRIME_MAX - 1; i >= 1; i --)
		if (hash[i] >= m)
		{
			printf("%d\n", i);
			break;
		}

	return 0;
}
