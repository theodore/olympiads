#include<cstdio>

using namespace std;

#define BUFSIZE 100000
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

#define MAXN 2048
#define LC(k) (k<<1)
#define RC(k) ((k<<1)+1)
#define MD(a,b) (((a)+(b))>>1)

int R,C,N,a,b,c,x,y,x1,x2,y1,y2,tmp;

inline int MAX( int a, int b) { return a>b?a:b;}

struct LT_1D{
	int Cov[MAXN],Max[MAXN];
	int find( int k, int l, int r){
		if (y1>=r||y2<=l) return 0;
		if (y1<=l&&y2>=r) return Max[k];
		int max=Cov[k];
		max=MAX(max,find(LC(k),l,MD(l,r)));
		max=MAX(max,find(RC(k),MD(l,r),r));
		return max;
	}
	void ins( int k, int l, int r){
		if (y1>=r||y2<=l) return ;
		if (y1<=l&&y2>=r) Cov[k]=MAX(Cov[k],tmp);
		else {
			ins(LC(k),l,MD(l,r));
			ins(RC(k),MD(l,r),r);
		}
		Max[k]=MAX(Max[k],tmp);
	}
};

struct LT_2D{
	LT_1D Cov[MAXN],Max[MAXN];
	int find( int k, int l, int r){
		if (x1>=r||x2<=l) return 0;
		if (x1<=l&&x2>=r) return Max[k].find(1,0,C);
		int max=Cov[k].find(1,0,C);
		max=MAX(max,find(LC(k),l,MD(l,r)));
		max=MAX(max,find(RC(k),MD(l,r),r));
		return max;
	}
	void ins( int k, int l, int r){
		if (x1>=r||x2<=l) return ;
		if (x1<=l&&x2>=r) Cov[k].ins(1,0,C);
		else {
			ins(LC(k),l,MD(l,r));
			ins(RC(k),MD(l,r),r);
		}
		Max[k].ins(1,0,C);
	}
} LT2;

int main(){
	scan(R);scan(C);scan(N);
	for ( int i=1;i<=N;i++){
		scan(a);scan(b);scan(c);scan(x);scan(y);

		x1=x;x2=x+a;y1=y;y2=y+b;
		tmp=LT2.find(1,0,R)+c;
		LT2.ins(1,0,R);
	}
	x1=0;x2=R;y1=0;y2=C;
	printf("%d\n",LT2.find(1,0,R));
}
