#include <iostream>
#include <cstdio>
#define MAXN 50000
#define INFINITE 1000000000
#define ll long long

using namespace std;

ll c[MAXN+1];
ll sum[MAXN+1];
int n;
ll L;
ll f[MAXN+1];
void Init(){
	scanf("%d%lld",&n,&L);
	for (int i = 1; i<=n; i++){
		scanf("%lld",&c[i]);
		sum[i] = sum[i-1]+c[i];
	}
}

#define SQR(x) ((x)*(x))
ll G(ll k) {return f[k-1]+SQR(sum[k-1]+k);}
double F(ll k,ll j) {return (G(k)-G(j))/(double)(sum[k-1]+k-sum[j-1]-j);}
class Queue{
public:
	int head, tail;
	int q[MAXN+1];
	Queue():head(1),tail(0){}
	int size(){return tail-head+1;}
	void push(int c){
		while(size()>1&&F(q[tail-1],q[tail])>F(q[tail],c)) tail--;
		q[++tail] = c;
	}
	int front(int c){
		while (size()>1&&F(q[head],q[head+1])<=2*(sum[c]+c-L)) head++;
		return q[head];
	}
}q;
void Solve(){
	f[1] = SQR(c[1]-L);
	q.push(1);
	for (int i = 2; i<=n; i++){
		q.push(i);
		int j = q.front(i);
		f[i] = f[j-1] + SQR(sum[i]-sum[j-1]+i-j-L);	
	}
	printf("%lld\n",f[n]);
}

int main(){
	Init();
	Solve();
	return 0;
}
