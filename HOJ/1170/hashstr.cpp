#include <cstdio>
#include <cstring>

char s[1000];

int main()
{
    scanf("%s", s);
    int n = strlen(s);
    int z = 0;
    for (int i = 0; i < n; ++i)
	z = z * 127 + s[i] - 1;
    printf("%u\n", z);
}
