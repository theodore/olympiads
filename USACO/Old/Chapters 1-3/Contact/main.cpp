/*
ID:theodor8
PROB:contact
LANG:C++
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#pragma warning(disable:4996)
//#define Debug
#define Try

using namespace std;

#ifdef Try
struct tryit{
	int n, c;
	char str[15];
} trie[1<<14];
#define up ((1<<(b+1))-1)
#define down ((1<<a)-1)
	//[down, up)
#endif

int a, b, n;
char s[200010];
//a trie, 0 left, 1 right
#ifndef Try
int trie[1<<14];

void print(int x){
	if (!x)
		return;
	int depth;
	for (int i=2; ; ++i)
		if ((1<<i)-1 > x){
			depth = i - 1;
			break;
		}
	if (x < (1<<depth) - 1 + (1 << (depth-1))){
		printf("0");
		x -= 1<<(depth-1);
	}
	else{
		printf("1");
		x -= 1<<depth;
	}
	print(x);
}
#endif

#ifdef Try
int cmp(const void* a, const void* b){
	if (((tryit*)a)->c == ((tryit*)b)->c)
		return ((tryit*)a)->n - ((tryit*)b)->n;
	else
		return ((tryit*)b)->c - ((tryit*)a)->c;
}
void output(){
	qsort(trie+down, up-down, sizeof(tryit), cmp);
	int i = down;
	for (int _=0; _<n && i<up; ++_){
		if (!trie[i].c)
			exit(0);
		printf("%d\n", trie[i].c);
		int count = 0;
		for (int now=trie[i].c; i<up && trie[i].c==now; ++i){
			if (count % 6)
				putchar(' ');
			printf("%s", trie[i].str+1);
			if (++count %  6 == 0)
				putchar('\n');
		}
		if (count % 6)
			putchar('\n');
	}
}
#else
void output(){
	int lim = 1<<30, now;
	for (int _=0; _<n; ++_){
		now = 0;
		for (int i=(1<<a)-1; i<(1<<(b+1))-1; ++i)
			if (trie[i] > now && trie[i] < lim)
				now = trie[i];
		if (!now)
			return;
		lim = now;
		printf("%d\n", lim);
		int count(0);
		for (int i=(1<<a)-1; i<(1<<(b+1))-1; ++i)
			if (trie[i] == now){
				if (count % 6)
					printf(" ");
				print(i);
				if (++count%6 == 0)
					printf("\n");
			}
		if (count%6)
			printf("\n");
	}
}
#endif

int main(){
	freopen("contact.in", "r", stdin);
	freopen("contact.out", "w", stdout);
	scanf("%d%d%d", &a, &b, &n);
	while (scanf("%s", s+strlen(s)) != EOF);
#ifdef Try
	for (int i=down; i<up; ++i)
		trie[i].n = i;
#endif

	for (int i=0; i<=strlen(s)-a; ++i){
		int now = 0;
		for (int j=0; i+j<strlen(s) && j<b; ++j){
			now = s[i+j]=='0' ? now*2+1 : now*2+2;
#ifdef Try
			trie[now].str[j] = s[i+j]=='0' ? '0' : '1';
			++trie[now].c;
#else
			++trie[now];
#endif
		}
	}
	output();
	return 0;
}
