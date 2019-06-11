#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#define MAXN 500000
#define INFINIT 1000000000
#define MAXDIGIT 20000

using namespace std;

int Ans[MAXN+1];
int aAns[MAXN+1];
int Ansstep = 0;
double tAns = INFINIT;
int p[MAXN+1];
bool hash[MAXN+1];
int a[MAXN+1];
int n;
void dfs(int step,int limit,int now,double logarithm){
    if (logarithm>tAns) return ;
    if (now == 1){
	if (logarithm<tAns){
	    tAns = logarithm;
	    memcpy(Ans,aAns,sizeof(Ans));
	    Ansstep = step-1;
	}
	return;
    }
    for (int i = 1; i<=limit; i++)
	if (!(now%(i+1))){
	    aAns[step] = i;
	    dfs(step+1,i,now/(i+1),logarithm+i*log((double)p[step]));
	}
}
int tmp[MAXDIGIT+1];
void Mul(int *a,int *b,int *c){
    memset(tmp,0,sizeof(tmp));
    for (int i = 1; i<=a[0]; i++)
	for (int j = 1; j<=b[0]; j++)
	    tmp[i+j-1] += a[i]*b[j],
		tmp[i+j] += tmp[i+j-1]/10,
		tmp[i+j-1] %= 10;
    tmp[0] = a[0]+b[0];
    while (!tmp[tmp[0]]&&tmp[0]>1) tmp[0]--;
    memcpy(c,tmp,sizeof(tmp));
}
void mul(int a,int *b){
    memset(tmp,0,sizeof(tmp));
    for (int i = 1; i<=b[0]+5; i++){
	tmp[i] += a*b[i];
	tmp[i+1] += tmp[i]/10;
	tmp[i] %= 10;
    }
    tmp[0] = b[0]+5;
    while (!tmp[tmp[0]]&&tmp[0]>1) tmp[0]--;
    memcpy(b,tmp,sizeof(tmp));
}
void Power(int p,int b,int *c){
    if (b == 0){
	c[0] = c[1] = 1;
    }else{
	Power(p,b>>1,c);
	Mul(c,c,c);
	if (b&1) mul(p,c);
    }
}
void Out(int *a){
    for (int i = a[0]; i>=1; i--)
	printf("%d",a[i]);
}
int main(){
    scanf("%d",&n);
    p[0] = 1;
    p[1] = 2;
    int t = 1;
    while (2*(++t)<=n) hash[2*t] = true;
    for (int i = 3; i<=n; i+=2)
	if (!hash[i]){
	    p[++p[0]] = i;
	    t = 1;
	    while (i*(++t)<=n) hash[i*t] = 1;
	}
    dfs(1,n,n,0);
    int C[MAXDIGIT+1] = {0};
    C[0] = 1;
    C[1] = 1;
    int B[MAXDIGIT+1] = {0};
    B[0] = B[1] = 1;
    for (int i = 1; i<=Ansstep; i++)
	Power(p[i],Ans[i],C),
	    Mul(C,B,B);
    Out(B);
    printf("\n");
    return 0;
}
