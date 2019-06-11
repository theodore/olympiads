#include <cstdio>
#include <cmath>
#include <cstring>
#include <iostream>

struct data_t
{
	data_t();
	long long cnt[11];
	data_t operator-(const data_t&);
	void operator+=(const data_t&);
	void output();
#ifdef DB
	void db();
#endif
};

data_t::data_t()
{
	memset(cnt, 0, sizeof cnt);
}

data_t data_t::operator-(const data_t& x)
{
	data_t ret;
	for (int i = 0; i <= 10; ++i)
		ret.cnt[i] = cnt[i] - x.cnt[i];
	return ret;
}

void data_t::operator+=(const data_t& x)
{
	for (int i = 0; i <= 10; ++i)
		cnt[i] += x.cnt[i];
}

void data_t::output()
{
	for (int i = 0; i < 9; ++i)
		std::cout << cnt[i] << ' ';
	std::cout << cnt[9] << std::endl;
}

#ifdef DB
void data_t::db()
{
	std::cerr << '{';
	for (int i = 0; i < 10; ++i)
		std::cerr << cnt[i] << ' ';
	std::cerr << '}';
}
#endif

// length, starting digit
data_t f[15][13];
long long ten[15];

void init(const int n)
{
	ten[0] = 1;
	for (int i = 1; i < n; ++i)
		ten[i] = ten[i - 1] * 10;
}

// f[1~n][0~10]
void calc(const int n)
{
	for (int i = 1; i <= 9; ++i)
		f[1][i].cnt[i] = f[1][i].cnt[10] = 1;
	f[1][10].cnt[0] = f[1][10].cnt[10] = 1;
	for (int i = 2; i <= n; ++i)
	{
		//long long t;
		for (int j = 0; j <= 9; ++j)
			f[i][0] += f[i - 1][j];
		for (int j = 1; j <= 9; ++j)
			for (int k = 1; k <= 10; ++k)
			{
				f[i][j] += f[i - 1][k];
				f[i][j].cnt[j] += f[i - 1][k].cnt[10];
				//f[i][j].cnt[j] += t = f[i - 1][k].cnt[10];
				//f[i][j].cnt[10] += t;
			}
		for (int j = 1; j <= 10; ++j)
		{
			f[i][10] += f[i - 1][j];
			f[i][10].cnt[0] += f[i - 1][j].cnt[10];
			//f[i][10].cnt[0] += t = f[i - 1][j].cnt[10];
			//f[i][10].cnt[10] += t;
		}
	}
#ifdef DB
	for (int i = 1; i <= n; ++i)
		for (int j = 0; j <= 10; ++j)
		{
			fprintf(stderr, "f[%d][%d] = ", i, j);
			f[i][j].db();
			fprintf(stderr, "\n");
		}
#endif
}

int digit[15];

data_t answer(long long x)
{
#ifdef DB
	fprintf(stderr, "answer %lld\n", x);
#endif
	data_t ret;
	if (x == -1)
		return ret;
	if (x)
	{
		int n = int(log10(double(x)) + 1);
		ret += f[n][0];
		for (int i = n, j; i; --i)
		{
#ifdef DB
			fprintf(stderr, "i = %d, x = %lld\n", i, x);
#endif
			if (ten[i - 1] > x)
			{
				++ret.cnt[digit[i] = 0];
#ifdef DB
				fprintf(stderr, "++ret.cnt[%d]\n", digit[i]);
#endif
				continue;
			}
			for (j = 0; (j + 1) * ten[i - 1] <= x; ++j)
			{
				if (j == 0)
				{
					if (i == n)
						continue;
					else
						j = 10;
				}
#ifdef DB
				ret.db();
				fprintf(stderr, " += f[i][%d] = ", j);
				f[i][j].db();
				std::cerr << std::endl;
#endif
				ret += f[i][j];
				for (int k = n; k > i; --k)
				{
					ret.cnt[digit[k]] += f[i][j].cnt[10];
#ifdef DB
					fprintf(stderr, "ret.cnt[%d] += s[%d][%d] = %lld\n", digit[k], i, j, f[i][j].cnt[10]);
#endif
				}
				if (j == 10)
					j = 0;
			}
			x -= (digit[i] = j) * ten[i - 1];
#ifdef DB
			fprintf(stderr, "digit[%d] = %d, (++cnt)\n", i, digit[i]);
#endif
			++ret.cnt[digit[i]];
		}
	}
	++ret.cnt[0];
	return ret;
}

int main()
{
	long long a, b;
	std::cin >> a >> b;
	if (b == 0)
	{
		data_t t;
		t.output();
		return 0;
	}
	init(int(log10(double(b)) + 1));
	calc(int(log10(double(b)) + 1));
	(answer(b) - answer(a - 1)).output();
	return 0;
}
