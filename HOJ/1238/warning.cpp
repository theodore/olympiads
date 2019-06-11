#include <cstdio>
#include <cctype>
#include <cstring>

const int maxn = 57;
const int maxs = 67;
char prgm[maxn][maxs];
int n;

inline void unreachable(const int line)
{ printf("Line %d: unreachable code\n", line); }
inline void uninitialized(const int line, const int vars)
{
    for (int i = 0; i < 26; ++i)
	if ((1 << i) & vars)
	    printf("Line %d: variable %c might not have been initialized\n",
		    line, i + 'A');
}

inline bool isif(const int z)
{ return strncmp(prgm[z], "IF", 2) == 0; }
inline bool iselse(const int z)
{ return strncmp(prgm[z], "ELSE", 4) == 0; }
inline bool isendif(const int z)
{ return strncmp(prgm[z], "END IF", 6) == 0; }
inline bool isret(const int z)
{ return strncmp(prgm[z], "RETURN", 6) == 0; }

inline int find_endif(int i)
{
    int c = 1;
    for (++i; c; ++i)
	if (isif(i))
	    ++c;
	else if (isendif(i))
	    --c;
    return i;
}
inline int find_else(int i)
{
    int c = 1;
    for (++i; c; ++i)
	if (isif(i))
	    ++c;
	else if (isendif(i))
	    --c;
	else if (c == 1 && iselse(i))
	    return i;
    return i;
}

#define check(s) if (!ret && isalpha(s[0]) && !(inited >> (s[0] - 'A') & 1)) \
    tmp |= 1 << (s[0] - 'A')
#define add(s) inited |= 1 << (s[0] - 'A')

void parse(int i, int last, int& inited, bool& ret)
{
#if DB >= 1
    fprintf(stderr, "%d %d %d %d\n", i, last, inited, ret);
#endif
    if (isif(i) && find_endif(i) == last)
    {
	if (ret)
	    unreachable(i);
	char a[17], b[3], c[17];
	sscanf(prgm[i], "IF %s%s%s", a, b, c);
	int tmp = 0;
	check(a);
	check(c);
	uninitialized(i, tmp);
	const int e = find_else(i);
	int i1 = inited;
	bool r1 = ret;
	if (e == last)
	    parse(i + 1, last - 1, i1, r1);
	else
	{
	    int i2 = inited;
	    bool r2 = ret;
	    parse(i + 1, e, i1, r1);
	    parse(e + 1, last, i2, r2);
	    //inited |= i1 & i2;
	    //ret |= r1 && r2;
	    if (!ret)
	    {
		if (r1)
		{
		    if (r2)
			ret = true;
		    else
			inited |= i2;
		}
		else
		{
		    if (r2)
			inited |= i1;
		    else
			inited |= i1 & i2;
		}
	    }
	}
	return;
    }
    for (; i < last; ++i)
    {
	if (ret && !iselse(i) && !isendif(i) && !isif(i))
	    unreachable(i);
	if (isret(i))
	{
	    char s[17];
	    sscanf(prgm[i], "RETURN%s", s);
	    int tmp = 0;
	    check(s);
	    uninitialized(i, tmp);
	    ret = true;
	}
	else if (isif(i))
	{
	    const int t = find_endif(i);
	    parse(i, t, inited, ret);
	    i = t - 1;
	}
	else if (!isendif(i) && !iselse(i))
	{
	    char a[3], b[17], c[3], d[17];
	    int tmp = 0;
	    if ((sscanf(prgm[i], "%s =%s%s%s", a, b, c, d)) == 4)
		check(d);
	    check(b);
	    uninitialized(i, tmp);
	    add(a);
	}
    }
}

int main()
{
    for (n = 1; gets(prgm[n]); ++n)
	;
    int s = 0;
    for (int i = 6; i < strlen(prgm[1]) && isalpha(prgm[1][i]); i += 2)
	s |= 1 << (prgm[1][i] - 'A');
    bool z = false;
    parse(2, n, s, z);
}
