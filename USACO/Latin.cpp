/*
PROB: latin
LANG: C++
*/
#pragma warning(disable: 4996)
#include <iostream>
//#define OUTPUT
//#define OUT

using namespace std;

int n, num[10][10];
long long ans;
bool hor[10][10], ver[10][10];

const int fact[] = {1, 1, 2, 6, 24, 120, 720};

#if defined (OUT) || defined (OUTPUT)
void output(){
	for (int i=0; i<n; ++i){
		for (int j=0; j<n; ++j)
			printf("%d ", num[i][j]);
		printf("\n");
	}
	printf("\n");
}
#endif

#ifdef OUTPUT
void search(int x = 1, int y = 1){
#else
void search(int x = 1, int y = 2){
#endif
	//printf("Searching %d, %d\n", x, y);
	for (int i=1; i<=n; ++i)
		if (!hor[x][i] && !ver[y][i]){
			hor[x][i] = ver[y][i] = true;
			num[x][y] = i;
			if (y < n-1)
				search(x, y+1);
			else if (x < n-2)
				search(x+1, 1);
			else{
#if defined (OUT) || defined (OUTPUT)
				output();
#endif
				++ans;
			}
			hor[x][i] = ver[y][i] = false;
		}
}

void search2(int x = 0, int y = 0){
	for (int i=1; i<=n; ++i)
		if (!hor[x][i] && !ver[y][i]){
			hor[x][i] = ver[y][i] = true;
			num[x][y] = i;
			if (y < n-1)
				search2(x, y+1);
			else if (x < n-2)
				search2(x+1, 0);
			else{
#ifdef OUTPUT
				output();
#endif
				++ans;
			}
			hor[x][i] = ver[y][i] = false;
		}
}

int main(){
	freopen("latin.in", "r", stdin);
	freopen("latin.out", "w", stdout);
#ifdef OUTPUT
	scanf("%d", &n);
#endif
	for (int i=0; i<6; ++i){
		num[i][0] = num[0][i] = i+1;
		hor[i][i+1] = ver[i][i+1] = true;
	}
#ifndef OUTPUT
	for (n=3; n<=7; ++n){
		ans = 0;
		printf("%d\t", n);
		num[1][1] = 1;
		hor[1][1] = ver[1][1] = true;
		search();
		long long int t = ans;
		ans = 0;
		num[1][1] = 3;
		hor[1][3] = ver[1][3] = true;
		hor[1][1] = ver[1][1] = false;
#endif
		search();
#ifdef OUTPUT
		printf("%I64d\n", ans * fact[n-1]);
#else
		printf("%I64d\n", (ans * (n-2) + t) * fact[n-1]);
		hor[1][3] = ver[1][3] = false;
	}
#endif
	//memset(hor, false, sizeof hor);
	//memset(ver, false, sizeof ver);
	//ans = 0;
	//printf("\nSearch2\n");
	//search2();
	//printf("%I64d\n", ans);
	return 0;
}
