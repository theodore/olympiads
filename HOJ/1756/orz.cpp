#include <cstdio>
#include <algorithm>
#include <ctime>
#define OK puts("OK")
#define rep(i,n) for(int i=0;i<n;i++)

using namespace std;

const int inf=~0U>>1,maxn=500000;

struct info
{
	int L,R,M,S;
	info(int x=-inf):L(x),R(x),M(x),S(x){}
};

info operator+(const info&l,const info&r)
{
	info f;if(l.M==-inf)return r;
	if(r.M==-inf)return l;
	f.L=max(l.L,l.S+r.L);
	f.R=max(r.R,r.S+l.R);
	f.S=l.S+r.S;
	f.M=max(l.M,r.M);
	f.M=max(f.M,l.R+r.L);
	return f;
}

info A[1<<20];
int main()
{
#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("ans", "w", stdout);
	int ss = clock();
#endif
	int n,m,q,a,b,c;scanf("%d %d",&n,&q);
	m=1;while(m<=n+3)m<<=1;
	rep(i,n)scanf("%d",&c),A[i+1+m]=info(c);
	for(int i=m-1;i>=1;i--)A[i]=A[i*2]+A[i*2+1];
	rep(i,q)
	{
		scanf("%d%d%d",&c,&a,&b);
		if(c==1)
		{
			info L,R;if(a>b)swap(a,b);
			for(a+=m-1,b+=m+1;a^b^1;a>>=1,b>>=1)
			{
				if(~a&1)L=L+A[a^1];
				if(b&1)R=A[b^1]+R;
			}
			printf("%d\n",(L+R).M);
		}
		else
		{
			for(A[a+=m]=info(b),a>>=1;a;a>>=1)
				A[a]=A[a*2]+A[a*2+1];
		}
	}
#ifdef LOCAL
	fprintf(stderr, "%ld\n", clock() - ss);
#endif
	return 0;
}

