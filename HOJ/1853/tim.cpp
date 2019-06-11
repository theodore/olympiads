#include <iostream>
#include <algorithm>
#define NNUM 3000
#define ll long long

using namespace std;

ll A,B;
void Init(){
	scanf("%I64d%I64d",&A,&B);
}

int n = 0;
ll a[NNUM+1];
void dfsNum(ll num){
	if (num > B) return;
	if (num <= B)
		a[++n] = num;
	dfsNum(num * (ll)10 + (ll)6);
	dfsNum(num * (ll)10 + (ll)8);
}
int cnt = 0;
ll b[NNUM+1];

ll Ans = 0, tmp;
	inline ll gcd(ll a, ll b){
		while (b)
			tmp = a, a = b, b = tmp % b;
		return a;
	}


int cmp(const void *a, const void *b){
	return (*(ll *)b) >  (*(ll *)a) ? 1 : -1;
}

ll dfs(int pos, ll num){
	if (pos == n+1) return B/num - A/num;
	ll ret = dfs(pos+1, num);
	ll newnum = num / gcd(num, a[pos]) * a[pos];
	if (newnum <= B && newnum >= 1)
		ret -= dfs(pos+1, newnum);
	return ret;
}

void Solve(){
	dfsNum(6); dfsNum(8);
	qsort(a+1, n, sizeof(a[0]), cmp);
	//printf("%d\n",n);
	for (int i = 1; i<=n; i++){
		bool boo = true;
		for (int j = 1; j<=n; j++)
			if (i!=j && a[i] % a[j] == 0){
				boo = false;
				break;
			}
		if (boo){
			a[++cnt] = a[i];
			//printf("%d %I64d\n", cnt, a[cnt]);
		}
	}
	n = cnt;
	//printf("%d\n",n);
	A--;
	printf("%I64d\n", B - A - dfs(1,1));
}

int main(){
	Init();
	Solve();
	return 0;
}
