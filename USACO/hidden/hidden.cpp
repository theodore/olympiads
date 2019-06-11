/*
PROB:hidden
LANG:C++
*/
#include <cstdio>
#include <cstring>
#include <cstdlib>

namespace again {
	int n;
	char str[200020];

	inline void init();
	inline int answer();
};

inline void again::init()
{
	scanf("%d", &n);
	for (int i=0; i<n; i+=72)
		scanf("%s", str+i);
	for (int i=0, j=n; i<n; ++i, ++j)
		str[j] = str[i];
}

inline int again::answer()
{
	int i(0), l(0);
	for (int j=1; j<2*n; ++j)
		if (str[i+l] < str[j]) {
		}
		else if (str[i+l] > str[j]) {
		}
	return i;
}

int main()
{
	freopen("hidden.in", "r", stdin);
#ifndef DB
	freopen("hidden.out", "w", stdout);
#endif
	again::init();
	printf("%d\n", again::answer());
	return 0;
}

