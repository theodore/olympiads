/*
PROB:hidden
LANG:C++
*/
// Just brute force
#include <cstdio>
#include <cstring>

namespace theo {
	int n;
	char str[200010];
	inline void init();
	inline int answer();
};

inline void theo::init()
{
	scanf("%d%s", &n, str);
	for (int i=0, j=n; i<n; ++i, ++j)
		str[j] = str[i];
}

inline int theo::answer()
{
#ifdef DB
	printf("WTF\n");
	printf("%s\n", str);
#endif
	int ans(0);
	for (int i=1; i<n; ++i)
		for (int j=0; j<n; ++j)
			if (str[i+j] < str[ans+j]) {
#ifdef DB
				printf("str[%d+%d] < str[%d+%d]), so ans = %d\n",
						i, j, ans, j, i);
#endif
				ans = i;
				break;
			}
			else if (str[i+j] > str[ans+j])
				break;
	return ans;
}

int main()
{
	freopen("hidden.in", "r", stdin);
	freopen("hidden.ans", "w", stdout);
	theo::init();
	printf("%d\n", theo::answer());
	return 0;
}

