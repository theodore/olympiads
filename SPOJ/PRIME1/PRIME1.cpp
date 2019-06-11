#include <cstdio>
#include <cstring>
#include <cmath>
#define max(a, b) ((a) > (b) ? (a) : (b))

int a, b;
int prime[31250001];
int list[3410];
bool rest[100003];

int main()
{
	freopen("ans", "w", stdout);
		memset(prime, 0xff, sizeof prime);
		prime[0] ^= 2;
		for (int i=3; i<=31625; i+=2) {
			if (!(prime[i/32] & (1<<(i%32))))
				continue;
			for (int j=i+i+i; j<=31625; j+=i+i) {
				prime[j/32] = ~(~prime[j/32] | (1<<(j%32)));
			}
		}
		//list[0] = 1;
		//list[1] = 2;
		for (int i=3; i<=31625; i+=2)
			if ((prime[i/32] & (1<<(i%32))))
				list[++list[0]] = i;
	int _;
	for (scanf("%d", &_); _; --_) {
		scanf("%d%d", &a, &b);
		if (a <= 2)
			printf("2\n");
		if (!(a & 1))
			++a;
		/*
		for (int i=a; i<=b; i+=2)
			if (i <= 31625) {
				if (prime[i/32] & (1<<(i%32)))
					printf("%d\n", i);
			}
			else {
				for (int j=1; j<=list[0]; ++j)
					if (i%list[j] == 0)
						goto next;
				printf("%d\n", i);
next:;
			}
		putchar('\n');
		*/
		memset(rest, 1, sizeof rest);
		if (a == 1)
			rest[0] = false;
		for (int i = 1; i <= list[0] && list[i]+list[i]+list[i] <= b; ++ i) {
			int j = max(3, a/list[i]);
			if (list[i]*j < a)
				++j;
			if (!(j&1))
				++j;
			for (; list[i]*j<=b; j+=2)
				rest[list[i]*j-a] = false;
		}
		for (int i=a; i<=b; i+=2)
			/*
			if (i<=31625)
			{
				if (prime[i/32] & (1<<(i%32)))
					printf("%d\n", i);
			}
			else
			*/
			if (rest[i-a])
				printf("%d\n", i);
		putchar('\n');
	}
	return 0;
}

