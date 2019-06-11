#define STDIO
/*
 * $File: generator.cpp
 * $Date: Fri Mar 11 11:45:04 2011 +0800
 */

#define INPUT	"generator.in"
#define OUTPUT	"generator.out"

#include <cstdio>
#include <cstring>
#include <algorithm>

namespace Solve
{
	const int
		WORDLEN_MAX = 105,
		STRLEN_MAX = 105,
		NWORD_MAX = 65,
		MOD = 10007,
		ALPHABET_SIZE = 'z' - 'a' + 1;
	struct Word
	{
		char str[WORDLEN_MAX];
		int len;
		Word& operator = (const Word &n)
		{ len = n.len; memcpy(str, n.str, len); return *this; }

		bool is_subword_of(const Word &word) const;
	};
	Word word[NWORD_MAX];
	int nword;

	struct Pre_word
	{
		int wnum, extlen;
		inline bool operator < (const Pre_word &p) const
		{ return extlen < p.extlen; }
	};
	Pre_word pre_word[NWORD_MAX][NWORD_MAX * WORDLEN_MAX];
	// pre_word[i]: words that can be put before word[i], sort by extlen,
	// ending with an element with extlen == 0

	int f[STRLEN_MAX][NWORD_MAX];
	// f[i][j]: the number of word-free strings which have length i and
	// end with word[j][0..(len(word[j]) - 2)]
	int calc_f(int len, int end_word);

	int g[STRLEN_MAX];
	// g[i]: the number of word-free strings whose length is i
	int calc_g(int len);

	void remove_useless_word();
	void init();

	void solve(FILE *fin, FILE *fout);
}

void Solve::solve(FILE *fin, FILE *fout)
{
	int m;
	fscanf(fin, "%d%d", &nword, &m);
	for (int i = 0; i < nword; i ++)
	{
		fscanf(fin, "%s", word[i].str);
		word[i].len = strlen(word[i].str);
	}
	init();

	memset(f, -1, sizeof(f));
	memset(g, -1, sizeof(g));
	int ans = 1;
	for (int i = 0; i < m; i ++)
		if ((ans *= ALPHABET_SIZE) >= MOD)
			ans %= MOD;
	ans -= calc_g(m);
	if (ans < 0)
		ans += MOD;
	fprintf(fout, "%d\n", ans);
}

void Solve::init()
{
	remove_useless_word();
	for (int i = 0; i < nword; i ++)
	{
		int len_wdi = word[i].len;
		int nprewd = 0;
		for (int j = 0; j < nword; j ++)
		{
			int len_wdj = word[j].len;
			for (int len = 1; len < len_wdi && len < len_wdj; len ++)
				if (!memcmp(word[i].str, word[j].str + len_wdj - len, len))
				{
					pre_word[i][nprewd].wnum = j;
					pre_word[i][nprewd].extlen = len_wdj - len;
					nprewd ++;
				}
		}
		std::sort(pre_word[i], pre_word[i] + nprewd);
	}
}

void Solve::remove_useless_word()
{
	bool usable[NWORD_MAX];
	memset(usable, 1, sizeof(usable));
	for (int i = 0; i < nword; i ++)
		for (int j = 0; j < nword; j ++)
			if (i != j && usable[j] && word[j].is_subword_of(word[i]))
			{
				usable[i] = 0;
				break;
			}

	int nw = 0;
	for (int i = 0; i < nword; )
	{
		while (!usable[i])
			i ++;
		if (i < nword)
		{
			if (i != nw)
				word[nw] = word[i];
			nw ++;
			i ++;
		}
	}
	nword = nw;
}

bool Solve::Word::is_subword_of(const Word &word) const
{
	if (len > word.len)
		return false;
	return strstr(word.str, str) != NULL;
}

int Solve::calc_f(int len, int end_word)
{
	int &ans = f[len][end_word];
	if (ans != -1)
		return ans;
	int wlen = word[end_word].len - 1;
	if (len == wlen)
		return ans = 1;
	if (len < wlen)
		return ans = 0;
	if (!wlen)
		return ans = calc_g(len);
	ans = calc_g(len - wlen);
#ifdef DB
	fprintf(stderr, "f %d %d %d\n", len + 1, end_word, ans);
#endif
	for (Pre_word *i = pre_word[end_word]; i->extlen && i->extlen + wlen <= len; i ++)
	{
#ifdef DB
	    fprintf(stderr, "wnum = %d, extlen = %d\n", i->wnum, i->extlen);
#endif
		ans -= calc_f(len - wlen + word[i->wnum].len - i->extlen - 1, i->wnum);
		if (ans < 0)
			ans += MOD;
	}
#ifdef DB
	fprintf(stderr, "f %d %d %d\n", len + 1, end_word, ans);
#endif
	return ans;
}

int Solve::calc_g(int len)
{
	int &ans = g[len];
	if (ans != -1)
		return ans;
	if (!len)
		return ans = 1;
	ans = calc_g(len - 1) * ALPHABET_SIZE % MOD;
	for (int i = 0; i < nword; i ++)
	{
		ans -= calc_f(len - 1, i);
		if (ans < 0)
			ans += MOD;
	}
	return ans;
}

int main()
{
#ifdef STDIO
	Solve::solve(stdin, stdout);
#else
	FILE *fin = fopen(INPUT, "r"),
		 *fout = fopen(OUTPUT, "w");
	Solve::solve(fin, fout);
	fclose(fin);
	fclose(fout);
#endif
}
