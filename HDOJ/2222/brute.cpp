#include <cstdio>
#include <cstring>

const int maxn = 10003;
const int maxl = 53;
const int maxs = 1000003;
int n;
char word[maxn][maxl];
char str[maxs];

bool in(const char s[])
{
	int wl = strlen(s);
	int l = strlen(str);
	for (int i = 0; i + wl <= l; ++i)
	{
		for (int j = 0; j < wl; ++j)
			if (s[j] != str[i + j])
				goto next;
#ifdef DB
		fprintf(stderr, "true\n");
#endif
		return true;
next:;
	}
#ifdef DB
	fprintf(stderr, "f\n");
#endif
	return false;
}

int main()
{
	int _;
	for (scanf("%d", &_); _--; )
	{
		scanf("%d", &n);
		for (int i = 0; i < n; ++i)
			scanf("%s", word[i]);
		scanf("%s", str);
		int ans = 0;
		for (int i = 0; i < n; ++i)
			ans += in(word[i]);
		printf("%d\n", ans);
	}
}
