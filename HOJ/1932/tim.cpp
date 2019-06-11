/*
 * $Prob: [SHOI2007] Setstack ?????????? / hybz p1932
 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

#define MAXN 2000
#define ll long long

#define EMPTY -43665

using namespace std;

const ll seed = 999991;
class Set
{
    public:
	Set ()
	{
	    n = 0;
	}
	ll hash()
	{
	    if (n == 0)
		return EMPTY;
	    ll ret = 0;
	    for (int i = 1; i <= n; i ++)
			ret = ret * seed + a[i] * a[i] + ret * ret;
	    return ret;
	}

	int n;
	ll a[1000];
};	
ll bracket(ll s)
{
    return s * s - s + EMPTY - s + s * s * s * s;
}

Set MakeSet(Set &s)
{
    Set ret;
    ret.n = 1;
    ret.a[1] = bracket(s.hash());
    return ret;
}

Set Union(const Set &a, const Set &b)
{
    int c[MAXN + 1], cnt = 0;
    for (int i = 1; i <= a.n; i ++)
	c[i] = a.a[i];
    cnt = a.n;
    for (int i = 1; i <= b.n; i ++)
	c[++ cnt] = b.a[i];
    sort(c + 1, c + 1 + cnt);
    Set ret;
    for (int i = 1; i <= cnt; i ++)
	if (c[i] != c[i - 1])
	    ret.a[++ ret.n] = c[i];
    return ret;
}
Set Intersect(const Set &a, const Set &b)
{
    Set ret;
    for (int i = 1; i <= a.n; i ++)
	for (int j = 1; j <= b.n; j ++)
	    if (a.a[i] == b.a[j])
	    {
		ret.a[++ ret.n] = a.a[i];
		break;
	    }
    return ret;
}

Set stack[MAXN + 1];
Set empty_set;
int top;
void PUSH()
{
    stack[++ top] = empty_set;
}

void DUP()
{
    stack[top + 1] = stack[top];
    top ++;
}

Set a, b;
void UNION()
{
    a = stack[top --];
    b = stack[top --];
    stack[++ top] = Union(a, b);}

void INTERSECT()
{
    a = stack[top --];
    b = stack[top --];
    stack[++ top] = Intersect(a, b);
}

void ADD()
{
    a = stack[top --];
    b = stack[top --];
    stack[++ top] = Union(b, MakeSet(a));
}

int main()
{
    int T;
    char cmd[10];
    scanf("%d", &T);
    while (T --)
    {
	scanf("%s", cmd);
	switch (cmd[0])
	{
	    case 'P': // PUSH
		PUSH();
		break;
	    case 'D': // DUP
		DUP();
		break;
	    case 'U': // UNION
		UNION();
		break;
	    case 'I': // INTERSECT
		INTERSECT();
		break;
	    case 'A': // ADD
		ADD();
		break;
	}
	printf("%d\n", stack[top].n);
    }
    return 0;
}
