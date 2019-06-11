#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAXN 2001
#define INFINITE 1e20
#define EPS 1e-8

class Point
{
	public:
		int x,y;
}p[MAXN];

bool cmp(const Point &a, const Point &b)
{
	if(a.x!=b.x)
		return a.x<b.x;
	return a.y<b.y;
}

int N;
int ans;
int f[MAXN][MAXN],g[MAXN],h[MAXN][MAXN],w[MAXN][MAXN];

int find(int x, int p)
{
	int left = g[x], right = N, mid;
	while(left+1<right)
	{
		mid = (left+right)>>1;
		if(h[x][mid]>p)
			right = mid;
		else
			left = mid;
	}
	return left;
}

int find2(int x, int p)
{
	int left = 0, right = N, mid;
	while(left+1<right)
	{
		mid = (left+right)>>1;
		if(w[x][mid]>p)
			right = mid;
		else
			left = mid;
	}
	return left;
}

void update(int i, int j)
{
	int tmp = f[i][j];
	while(tmp>=0&&h[i][tmp]>p[j].y)
		h[i][tmp] = p[j].y, tmp--;
	tmp = f[i][j];
	while(tmp>=0&&w[j][tmp]>p[i].y)
		w[j][tmp] = p[i].y, tmp--;
}

void init()
{
	scanf("%d",&N);
	for(int i = 0; i < N; i++)
		scanf("%d %d",&p[i].x,&p[i].y);
	sort(p,p+N,cmp);
}

void solve()
{
	int tmp;
	memset(h,0x7f,sizeof(h));
	memset(w,0x7f,sizeof(w));
	for(int i = 0; i < N; i++)
	{
		g[i] = 1;
		for(int j = 0; j < i; j++)
			if(p[j].y<=p[i].y)
			{
				tmp = g[j]+1;
				g[i] = MAX(g[i],tmp);
			}
		h[i][g[i]] = 0;
		w[i][0] = 0;
	}
	for(int i = 0; i < N; i++)
		for(int j = i+1; j < N; j++)
		{
			f[i][j] = find(i,p[j].y)+1;
			/*for(int k = i+1; k < j; k++)
			  if(p[k].y<=p[j].y)
			  {
			  tmp = f[i][k]+1;
			  f[i][j] = MAX(f[i][j],tmp);
			  }*/
			tmp = find2(i,p[j].y)+1;
			f[i][j] = MAX(f[i][j],tmp);
			/*for(int k = 0; k < i; k++)
			  if(p[k].y<=p[j].y)
			  {
			  tmp = f[k][i]+1;
			  f[i][j] = MAX(f[i][j],tmp);
			  }*/
			update(i,j);
			ans = MAX(ans,f[i][j]);
		}
}

void print()
{
	printf("%d\n",ans);
}

int main(void)
{
	init();
	solve();
	print();
	return 0;
}
