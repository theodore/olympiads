/*
 * $File: harbingers.cpp
 * $Date: Wed Jul 28 23:44:38 2010 +0800
 */

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

#define MAXN 100000
#define MAXM MAXN * 2
#define data_t long long

using namespace std;

#define BUFSIZE 1000000
char buf[BUFSIZE], *pt = buf + BUFSIZE, *pend = buf + BUFSIZE;
#define read() \
	do{ \
		if (pt >= pend) \
		{ \
			pt = buf; \
			fread(buf, 1, BUFSIZE, stdin); \
		} \
	} while(0) 

#define scan(t) \
{ \
	t = 0; \
	read(); \
	bool nega = false; \
	while (!(((*pt) >= '0' && (*pt) <= '9') || (*pt == '-'))) {pt ++; read();} \
	if ((*pt) == '-') {nega = true, pt ++; read();} \
	while (((*pt) >= '0' && (*pt) <= '9')) {t = t * 10 + (*(pt ++)) - '0'; read();}\
	if (nega) t = -t; \
}

int Count = 0;
int begin[MAXN + 1], end[MAXM + 1], next[MAXM + 1], cost[MAXM + 1];
void AddEdge(int a, int b, int v)
{
	Count ++;
	next[Count] = begin[a];
	begin[a] = Count;
	end[Count] = b;
	cost[Count] = v;
}

int n;
data_t s[MAXN + 1], v[MAXN + 1];
void Init()
{
	scan(n);
	int a, b, d;
	for (int i = 1; i <= n - 1; i ++)
	{
		scan(a); scan(b); scan(d);
		AddEdge(a, b, d);
		AddEdge(b, a, d);
	}
	for (int i = 2; i <= n; i ++)
	{
		scan(s[i]); scan(v[i]);
	}
}

class StackNode
{
	public:
		data_t f, d;
		data_t val(data_t v)
		{
			return f - d * v;
		}
};
StackNode stack[MAXN + 1];
int top;
data_t ans[MAXN + 1];

data_t GetVal(data_t v)
{
	data_t ret = 0;
	int l = 1, r = top;
	while (l + 2 < r)
	{
		int unit = (r - l + 1) / 3;
		int p = l + unit, q = r - unit;
		if (stack[p].val(v) < stack[q].val(v))
			r = q;
		else
			l = p;
	}
	for (int i = l; i <= r; i ++)
		ret = min(ret, stack[i].val(v));
	return ret;
}

double GetX(const StackNode &a, const StackNode &b)
{
	return (double)(b.f - a.f) / (double)(b.d - a.d);
}

int dist[MAXN + 1], father[MAXN + 1];

class DfsStack
{
	public:
		int x, d, fa;
		int pre_top, top_pos;
		bool first;
		StackNode stack_modified;

		void set(int _x, int _d, int _fa, bool _first, int _pre_top, int _top_pos, StackNode &_stack_modified)
		{
			x = _x, d = _d, fa = _fa, first = _first;
			pre_top = _pre_top, top_pos = _top_pos;
			stack_modified = _stack_modified;
		}
		void get(int &_x, int &_d, int &_fa, bool &_first, int &_pre_top, int &_top_pos, StackNode &_stack_modified)
		{
			_x = x, _d = d, _fa = fa, _first = first;
			_pre_top = pre_top, _top_pos = top_pos;
			_stack_modified = stack_modified;
		}
};

DfsStack S[MAXN + 1];
void DFS()
{
	int nNode = 0;
	int Top = 0;
	StackNode tmp;
	S[Top = 1].set(1, 0, 0, 1, 0, 0, tmp);
	while (Top)
	{
		int x, d, fa;
		int pre_top, top_pos;
		bool first;
		StackNode stack_modified;
		S[Top].get(x, d, fa, first, pre_top, top_pos, stack_modified); Top --;
		if (first)
		{
			nNode ++;
			ans[x] = min(s[x] + d * v[x], GetVal(v[x]) + d * v[x] + s[x]);
			pre_top = top;
			StackNode stack_now;
			stack_now.f = ans[x], stack_now.d = d;
			if (x != 1)
			{
				// pop stack
				if (top >= 2)
					do{
						if (GetX(stack[top], stack_now) > GetX(stack[top - 1], stack[top]))
							break;
						if (top >= 2)
						{
							int l = 1, r = top;
							while (l < r)
							{
								int mid = (l + r) >> 1;
								if (GetX(stack[mid + 1], stack_now) < GetX(stack[mid], stack_now))
									r = mid;
								else
									l = mid + 1;
							}
							top = l;
						}
						while (top >= 2 && GetX(stack[top], stack_now) < GetX(stack[top - 1], stack_now))
							top --;
					} while (0);
				// end pop stack
			}
			//
			if (x != 1)
			{
				stack_modified = stack[top + 1];
				stack[++top] = stack_now;
				top_pos = top;
			}
		}
		bool deepning = false;
		for (int now = begin[x]; now; now = next[now])
			if (end[now] !=fa)
			{
				S[++Top].set(x, d, fa, 0, pre_top, top_pos, stack_modified);
				S[++Top].set(end[now], d + cost[now], x, 1, 0, 0, tmp);
				begin[x] = next[now];
				deepning = true;;
				break;
			}
		if (!deepning && x != 1)
		{
			stack[top_pos] = stack_modified;
			top = pre_top;
		}
	}
}

char str[3000000];
int pos = 0;
void Add(long long v)
{
	int cnt = 0;
	static char buf[100];
	while (v)
		buf[cnt ++] = v % 10 + '0', v /= 10;
	if (!cnt)
		buf[cnt ++] = '0';
	while (cnt)
		str[pos ++] = buf[-- cnt];
	str[pos ++] = ' ';
}

void Solve()
{
	DFS();
	for (int i = 2; i <= n; i ++)
		Add(ans[i]);
	puts(str);
}

int main()
{
	Init();
	Solve();
	return 0;
}
