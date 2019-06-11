/*
ID:theodor8
TASK:transform
LANG:C++
*/
#include <iostream>
#pragma warning(disable:4996)
using namespace std;

int n;
char b4[11][11], after[11][11], to[11][11];

void cmp(const int& x)
{
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			if (to[i][j] != after[i][j])
				return;
	printf("%d\n", x);
	exit(0);
}
void r90(const bool& self = true){
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			to[j][n-i+1] = b4[i][j];
	if (self)
		cmp(1);
	else
		cmp(5);
}
void r180(const bool& self = true){
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			to[n+1-i][n+1-j] = b4[i][j];
	if (self)
		cmp(2);
	else
		cmp(5);
}
void r270(const bool& self = true){
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			to[n+1-j][i] = b4[i][j];
	if (self)
		cmp(3);
	else
		cmp(5);
}
void reflection(const bool& self = true){
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			to[i][n+1-j] = b4[i][j];
	if (self) cmp(4);
}
void combination(){
	reflection(false);
	char tmp[11][11];
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j){
			tmp[i][j] = b4[i][j];
			b4[i][j] = to[i][j];
		}
	r90(false);
	r180(false);
	r270(false);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			b4[i][j] = tmp[i][j];
}
void no_change(){
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			to[i][j] = b4[i][j];
	cmp(6);
}
void invalid(){
	printf("7\n");
	exit(0);
}

int main()
{
	freopen("transform.in", "r", stdin);
	freopen("transform.out", "w", stdout);
	scanf("%d\n", &n);
	for (int i = 1; i <= n; ++i){
		for (int j = 1; j <= n; ++j)
			scanf("%c", &b4[i][j]);
		scanf("\n");
	}
	for (int i = 1; i <= n; ++i){
		for (int j = 1; j <= n; ++j)
			scanf("%c", &after[i][j]);
		scanf("\n");
	}
	r90();
	r180();
	r270();
	reflection();
	combination();
	no_change();
	invalid();
	return 0;
}
