#include <cstdio>
#include <iostream>
#include <queue>
#include <string>

using std::string;

struct node_t
{
    int son[26];
    bool is_word;
};

const int maxn = 63;
const int maxm = 103;
const int maxN = maxn * maxm;
const int mod = 10007;
int n, m, nc;
string word[maxn];
node_t node[maxN];
std::queue<int> q;
int f[maxm][maxN], pow[maxm];
int ans;

void initpow()
{
    pow[0] = 1;
    for (int i = 1; i < m; ++i)
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

void mktrie()
{
    nc = 1;
    for (int _ = 0; _ < n; ++_)
    {
	const string& s = word[_];
	int i, j;
	for (i = 0, j = 1; i < s.size(); ++i)
	{
	    int& t = node[j].son[s[i] - 'A'];
	    if (!t)
		t = ++nc;
	    j = t;
	}
	node[j].is_word = true;
    }
    static int suff[maxN];
    q.push(1);
    while (!q.empty())
    {
	const int x = q.front();
	q.pop();
	for (int i = 0, t; i < 26; ++i)
	    if ((t = node[x].son[i]))
	    {
		suff[t] = 1;
		for (int j = suff[x]; j; j = suff[j])
		    if (node[j].son[i])
		    {
			suff[t] = node[j].son[i];
			break;
		    }
		q.push(t);
	    }
    }
    for (int i = 0; i < 26; ++i)
	if (node[1].son[i])
	    q.push(node[1].son[i]);
	else
	    node[1].son[i] = 1;
    while (!q.empty())
    {
	const int x = q.front();
	q.pop();
	for (int i = 0; i < 26; ++i)
	    if (node[x].son[i])
		q.push(node[x].son[i]);
	    else
		node[x].son[i] = node[suff[x]].son[i];
    }
}

void dp()
{
    f[0][1] = 1;
    for (int i = 0; i <= m; ++i)
	for (int j = 1; j <= nc; ++j)
	{
	    if (node[j].is_word)
	    {
		ans += f[i][j] * pow[m - i];
		ans %= mod;
	    }
	    else
	    {
		const int ii = i + 1;
		for (char c = 'A'; c <= 'Z'; ++c)
		{
		    int jj = node[j].son[c - 'A'];
		    f[ii][jj] += f[i][j];
		    f[ii][jj] %= mod;
		}
	    }
	}
}

int main()
{
    scanf("%d%d", &n, &m);
    initpow();
    for (int i = 0; i < n; ++i)
	std::cin >> word[i];
    rmred();
    mktrie();
    dp();
    printf("%d\n", ans);
}
