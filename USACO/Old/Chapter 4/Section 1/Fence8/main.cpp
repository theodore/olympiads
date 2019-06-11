/*
PROB:fence8
LANG:C++
*/
#include <iostream>
#include <algorithm>
//#define DEBUG

using namespace std;

int board[60], rail[1100];
int sumb, sumr[1100];

void init(){
	scanf("%d", board);
	for (int i=1; i<=board[0]; ++i)
		sumb += (scanf("%d", board+i), board[i]);
	sort(board+1, board+board[0]+1);
	scanf("%d", rail);
	for (int i=1; i<=rail[0]; ++i)
		scanf("%d", rail+i);
	sort(rail+1, rail+rail[0]+1);
	for (int i=1; i<=rail[0]; ++i)
		sumr[i] = sumr[i-1] + rail[i];
}

bool chosen[1024], good(false);
int ans(0);

bool fit(int tim, int& ind){
	for (ind=board[0]; ind; --ind)
		if (board[ind] >= rail[tim])
			return true;
	return false;
}

void search(int now, const int dep){
	if (now == dep){
		good = true;
		ans = dep;
		return;
	}
	//prune here
	int small = 0;
	for (int i=1; i<=rail[0]; ++i)
		if (!chosen[i]){
			small = rail[i];
			break;
		}
	if (!small)
		return;
	int sum = 0;
	for (int i=1; i<=board[0]; ++i)
		if (board[i] < small)
			sum += board[i];
	if (sum > sumb - sumr[dep])
		return;

	for (int i=1; i<=rail[0]&&!good; ++i){
		int pos;
		if (!chosen[i] && fit(i, pos)){
			board[pos] -= rail[i];
			chosen[i] = true;
			search(now+1, dep);
			board[pos] += rail[i];
			chosen[i] = false;
		}
	}
}

void getit(){
	for (int dep=1; good||dep==1; ++dep){
		good = false;
		search(0, dep);
	}
	printf("%d\n", ans);
}

int main(){
	freopen("fence8.in", "r", stdin);
	freopen("fence8.out", "w", stdout);
	init();
	getit();
	return 0;
}
