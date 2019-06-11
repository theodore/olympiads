#include <cstdio>
#include <iostream>
#include <string>

using std::string;

const int maxn = 63;
const int maxm = 103;
//const int maxN = maxn * maxm;
const int mod = 10007;
int n, m;
string word[maxn];
int f[maxm][maxn], g[maxm];
int pow[maxm];

void initpow()
{
    pow[0] = 1;
    for (int i = 1; i <= m; ++i)
	pow[i] = pow[i - 1] * 26 % mod;
}

void rmred()
{
    static bool redundant[maxn];
    for (int i = 0; i < n; ++i)
	for (int j = i + 1; j < n; ++j)
	    if (word[i] == word[j])
		redundant[j] = true;
    for (int i = 0; i < n; ++i)
	if (!redundant[i])
	    for (int j = 0; j < n; ++j)
		if (!redundant[j] && i != j && word[j].find(word[i]) != string::npos)
		    redundant[j] = true;
    int i, j;
    for (i = j = 0; i < n; ++i)
	if (!redundant[i])
	    word[j++] = word[i];
    n = j;
}

void dp()
{
    g[0] = 1;
    for (int i = 1; i <= m; ++i)
    {
	g[i] = g[i - 1] * 26;
	for (int j = 0, z; j < n; ++j)
	{
	    if ((z = i - word[j].size()) >= 0)
	    {
		f[i][j] = g[z];
		for (int k = 0; k < n; ++k)
		    for (int l = std::max(1, int(word[k].size()) - int(word[j].size())); l <= std::min(z, int(word[k].size()) - 1); ++l)
		    {
			for (int o = l; o < int(word[k].size()); ++o)
			    if (word[k][o] != word[j][o - l])
				goto next;
			f[i][j] -= f[z + word[k].size() - l][k];
			f[i][j] %= mod;
next:;
		    }
	    }
	    f[i][j] += mod;
	    f[i][j] %= mod;
#ifdef DB
	    fprintf(stderr, "f %d %d %d\n", i, j, f[i][j]);
#endif
	    g[i] -= f[i][j];
	}
	g[i] %= mod;
	g[i] += mod;
	g[i] %= mod;
#ifdef DB
	fprintf(stderr, "g %d %d\n\n", i, g[i]);
#endif
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    initpow();
    for (int i = 0; i < n; ++i)
	std::cin >> word[i];
    rmred();
    dp();
    printf("%d\n", (pow[m] + mod - g[m]) % mod);
}
