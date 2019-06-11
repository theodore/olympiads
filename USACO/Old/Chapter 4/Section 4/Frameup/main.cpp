/*
PROB:frameup
LANG:C++
*/
#include <iostream>
#include <cstring>
//#define Debug

using namespace std;

int n, m, ansc;

char frame[33][33], ans[121][33];

#ifdef Debug
void display(char arg[][33]){
	for (int i=0; i<n; ++i)
		printf("%s\n", arg[i]);
	printf("******************************\n");
}
#endif

int cmp(const void* a, const void* b){
	return strcmp((char*)a, (char*)b);
}

bool done(char f[][33]){
	for (int i=0; i<n; ++i)
		for (int j=0; j<m; ++j)
			if (f[i][j] != '*' && f[i][j] != '.')
				return false;
	return true;
}

bool chosen[7];
void search(char f[][33], int dep = 4){
#ifdef Debug
	printf("%d\n", dep);
	for (int i=0; i<5; ++i)
		printf("%c", ans[ansc][i]);
	printf("\n");
	display(f);
#endif
	if (dep == -1){
		++ansc;
		return;
	}
	if (done(f)){
		for (int i=0, j=dep+1; j<=5; ++i, ++j)
			ans[ansc][i] = ans[ansc][j];
		++ansc;
		return;
	}
	char now[33][33];
	for (char i='A'; i<='E'; ++i){
		if (chosen[i-'A'])
			continue;
		for (int i=0; i<n; ++i)
			strcpy(now[i], f[i]);
		int u, l, d, r;
		for (int j=0; j<n; ++j)
			for (int k=0; k<m; ++k)
				if (now[j][k] == i){
					u = j;
					goto gotu;
				}
gotu:
		for (int k=0; k<m; ++k)
			for (int j=0; j<n; ++j)
				if (now[j][k] == i){
					l = k;
					goto gotl;
				}
gotl:
		for (int j=n-1; j>=0; --j)
			for (int k=0; k<m; ++k)
				if (now[j][k] == i){
					d = j;
					goto gotd;
				}
gotd:
		for (int k=m-1; k>=0; --k)
			for (int j=0; j<n; ++j)
				if (now[j][k] == i){
					r = k;
					goto gotr;
				}
gotr:
		bool over = false;
		for (int j=l; j<=r; ++j)
			if ((now[u][j] == i || now[u][j] == '*') && (now[d][j] == i || now[d][j] == '*'))
				now[u][j] = now[d][j] = '*';
			else{
				over = true;
				break;
			}
		if (over)
			continue;
		for (int j=u+1; j<d; ++j)
			if ((now[j][l] == i || now[j][l] == '*') && (now[j][r] == i || now[j][r] == '*'))
				now[j][l] = now[j][r] = '*';
			else{
				over = true;
				break;
			}
		if (over)
			continue;
		ans[ansc][dep] = i;
		chosen[i-'A'] = true;
		char cantgo[100];
		for (int i=0; i<6; ++i)
			cantgo[i] = ans[ansc][i];
		search(now, dep-1);
		for (int i=0; i<6; ++i)
			ans[ansc][i] = cantgo[i];
		chosen[i-'A'] = false;
	}
}

int main(){
	freopen("frameup.in", "r", stdin);
#ifndef Debug
	freopen("frameup.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	for (int i=0; i<n; ++i)
		scanf("%s", frame[i]);
	search(frame);
	qsort(ans, ansc, sizeof(ans[0]), cmp);
	for (int i=0; i<ansc; ++i)
		printf("%s\n", ans[i]);
    return 0;
}
