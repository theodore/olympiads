/*
PROB:hidden
LANG:C++
*/
#include <cstdio>
#include <cstring>
#ifdef DB
#include <cstdlib>
#endif

namespace again {
	int n;
	char str[200020];

	inline void init();
	inline int answer();
};

inline void again::init()
{
	scanf("%s", str);
	n = strlen(str);
	//scanf("%d", &n);
	//for (int i=0; i<n; i+=72)
	//	scanf("%s", str+i);
	for (int i=0, j=n; i<n; ++i, ++j)
		str[j] = str[i];
}

inline int again::answer()
{
	int i=0;
	for (int j=1; j<n;) {
#ifdef DB
		printf("j = %d\n", j);
#endif
		for (int k=0; k<n; ++k)
			if (str[i+k] > str[j+k]) {
				i = j;
#ifdef DB
				printf("i = %d, k = %d\n", i, k);
#endif
				if (k)
					j = i + k;
				else
					++j;
				goto next;
			}
			else if (str[i+k] < str[j+k]) {
#ifdef DB
				printf("str[i+k] = %c, str[j+k] = %c, ", str[i+k], str[j+k]);
				printf("k = %d\n", k);
				//exit(1);
#endif
				if (k)
					j += k;
				else
					++j;
				goto next;
			}
		j += n;
next:;

	}
	return i;
}

int main()
{
	freopen("hidden.in", "r", stdin);
	//freopen("hidden.out", "w", stdout);
	again::init();
	printf("%d\n", again::answer());
	return 0;
}

