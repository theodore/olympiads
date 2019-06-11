#include<iostream>
#include<stdio.h>
#include<string.h>
#include<cmath>
#include<map>
#include<string>
#include<algorithm>
#include<vector>

using namespace std;

typedef long long LL;

const int maxn = 36000;
int f[4][maxn];

int b[5] = {0,0,0,0};
int w[5] = {2,3,4679,35617};
const int P = 999911659;
int N,G;

int ext_gcd(int a, int b, int &x, int &y){
    int t, d;
    if (! b) { x = 1; y = 0; return a; }
    d = ext_gcd(b, a % b, x, y);
    t = x;
    x = y;
    y = t - a / b*y;
    return d;
}
int China(int b[], int w[], int k) {
    int i;
    int d, x, y, m, n = 1;
    LL a = 0;
    for (i = 0; i < k; i++) n *= w[i];
    for (i = 0; i < k; i++) {
	m = n / w[i];
	d = ext_gcd(w[i], m, x, y);
	a = (a + (LL)y * m * b[i]) % n;
    }
    if (a > 0) return a;
    return (a + n);
}

int s[2][101];

int powmod(LL a,int b,int c){
    LL ret = 1;
    while(b){
	if(b & 0x1) ret = ret * a % c;
	a = a * a % c;
	b >>= 1;
    }
    return ret;
}
int cnk(int n,int k,int cur){
    int ans = f[cur][n],p = w[cur];
    ans = ans * powmod(f[cur][k],p - 2, p) % p;
    ans = ans * powmod(f[cur][n - k],p - 2, p) % p;
    return ans;
}

int C(int n,int k,int cur){
    int i,x,len[2] = {0,0},c = 0,p = w[cur];
    x = n;
    while(x) s[0][len[0] ++] = x % p,x /= p;
    x = k;
    while(x) s[1][len[1] ++] = x % p, x/= p;
    while(len[1] < len[0]) s[1][len[1] ++] = 0;
    for(i = 0; i < len[0]; ++ i) if(s[1][i] > s[0][i]) return 0;
    int ans = 1;
    for(i = 0; i < len[0]; ++ i) ans = ans * cnk(s[0][i],s[1][i],cur) % p;
    return ans;
}

int main(){
    int i,j;
    for(i = 0; i < 4; ++ i){
	f[i][0] = 1;
	for(j = 1; j < w[i]; ++ j)
	    f[i][j] = f[i][j - 1] * j % w[i];
    }
    scanf("%d%d",&N,&G);
    if(G == P){
	puts("0");
	return 0;
    }
    G %= P;
    for(i = 1; i * i <= N; ++ i)
	if(N % i == 0){
	    int x = i;
	    b[0] = (b[0] + C(N,x,0)) % w[0];
	    b[1] = (b[1] + C(N,x,1)) % w[1];
	    b[2] = (b[2] + C(N,x,2)) % w[2];
	    b[3] = (b[3] + C(N,x,3)) % w[3];
	    x = N / i;
	    if(i * i != N){
		b[0] = (b[0] + C(N,x,0)) % w[0];
		b[1] = (b[1] + C(N,x,1)) % w[1];
		b[2] = (b[2] + C(N,x,2)) % w[2];
		b[3] = (b[3] + C(N,x,3)) % w[3];
	    }
	}
    int ans = powmod(G,China(b,w,4),P);
    printf("%d\n",ans);
    return 0;
}
