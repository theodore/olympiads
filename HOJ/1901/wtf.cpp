#include <cstdio>

int main()
{
	int c(0);
	for (; ; )
	{
		char s[10];
		scanf("%s", s);
		if (s[0] >= '0' && s[0] <= '9')
			++c;
		else
			break;
	}
	printf("%d\n", c);
}
