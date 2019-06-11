#include <cstdio>
#include <cstring>

class Float
{
	public:
		 Float();
		 Float(const int);
		bool input();
		void output();
		Float operator*(const Float&);
		void operator*=(const Float&);
		void operator=(const Float&);
	private:
		static const int maxn = 53;
		static const int N = 10000;
		int dig, point;
		int num[maxn];
		void init();
};

Float::Float()
	: dig(1), point(0)
{
	memset(num, 0, sizeof num);
}

Float::Float(const int x)
	: dig(1), point(0)
{
	memset(num, 0, sizeof num);
	//assert(x < N);
	num[0] = x;
}

void Float::init()
{
	memset(num, 0, sizeof num);
	dig = 1;
	point = 0;
}

char str[163];

bool Float::input()
{
	init();
	if (scanf("%s", str) != EOF)
	{
		for (char* i = str; *i; ++i)
			if (*i == '.')
				for (char* j = i; *j; ++j)
				{
					++point;
					*j = *(j + 1);
				}
		if (point > 0)
			--point;
		sscanf(str, "%d", &num[0]);
		if (num[0] >= N)
		{
			num[1] = num[0] / N;
			num[0] %= N;
			++dig;
		}
		return true;
	}
	return false;
}

void Float::output()
{
	str[0] = '\0';
	for (int i = dig - 1; i >= 0; --i)
		sprintf(str + strlen(str), "%04d", num[i]);
	char* i;
	const int len = strlen(str);
	for (i = str + len; i > str + len - point; --i)
		*(i + 1) = *i;
	*(i + 1) = *i;
	*i = '.';
	for (i = str + strlen(str) - 1; *i == '0'; --i)
		*i = '\0';
	if (*i == '.')
		*i = '\0';
	for (i = str; *i == '0'; ++i)
		;
	if (strlen(i))
		printf("%s\n", i);
	else
		printf("0\n");
}

Float Float::operator*(const Float& x)
{
	Float ret;
	ret.dig = dig + x.dig;
	ret.point = point + x.point;
#ifdef DB
	fprintf(stderr, "%d %d\n", ret.dig, ret.point);
#endif
	for (int i = 0, c = 0; i < dig; ++i)
	{
		for (int j = 0; c || j < x.dig; ++j)
		{
			if (i + j >= ret.dig)
				ret.dig = i + j + 1;
			ret.num[i + j] += c + num[i] * x.num[j];
			c = ret.num[i + j] / N;
			ret.num[i + j] %= N;
		}
	}
	return ret;
}

void Float::operator*=(const Float& x)
{
	*this = *this * x;
}

void Float::operator=(const Float& x)
{
	init();
	point = x.point;
	dig = x.dig;
	for (int i = 0; i < dig; ++i)
		num[i] = x.num[i];
}

int main()
{
	int n;
	Float a;
	while (a.input())
	{
		scanf("%d", &n);
		Float b(1);
		for (int i = 0; i < n; ++i)
			b *= a;
		b.output();
	}
	return 0;
}
